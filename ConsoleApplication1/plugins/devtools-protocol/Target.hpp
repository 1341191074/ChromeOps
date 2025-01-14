#pragma once
#include "BaseDomain.hpp"

using std::string;
using std::map;

using OnMessageListener = std::function<void(string, nlohmann::json)>;

class Target : public BaseDomain
{
public:
    Target(AsyncDriver* mdriver) : BaseDomain(mdriver) {
        std::map<std::string, std::variant<int, std::string, bool, float, nlohmann::json>> params;
        params["discover"] = true;
        this->sendCommandNoWait("Target.setDiscoverTargets", params);
    }

    void activateTarget(string targetId)
    {
        map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
        params["targetId"] = targetId;
        this->sendCommandNoWait("DOM.activateTarget", params);
    }

    void attachToTarget(string targetId)
    {
        map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
        params["targetId"] = targetId;
        this->sendCommandNoWait("DOM.attachToTarget", params);
    }

    void closeTarget(string targetId)
    {
        map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
        params["targetId"] = targetId;
        this->sendCommandNoWait("DOM.closeTarget", params);
    }

    string createTarget(string url)
    {
        map<string, std::variant<int, string, bool, float, nlohmann::json>> params;
        params["url"] = url;
        nlohmann::json retJson = this->sendCommandAndWait("DOM.createTarget", params);
        string ret = retJson["targetId"];
        return ret;
    }

    string getTargets()
    {
        nlohmann::json retJson = this->sendCommandAndWait("Target.getTargets", {});
        string ret = retJson["targetInfos"];
        return ret;
    }

    string getBrowserContexts()
    {
        nlohmann::json retJson = this->sendCommandAndWait("Target.getBrowserContexts", {});
        string ret = retJson["browserContextIds"];
        return ret;
    }
};

