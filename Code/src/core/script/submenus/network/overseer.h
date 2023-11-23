#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/keyboard.h"
#include "src/framework/option_types/button.h"
#include <src/framework/option_types/break.h>
#include <src/framework/option_types/submenu.h>
#include "src/features/utils/rid_utils.h"

namespace Base::submenus::network::overseer {
    using namespace Framework;
    using json = nlohmann::json;
    void add_player(const char* itemName, int itemValue) {
        std::string filePath = "C:\\Native\\Overseer\\players.json";
        if (!std::ifstream(filePath)) {
            json initialData = {
                {"items", json::array()}
            };
            std::ofstream initialOutputFile(filePath);
            initialOutputFile << std::setw(4) << initialData << std::endl;
            initialOutputFile.close();
        }

        std::ifstream inputFile(filePath);
        json data;
        inputFile >> data;
        inputFile.close();

        for (const auto& item : data["items"]) {
            std::string itemName2 = item["name"];
            int itemValue2 = item["rid"];

            if (item.contains("name") && item.contains("rid")) {
                if (itemName == itemName2) return;
            }
        }

        json newItem = {
            {"name", itemName},
            {"rid", itemValue}
        };

   
        data["items"].push_back(newItem);

        std::ofstream outputFile(filePath);
        outputFile << std::setw(4) << data << std::endl;
        outputFile.close();
    }
    vector_pair_double<str, int> famous_people {
        {"Sonny Uploads", 214048684},
        { "RealDarkViperAU", 64839021 },
        { "MrBossFTW", 26204131 },
        { "IXpertThief", 21986863 },
        { "IShowSpeed", 115038565 },
    };
	void main() {
        draw->submenu_second("Add Player", "overseer_add_player", [] {
            draw->submenu_second("Friends", "overseer_friends", [] {
                for (u32 i = 0; i < g_pointers->m_friend_registry->m_friend_count; i++) {
                    draw->button(g_pointers->m_friend_registry->get(i)->m_name, [=] {
                        add_player(g_pointers->m_friend_registry->get(i)->m_name, g_pointers->m_friend_registry->get(i)->m_rockstar_id);
                    });

                }
            });
            draw->submenu_second("In Session", "overseer_in_session", [] {
                for (auto i = 0; i < 31; i++) {
                    if (auto player = g_pointers->m_get_net_player(i); player && player->is_valid()) {
                        draw->button(player->get_name(), [=] {
                            add_player(player->get_name(), player->get_net_data()->m_gamer_handle.m_rockstar_id);
                        });
                    }
                }
            });
            draw->submenu_second("Known/Famous", "overseer_famous", [] {
                for (auto& person : famous_people) {
                    draw->button(person.first, [=] {
                        add_player(person.first.c_str(), person.second);
                    });
                }
            });
        });
        add_option(seperator("Players"));
        if (!g_file_utils->does_file_exist("C:\\Native\\Overseer\\players.json")) return;
        std::ifstream inputFile("C:\\Native\\Overseer\\players.json");
        json data;
        inputFile >> data;
        inputFile.close();

        for (const auto& item : data["items"]) {
            std::string itemName = item["name"];
            int itemValue = item["rid"];

            if (item.contains("name") && item.contains("rid")) {
                std::string name{ itemName };
                //if (rid_utils::is_rid_online(itemValue))
                //    name.append(" [Online]");
                draw->submenu_second(name.c_str(), name.c_str() + std::to_string(itemValue), [=] {
                    draw->button("Join", [=] {
                        rid_utils::rid_join(itemValue);
                    });
                    draw->button("Invite", [=] {
                        rid_utils::invite_player(itemValue);
                    });
                });
            }
        }
        
	}
}
