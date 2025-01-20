#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <mutex>
#include "nlohmann/json.hpp"
#include "utils/GlobalData.hpp"

using std::string;

class AsyncDriver {
private:
	CURL* curl;
	std::thread m_thread;
	std::mutex m_mutex;
	bool runing = false;

	std::function<void(bool success)> m_on_connect_complete;
	std::vector<std::function<void(string, nlohmann::json)>> callbacks;
public:
	string msg;
public:
	AsyncDriver() {
		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 2L); /* websocket style */
	}

	~AsyncDriver() {
		curl_easy_cleanup(curl);
	}

	void registerCallback(std::function<void(string, nlohmann::json)> cb) {
		callbacks.push_back(cb);
	}

	void wsRecv() {
		this->runing = true;
		while (runing) {
			size_t rlen;
			const struct curl_ws_frame* meta;
			char buffer[2048]; //每次接收1k的数据。

			CURLcode result = curl_ws_recv(curl, buffer, sizeof(buffer), &rlen, &meta);
			if (result == CURLE_OK) {
				std::vector<char> vec;
				try {
					size_t total_size = 0;

					total_size = rlen;
					if (meta->bytesleft > 0) {
						total_size = rlen + meta->bytesleft;
					}

					vec.resize(total_size);

					// 首次初始化
					for (int i = 0; i < rlen; i++) {
						vec[i] = buffer[i];
					}

					while (meta->bytesleft > 0) {//循环获取
						result = curl_ws_recv(curl, buffer, sizeof(buffer), &rlen, &meta);
						for (int i = 0, j = meta->offset; i < rlen; i++, j++) {
							vec[j] = buffer[i];
						}
					}


					string str(vec.data(), vec.size());
					//std::cout << "str=" << str << std::endl;
					nlohmann::json obj = nlohmann::json::parse(str);
					if (obj.contains("method")) { // Events
						for (const auto& callback : callbacks) {
							string method = obj["method"];
							callback(method, obj);
						}
					}
					else if (obj.contains("result") && obj.at("result").is_object()) {
						GlobalData::getResult()[obj["id"]] = obj["result"];
					}
					else {
						// nothing
					}
				}
				catch (std::exception& ex) {
					//string str(vec.data(), vec.size());
				}

			}
		}
	}

	// public
	void connect(const std::string& uri, std::function<void(bool success)> on_connect_complete) {
		if (!this->runing) { //未连接
			curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());

			CURLcode res = curl_easy_perform(curl);
			if (res == CURLE_OK) {
				on_connect_complete(true); // call callback

				//连接成功后，启动消息接收线程
				if (!m_thread.joinable()) {
					m_thread = std::thread(&AsyncDriver::wsRecv, this);
				}
			}
		}
	}

	void send_message(const std::string& message) {
		std::lock_guard<std::mutex> lock(m_mutex);
		size_t sent;
		CURLcode result = curl_ws_send(curl, message.c_str(), strlen(message.c_str()), &sent, 0, CURLWS_TEXT);
	}

	void stop() {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (this->runing) {
			//停止标志
			this->runing = false;
			//等待线程结束
			m_thread.join();

			//断开连接
			size_t sent;
			(void)curl_ws_send(curl, "", 0, &sent, 0, CURLWS_CLOSE);
		}
	}
};

