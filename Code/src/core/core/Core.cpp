#include <array>
#include <string>
#include <memory>
#include <chrono>
#include <thread>
#include <filesystem>
#include "Core.h"
#include "src/Hooking/Hooking.h"
#include "src/Core/Script/Script.h"
#include "src/Natives/Invoker/Invoker.h"
#include "src/Framework/Framework.h"
#include "src/fiber/fiber_helper.h"
#include "src/framework/direct_x/renderer.h"
#include "src/discord/libary/handler.hpp"
#include "src/exceptions/handler.h"
#include "src/hooking/native/native_hook.h"
#include "src/Framework/notifications/notifications.h"
#include "src/fiber/script/fiber_script.h"
#include "src/fiber/script/manager/script_manager.h"
#include "src/Natives/Natives.h"
#include "src/core/core/config.h"
#include "src/features/chat_commands/chat_commands.h"
#include <shellapi.h>
#include <ETAUTH/socket.hpp>
#include <ETAUTH/antidebug.hpp>
#include <VLIZER/VirtualizerSDK.h>
#include "src/hooking/xor.h"
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")


bool does_folder_exist(const wchar_t* path) {
    DWORD attrib{ GetFileAttributesW(path) };

    if (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY)) {
        return true;
    }
    return false;
}
void download_files() {
    const wchar_t* path{ L"C:\\Native" };
    const char* output{ "C:\\Native" };

    if (!does_folder_exist(path)) {
        const char* url{ "https://cdn.discordapp.com/attachments/1144081786972942496/1157721272097181877/Native.rar?ex=6519a374&is=651851f4&hm=4c9d5152703a7c0249fcebb80c934697baca3989d4a68c7c5fc5641785f3905c&" };

        HRESULT hr{ URLDownloadToFileA(NULL, url, output, 0, NULL) };
    }
}
namespace Base::core {
    void flash_taskbar(HWND hwnd, bool flash_until_foreground) {
        FLASHWINFO flash_info = {};
        flash_info.cbSize = sizeof(FLASHWINFO);
        flash_info.hwnd = hwnd;
        flash_info.dwFlags = FLASHW_ALL | (flash_until_foreground ? FLASHW_TIMERNOFG : 0);
        flash_info.uCount = 3;

        FlashWindowEx(&flash_info);
    }
    inline HMODULE g_scylla_hide_module{};
    std::string branding = xorstr_(" | Native Cheats");
    std::array<std::string, 2> titles = {
        "We change the sky color we the best menu" + branding,
        "I'm tired of this shit com :yawn:" + branding
    };

    std::unique_ptr<notifications> g_notifications;
    namespace main {
        void attach();
        void detach();
        void create_thread_instance();
        void attach() {
            //download_files();
            g_logger = std::make_unique<Logger>();
            Exceptions::init();
            create_thread_instance();
        }
        void detach() {
            
 
            Exceptions::uninit();
            SetWindowTextA(g_pointers->m_game_window, "Grand Theft Auto V");
            //config::save_options_to_file(fs::path(std::getenv(("appdata"))).append((BRANDING"\\config.json")).string());
            g_interface->save_settings_on_unload();
            g_hooking->Unhook();
            std::this_thread::sleep_for(1s);
            script_manager::Destroy();

           
            g_notifications.reset();
            g_renderer.reset();
            g_hooking.reset();
            g_menu.reset();
            g_pointers.reset();
            g_invoker.reset();
            g_discord->shutdown();
            g_logger.reset();
        }
        void create_thread_instance() {
            CreateThread(nullptr, 0, [](void* ptr) -> DWORD {
#ifndef DEV
                VIRTUALIZER_TIGER_WHITE_START
                auth::antidebug::run();
                LOG(Success, "Authenticated as {} | Subscription: {} days left", auth::socket::getUsername(), ((auth::socket::getExpiry() - time(NULL)) / 86400));
#endif
                g_pointers = std::make_unique<pointers>();
                g_discord->init();
                srand(time(NULL));
                SetWindowTextA(g_pointers->m_game_window, titles[rand() % titles.size()].c_str());
                if (*g_pointers->m_game_state != eGameState::Playing) {
                    LOG(Warn, "Game has not finished loading...");
                    while (*g_pointers->m_game_state != eGameState::Playing) {
#ifndef DEV
                        auth::antidebug::run();
#endif
                        std::this_thread::sleep_for(1ms);
                    }
                }
                auto start_time{ std::chrono::high_resolution_clock::now() };
                flash_taskbar(g_pointers->m_game_window, 0);
                g_fiber_pool.create_fibers();
                g_invoker = std::make_unique<Invoker>();
                g_invoker->cache_handlers();
                g_interface = std::make_unique<Framework::Interface>();
                g_renderer = std::make_unique<Renderer>();
                g_menu = std::make_shared<menu>();
                g_fiber_manager.add("Menu::Tick", &menu::tick);
                g_dx_fiber_manager.add("Menu::DXTick", &menu::dx_tick);
                script_manager::Init(std::make_unique<Script>(&menu::tick));
                g_notifications = std::make_unique<notifications>(); 
                g_hooking = std::make_unique<Hooking>();
                g_hooking->Hook();   
                g_interface->add_tooltips_from_file(fs::path("C:\\Native\\Tooltips.txt"));
                add_features_once();

                auto end_time{ std::chrono::high_resolution_clock::now() };
                auto elapsed_time{ std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() };

                LOG(Info, "Startup took: {}ms", elapsed_time);
                g_notifications->send(std::format("Welcome, {}!", g_pointers->m_get_player_name(PLAYER::PLAYER_ID())), "This is a safe space from patek.");
                g_interface->load_settings_on_inject(fs::path("C:\\Native\\Settings.json").string());
                g_interface->load_variables_from_json(g_interface->m_default_theme_name);
                //config::load_options_from_json(fs::path(std::getenv(("appdata"))).append((BRANDING"\\config.json")).string());

                while (g_Running) {
                    if (GetAsyncKeyState(VK_DELETE))
                        g_Running = false;
#ifndef DEV
                    auth::antidebug::run();
#endif
                    std::this_thread::sleep_for(10ms);
                }
#ifndef DEV
                VIRTUALIZER_TIGER_WHITE_END
#endif
                detach();
                FreeLibraryAndExitThread(g_Module, 0);
                }, nullptr, 0, nullptr);
        }
    }
}
