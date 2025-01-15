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
		if (isFinished) { //如果加载全部成功，则清空请求缓存
			requests.clear();
		}
		return isFinished;
	}

	nlohmann::json getCookies(nlohmann::json urls) {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["urls"] = urls;
		nlohmann::json retJson = this->sendCommandAndWait("Network.getCookies", params, 10000);
		if (retJson.count("cookies") > 0) {
			return retJson["cookies"];
		}
		return {};
	}

	void setCookie(string name, string value, string url = "", string domain = "", string path = "", bool secure = false, bool httpOnly = false, string sameSite = "", int expires = -1) {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["name"] = name;
		params["value"] = value;
		if ("" != url) {
			params["url"] = url;
		}
		if ("" != domain) {
			params["domain"] = domain;
		}
		if ("" != path) {
			params["path"] = path;
		}
		if (secure) {
			params["secure"] = secure;
		}
		if (httpOnly) {
			params["httpOnly"] = httpOnly;
		}
		if ("" != sameSite) {
			params["sameSite"] = sameSite;
		}
		if (expires > -1) {
			params["expires"] = expires;
		}
		this->sendCommandNoWait("Network.setCookie", params);
	}

	void setCookies(string jsonCookies) {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["cookies"] = jsonCookies;
		this->sendCommandNoWait("Network.setCookies", params);
	}

	void clearBrowserCache() {
		this->sendCommandNoWait("Network.clearBrowserCache", {});
	}

	void clearBrowserCookies() {
		this->sendCommandNoWait("Network.clearBrowserCookies", {});
	}

	void setCacheDisabled(bool cacheDisabled = false) {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["cacheDisabled"] = cacheDisabled;
		this->sendCommandNoWait("Network.setCacheDisabled", params);
	}
};