#include "dllinc.h"
#include "dependencies/discord_rpc.h"

static Discord_Initialize_t Discord_Initialize;
static Discord_UpdatePresence_t Discord_UpdatePresence;
static Discord_ClearPresence_t Discord_ClearPresence;

static time_t starttime;

DLL_EXPORT void discordUpdate(string ver, UINT lvl, enumt gameState, enumt race, string date) {
    DiscordRichPresence discordPresence = {0};

    char details[0xff] = {0};

    string state;

    string largeimage = "lona_human";
    string raceStr = "Human";

    if (race == RACE_DEEPONE) {
        raceStr = "Deepone";
        largeimage = "lona_deepone";
    } else if (race == RACE_SEAWITCH) {
        raceStr = "Sea Witch";
        largeimage = "lona_seawitch";
    } else if (race == RACE_MOOD) {
        raceStr = "Mixed";
        largeimage = "lona_abomination";
    } else if (race == RACE_ABOMINATION) {
        raceStr = "Abomination";
        largeimage = "lona_abomination";
    }

    if (gameState == GAME_MENU) {
        state = "In Main Menu";
        largeimage = "lona_menu";
    } else {
        sprintf(details, "Lvl: %d, Race: %s, Date: %s", lvl, raceStr, date);
    }
    if (gameState == GAME_GAME) {
        state = "In Game";
    } else if (gameState == GAME_SEX) {
        state = "Has Sex";
        discordPresence.smallImageKey = "heart_baloon";
    }

    discordPresence.startTimestamp = starttime;
    discordPresence.largeImageKey = largeimage;
    discordPresence.state = state;
    discordPresence.largeImageText = ver;
    discordPresence.partyPrivacy = FALSE;
    discordPresence.details = details;

    Discord_UpdatePresence(&discordPresence);
}

static void discordErrorHandler(int errcode, string message) {
    printf("Discord error %d: %s\n", errcode, message);
}

DLL_EXPORT void discordInit(void) {
    DiscordEventHandlers *handlers = (DiscordEventHandlers*)calloc(1, sizeof(DiscordEventHandlers));
    memset(handlers, 0, sizeof(DiscordEventHandlers));

    handlers->errored = discordErrorHandler;

    starttime = time(0);

    Discord_Initialize(APP_ID, handlers, 1, NULL);
    Discord_ClearPresence();
}

DLL_EXPORT void loadLibraries(string ld_path) {
    SetDllDirectoryA(ld_path);
    HMODULE discordrpc = LoadLibraryA("discord-rpc.dll");

    Discord_Initialize = (Discord_Initialize_t)GetProcAddress(discordrpc, "Discord_Initialize");
    Discord_UpdatePresence = (Discord_UpdatePresence_t)GetProcAddress(discordrpc, "Discord_UpdatePresence");
    Discord_ClearPresence = (Discord_ClearPresence_t)GetProcAddress(discordrpc, "Discord_ClearPresence");
}