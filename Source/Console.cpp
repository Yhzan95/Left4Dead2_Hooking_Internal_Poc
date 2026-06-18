#include "Console.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdarg>
#include <iomanip>

static std::ofstream logfile;

namespace Console
{
    static HANDLE hConsole = nullptr;

    std::string GetTimestamp()
    {
        std::time_t t = std::time(nullptr);
        std::tm tm;
        localtime_s(&tm, &t);

        char buffer[16];
        std::strftime(buffer, sizeof(buffer), "[%H:%M:%S]", &tm);
        return std::string(buffer);
    }

    void Init()
    {
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
        SetConsoleTitleA("Debug Console");

        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        logfile.open("H2R_log.txt", std::ios::out | std::ios::app);
        LogInfo("Console initialized.");
    }

    void Shutdown()
    {
        LogInfo("Console shutdown.");
        logfile.close();
        FreeConsole();
    }

    void Log(LogType type, const char* fmt, ...)
    {
        if (!fmt) return;
        char buffer[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, args);
        va_end(args);

        std::string timestamp = GetTimestamp();

        switch (type)
        {
        case LogType::Info:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case LogType::Warning:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case LogType::Error:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        }

        std::cout << timestamp << " " << buffer << std::endl;

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        if (logfile.is_open())
            logfile << timestamp << " " << buffer << std::endl;
    }

    void LogInfo(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        Log(LogType::Info, fmt, args);
        va_end(args);
    }

    void LogWarning(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        Log(LogType::Warning, fmt, args);
        va_end(args);
    }

    void LogError(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        Log(LogType::Error, fmt, args);
        va_end(args);
    }
}
