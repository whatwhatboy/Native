#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	namespace settings {
		float delay{ 0 };
		bool disable_shooting{ false };
		bool disable_when_reloading{ false };
		bool only_when_aiming{ false };
		int bullets{ 1 };
		const char* type[2] = { "2_lazers", "homing" };
		int pos{ 0 };
	}

    namespace util {
        std::vector<int32_t> get_vehicles() {
            const int get = 100;
            int nearby[get * 2 + 2] = { get * 2 + 2 };
            auto count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), (Any*)&nearby);
            std::vector<int32_t> total;

            for (int i = 0; i < count; i++) {
                auto v = nearby[i * 2 + 2];
                total.push_back(v);
            }

            return total;
        }

        std::vector<int32_t> get_peds() {
            const int get = 100;
            int nearby[get * 2 + 2] = { get * 2 + 2 };
            auto count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), (Any*)&nearby, PLAYER::PLAYER_PED_ID());
            std::vector<int32_t> total;

            for (int i = 0; i < count; i++) {
                auto p = nearby[i * 2 + 2];
                total.push_back(p);
            }

            return total;
        }

        bool control_pressed(int control) {
            return PAD::IS_CONTROL_PRESSED(2, control);
        }

        bool key_press(std::uint16_t keycode, bool only_once = false) {
            if (keycode == VK_SHIFT || keycode == VK_ESCAPE || keycode == 0x5C) {
                return false;
            }
            if (only_once) {
                if (GetAsyncKeyState(keycode) & 1) {
                    return true;
                }
            }
            else {
                if (GetAsyncKeyState(keycode) & 0x8000) {
                    return true;
                }
            }
            return false;
        }
    }

    bool enabled{ false };

    void no_clip() {
        if (!ENTITY::IS_ENTITY_PLAYING_ANIM(g_utils->self(), "missbigscore2aig_5", "push_trolly_walk", 0)) {
            while (!STREAMING::HAS_ANIM_DICT_LOADED("missbigscore2aig_5")) {
                STREAMING::REQUEST_ANIM_DICT("missbigscore2aig_5");
                fiber::current()->wait();
            }
            TASK::TASK_PLAY_ANIM(g_utils->self(), "missbigscore2aig_5", "push_trolly_walk", 8.0f, 0.0f, -1, 0, 0, 0, 0, 0);
        }
        auto cam{ g_utils->cam.get() };
        auto self_coords{ g_utils->coords() };
        auto start_dist{ std::distance(&cam.coords, &self_coords) };
        auto new_coords{ cam.direction * 1.5 };

        ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_utils->self(), self_coords.x, self_coords.y, self_coords.z, true, true, true);
        if (util::key_press(0x57) || util::control_pressed(32)) {
            auto new_c{ self_coords + new_coords };
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_utils->self(), new_c.x, new_c.y, new_c.z, true, true, true);
        }
        auto old_rotation{ ENTITY::GET_ENTITY_ROTATION(g_utils->self(), 0) };
        ENTITY::SET_ENTITY_ROTATION(g_utils->self(), cam.rotation.x, cam.rotation.y, cam.rotation.z, 2, 1);
    }

    float get_new_rotation = 0.0;

    void iron_man::on_disable() {
        TASK::CLEAR_PED_TASKS_IMMEDIATELY(g_utils->self());
    }
	void iron_man::tick() {
        if (!m_enabled) return;

        auto cam{ g_utils->cam.get() };
        if (m_enabled) {
            no_clip();
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25)) {
                HUD::DISPLAY_SNIPER_SCOPE_THIS_FRAME();
                settings::pos = 1;
            }
            else {
                settings::pos = 0;
            }
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 24) && !g_interface->m_opened && (settings::pos == 0)) {
                auto weapon_entity{ WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(g_utils->self(), 0) };
                auto left_hand{ g_utils->get_ped_bone_coords(SKEL_L_Hand) };
                auto right_hand{ g_utils->get_ped_bone_coords(SKEL_R_Hand) };
                auto start_distance{ g_math->distance(cam.coords, g_utils->coords()) + 0.25 };
                auto end_distance{ g_math->distance(cam.coords, g_utils->coords()) + 1000.0 };
                auto multiply{ cam.direction * end_distance };
                WEAPON::REQUEST_WEAPON_ASSET(1198256469, 31, 0);
                g_fiber_pool.queue([=] {
                    while (!WEAPON::HAS_WEAPON_ASSET_LOADED(1198256469))
                        fiber::current()->wait();
                    });
                g_utils->timed_function(100, [&] {
                    MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(left_hand.x, left_hand.y - 0.2, left_hand.z,
                    left_hand.x + multiply.x,
                    left_hand.y + multiply.y,
                    left_hand.z + multiply.z,
                    250, 1, 1198256469, g_utils->self(), 1, 0, -1.0);
                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(right_hand.x, right_hand.y + 0.2, right_hand.z,
                    right_hand.x + multiply.x,
                    right_hand.y + multiply.y,
                    right_hand.z + multiply.z,
                    250, 1, 1198256469, g_utils->self(), 1, 0, -1.0);
                });

            }
            if (settings::pos == 1) {
                auto get_nearby_vehs = util::get_vehicles();
                auto get_nearby_peds = util::get_peds();
                get_nearby_vehs.insert(get_nearby_vehs.end(), get_nearby_peds.begin(), get_nearby_peds.end());
                for (auto target : get_nearby_vehs) {
                    if (target && ENTITY::DOES_ENTITY_EXIST(target) && !ENTITY::IS_ENTITY_DEAD(target, 0) && (VEHICLE::GET_VEHICLE_BODY_HEALTH(target) > 0)) {
                        float screen_x, screen_y;
                        BOOL on_screen{ GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(target, true).x, ENTITY::GET_ENTITY_COORDS(target, true).y, ENTITY::GET_ENTITY_COORDS(target, true).z, &screen_x, &screen_y) };
                        if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 24) && !g_interface->m_opened && on_screen) {
                            auto coords{ g_utils->coords(target) };
                            auto weapon_entity{ WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(g_utils->self(), 0) };
                            auto left_hand{ g_utils->get_ped_bone_coords(SKEL_L_Hand) };
                            auto right_hand{ g_utils->get_ped_bone_coords(SKEL_R_Hand) };
                            auto start_distance{ g_math->distance(cam.coords, g_utils->coords()) + 0.25 };
                            auto end_distance{ g_math->distance(cam.coords, g_utils->coords()) + 1000.0 };
                            auto multiply{ cam.direction * end_distance };
                            WEAPON::REQUEST_WEAPON_ASSET(MISC::GET_HASH_KEY("WEAPON_RPG"), 31, 0);
                            g_fiber_pool.queue([=] {
                                while (!WEAPON::HAS_WEAPON_ASSET_LOADED(MISC::GET_HASH_KEY("WEAPON_RPG")))
                                    fiber::current()->wait();
                                });
                            g_utils->timed_function(100, [&] {
                                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(left_hand.x, left_hand.y, left_hand.z,
                                coords.x,
                                coords.y,
                                coords.z,
                                250, 1, MISC::GET_HASH_KEY("WEAPON_RPG"), g_utils->self(), 1, 0, -1.0);
                            MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(right_hand.x, right_hand.y, right_hand.z,
                                coords.x,
                                coords.y,
                                coords.z,
                                250, 1, MISC::GET_HASH_KEY("WEAPON_RPG"), g_utils->self(), 1, 0, -1.0);
                               });
                        }
                    }
                }
            }
        }
	}
}
