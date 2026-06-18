#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdarg>
#include <ctime>
#include <cstdio>
#include <cstdint>

typedef void* (*CreateInterfaceFn)(const char*, int*);
typedef int CVarDLLIdentifier_t;

class IConsoleDisplayFunc {};
class ConVar;
class ConCommand;
class ConCommandBase; 

typedef void(*FnChangeCallback_t)(ConVar* var, const char* pOldValue, float flOldValue);

class IAppSystem {
public:
    virtual bool Connect(void* factory) = 0;
    virtual void Disconnect() = 0;
    virtual void* QueryInterface(const char* pInterfaceName) = 0;
    virtual int Init() = 0;
    virtual void Shutdown() = 0;
};

class ICvar : public IAppSystem {
public:
    virtual CVarDLLIdentifier_t        AllocateDLLIdentifier() = 0;
    virtual void                       RegisterConCommand(ConCommandBase* pCommandBase) = 0;
    virtual void                       UnregisterConCommand(ConCommandBase* pCommandBase) = 0;
    virtual void                       UnregisterConCommands(CVarDLLIdentifier_t id) = 0;
    virtual const char* GetCommandLineValue(const char* pVariableName) = 0;
    virtual ConCommandBase* FindCommandBase(const char* name) = 0;
    virtual const ConCommandBase* FindCommandBase(const char* name) const = 0;
    virtual ConVar* FindVar(const char* var_name) = 0;
    virtual const ConVar* FindVar(const char* var_name) const = 0;
    virtual ConCommand* FindCommand(const char* name) = 0;
    virtual const ConCommand* FindCommand(const char* name) const = 0;
    virtual void                       InstallGlobalChangeCallback(FnChangeCallback_t callback) = 0;
    virtual void                       RemoveGlobalChangeCallback(FnChangeCallback_t callback) = 0;
    virtual void                       CallGlobalChangeCallbacks(ConVar* var, const char* pOldString, float flOldValue) = 0;
    virtual void                       InstallConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
    virtual void                       RemoveConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
    virtual void ConsoleColorPrintf(const uint8_t* clr, const char* pFormat, ...) const = 0;
    virtual void ConsolePrintf(const char* pFormat, ...) const = 0;
    virtual void ConsoleDPrintf(const char* pFormat, ...) const = 0;
    virtual void RevertFlaggedConVars(int nFlag) = 0;
};

ICvar* g_pCVar = nullptr;

void GameConsolePrint(const uint8_t clr[4], const char* fmt, ...)
{
    if (!g_pCVar) return;

    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    time_t now = time(nullptr);
    tm lt{};
    localtime_s(&lt, &now);
    char final[1150];
    snprintf(final, sizeof(final), "[%02d:%02d:%02d] %s", lt.tm_hour, lt.tm_min, lt.tm_sec, buffer);
    g_pCVar->ConsoleColorPrintf(clr, "%s", final);
}

DWORD WINAPI InitThread(LPVOID)
{
    while (!GetModuleHandleA("vstdlib.dll"))
        Sleep(100);
    auto fnCI = reinterpret_cast<CreateInterfaceFn>(
        GetProcAddress(GetModuleHandleA("vstdlib.dll"), "CreateInterface")
        );

    g_pCVar = reinterpret_cast<ICvar*>(fnCI("VEngineCvar007", nullptr));
    if (!g_pCVar) return 0;
    const uint8_t cyan[4] = { 0, 255, 255, 255 };
    const uint8_t green[4] = { 0, 255, 0, 255 };
    const uint8_t red[4] = { 255, 0, 0, 255 };
    GameConsolePrint(cyan, "[INFO] Logger couleur prêt.\n");
    GameConsolePrint(green, "[OK] Injection réussie.\n");
    GameConsolePrint(red, "[ERREUR] Ceci est un test rouge.\n");
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hMod, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hMod);
        CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
    }

    return TRUE;
}
