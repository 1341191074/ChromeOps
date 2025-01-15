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
	/// ��װЭ������
	/// </summary>
	/// <param name="method"></param>
	/// <param name="params"></param>
	/// <param name="retCmdId"></param>
	/// <returns></returns>
	std::string getSendData(std::string method, int* retCmdId, std::map<std::string, std::variant<int, std::string, bool, float, nlohmann::json>> params = std::map<std::string, std::variant<int, std::string, bool, float, nlohmann::json>>()) {
		nlohmann::json obj;
		*retCmdId = GlobalData::cmdIdx; // �����ε� cmdIdx ���ظ��ϲ�
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

		GlobalData::cmdIdx++; // �������� ID
		// ���л� JSON ����Ϊ�ַ���
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
		while (ret == NULL) {//��ʼ״̬�£��ȴ��󶨳ɹ�����ʧ��
			auto now = std::chrono::system_clock::now();
			if (now >= end) {
				// ��ʱ�ˣ����ؿ��ַ������ض��Ĵ�����Ϣ
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
	// ˽�г�Ա���������ڷ�������ȴ���Ӧ
	nlohmann::json sendCommandAndWait(const std::string& method, const std::map<std::string, std::variant<int, std::string, bool, float, nlohmann::json>>& params, int timeout = 2000) {
		int cmdIdx = -1;
		std::string cmd = this->getSendData(method, &cmdIdx, params);
		return this->sendMessage(cmd, cmdIdx, timeout);
	}

	// ˽�г�Ա���������ڷ���������ȴ���Ӧ
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


