#pragma once
#include <map>
#include <string>
#include <variant>
#include "nlohmann/json.hpp"

class GlobalData {
public:
	inline static int cmdIdx = 1;
	// 提供一个公共的静态函数来获取对result的引用
	static std::map<int, nlohmann::json>& getResult() {
		return result;
	}

	// 禁止实例化GlobalData类
	GlobalData() = delete;
	~GlobalData() = delete;
	GlobalData(const GlobalData&) = delete;
	GlobalData& operator=(const GlobalData&) = delete;

private:
	// 声明静态成员变量result
	static std::map<int, nlohmann::json> result;
};
