#pragma once
// boost和curl可能存在冲突，如果改hpp不加入boost引入，则程序编译不通过
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
			// 构造启动Chrome的命令
			bp::child c(chromeFullPath, args);
			c.detach();
			// 延迟2秒
			std::this_thread::sleep_for(std::chrono::seconds(2));
			// 返回子进程对象，以便后续可以关闭它
			return c;
		}
		catch (const bp::process_error& e) {
			throw std::runtime_error("Failed to start Chrome: " + std::string(e.what()));
		}
	}
	void closeChrome(bp::child& chromeProcess) {
		try {
			// 等待并终止子进程（即Chrome浏览器）
			chromeProcess.terminate();
			chromeProcess.wait(); // 可选：等待进程真正结束
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

			// 设置请求方法为 HEAD，因为我们只需要检查连接是否成功，不需要获取响应体
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "HEAD");

			// 执行请求
			res = curl_easy_perform(curl);
			// 清理并释放资源
			curl_easy_cleanup(curl);

			// 检查请求结果
			if (res == CURLE_OK) {
				return true;
			}


		}
		return false;
	}
};

