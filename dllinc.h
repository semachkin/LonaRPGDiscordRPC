#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define DYNAMIC_LIB

#ifdef DYNAMIC_LIB
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT
#endif

#define APP_ID "1279709322917580800"

enum GAME_STATE {
    GAME_MENU,
    GAME_GAME,
    GAME_SEX
};
enum RACE {
    RACE_HUMAN,
    RACE_DEEPONE,
    RACE_SEAWITCH,
    RACE_MOOD,
    RACE_ABOMINATION
};

typedef const char* string;
typedef unsigned char enumt;

DLL_EXPORT void discordUpdate(string ver, UINT lvl, enumt gameState, enumt race, string date);
DLL_EXPORT void discordInit(void);

DLL_EXPORT void loadLibraries(string ld_path);