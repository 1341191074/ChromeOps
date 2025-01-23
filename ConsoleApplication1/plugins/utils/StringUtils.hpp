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
		// ��ȡת������ַ���������ֽ�������������ֹ��
		int len = WideCharToMultiByte(CP_UTF8, 0, bstr, -1, NULL, 0, NULL, NULL);
		if (len == 0) {
			// ���ת��ʧ�ܣ�WideCharToMultiByte �᷵�� 0
			throw std::runtime_error("WideCharToMultiByte failed");
		}
		
		char* szUtf8 = new char[len + 1];
		// ִ��ת��
		WideCharToMultiByte(CP_UTF8, 0, bstr, -1, szUtf8, len - 1, NULL, NULL);

		std::string strUtf8(szUtf8);
		delete[] szUtf8;
		return strUtf8;
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

