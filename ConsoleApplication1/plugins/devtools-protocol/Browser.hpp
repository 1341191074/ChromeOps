#pragma once
#include <string>
#include "BaseDomain.hpp"

class Browser : public BaseDomain
{
public:
	Browser(AsyncDriver* mdriver) : BaseDomain(mdriver) {
	}
	void close()
	{
		this->sendCommandNoWait("Browser.close", {});
	}

	std::string getVersion()
	{
		nlohmann::json retJson = this->sendCommandAndWait("Browser.close", {});
		if (retJson.contains("root")) {
			return retJson["root"];
		}
		return "unknown";
	}
};

