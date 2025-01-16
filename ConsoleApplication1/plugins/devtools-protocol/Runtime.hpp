#pragma once
#include "BaseDomain.hpp"

using std::string;
using std::map;

class Runtime : public BaseDomain
{
public:
	Runtime(AsyncDriver* mdriver) : BaseDomain(mdriver) {
		this->driver = mdriver;
		this->sendCommandAndWait("Runtime.enable", {});
		this->driver->registerCallback([this](string method, nlohmann::json msgObj) {
			if ("Runtime.executionContextCreated" == method) {

			}
			});
	}

	void releaseObject(string objectId) {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["objectId"] = objectId;
		this->sendCommandNoWait("Runtime.releaseObject", params);
	}

	void callFunctionOn(string objectId, string functionDeclaration, string arguments[]) {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["objectId"] = objectId;
		params["functionDeclaration"] = functionDeclaration;
		params["silent"] = true;
		this->sendCommandNoWait("Runtime.callFunctionOn", params);
	}

	/// <summary>
	/// 编译脚本，并返回脚本id
	/// </summary>
	/// <param name="expression"></param>
	/// <returns>scriptId</returns>
	string evaluate(string expression) {
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["expression"] = expression;
		params["objectGroup"] = string("console");
		params["includeCommandLineAPI"] = true;
		params["silent"] = false;
		params["returnByValue"] = false;
		params["generatePreview"] = true;
		params["userGesture"] = true;
		params["awaitPromise"] = false;
		params["replMode"] = true;
		params["allowUnsafeEvalBlockedByCSP"] = false;
		nlohmann::json retJson = this->sendCommandAndWait("Runtime.evaluate", params);
		if (retJson.contains("result")) {
			nlohmann::json resultObj = retJson["result"];
			if (resultObj.contains("subtype")) {
				string  subtypeStr = resultObj["subtype"];
				string subtype(subtypeStr.data(), subtypeStr.size());
				if (subtype == "error") { //出现错误直接返回空
					return "";
				}
			}
			if (resultObj.contains("description")) {
				return resultObj["description"];
			}
		}
		return "";
	}


};

