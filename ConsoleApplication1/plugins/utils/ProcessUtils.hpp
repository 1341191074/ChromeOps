#pragma once
#include <windows.h>
#include <iostream>

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
        STARTUPINFO si = { sizeof(si) };
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
};

