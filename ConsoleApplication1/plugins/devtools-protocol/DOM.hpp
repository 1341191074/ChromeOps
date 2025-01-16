#pragma once
#include "BaseDomain.hpp"

using std::string;
using std::map;
class DOM : public BaseDomain
{
private:
	int rootId = 1;
public:
	DOM(AsyncDriver* mdriver) : BaseDomain(mdriver) {
		this->driver = mdriver;
		this->sendCommandNoWait("DOM.enable", {});
		nlohmann::json root = this->getDocument(0);
		this->rootId = root["nodeId"];
	}

	int querySelector(string selector)
	{
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["nodeId"] = this->rootId;
		params["selector"] = selector;
		nlohmann::json retJson = this->sendCommandAndWait("DOM.querySelector", params);
		if (retJson.contains("nodeId")) {
			return retJson["nodeId"];
		}
		return -1;
	}

	nlohmann::json getDocument(int depth)
	{
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["depth"] = depth;
		params["pierce"] = false;
		nlohmann::json retJson = this->sendCommandAndWait("DOM.getDocument", params);
		if (retJson.contains("root")) {
			return retJson["root"];
		}
		return {};
	}

	string getOuterHTML(string selector)
	{
		int nodeId = this->querySelector(selector);
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["nodeId"] = nodeId;
		nlohmann::json retJson = this->sendCommandAndWait("DOM.getOuterHTML", params);
		if (retJson.contains("outerHTML")) {
			return retJson["outerHTML"];
		}
		return "";
	}

	void focus(string selector)
	{
		int nodeId = this->querySelector(selector);
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["nodeId"] = nodeId;
		this->sendCommandNoWait("DOM.focus", params);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="selector"></param>
	/// <returns>objectId</returns>
	string resolveNode(string selector) {
		int nodeId = this->querySelector(selector);
		map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
		params["nodeId"] = nodeId;
		nlohmann::json retJson = this->sendCommandAndWait("DOM.resolveNode", params);
		if (retJson.contains("object")) {
			if (retJson["object"].contains("objectId")) {
				return retJson["object"]["objectId"];
			}
		}
		return "";
	}
};

