#pragma once
#include <map>
#include <string>
#include <variant>
#include "nlohmann/json.hpp"

class GlobalData {
public:
	inline static int cmdIdx = 1;
	// �ṩһ�������ľ�̬��������ȡ��result������
	static std::map<int, nlohmann::json>& getResult() {
		return result;
	}

	// ��ֹʵ����GlobalData��
	GlobalData() = delete;
	~GlobalData() = delete;
	GlobalData(const GlobalData&) = delete;
	GlobalData& operator=(const GlobalData&) = delete;

private:
	// ������̬��Ա����result
	static std::map<int, nlohmann::json> result;
};
