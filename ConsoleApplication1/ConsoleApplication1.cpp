#include <string>
#include <vector>
#include <iostream>
#include <thread>
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
	//chrome.launch("C:\\Users\\Reach\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe", true);
	//chrome.launch("C:\\Users\\Lenovo\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe", true);
	int ret = chrome.chromeBind("localhost", 9222);
	string jsonObj = chrome.findTargetList();
	std::cout << jsonObj << std::endl;
	std::map<string, nlohmann::json> jsonCache;
	JsonUtils jsonUtils;
	string uuidStr = jsonUtils.parseJson(jsonObj, &jsonCache);
	string targetId = jsonUtils.getValueFromJson(jsonCache[uuidStr][0], "targetId");
	std::cout << "targetId = " << targetId << std::endl;

	string lid = chrome.getLastTargetId();
	std::cout << "lid = " << lid << std::endl;

	//std::vector<std::string> tokens;
	//stringUtils.split(html, '====', tokens);
	//string tab = tokens.at(0);
	//stringUtils.split(tab, '|||', tokens);
	//mylog(tab); // 输出log
	//tab = tokens.at(0);
	//chrome.switchTab(tab);

	//chrome.navigate("https://www.baidu.com", "");
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//boolean finished = chrome.isLoadingFinished();//0=没有加载完成 1=加载完成
	//while (!finished) {
	//	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	//	finished = chrome.isLoadingFinished();
	//}
	//std::cout << "加载完成" << std::endl;

	//nlohmann::json obj = nlohmann::json::parse("[\"https://www.baidu.com\"]");
	//string cookies = chrome.getCookies(obj);
	//std::cout << cookies << std::endl;

	//chrome.captureScreenshot("png", 100, 0, 0, 800, 600, 1.0, "e:\\output1.png");
	//chrome.captureFullScreenshot("png", 100, "e:\\output2.png");

	//string desc = chrome.runScript("var i;i=1;");
	//std::cout << desc << std::endl;

	//chrome.runScript("function mylog(){console.log(\"test\");}mylog();");

	//string selector = "#kw";
	//string text = "c++加载完成";
	//text = stringUtils.GBKToUTF8(text);
	//chrome.inputText(selector,text);

	//while (true) {
	//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//}
}
