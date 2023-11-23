#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/icon_button.h"
#include "src/framework/option_types/button.h"

namespace Base::submenus::self {
    std::vector<std::pair<const char*, const char*>> clipsets_data = {
        {"Ballistic", "ANIM_GROUP_MOVE_BALLISTIC"},
        {"Lemar Alley", "ANIM_GROUP_MOVE_LEMAR_ALLEY"},
        {"Trash Fast Turn", "clipset@move@trash_fast_turn"},
        {"Fast Runner", "FEMALE_FAST_RUNNER"},
        {"Garbageman", "missfbi4prepp1_garbageman"},
        {"Franklin Fire", "move_characters@franklin@fire"},
        {"Jimmy Slow", "move_characters@Jimmy@slow@"},
        {"Michael Fire", "move_characters@michael@fire"},
        {"Flee", "move_f@flee@a"},
        {"Scared", "move_f@scared"},
        {"Sexy", "move_f@sexy@a"},
        {"Heist Lester", "move_heist_lester"},
        {"Injured Generic", "move_injured_generic"},
        {"Lester Cane Up", "move_lester_CaneUp"},
        {"Bag", "move_m@bag"},
        {"Bail Bond", "MOVE_M@BAIL_BOND_NOT_TAZERED"},
        {"Bail Bond Tazered", "MOVE_M@BAIL_BOND_TAZERED"},
        {"Brave", "move_m@brave"},
        {"Casual", "move_m@casual@d"},
        {"Moderated Drunk", "move_m@drunk@moderatedrunk"},
        {"Moderated Drunk 2", "MOVE_M@DRUNK@MODERATEDRUNK"},
        {"Moderately Drunk", "MOVE_M@DRUNK@MODERATEDRUNK_HEAD_UP"},
        {"Slightly drunk", "MOVE_M@DRUNK@SLIGHTLYDRUNK"},
        {"Very Drunk", "MOVE_M@DRUNK@VERYDRUNK"},
        {"Fire", "move_m@fire"},
        {"Gangster Var E", "move_m@gangster@var_e"},
        {"Gangster Var F", "move_m@gangster@var_f"},
        {"Gangster Var I", "move_m@gangster@var_i"},
        {"Jog", "move_m@JOG@"},
        {"Prison Gaurd", "MOVE_M@PRISON_GAURD"},
        {"One", "MOVE_P_M_ONE"},
        {"Briefcase", "MOVE_P_M_ONE_BRIEFCASE"},
        {"Janitor", "move_p_m_zero_janitor"},
        {"Slow", "move_p_m_zero_slow"},
        {"Ped Bucket", "move_ped_bucket"},
        {"Ped Crouched", "move_ped_crouched"},
        {"Ped Mop", "move_ped_mop"},
        {"Femme Male", "MOVE_M@FEMME@"},
        {"Femme Female", "MOVE_F@FEMME@"},
        {"Gangster Male", "MOVE_M@GANGSTER@NG"},
        {"Gangster Female", "MOVE_F@GANGSTER@NG"},
        {"Posh Male", "MOVE_M@POSH@"},
        {"Posh Female", "MOVE_F@POSH@"},
        {"Tough Guy Male", "MOVE_M@TOUGH_GUY@"},
        {"Tough Guy Female", "MOVE_F@TOUGH_GUY@"}
    };
    std::vector<std::pair<const char*, const char*>> weapon_animations = {
        {"Default", "Default"},
        {"First Person", "FirstPerson"},
        {"Gangster", "Gang1H"},
        {"Hillbilly", "Hillbilly"},
    };
    const char* selected{};
    const char* selected2{};
    const char* selected3{ "Default" };
    void change(const char* walkstyle, bool weapon = false) {
        while (!STREAMING::HAS_ANIM_SET_LOADED(walkstyle)) {
            STREAMING::REQUEST_ANIM_SET(walkstyle);
            fiber::current()->wait();
        }
        weapon ? PED::SET_PED_WEAPON_MOVEMENT_CLIPSET(g_utils->self(), walkstyle) : PED::SET_PED_MOVEMENT_CLIPSET(g_utils->self(), walkstyle, 1);
    }
	void clipsets() {
        draw->submenu_second("Movement", "movement_clipsets", [] {
            for (int i = 0; i < clipsets_data.size(); i++) {
                if (clipsets_data[i].second == selected) {
                    add_option<Framework::icon_button>(clipsets_data[i].first, "", "On", [=] {
                        g_fiber_pool.queue([=] {
                            change(clipsets_data[i].second);
                        });
                        selected = clipsets_data[i].second;
                    });
                }
                else {
                    add_option<Framework::button>(clipsets_data[i].first, "", [=] {
                        g_fiber_pool.queue([=] {
                            change(clipsets_data[i].second);
                        });
                        selected = clipsets_data[i].second;
                    });
                }
            }
        });
        draw->submenu_second("Weapon", "weapon_clipset", [] {
            for (int i = 0; i < clipsets_data.size(); i++) {
                if (clipsets_data[i].second == selected2) {
                    add_option<Framework::icon_button>(clipsets_data[i].first, "", "On", [=] {
                        g_fiber_pool.queue([=] {
                            change(clipsets_data[i].second, true);
                            });
                        selected2 = clipsets_data[i].second;
                        });
                }
                else {
                    add_option<Framework::button>(clipsets_data[i].first, "", [=] {
                        g_fiber_pool.queue([=] {
                            change(clipsets_data[i].second, true);
                            });
                        selected2 = clipsets_data[i].second;
                        });
                }
            }
            });
        draw->submenu_second("Weapon Animation", "weapon_animation_clipset", [] {
            for (int i = 0; i < weapon_animations.size(); i++) {
                auto animation_action = [=, &weapon_animations = weapon_animations[i]] {
                    g_fiber_pool.queue([=] {
                        WEAPON::SET_WEAPON_ANIMATION_OVERRIDE(g_utils->self(), rage::joaat(weapon_animations.second));
                    });
                    selected3 = weapon_animations.second;
                };
                weapon_animations[i].second == selected3 ? add_option<Framework::icon_button>(weapon_animations[i].first, "", "On", animation_action) : add_option<Framework::button>(weapon_animations[i].first, "", animation_action);
            }
        });
	}
}
