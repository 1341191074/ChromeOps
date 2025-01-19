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
    /// ����json��������vec
    /// </summary>
    /// <param name="jsonStr">json�ַ���</param>
    /// <param name="vec">json����</param>
    void parseJson(CString jsonStr, map<string, json>* jsonCache) {
        uuids::random_generator uuid_gen;
        uuids::uuid uuid1 = uuid_gen();
        uuids::uuid uuid2 = uuid_gen();

        std::cout << "UUID 1: " << uuid1 << std::endl;
        std::cout << "UUID 2: " << uuid2 << std::endl;
    }

    // ��������������ָ����ַ���ת��Ϊ����������֧����������
    vector<string> splitKeys(const string& keyPath) {
        vector<string> keys;
        stringstream ss(keyPath);
        string key;
        size_t arrayIndexStart = 0;
        while (getline(ss, key, '.')) {
            // ����Ƿ������������
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
                    // ��ʽ����Ӧ����'['��']'
                    throw invalid_argument("Invalid array index format in key path: " + keyPath);
                }
            }
            else {
                keys.push_back(key);
            }
        }
        return keys;
    }

    // �����������ݼ�·����JSON�����л�ȡֵ
    json getValueFromJson(const json& j, const string& keyPath) {
        vector<string> keys = splitKeys(keyPath);
        json currentValue = j;
        for (const string& key : keys) {
            size_t arrayIndexStart = key.find('[');
            if (arrayIndexStart != string::npos) {
                // ������������
                size_t arrayIndexEnd = key.find(']');
                if (arrayIndexEnd != string::npos) {
                    string arrayKey = key.substr(0, arrayIndexStart);
                    string arrayIndexStr = key.substr(arrayIndexStart + 1, arrayIndexEnd - arrayIndexStart - 1);
                    size_t arrayIndex = stoul(arrayIndexStr);

                    if (currentValue.contains(arrayKey) && currentValue[arrayKey].is_array()) {
                        currentValue = currentValue[arrayKey][arrayIndex];
                    }
                    else {
                        // ����������ڻ������飬�����׳�һ���쳣���߷���һ����json����
                        // ��������ѡ�񷵻�һ����json����
                        return json();
                    }
                }
                else {
                    // ��ʽ����Ӧ����']'
                    throw invalid_argument("Invalid array index format in key path: " + keyPath);
                }
            }
            else {
                if (currentValue.contains(key)) {
                    currentValue = currentValue[key];
                }
                else {
                    // ����������ڣ������׳�һ���쳣���߷���һ����json����
                    // ��������ѡ�񷵻�һ����json����
                    return json();
                }
            }
        }
        return currentValue;
    }

};
