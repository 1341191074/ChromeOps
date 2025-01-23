#pragma once
#include <windows.h>
#include <comdef.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

using std::string;

class StringUtils
{
public:
	void split(string str, const char split, std::vector<string>& res)
	{
		res.clear();
		std::istringstream iss(str);	// 输入流
		string token;			// 接收缓冲区
		while (std::getline(iss, token, split))	// 以split为分隔符
		{
			if (!token.empty()) {
				res.push_back(token);
			}
		}
	}

	std::string GBKToUTF8(const std::string& strGBK) {
		int len = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
		wchar_t* wszUtf8 = new wchar_t[len];
		memset(wszUtf8, 0, len * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, wszUtf8, len);

		len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
		char* szUtf8 = new char[len + 1];
		memset(szUtf8, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);

		std::string strUtf8(szUtf8);
		delete[] szUtf8;
		delete[] wszUtf8;
		return strUtf8;
	}

	std::string BSTRToString(BSTR bstr) {
		// 获取转换后的字符串所需的字节数，包括空终止符
		int len = WideCharToMultiByte(CP_UTF8, 0, bstr, -1, NULL, 0, NULL, NULL);
		if (len == 0) {
			// 如果转换失败，WideCharToMultiByte 会返回 0
			throw std::runtime_error("WideCharToMultiByte failed");
		}
		
		char* szUtf8 = new char[len + 1];
		// 执行转换
		WideCharToMultiByte(CP_UTF8, 0, bstr, -1, szUtf8, len - 1, NULL, NULL);

		std::string strUtf8(szUtf8);
		delete[] szUtf8;
		return strUtf8;
	}

	BSTR stringToBSTR(std::string str) {
		// 将std::string转换为wchar_t*（宽字符字符串）
   // 注意：这里使用了MultiByteToWideChar函数进行转换，需要包含<windows.h>
		int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		wchar_t* wstr = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, len);

		// 使用SysAllocString（或AtlAllocBSTR，如果使用ATL）将wchar_t*转换为BSTR
		BSTR bstr = SysAllocString(wstr);

		// 检查转换是否成功
		if (bstr == nullptr) {
			delete[] wstr; // 不要忘记释放wchar_t*内存
			return NULL;
		}

		// 释放BSTR内存
		//SysFreeString(bstr);

		// 释放wchar_t*内存
		delete[] wstr;
		return bstr;
	}

	std::vector<unsigned char> base64_decode(const std::string& input) {
		// 计算解码后的数据长度
		size_t decoded_length = input.size() / 4 * 3;
		if (input[input.size() - 1] == '=') decoded_length--;
		if (input[input.size() - 2] == '=') decoded_length--;

		// 创建输出缓冲区
		std::vector<unsigned char> decoded_data(decoded_length);

		// 解码Base64字符串
		int result = EVP_DecodeBlock(decoded_data.data(),
			reinterpret_cast<const unsigned char*>(input.c_str()),
			input.size());

		// 检查解码是否成功
		if (result == -1) {
			throw std::runtime_error("Base64 decoding failed");
		}

		// 返回解码后的数据
		return decoded_data;
	}

	void write_to_jpg_file(const std::vector<unsigned char>& data, const std::string& filename) {
		// 打开输出文件流
		std::ofstream outFile(filename, std::ios::binary);

		// 检查文件是否成功打开
		if (!outFile.is_open()) {
			throw std::runtime_error("Failed to open output file");
		}

		// 将数据写入文件
		outFile.write(reinterpret_cast<const char*>(data.data()), data.size());

		// 关闭文件流
		outFile.close();
	}

};

