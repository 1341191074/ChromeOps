#pragma once

#include <boost/process.hpp>

namespace bp = boost::process;
class ProcessUtils
{
public:
    
    bp::child startChrome(std::string chromeFullPath, std::vector<std::string> args) {
        try {
            // ��������Chrome������
            bp::child c(chromeFullPath, args);
            c.detach();
            // �ӳ�2��
            std::this_thread::sleep_for(std::chrono::seconds(2));
            // �����ӽ��̶����Ա�������Թر���
            return c;
        }
        catch (const bp::process_error& e) {
            throw std::runtime_error("Failed to start Chrome: " + std::string(e.what()));
        }
    }
    void closeChrome(bp::child& chromeProcess) {
        try {
            // �ȴ�����ֹ�ӽ��̣���Chrome�������
            chromeProcess.terminate();
            chromeProcess.wait(); // ��ѡ���ȴ�������������
        }
        catch (const bp::process_error& e) {
        }
    }
};

