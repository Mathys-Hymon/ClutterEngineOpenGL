#pragma once

#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

/**
 * @class CLog
 * @brief A logging utility class for handling console and file-based logging.
 */
class CLUTTER_API CLog
{
public:
    /**
     * @enum LogLevel
     * @brief Represents the severity level of a log message.
     */
    enum class LogLevel {
        INFO,    ///< Informational messages.
        WARNING, ///< Warning messages.
        CERROR,  ///< Error messages.
        LOG      ///< General log messages.
    };

    /**
     * @brief Initializes the logging system.
     * @param logName The name of the log file.
     * @param logFilePath The directory path where the log file will be created. Defaults to an empty string.
     */
    static void Init(const std::string& logName, const std::string& logFilePath = "") {
#ifdef _DEBUG

        std::filesystem::create_directories(logFilePath + "logs");

        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);

        struct tm timeInfo;
        localtime_s(&timeInfo, &now_time);

        std::ostringstream oss;
        oss << logFilePath << "logs/" << logName << "_" << std::put_time(&timeInfo, "%Y-%m-%d__%H-%M-%S") << "_log.json";

        std::string filePath = oss.str();
        GetInstance().mLogFile.open(filePath, std::ios::out | std::ios::trunc);
        if (GetInstance().mLogFile.is_open()) {
            std::cerr << "Log file opened successfully: " << filePath << "\n";
            GetInstance().mLogFile << "[\n";
            GetInstance().mFirstEntry = true;
        }
#endif
    }

    /**
     * @brief Shuts down the logging system and closes the log file.
     */
    static void Shutdown() {
#ifdef _DEBUG
        if (GetInstance().mLogFile.is_open()) {
            GetInstance().mLogFile << "\n]\n";
            GetInstance().mLogFile.close();
        }
#endif
    }

    /**
     * @brief Logs a message to the console and/or a JSON file.
     * @tparam Args Variadic template for additional arguments to format the message.
     * @param level The severity level of the log message.
     * @param message The log message format string.
     * @param file The source file where the log was generated.
     * @param line The line number in the source file where the log was generated.
     * @param args Additional arguments for formatting the message.
     */
    template<typename... Args>
    static void Log(LogLevel level, const std::string& message, const char* file, int line, Args... args)
    {
#ifdef EDITOR

        if (level == LogLevel::CERROR) {

            std::cout << GetConsoleColor(level)
                << FormatConsoleMessage(level, message,file, line, args...)
                << "\033[0m" << std::endl;

            #ifdef _MSC_VER
            __debugbreak();
            #else
            std::abort(); // fallback for non-MSVC compilers
            #endif
        }
        else
        {
            std::cout << GetConsoleColor(level)
                << FormatConsoleMessage(level, message, args...)
                << "\033[0m" << std::endl;
        }

#endif

#ifdef _DEBUG
        WriteToJsonFile(level, message, file, line, args...);

        if (level == LogLevel::CERROR) {
            std::exit(EXIT_FAILURE);
        }
#endif
    }

