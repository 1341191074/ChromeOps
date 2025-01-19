#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include "base/Chrome.hpp"
#include "utils/StringUtils.h"
#include "nlohmann/json.hpp" 
#include "utils/JsonUtils.hpp"

using std::string;
using std::variant;
using std::istringstream;

// 初始化全局变量
std::map<int, nlohmann::json> GlobalData::result = std::map<int, nlohmann::json>();

static void mylog(variant<int, string> var) {
    if (std::holds_alternative<int>(var)) {
        std::cout << std::to_string(std::get<int>(var)) << std::endl;
    }
    else {
        std::cout << std::get<string>(var) << std::endl;
    }
}

int main1()
{
    //SetConsoleOutputCP(CP_UTF8);

    curl_global_init(CURL_GLOBAL_ALL);//全局只执行\1次

    StringUtils stringUtils;
    Chrome chrome;
    chrome.pushArgs("--remote-debugging-port=9222");
    chrome.pushArgs("--user-data-dir=E:\\test\\ud0");
    chrome.launch("C:\\Users\\Reach\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe", true);
    int ret = chrome.chromeBind("localhost", 9222);
    string html = chrome.findTargetList();
    std::vector<std::string> tokens;
    stringUtils.split(html, '====', tokens);
    string tab = tokens.at(0);
    stringUtils.split(tab, '|||', tokens);
    mylog(tab); // 输出log
    tab = tokens.at(0);
    chrome.switchTab(tab);

    chrome.navigate("https://www.baidu.com", "");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    boolean finished = chrome.isLoadingFinished();//0=没有加载完成 1=加载完成
    while (!finished) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        finished = chrome.isLoadingFinished();
    }
    std::cout << "加载完成" << std::endl;

    //nlohmann::json obj = nlohmann::json::parse("[\"https://www.baidu.com\"]");
    //string cookies = chrome.getCookies(obj);
    //std::cout << cookies << std::endl;

    //chrome.captureScreenshot("png", 100, 0, 0, 800, 600, 1.0, "e:\\output1.png");
    chrome.captureFullScreenshot("png", 100, "e:\\output2.png");

    //string desc = chrome.runScript("var i;i=1;");
    //std::cout << desc << std::endl;

    //chrome.runScript("function mylog(){console.log(\"test\");}mylog();");

    //string selector = "#kw";
    //string text = "c++加载完成";
    //text = stringUtils.GBKToUTF8(text);
    //chrome.inputText(selector,text);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

}

int main() {

    // 示例JSON字符串，包含数组
    CString jsonString = R"({
        "obj": {
            "domain": {
                "x1": "value1",
                "x2": "value2",
                "list": [
                    {"item1": "valueA"},
                    {"item1": "valueB"}
                ]
            }
        }
    })";
    std::map<string, nlohmann::json> jsonCache;
    JsonUtils jsonUtil;
    jsonUtil.parseJson(jsonString, &jsonCache);


    //// 解析JSON字符串
    //nlohmann::json j = nlohmann::json::parse(jsonString);

    //// 要获取的键路径，包含数组索引
    ////string keyPath = "obj.domain.list[2].item1";
    //string keyPath = "obj.x1";



    //// 获取值
    //nlohmann::json value = jsonUtil.getValueFromJson(j, keyPath);

    //// 输出值
    //if (value.is_string()) {
    //	std::cout << "The value of " << keyPath << " is: " << value.get<string>() << std::endl;
    //}
    //else {
    //	if (value.is_null()) {
    //		std::cout << "The value of " << keyPath << " is NULL ." << value << std::endl;
    //	}
    //	else {
    //		std::cout << "The value of " << keyPath << " is not a string." << value << std::endl;
    //	}

    //}

    return 0;
}