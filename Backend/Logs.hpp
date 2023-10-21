#include <memory>
#include <fstream>
#include <string>

void startLog(const std::string& filepath);

void log(Level s, const std::string& msg);

class Log {
public:
    Log(const std::string& filepath);
    void addLog(Level s, const std::string& msg);
    ~Log();
private:
    std::ofstream m_logfile;
};
