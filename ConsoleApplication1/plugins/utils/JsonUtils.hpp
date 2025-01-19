#pragma once
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "nlohmann/json.hpp" 
#include <atlstr.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace uuids = boost::uuids;
using json = nlohmann::json;
using namespace std;
class JsonUtils
{
public:

    /// <summary>
    /// 解析json，并放入vec
    /// </summary>
    /// <param name="jsonStr">json字符串</param>
    /// <param name="vec">json容器</param>
    void parseJson(CString jsonStr, map<string, json>* jsonCache) {
        uuids::random_generator uuid_gen;
        uuids::uuid uuid1 = uuid_gen();
        uuids::uuid uuid2 = uuid_gen();

        std::cout << "UUID 1: " << uuid1 << std::endl;
        std::cout << "UUID 2: " << uuid2 << std::endl;
    }

    // 辅助函数：将点分隔的字符串转换为键的向量，支持数组索引
    vector<string> splitKeys(const string& keyPath) {
        vector<string> keys;
        stringstream ss(keyPath);
        string key;
        size_t arrayIndexStart = 0;
        while (getline(ss, key, '.')) {
            // 检查是否包含数组索引
            size_t arrayIndexEnd = key.find(']');
            if (arrayIndexEnd != string::npos && key[arrayIndexEnd - 1] == ']') {
                size_t arrayIndexStart = key.find('[');
                if (arrayIndexStart != string::npos) {
                    string arrayKey = key.substr(0, arrayIndexStart - 1);
                    string arrayIndexStr = key.substr(arrayIndexStart + 1, arrayIndexEnd - arrayIndexStart - 1);
                    size_t arrayIndex = stoul(arrayIndexStr);
                    keys.push_back(arrayKey + "[" + to_string(arrayIndex) + "]");
                }
                else {
                    // 格式错误，应包含'['和']'
                    throw invalid_argument("Invalid array index format in key path: " + keyPath);
                }
            }
            else {
                keys.push_back(key);
            }
        }
        return keys;
    }

    // 主函数：根据键路径从JSON对象中获取值
    json getValueFromJson(const json& j, const string& keyPath) {
        vector<string> keys = splitKeys(keyPath);
        json currentValue = j;
        for (const string& key : keys) {
            size_t arrayIndexStart = key.find('[');
            if (arrayIndexStart != string::npos) {
                // 处理数组索引
                size_t arrayIndexEnd = key.find(']');
                if (arrayIndexEnd != string::npos) {
                    string arrayKey = key.substr(0, arrayIndexStart);
                    string arrayIndexStr = key.substr(arrayIndexStart + 1, arrayIndexEnd - arrayIndexStart - 1);
                    size_t arrayIndex = stoul(arrayIndexStr);

                    if (currentValue.contains(arrayKey) && currentValue[arrayKey].is_array()) {
                        currentValue = currentValue[arrayKey][arrayIndex];
                    }
                    else {
                        // 如果键不存在或不是数组，可以抛出一个异常或者返回一个空json对象
                        // 这里我们选择返回一个空json对象
                        return json();
                    }
                }
                else {
                    // 格式错误，应包含']'
                    throw invalid_argument("Invalid array index format in key path: " + keyPath);
                }
            }
            else {
                if (currentValue.contains(key)) {
                    currentValue = currentValue[key];
                }
                else {
                    // 如果键不存在，可以抛出一个异常或者返回一个空json对象
                    // 这里我们选择返回一个空json对象
                    return json();
                }
            }
        }
        return currentValue;
    }

};
