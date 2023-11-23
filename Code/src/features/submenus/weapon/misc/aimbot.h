#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base::aimbot {
	namespace settings {
		bool smoothing{ true };
		float smoothing_speed{ 6.2 };
		float distance{ 1000 };
		bool only_enemy{ false };

		bool only_players{ false };
		bool always_lockon{ false };
	}
	bool enabled{ false };
	Vector3 aim_lock;
	Vector2 new_mouse_coords;
	void init() {
		if (!enabled) return;

		g_interface->m_aimbot_is_on = true;
		float fov{ g_interface->m_aimbot_fov };
		for (auto ped : g_pools->peds()) {
			if (!ENTITY::IS_ENTITY_DEAD(ped, 0)) {
				int relation{ PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped, g_utils->self()) };
				int type{ PED::GET_PED_TYPE(ped) };
				auto world_position{ g_utils->coords(ped) };

				if (SYSTEM::VDIST2(g_utils->coords().x, g_utils->coords().y, g_utils->coords().z, world_position.x, world_position.y, world_position.z) > (settings::distance * settings::distance))
					continue;

				if (PED::IS_PED_A_PLAYER(ped) && !settings::only_enemy)
					goto aim;
				else if (relation == 4 || relation == 5)
					goto aim;
				else if (!PED::IS_PED_A_PLAYER(ped) && !settings::only_enemy)

				aim:
				{
					if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(g_utils->self(), ped, 17))
						continue;

					if (settings::only_players && !PED::IS_PED_A_PLAYER(ped)) return;

					aim_lock = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(ped, PED::GET_PED_BONE_INDEX(ped, 0x796E));
					if ((aim_lock.x != 0) && (aim_lock.y != 0) && (aim_lock.z != 0))  {
						Vector2 screen_dimensions, movement;
						GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(aim_lock.x, aim_lock.y, aim_lock.z, &screen_dimensions.x,&screen_dimensions.y);
						if ((screen_dimensions.x >= 0) && (screen_dimensions.y >= 0))
						{
							auto& io = ImGui::GetIO();
							ImVec2 center(io.DisplaySize.x / 2.f, io.DisplaySize.y / 2.f);
							screen_dimensions.x *= io.DisplaySize.x;
							screen_dimensions.y *= io.DisplaySize.y;

							if (screen_dimensions.x > center.x)  { 
								movement.x = -(center.x - screen_dimensions.x);
								if (movement.x + center.x > center.x * 2)
									movement.x = 0;
							}
							else { 
								movement.x = screen_dimensions.x - center.x;
								if (movement.x + center.x < 0)
									movement.x = 0;
							}

							if (screen_dimensions.y > center.y) {
								movement.y = -(center.y - screen_dimensions.y);
								if (movement.y + center.y > center.y * 2)
									movement.x = 0;
							}
							else {
								movement.y = screen_dimensions.y - center.y;
								if (movement.y + center.y < 0)
									movement.y = 0;
							}

							if (sqrt(pow(movement.x, 2) + pow(movement.y, 2)) < fov) { 
								fov = sqrt(pow(movement.x, 2) + pow(movement.y, 2));
								new_mouse_coords.x = movement.x;
								new_mouse_coords.y = movement.y;
							}
						}
					}
				}
			}
		}

		if (PLAYER::IS_PLAYER_FREE_AIMING(g_utils->self_id()) || settings::always_lockon) {
			static bool update_time_now{ true };
			static std::chrono::system_clock::time_point current_time;

			if (update_time_now){
				current_time = std::chrono::system_clock::now();
				update_time_now = false;
			}

			std::chrono::duration<double> elapsed_time{std::chrono::system_clock::now() - current_time};
			if (elapsed_time.count() > 0.f) {
				INPUT mouse;
				mouse.type = INPUT_MOUSE;
				mouse.mi.dwFlags = MOUSEEVENTF_MOVE;

				mouse.mi.dx =  new_mouse_coords.x / (settings::smoothing ? settings::smoothing_speed : 2);
				mouse.mi.dy = new_mouse_coords.y / (settings::smoothing ? settings::smoothing_speed : 2);
				SendInput(1, &mouse, sizeof(mouse));

				new_mouse_coords.x = 0, new_mouse_coords.y = 0;
				update_time_now = true; 
			}
		}
	}
	void on_disable() {
		g_interface->m_aimbot_is_on = false;
	}
}
