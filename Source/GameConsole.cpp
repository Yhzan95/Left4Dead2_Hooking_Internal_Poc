#include "GameConsole.h"
#include <cstdarg>
#include <cstdio>

void PrintToGameConsole(const char* message)
{
    // Adresse connue que tu m’as donnée
    IGameConsole* pConsole = reinterpret_cast<IGameConsole*>(0x1FA0E0);

    if (pConsole)
        pConsole->Printf("%s\n", message);
}
