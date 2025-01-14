#include <string>
#include <vector>
#include "base/Chrome.hpp"
#include "utils/StringUtils.h"

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
	//SetConsoleOutputCP(CP_UTF8);

	StringUtils stringUtils;
	Chrome chrome;
	chrome.pushArgs("--remote-debugging-port=9222");
	chrome.pushArgs("--user-data-dir=E:\\test\\ud0");
	//chrome.launch("C:\\Users\\Lenovo\\AppData\\Local\\Google\\Chrome\\Application\\chrome.exe", false);
	int ret = chrome.chromeBind("localhost", 9222);
	string html = chrome.findTargetList();
	std::vector<std::string> tokens;
	stringUtils.split(html, '====', tokens);
	string tab = tokens.at(0);
	stringUtils.split(tab, '|||', tokens);
	mylog(tab); // 输出log
	tab = tokens.at(0);
	chrome.switchTab(tab);

	//chrome.runScript("function mylog(){console.log(\"test\");}mylog();");
	//chrome.runScript("var i;i=1;");

	//chrome.captureScreenshot("jpeg", 100, 0, 0, 500, 600, 1.0, "output.jpg");

	//string selector = "#kw";
	//string text = "c++开发工具";
	//text = stringUtils.GBKToUTF8(text);
	//chrome.inputText(selector,text);

	chrome.navigate("https://www.sina.com.cn/", "");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	boolean finished = chrome.isLoadingFinished();//0=没有加载完成 1=加载完成
	std::cout << std::to_string(finished) << std::endl;
	mylog("执行完成");

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

}

