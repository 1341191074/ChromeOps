#pragma once
#include <variant>
#include <map>
#include <sstream>
#include "nlohmann/json.hpp"
#include "base/AsyncDriver.hpp"
#include "utils/GlobalData.hpp"

using std::string;

class BaseDomain
{
private:
	/// <summary>
	/// 组装协议数据
	/// </summary>
	/// <param name="method"></param>
	/// <param name="params"></param>
	/// <param name="retCmdId"></param>
	/// <returns></returns>
	std::string getSendData(std::string method, int* retCmdId, std::map<std::string, std::variant<int, std::string, bool, float, nlohmann::json>> params = std::map<std::string, std::variant<int, std::string, bool, float, nlohmann::json>>()) {
		nlohmann::json obj;
		*retCmdId = GlobalData::cmdIdx; // 将本次的 cmdIdx 返回给上层
		obj["id"] = GlobalData::cmdIdx;
		obj["method"] = method;

		if (!params.empty()) {
			nlohmann::json jsonParams;
			for (const auto& param : params) {
				if (std::holds_alternative<int>(param.second)) {
					jsonParams[param.first] = std::get<int>(param.second);
				}
				else if (std::holds_alternative<std::string>(param.second)) {
					jsonParams[param.first] = std::get<std::string>(param.second);
				}
				else if (std::holds_alternative<bool>(param.second)) {
					jsonParams[param.first] = std::get<bool>(param.second);
				}
				else if (std::holds_alternative<float>(param.second)) {
					jsonParams[param.first] = std::get<float>(param.second);
				}
				else if (std::holds_alternative<nlohmann::json>(param.second)) {
					jsonParams[param.first] = std::get<nlohmann::json>(param.second);
				}
			}
			obj["params"] = jsonParams;
		}

		GlobalData::cmdIdx++; // 增加命令 ID
		// 序列化 JSON 对象为字符串
		return obj.dump();
	}

	void sendMessageNoWait(string cmd, int cmdIdx) {
		this->driver->send_message(cmd);
	}

	nlohmann::json sendMessage(string cmd, int cmdIdx, int timeout = 2000) {
		this->driver->send_message(cmd);

		auto start = std::chrono::system_clock::now();
		auto end = start + std::chrono::milliseconds(timeout);
		nlohmann::json ret = this->getResult(cmdIdx);
		while (ret == NULL) {//初始状态下，等待绑定成功或者失败
			auto now = std::chrono::system_clock::now();
			if (now >= end) {
				// 超时了，返回空字符串或特定的错误消息
				return ret;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			ret = this->getResult(cmdIdx);
		}
		return ret;
	}
protected:
	AsyncDriver* driver;
protected:
	// 私有成员函数，用于发送命令并等待响应
	nlohmann::json sendCommandAndWait(const std::string& method, const std::map<std::string, std::variant<int, std::string, bool, float, nlohmann::json>>& params, int timeout = 2000) {
		int cmdIdx = -1;
		std::string cmd = this->getSendData(method, &cmdIdx, params);
		return this->sendMessage(cmd, cmdIdx, timeout);
	}

	// 私有成员函数，用于发送命令但不等待响应
	void sendCommandNoWait(const std::string& method, const std::map<std::string, std::variant<int, std::string, bool, float, nlohmann::json>>& params) {
		int cmdIdx = -1;
		std::string cmd = this->getSendData(method, &cmdIdx, params);
		this->sendMessageNoWait(cmd, cmdIdx);
	}

public:
	BaseDomain() {
	}
	BaseDomain(AsyncDriver* mdriver) {
		this->driver = mdriver;
	}

	~BaseDomain() {
	}

	nlohmann::json getResult(int key) {
		if (GlobalData::getResult().count(key) > 0) {
			nlohmann::json ret = GlobalData::getResult()[key];
			GlobalData::getResult().erase(key);
			return  ret;
		}
		return  NULL;
	}
};


