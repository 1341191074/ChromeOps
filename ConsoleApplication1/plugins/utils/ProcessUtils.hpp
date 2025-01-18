#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "curl/curl.h"

class ProcessUtils
{
public:
    std::wstring AnsiToUnicode(const std::string& ansiStr) {
        int len = MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, nullptr, 0);
        std::wstring unicodeStr(len, 0);
        MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, &unicodeStr[0], len);
        return unicodeStr;
    }
    PROCESS_INFORMATION startChrome(std::string chromeFullPath, std::vector<std::string> args) {
        STARTUPINFOW si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        std::wstring unicodeStr = AnsiToUnicode(chromeFullPath);
        // ���������Ľ���
        BOOL success = CreateProcessW(
            unicodeStr.c_str(),                   // ��ִ���ļ�·��
            NULL,                      // �����в������ڴ˴�ΪNULL����Ϊ������exePath��ָ��������·����
            NULL,                      // ���̰�ȫ���ԣ�NULL��ʾʹ��Ĭ�����ã�
            NULL,                      // �̰߳�ȫ���ԣ�NULL��ʾʹ��Ĭ�����ã�
            FALSE,                     // ���̳о��
            CREATE_NEW_PROCESS_GROUP | // ����һ���µĽ�����
            CREATE_UNICODE_ENVIRONMENT,// ʹ��Unicode��������
            NULL,                      // ʹ�ø����̵Ļ�������
            NULL,                      // ʹ�ø����̵ĵ�ǰĿ¼
            &si,                       // ������Ϣ
            &pi                        // ������Ϣ
        );

        if (success) {
            std::cout << "Independent process created." << std::endl;
        }
        else {
            std::cerr << "Failed to create independent process." << std::endl;
        }
        return pi;
    }
    void closeChrome(PROCESS_INFORMATION pi) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    bool isPortOpen(const std::string& ip, std::string port) {
        CURL* curl;
        CURLcode res;

        curl = curl_easy_init();
        if (curl) {
            std::string url = "http://" + ip + ":" + port;
            curl_easy_setopt(curl, CURLOPT_URL, url);

            // �������󷽷�Ϊ HEAD����Ϊ����ֻ��Ҫ��������Ƿ�ɹ�������Ҫ��ȡ��Ӧ��
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "HEAD");

            // ִ������
            res = curl_easy_perform(curl);
            // �����ͷ���Դ
            curl_easy_cleanup(curl);

            // ���������
            if (res == CURLE_OK) {
                printf("Connection successful!\n");
                return true;
            }

            
        }
        return true;
    }
};

