#pragma once
#include <iostream>
#include <string>
#include <functional>
#include "nlohmann/json.hpp"
#include "utils/GlobalData.hpp"

using std::string;

class AsyncDriver {
private:
	std::function<void(bool success)> m_on_connect_complete;
	std::vector<std::function<void(string, nlohmann::json)>> callbacks;
public:
	string msg;
public:
	AsyncDriver() {
	}

	~AsyncDriver() {
		
	}

	void registerCallback(std::function<void(string, nlohmann::json)> cb) {
		callbacks.push_back(cb);
	}

	// public
	void connect(const std::string& uri, std::function<void(bool success)> on_connect_complete) {
		
	}

	void send_message(const std::string& message) {
		
	}

	void stop() {
	}
};

