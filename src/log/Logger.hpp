#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    static Logger& instance();

    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);

private:
    Logger();
    void write(const std::string& level, const std::string& msg);

    std::ofstream file_;
    std::mutex mtx_;
};