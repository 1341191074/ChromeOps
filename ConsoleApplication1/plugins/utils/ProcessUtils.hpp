#pragma once

#include <boost/process.hpp>

namespace bp = boost::process;
class ProcessUtils
{
public:
    
    bp::child startChrome(std::string chromeFullPath, std::vector<std::string> args) {
        try {
            // 构造启动Chrome的命令
            bp::child c(chromeFullPath, args);
            c.detach();
            // 延迟2秒
            std::this_thread::sleep_for(std::chrono::seconds(2));
            // 返回子进程对象，以便后续可以关闭它
            return c;
        }
        catch (const bp::process_error& e) {
            throw std::runtime_error("Failed to start Chrome: " + std::string(e.what()));
        }
    }
    void closeChrome(bp::child& chromeProcess) {
        try {
            // 等待并终止子进程（即Chrome浏览器）
            chromeProcess.terminate();
            chromeProcess.wait(); // 可选：等待进程真正结束
        }
        catch (const bp::process_error& e) {
        }
    }
};

