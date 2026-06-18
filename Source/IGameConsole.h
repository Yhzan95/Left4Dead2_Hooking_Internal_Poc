class IGameConsole
{
public:
    virtual void Activate() = 0;
    virtual void Initialize() = 0;
    virtual void Hide() = 0;
    virtual void Clear() = 0;
    virtual void IsConsoleVisible() = 0;
    virtual void Printf(const char* fmt, ...) = 0;
    virtual void DPrintf(const char* fmt, ...) = 0;
    virtual void SetParent(int parent) = 0;
};
