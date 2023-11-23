#include "libary/handler.hpp"
#include "libary/register.h"
#include "libary/rpc.h"
#include <chrono>
#include "src/utility/common/common.h"
#include "src/Natives/Natives.h"
#pragma comment(lib, "discord-rpc.lib")
using namespace Base;

void discord_handler::init() {
    DiscordEventHandlers handlers;
    std::memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize("1131090393551872021", &handlers, 1, "0");
}

std::string UserType;
std::string State;
str get_game_type() {
    str module_key{ "Rockstar Games" };
    if (GetModuleHandleA("EOSSDK-Win64-Shipping.dll")) {
        module_key = "Epic Games";
    }
    else if (GetModuleHandleA("steam_api64.dll")) {
        module_key = "Steam";
    }
    return module_key;
}
void discord_handler::tick() {

    str branding{ " Native" };

    static int64_t start_time{ std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() };
    DiscordRichPresence discordPresence;
    std::memset(&discordPresence, 0, sizeof(discordPresence));
    std::string SessionType;
    srand(time(NULL));
    str details{ "Playing with" + branding + " on " + get_game_type()};
    discordPresence.details = details.c_str();
    discordPresence.startTimestamp = start_time;
    discordPresence.largeImageKey = "logo";
    discordPresence.largeImageText = "Menu Version: Tester";
    discordPresence.button1name = "Discord";
    discordPresence.button1link = "https://discord.gg/U4SCUqJyEY";
    if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
        discordPresence.state = "Online";
        discordPresence.partySize = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
        discordPresence.partyMax = 32;
    }
    else {
        discordPresence.state = "Story Mode";
    }
    discordPresence.instance = 1;
    Discord_UpdatePresence(&discordPresence);
}

void discord_handler::shutdown() {
    Discord_ClearPresence();
    Discord_Shutdown();
}