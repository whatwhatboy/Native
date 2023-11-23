#pragma once
#include "register.h"
#include "rpc.h"

namespace Base {
    class discord_handler {
    public:
        void init();
        void tick();
        void shutdown();
    };
    inline std::unique_ptr<discord_handler> g_discord;
}