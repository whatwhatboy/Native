#pragma once
#include "src/core/script/drawing/drawing.h"
#include "noclip.h"
#include <src/memory/memory.h>
#include "src/framework/option_types/button.h"
#include "model_changer_table.h"
#include "src/hooking/hooking.h"
#include <unordered_set>

namespace Base::submenus::self {

    bool only_show_named{ false };
    std::string search_model_changer;
    std::unordered_set<uint32_t> named_hashes;

    struct saved_weapon {
        Hash hash;
        std::vector<Hash> components;
        int ammo;
    };
    std::vector<saved_weapon> saved_weapons;
    bool save_weapons{ true };

    std::string get_name_from_hash(uint32_t hash) {
        for (auto& model : model_changer_table) {
            uint32_t modelHash = rage::joaat(model);
            if (hash == modelHash)
                return model;
        }
        return std::to_string(hash);
    }
    void initialize_named_hashes() {
        named_hashes.clear();
        for (const auto& model : model_changer_table) {
            named_hashes.insert(rage::joaat(model));
        }
    }

    bool is_named(uint32_t hash) {
        return named_hashes.find(hash) != named_hashes.end();
    }

    void copy_to_clipboard(const std::string& text) {
        if (OpenClipboard(nullptr)) {
            HGLOBAL clip_buffer;
            EmptyClipboard();

            // Allocate memory for the text and copy the data
            clip_buffer = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
            if (clip_buffer) {
                char* buffer = static_cast<char*>(GlobalLock(clip_buffer));
                if (buffer) {
                    strcpy_s(buffer, text.size() + 1, text.c_str());
                    GlobalUnlock(clip_buffer);
                    SetClipboardData(CF_TEXT, clip_buffer);
                }
            }

            CloseClipboard();
        }
    }
    void model_changer() {
        if (!cached) {
            initialize_named_hashes();
            just_entered_model_changer = true;
            draw->text("Getting Peds");
        }

        if (cached) {
            add_option<Framework::keyboard>("Search", "", &search_model_changer);
            draw->toggle("Save Weapons", &save_weapons);
            draw->seperator("List");

            for (auto& ped_hash : model_changer_table) {
                u32 hash{ rage::joaat(ped_hash) };

                if (!g_utils->has_string_attached(ped_hash, "slod")) {
                    draw->button(ped_hash, [=] {
                        g_fiber_pool.queue([=] {
                            std::vector<Hash> component_list;
                            while (!STREAMING::HAS_MODEL_LOADED(hash)) {
                                STREAMING::REQUEST_MODEL(hash);
                                fiber::current()->wait();
                            }

                            if (save_weapons) {
                                auto hashes{ g_utils->get_hash_list_from_hash_table(*(u32*)(g_pointers->m_weapon_components.m_count) - 1, g_pointers->m_weapon_components.m_list) };
                                for (int i = 0; i < sizeof(all_weapons_hash); i++)
                                    if (WEAPON::HAS_PED_GOT_WEAPON(g_utils->self(), all_weapons_hash[i], 0)) {
                                        for (u32 component : hashes) {
                                            if (WEAPON::IS_PED_WEAPON_COMPONENT_ACTIVE(g_utils->self(), all_weapons_hash[i], component))
                                                component_list.push_back(component);
                                        }
                                        saved_weapons.push_back({ all_weapons_hash[i], component_list, WEAPON::GET_AMMO_IN_PED_WEAPON(g_utils->self(), all_weapons_hash[i]) });
                                    }
                            }

                            PLAYER::SET_PLAYER_MODEL(g_utils->self_id(), hash);
                            fiber::current()->wait();
                            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
                            for (int i = 0; i < 12; i++)
                                PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), i, PED::GET_PED_DRAWABLE_VARIATION(g_utils->self(), i), PED::GET_PED_TEXTURE_VARIATION(g_utils->self(), i), PED::GET_PED_PALETTE_VARIATION(g_utils->self(), i));

                            if (save_weapons)
                                for (auto weapon : saved_weapons) {
                                    WEAPON::GIVE_DELAYED_WEAPON_TO_PED(g_utils->self(), weapon.hash, weapon.ammo, false);
                                    for (uint32_t component : weapon.components)
                                        if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(hash, component))
                                            WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(g_utils->self(), hash, component);
                                }

                            saved_weapons.clear();
                            component_list.clear();
                            });
                        });
                }
                
            }
        }
    }

}
