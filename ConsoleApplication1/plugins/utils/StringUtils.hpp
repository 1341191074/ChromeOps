#pragma once
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
		std::istringstream iss(str);	// ������
		string token;			// ���ջ�����
		while (std::getline(iss, token, split))	// ��splitΪ�ָ���
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
		// ���BSTR�Ƿ�Ϊ��
		if (bstr == nullptr) {
			throw std::invalid_argument("BSTR is null");
		}
		
		// ��ȡBSTR�ĳ��ȣ����ֽ�Ϊ��λ������ת��Ϊ�ַ��������ǵ�Unicode��
		size_t length = SysStringLen(bstr);
		if (length == 0) {
			return "";
		}

		// ����һ��std::string���󣬲�Ϊ������㹻�Ŀռ����洢ת������ַ���
		std::string result(length, ' ');

		// ʹ��WideCharToMultiByte������BSTRת��Ϊ���ֽ��ַ�����ANSI��
		// ��������Ǽ���Ŀ�������UTF-8��Ȼ��������std::string��C++�в�ֱ��֧��UTF-8��
		// ���ǿ�����Ҫ��һ��������ȷ����ȷ�ı��롣Ϊ�˼�ʾ��������ʹ��ϵͳĬ�ϵĶ��ֽڱ��롣
		// �����ҪUTF-8���룬�����CP_UTF8��ΪCodePage����������Ӧ�ص���result�����ͻ���ʽ��
		int bytesCopied = WideCharToMultiByte(
			CP_UTF8,            // Code page to use for translation
			0,                 // Performance and mapping flags
			bstr,              // Pointer to the Unicode string
			length,            // Number of characters in the string
			&result[0],        // Pointer to the buffer for the new string
			static_cast<int>(result.size()), // Size of the buffer, in bytes
			nullptr,           // Pointer to character not used in translation
			nullptr            // Pointer to flag set when default chars are used
		);
		// ���ת���Ƿ�ɹ�
		if (bytesCopied == 0) {
			// ת��ʧ�ܣ��׳��쳣
			throw std::runtime_error("Failed to convert BSTR to std::string");
		}

		// ����std::string�Ĵ�С��ƥ��ʵ��ת�����ֽ��������ܲ����������ַ�������Ϊ���ֽڱ��룩
		// ע�⣺�������Ǽ���WideCharToMultiByteû�нض��ַ�������ת������ֽ���ǡ�����ַ��������ַ���С��
		// ���ڴ����������ǳ����ģ�����һ��������ˣ��ر��ǵ�ʹ�ö��ֽڱ���ʱ��
		// Ϊ�˸���ȫ�Ĵ������ǿ�����Ҫ�����ӵ��߼���������ܵĽضϺͲ���ȫ���ַ���
		// Ȼ����Ϊ�˼�ʾ�������������������ּ��衣
		result.resize(bytesCopied);
		return result;
	}

	BSTR stringToBSTR(std::string str) {
		// ��std::stringת��Ϊwchar_t*�����ַ��ַ�����
   // ע�⣺����ʹ����MultiByteToWideChar��������ת������Ҫ����<windows.h>
		int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		wchar_t* wstr = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, len);

		// ʹ��SysAllocString����AtlAllocBSTR�����ʹ��ATL����wchar_t*ת��ΪBSTR
		BSTR bstr = SysAllocString(wstr);

		// ���ת���Ƿ�ɹ�
		if (bstr == nullptr) {
			delete[] wstr; // ��Ҫ�����ͷ�wchar_t*�ڴ�
			return NULL;
		}

		// �ͷ�BSTR�ڴ�
		//SysFreeString(bstr);

		// �ͷ�wchar_t*�ڴ�
		delete[] wstr;
		return bstr;
	}

	std::vector<unsigned char> base64_decode(const std::string& input) {
		// ������������ݳ���
		size_t decoded_length = input.size() / 4 * 3;
		if (input[input.size() - 1] == '=') decoded_length--;
		if (input[input.size() - 2] == '=') decoded_length--;

		// �������������
		std::vector<unsigned char> decoded_data(decoded_length);

		// ����Base64�ַ���
		int result = EVP_DecodeBlock(decoded_data.data(),
			reinterpret_cast<const unsigned char*>(input.c_str()),
			input.size());

		// �������Ƿ�ɹ�
		if (result == -1) {
			throw std::runtime_error("Base64 decoding failed");
		}

		// ���ؽ���������
		return decoded_data;
	}

	void write_to_jpg_file(const std::vector<unsigned char>& data, const std::string& filename) {
		// ������ļ���
		std::ofstream outFile(filename, std::ios::binary);

		// ����ļ��Ƿ�ɹ���
		if (!outFile.is_open()) {
			throw std::runtime_error("Failed to open output file");
		}

		// ������д���ļ�
		outFile.write(reinterpret_cast<const char*>(data.data()), data.size());

		// �ر��ļ���
		outFile.close();
	}

};

