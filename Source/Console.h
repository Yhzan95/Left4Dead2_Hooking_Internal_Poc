#pragma once
#include <Windows.h>
#include <string>

namespace Console
{
    enum class LogType { Info, Warning, Error };

    void Init();
    void Shutdown();

    void Log(LogType type, const char* fmt, ...);

    void LogInfo(const char* fmt, ...);
    void LogWarning(const char* fmt, ...);
    void LogError(const char* fmt, ...);
}
