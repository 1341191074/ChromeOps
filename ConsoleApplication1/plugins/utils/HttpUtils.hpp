#pragma once
#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include "curl/curl.h"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
class HttpUtils
{
public:
    std::string get(std::string host, std::string port, std::string target) {
		CURL* curl;
		CURLcode res;
		// 初始化libcurl
		curl = curl_easy_init();
		std::string htmlContent;
		std::string url = "http://" + host + ":" + port + target;
		// 设置URL
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// 设置回调函数，用于接收数据
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

		// 设置回调函数的用户数据，即存储HTML内容的字符串
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent);

		// 发送请求
		res = curl_easy_perform(curl);

		//// 检查请求是否成功
		//if (res != CURLE_OK) {
		//	std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
		//}
		//else {
		//	// 打印HTML内容
		//	std::cout << "HTML content:\n" << htmlContent << std::endl;
		//}

		// 清理libcurl
		curl_easy_cleanup(curl);
		return htmlContent;

    }
};

