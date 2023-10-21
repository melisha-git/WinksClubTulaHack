#pragma once

#include <fstream>
#include <string>

class Log {
public:
    Log(const std::string& filepath = "./BackendLogs/", const std::string& fileName = "BackendLogs.jog");
    void addLog(const std::string& msg);
    ~Log();
private:
    bool isOpen_;
    std::string filepath_;
    std::string fileName_;
    std::ofstream logFile_;
};
