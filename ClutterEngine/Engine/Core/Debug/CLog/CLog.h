#pragma once

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

class CLUTTER_API CLog 
{
public:
    enum class LogLevel {
        INFO,
        WARNING,
        CERROR,
        LOG 
    };

    static void Init(const std::string& logFilePath = "template") {
#ifdef _DEBUG

        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);

        struct tm timeInfo;
        localtime_s(&timeInfo, &now_time);
        
        std::ostringstream oss;  
               oss << logFilePath << "_" << std::put_time(&timeInfo, "%Y-%m-%d -- %H:%M:%S") << "_log.json";
               std::string temp = oss.str();

        std::string filePath = oss.str();
        GetInstance().m_logFile.open(filePath, std::ios::out | std::ios::trunc);
        if (GetInstance().m_logFile.is_open()) {
            GetInstance().m_logFile << "[\n";
            GetInstance().m_firstEntry = true;
        }
#endif
    }

    static void Shutdown() {
#ifdef _DEBUG
        if (GetInstance().m_logFile.is_open()) {
            GetInstance().m_logFile << "\n]\n";
            GetInstance().m_logFile.close();
        }
#endif
    }

    template<typename... Args>
    static void Log(LogLevel level, const std::string& message, Args... args) 
    {
#ifdef EDITOR
        std::cout << GetConsoleColor(level)
            << FormatConsoleMessage(level, message, args...)
            << "\033[0m" << std::endl;
#endif

#ifdef _DEBUG
        WriteToJsonFile(level, message, args...);
#endif
    }

private:
    std::ofstream m_logFile;
    bool m_firstEntry = true;

    static CLog& GetInstance() {
        static CLog instance;
        return instance;
    }

    static const char* GetConsoleColor(LogLevel level) {
        switch (level) {
        case LogLevel::INFO:      return "\033[38;5;120m";
        case LogLevel::LOG:       return "\033[0;37m";
        case LogLevel::WARNING:   return "\033[1;33m";
        case LogLevel::CERROR:    return "\033[1;31m";
        default:                  return "\033[0m";   
        }
    }

    template<typename... Args>
    static std::string FormatConsoleMessage(LogLevel level, const std::string& format, Args... args) {
        std::string levelStr;
        switch (level) {
        case LogLevel::INFO:     levelStr = "[INFO] "; break;
        case LogLevel::WARNING:  levelStr = "[WARNING] "; break;
        case LogLevel::CERROR:    levelStr = "[ERROR] "; break;
        case LogLevel::LOG:      levelStr = "[LOG] "; break;
        }

        char buffer[1024];
        snprintf(buffer, sizeof(buffer), format.c_str(), args...);
        return levelStr + buffer;
    }

    template<typename... Args>
    static void WriteToJsonFile(LogLevel level, const std::string& format, Args... args) {
        if (!GetInstance().m_logFile.is_open()) return;

        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);

        char messageBuffer[1024];
        snprintf(messageBuffer, sizeof(messageBuffer), format.c_str(), args...);

        if (!GetInstance().m_firstEntry) {
            GetInstance().m_logFile << ",\n";
        }
        else {
            GetInstance().m_firstEntry = false;
        }

        struct tm timeInfo;
        localtime_s(&timeInfo, &now_time);

        GetInstance().m_logFile 
            << "  {\n"
            << "    \"timestamp\": \"" << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << "\",\n"
            << "    \"level\": \"" << LogLevelToString(level) << "\",\n"
            << "    \"message\": \"" << EscapeJsonString(messageBuffer) << "\"\n"
            << "  }";
    }

    static std::string LogLevelToString(LogLevel level) {
        switch (level) {
        case LogLevel::INFO:     return "INFO";
        case LogLevel::WARNING:  return "WARNING";
        case LogLevel::CERROR:    return "ERROR";
        case LogLevel::LOG:      return "LOG";
        default:                return "UNKNOWN";
        }
    }

    static std::string EscapeJsonString(const std::string& input) {
        std::ostringstream ss;
        for (char c : input) {
            switch (c) {
            case '"': ss << "\\\""; break;
            case '\\': ss << "\\\\"; break;
            case '\b': ss << "\\b"; break;
            case '\f': ss << "\\f"; break;
            case '\n': ss << "\\n"; break;
            case '\r': ss << "\\r"; break;
            case '\t': ss << "\\t"; break;
            default: ss << c; break;
            }
        }
        return ss.str();
    }
};

#define CLUTTER_LOG(message, ...)    CLog::Log(CLog::LogLevel::LOG, message, ##__VA_ARGS__)
#define CLUTTER_INFO(message, ...)   CLog::Log(CLog::LogLevel::INFO, message, ##__VA_ARGS__)
#define CLUTTER_WARNING(message, ...) CLog::Log(CLog::LogLevel::WARNING, message, ##__VA_ARGS__)
#define CLUTTER_ERROR(message, ...)  CLog::Log(CLog::LogLevel::CERROR, message, ##__VA_ARGS__)