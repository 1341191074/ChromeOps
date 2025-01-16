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
        // 创建独立的进程
        BOOL success = CreateProcessW(
            unicodeStr.c_str(),                   // 可执行文件路径
            NULL,                      // 命令行参数（在此处为NULL，因为我们在exePath中指定了完整路径）
            NULL,                      // 进程安全属性（NULL表示使用默认设置）
            NULL,                      // 线程安全属性（NULL表示使用默认设置）
            FALSE,                     // 不继承句柄
            CREATE_NEW_PROCESS_GROUP | // 创建一个新的进程组
            CREATE_UNICODE_ENVIRONMENT,// 使用Unicode环境变量
            NULL,                      // 使用父进程的环境变量
            NULL,                      // 使用父进程的当前目录
            &si,                       // 启动信息
            &pi                        // 进程信息
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

