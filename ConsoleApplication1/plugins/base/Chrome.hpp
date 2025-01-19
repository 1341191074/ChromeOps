#pragma once
#include "nlohmann/json.hpp"
#include "utils/ProcessUtils.hpp"
#include "utils/HttpUtils.hpp"
#include "utils/StringUtils.h"
#include "devtools-protocol/Browser.hpp"
#include "devtools-protocol/Target.hpp"
#include "devtools-protocol/DOM.hpp"
#include "devtools-protocol/Runtime.hpp"
#include "devtools-protocol/Page.hpp"
#include "devtools-protocol/Input.hpp"
#include "devtools-protocol/Network.hpp"


class Chrome
{
private:
    AsyncDriver* targetDriver;//管理端driver， 对标target
    AsyncDriver* pageDriver;//管理端driver， 对标target
    ProcessUtils processUtils;
    HttpUtils httpUtils;
    StringUtils stringUtils;

    std::string chromeFullPath;
    std::string host;
    int port;
    std::vector<std::string> args;
    bp::child chrome_process;
    int isBind; // -1=初始状态, 0=失败, 1=成功
    int isPageBind; // -1=初始状态, 0=失败, 1=成功
    std::string lastTab;
    std::map<std::string, std::string> targetsCache;

public:
    Browser* browser;
    Target* target;
    DOM* dom;
    Runtime* runtime;
    Page* page;
    Input* input;
    Network* network;
public:
#pragma region 基础方法块
    Chrome() {
        this->isBind = -1;
        this->isPageBind = -1;
        this->host = "localhost";
        this->port = 9222;

        this->targetDriver = new AsyncDriver();
        this->pageDriver = new AsyncDriver();
    }

    ~Chrome() {
        this->stop();

        delete target;
        delete dom;
        delete runtime;
        delete page;
        delete input;
        delete network;

        delete targetDriver;
        delete pageDriver;
    }

    void pushArgs(std::string arg)
    {
        this->args.push_back(arg);
    }

    void launch(std::string chromeFullPath, int tryBind)
    {
        // tryBind时，判断是否可直接绑定
        if (tryBind) {
            bool b = this->processUtils.isPortOpen(this->host, std::to_string(this->port));

            if (!b) {
                this->chromeFullPath = chromeFullPath;
                this->chrome_process = this->processUtils.startChrome(this->chromeFullPath, this->args);
                //启动浏览器后尝试连接
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            this->chromeBind(this->host, this->port);
        }
    }

    int chromeBind(std::string host, int port)
    {
        this->host = host;
        this->port = port;
        std::string res = this->httpUtils.get(this->host, std::to_string(this->port), "/json/version");
        nlohmann::json obj = nlohmann::json::parse(res);
        string url = obj["webSocketDebuggerUrl"];

        this->targetDriver->connect(url, [this](bool success) {
            if (success) {
                this->isBind = 1;
            }
            else {
                this->isBind = 0;
            }
            });

        while (this->isBind == -1) {//初始状态下，等待绑定成功或者失败
            std::this_thread::sleep_for(std::chrono::milliseconds(2)); // Simulate running for a while
        }
        this->target = new Target(this->targetDriver);
        this->browser = new Browser(this->targetDriver);
        return this->isBind;
    }

    std::string findTargetList()
    {
        std::string res = this->httpUtils.get(this->host, std::to_string(this->port), "/json");
        nlohmann::json parsed_json = nlohmann::json::parse(res);
        // 遍历JSON数组
        std::stringstream ret;
        for (const auto& item : parsed_json) {
            // 访问数组中的对象并获取字段值
            string n = item["type"];
            if ("page" == n) {
                string tabId = item["id"];
                string title = item["title"];
                string webSocketDebuggerUrl = item["webSocketDebuggerUrl"];
                this->targetsCache[tabId] = webSocketDebuggerUrl;

                ret << tabId;
                ret << "|||";
                ret << title;
                ret << "======";
            }
        }
        return ret.str();
    }

    int switchTab(std::string tabId)
    {
        if (this->isBind == 1) {
            this->isPageBind = -1;
            std::string url = this->targetsCache[tabId];

            this->pageDriver->connect(url, [this](bool success) {
                if (success) {
                    this->isPageBind = 1;
                }
                else {
                    this->isPageBind = 0;
                }
                });

            while (this->isPageBind == -1) {//初始状态下，等待绑定成功或者失败
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate running for a while
            }
            this->lastTab = tabId;

            this->dom = new DOM(this->pageDriver);
            this->runtime = new Runtime(this->pageDriver);
            this->page = new Page(this->pageDriver);
            this->input = new Input(this->pageDriver);
            this->network = new Network(this->pageDriver);
        }
        return 1;
    }

    void stop()
    {
        this->pageDriver->stop();
        this->targetDriver->stop();
    }
#pragma endregion

#pragma region 协议块

    void navigate(string url, string referrer) {
        this->page->navigate(url, referrer);
    }

    bool isLoadingFinished() {
        return this->network->isLoadingFinished(this->page->loaderId);
    }

    string getOuterHTML(string selector) {
        return this->dom->getOuterHTML(selector);
    }

    string runScript(string expression) {
        string res = this->runtime->evaluate(expression);
        return res;
    }

    void captureFullScreenshot(string format, int quality, string imgFullPath) {
        string base64_str = this->page->captureFullScreenshot(format, quality);
        try {
            if (base64_str != "") {
                // 解码Base64字符串
                std::vector<unsigned char> decoded_data = stringUtils.base64_decode(base64_str);
                // 将解码后的数据写入JPG文件
                stringUtils.write_to_jpg_file(decoded_data, imgFullPath);
            }
        }
        catch (const std::exception& e) {
        }
    }

    void captureScreenshot(string format, int quality, int x, int y, int width, int height, float scale, string imgFullPath) {
        PageTypes::Clip clip(x, y, width, height, scale);
        string base64_str = this->page->captureScreenshot(format, quality, &clip);
        try {
            if (base64_str != "") {
                // 解码Base64字符串
                std::vector<unsigned char> decoded_data = stringUtils.base64_decode(base64_str);
                // 将解码后的数据写入JPG文件
                stringUtils.write_to_jpg_file(decoded_data, imgFullPath);
            }
        }
        catch (const std::exception& e) {
        }
    }

    void inputText(string selector, string txt) {
        string objectId = this->dom->resolveNode(selector);
        this->runtime->callFunctionOn(objectId, "function(){this.focus();}", NULL);
        //this->input->insertText(txt);
        this->runtime->callFunctionOn(objectId, "function(){this.value='" + txt + "';var inputEvent = new Event('input');this.dispatchEvent(inputEvent);}", NULL);
        this->runtime->releaseObject(objectId);
        //this->page->bringToFront();
    }

    string getCookies(nlohmann::json urls) {
        nlohmann::json ret = this->network->getCookies(urls);
        return ret.dump();
    }

    void setCookie(string name, string value, string url = "", string domain = "", string path = "", bool secure = false, bool httpOnly = false, string sameSite = "", int expires = -1) {
        this->network->setCookie(name, value, url, domain, path, secure, httpOnly, sameSite, expires);
    }

    void setCookies(string jsonCookies) {
        this->network->setCookies(jsonCookies);
    }

    void clearBrowserCache() {
        this->network->clearBrowserCache();
    }

    void clearBrowserCookies() {
        this->network->clearBrowserCookies();
    }

    void setCacheDisabled(bool cacheDisabled = false) {
        this->network->setCacheDisabled(cacheDisabled);
    }
#pragma endregion

};

