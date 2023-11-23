#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base {
	namespace horn_boost {
		namespace settings {
			bool smooth{ false };
			std::vector<const char*> smooth_type = { "Force", "Forward Speed" }; int smoothPos{ 0 };
			bool only_on_ground{ false };
			std::vector<const char*> boostType = { "Forward", "Backward", "Jump" };
			int boost_pos{ 0 };
			float speed{ 100 };
			float boost_power{ 1.0f };
		}
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			if (!PLAYER::IS_PLAYER_PRESSING_HORN(g_utils->self_id())) return;
			if (settings::only_on_ground && !VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(g_utils->vehicle())) return;

			if (settings::boost_pos == 0 || settings::boost_pos == 1) {
				if (settings::smooth && ENTITY::GET_ENTITY_SPEED(g_utils->vehicle()) < settings::speed) {
					switch (settings::smoothPos) {
					case 0:
						ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), 1, 0.0, (float)(((settings::boost_power - 1.0f) * 2.1f) / 69.0f), 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
						break;
					case 1:
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(g_utils->vehicle(), settings::boost_pos == 0 ? ENTITY::GET_ENTITY_SPEED(g_utils->vehicle()) + settings::boost_power : -ENTITY::GET_ENTITY_SPEED(g_utils->vehicle()) - settings::boost_power);
						break;
					}
				}
				else
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(g_utils->vehicle(), settings::boost_pos == 0 ? settings::speed : -settings::speed);
			}
			if (settings::boost_pos == 2)
				ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(g_utils->vehicle()), 0 + ENTITY::GET_ENTITY_FORWARD_Y(g_utils->vehicle()), 0.5f, 0, 0, 0, 1, 0, 1, 1, 1, 1);
		}

	}
}