private:
    std::ofstream mLogFile; ///< The file stream for the log file.
    bool mFirstEntry = true; ///< Indicates if the current log entry is the first in the file.

    /**
     * @brief Retrieves the singleton instance of the CLog class.
     * @return A reference to the singleton instance.
     */
    static CLog& GetInstance() {
        static CLog instance;
        return instance;
    }

    /**
     * @brief Gets the console color code for a given log level.
     * @param level The log level.
     * @return The console color code as a C-string.
     */
    static const char* GetConsoleColor(LogLevel level) {
        switch (level) {
        case LogLevel::INFO:      return "\033[38;5;120m";
        case LogLevel::LOG:       return "\033[0;37m";
        case LogLevel::WARNING:   return "\033[1;33m";
        case LogLevel::CERROR:    return "\033[1;31m";
        default:                  return "\033[0m";
        }
    }

    /**
     * @brief Formats a log message for console output.
     * @tparam Args Variadic template for additional arguments to format the message.
     * @param level The severity level of the log message.
     * @param format The log message format string.
     * @param file The source file where the log was generated.
     * @param line The line number in the source file where the log was generated.
     * @param args Additional arguments for formatting the message.
     * @return The formatted log message as a string.
     */
    template<typename... Args>
    static std::string FormatConsoleMessage(LogLevel level, const std::string& format, const char* file, int line, Args... args) {
        std::string levelStr;
        switch (level) {
        case LogLevel::INFO:     levelStr = "[INFO] "; break;
        case LogLevel::WARNING:  levelStr = "[WARNING] "; break;
        case LogLevel::CERROR:   levelStr = "[ERROR] "; break;
        case LogLevel::LOG:      levelStr = "[LOG] "; break;
        }

        char buffer[1024];
        snprintf(buffer, sizeof(buffer), format.c_str(), args...);

        std::ostringstream oss;
        oss << levelStr << buffer << " (" << file << ":" << line << ")";
        return oss.str();
    }

    template<typename... Args>
    static std::string FormatConsoleMessage(LogLevel level, const std::string& format, Args... args) {
        std::string levelStr;
        switch (level) {
        case LogLevel::INFO:     levelStr = "[INFO] "; break;
        case LogLevel::WARNING:  levelStr = "[WARNING] "; break;
        case LogLevel::CERROR:   levelStr = "[ERROR] "; break;
        case LogLevel::LOG:      levelStr = "[LOG] "; break;
        }

        char buffer[1024];
        snprintf(buffer, sizeof(buffer), format.c_str(), args...);

        std::ostringstream oss;
        oss << levelStr << buffer;
        return oss.str();
    }

    /**
     * @brief Writes a log message to a JSON file.
     * @tparam Args Variadic template for additional arguments to format the message.
     * @param level The severity level of the log message.
     * @param format The log message format string.
     * @param file The source file where the log was generated.
     * @param line The line number in the source file where the log was generated.
     * @param args Additional arguments for formatting the message.
     */
    template<typename... Args>
    static void WriteToJsonFile(LogLevel level, const std::string& format, const char* file, int line, Args... args) {
        if (!GetInstance().mLogFile.is_open()) return;

        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);

        char messageBuffer[1024];
        snprintf(messageBuffer, sizeof(messageBuffer), format.c_str(), args...);

        if (!GetInstance().mFirstEntry) {
            GetInstance().mLogFile << ",\n";
        }
        else {
            GetInstance().mFirstEntry = false;
        }

        struct tm timeInfo;
        localtime_s(&timeInfo, &now_time);

        GetInstance().mLogFile
            << "  {\n"
            << "    \"time\": \"" << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << "\",\n"
            << "    \"level\": \"" << LogLevelToString(level) << "\",\n"
            << "    \"message\": \"" << EscapeJsonString(messageBuffer) << "\",\n"
            << "    \"file\": \"" << EscapeJsonString(file) << "\",\n"
            << "    \"line\": " << line << "\n"
            << "  }";
    }

    /**
     * @brief Converts a log level to its string representation.
     * @param level The log level.
     * @return The string representation of the log level.
     */
    static std::string LogLevelToString(LogLevel level) {
        switch (level) {
        case LogLevel::INFO:     return "INFO";
        case LogLevel::WARNING:  return "WARNING";
        case LogLevel::CERROR:   return "ERROR";
        case LogLevel::LOG:      return "LOG";
        default:                 return "UNKNOWN";
        }
    }

    /**
     * @brief Escapes special characters in a string for JSON formatting.
     * @param input The input string.
     * @return The escaped string.
     */
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

// Macros
#define CLUTTER_LOG(message, ...)     CLog::Log(CLog::LogLevel::LOG, message, __FILE__, __LINE__, ##__VA_ARGS__)
#define CLUTTER_INFO(message, ...)    CLog::Log(CLog::LogLevel::INFO, message, __FILE__, __LINE__, ##__VA_ARGS__)
#define CLUTTER_WARNING(message, ...) CLog::Log(CLog::LogLevel::WARNING, message, __FILE__, __LINE__, ##__VA_ARGS__)
#define CLUTTER_ERROR(message, ...)   CLog::Log(CLog::LogLevel::CERROR, message, __FILE__, __LINE__, ##__VA_ARGS__)
