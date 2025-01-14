#pragma once
#include <vector>
#include "BaseDomain.hpp"
#include "Types.hpp"

using std::string;
using std::map;

class Network : public BaseDomain {
private:
	std::map<string, nlohmann::json> requests;
public:
	Network(AsyncDriver* mdriver) : BaseDomain(mdriver) {
		this->driver = mdriver;
		this->sendCommandNoWait("Network.enable", {});
		this->driver->registerCallback([this](string method, nlohmann::json msgObj) {
			if ("Network.requestWillBeSent" == method) {
				msgObj["ff"] = -1;
				requests[msgObj["requestId"]] = msgObj;
			}
			else if ("Network.loadingFinished" == method) {
				if (requests.count(msgObj["requestId"]) > 0) {
					requests[msgObj["requestId"]]["ff"] = 1;
				}
			}
			else if ("Network.loadingFailed" == method) {
				if (requests.count(msgObj["requestId"]) > 0) {
					requests[msgObj["requestId"]]["ff"] = 0;
				}
			}
			});
	}

	bool isLoadingFinished(NetworkTypes::LoaderId loaderId) {
		bool isFinished = true;
		for (auto& request : requests) {
			nlohmann::json tmp = request.second;
			if (tmp["loaderId"] == loaderId.loaderId) {
				if (tmp["ff"] == -1) {
					isFinished = false;
					break;
				}
			}
		}
		if (isFinished) { //�������ȫ���ɹ�����������󻺴�
			requests.clear();
		}
		return isFinished;
	}
};