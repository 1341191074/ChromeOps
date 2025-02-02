#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <locale.h>
#include "base/Chrome.hpp"
#include "utils/StringUtils.hpp"
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

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    curl_global_init(CURL_GLOBAL_ALL);//全局只执行\1次

    StringUtils stringUtils;
    Chrome chrome;
    chrome.pushArgs("--remote-debugging-port=9222");
    chrome.pushArgs("--user-data-dir=E:\\test\\ud0");
    chrome.launch("C:\\Users\\Reach\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe", true);
    //chrome.launch("C:\\Users\\Lenovo\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe", true);
    int ret = chrome.chromeBind("localhost", 9222);
    string jsonObj = chrome.findTargetList();
    std::map<string, nlohmann::json> jsonCache;
    JsonUtils jsonUtils;
    string uuidStr = jsonUtils.parseJson(jsonObj, &jsonCache);
    string targetId = jsonUtils.getValueFromJson(jsonCache[uuidStr][0], "targetId");
    chrome.switchTab(targetId);

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //string lastTargetId = chrome.getLastTargetId();
    //std::cout << "lid = " << lastTargetId << std::endl;

    string urls = "https://tieba.baidu.com/|https://www.baidu.com/|https://www.csdn.net/";
    std::vector<string> res;
    stringUtils.split(urls, '|', res);
    int size = res.size();
    std::cout << "size = " << size << std::endl;

    for (int i = 0; i < size; i++) {
        chrome.navigate(res.at(i), "");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        boolean finished = chrome.isLoadingFinished();//0=没有加载完成 1=加载完成
        while (!finished) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            finished = chrome.isLoadingFinished();
        }
        std::cout << "finished ," << res.at(i) << std::endl;
        string picName = "e:\\" + std::to_string(i) + "\.jpg";
        chrome.captureScreenshot("jpeg", 100, 0, 0, 0, 0, 1.0, picName);
        //chrome.captureFullScreenshot("jpeg", 100, picName);
    }
}
