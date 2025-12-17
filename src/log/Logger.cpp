#include "Logger.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>

Logger::Logger() {
    std::filesystem::create_directories("data");
    file_.open("data/log.txt", std::ios::app);
}

Logger& Logger::instance() {
    static Logger inst;
    return inst;
}

void Logger::write(const std::string& level, const std::string& msg) {
    std::lock_guard<std::mutex> lock(mtx_);

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream ts;
    ts << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    file_ << "[" << ts.str() << "] [" << level << "] " << msg << "\n";
    file_.flush();
}

void Logger::info(const std::string& msg)  { write("INFO", msg); }
void Logger::warn(const std::string& msg)  { write("WARN", msg); }
void Logger::error(const std::string& msg) { write("ERROR", msg); }