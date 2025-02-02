#pragma once
// boost��curl���ܴ��ڳ�ͻ�������hpp������boost���룬�������벻ͨ��
#include <boost/process.hpp>
#include "curl/curl.h"

namespace bp = boost::process;

class ProcessUtils
{
public:
	std::wstring AnsiToUnicode(const std::string& ansiStr) {
		int len = MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, nullptr, 0);
		std::wstring unicodeStr(len, 0);
		MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, &unicodeStr[0], len);
		return unicodeStr;
	}
	bp::child startChrome(std::string chromeFullPath, std::vector<std::string> args) {
		try {
			// ��������Chrome������
			bp::child c(chromeFullPath, args);
			c.detach();
			// �ӳ�2��
			std::this_thread::sleep_for(std::chrono::seconds(2));
			// �����ӽ��̶����Ա�������Թر���
			return c;
		}
		catch (const bp::process_error& e) {
			throw std::runtime_error("Failed to start Chrome: " + std::string(e.what()));
		}
	}
	void closeChrome(bp::child& chromeProcess) {
		try {
			// �ȴ�����ֹ�ӽ��̣���Chrome�������
			chromeProcess.terminate();
			chromeProcess.wait(); // ��ѡ���ȴ�������������
		}
		catch (const bp::process_error& e) {
		}
	}

	bool isPortOpen(const std::string& ip, std::string port) {
		CURL* curl;
		CURLcode res;

		curl = curl_easy_init();
		if (curl) {
			std::string url = "http://" + ip + ":" + port;
			curl_easy_setopt(curl, CURLOPT_URL, url);

			// �������󷽷�Ϊ HEAD����Ϊ����ֻ��Ҫ��������Ƿ�ɹ�������Ҫ��ȡ��Ӧ��
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "HEAD");

			// ִ������
			res = curl_easy_perform(curl);
			// �����ͷ���Դ
			curl_easy_cleanup(curl);

			// ���������
			if (res == CURLE_OK) {
				return true;
			}


		}
		return false;
	}
};

