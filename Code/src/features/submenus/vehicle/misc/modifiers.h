#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base {
	namespace negitive_torque {
		bool enabled{ false };
		float value{ 1.0 };
		void init() {
			if (!enabled) return;
			VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(g_utils->vehicle(), -value);
		}
		void on_disable() {
			VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(g_utils->vehicle(), 1.0);
		}
	}

	namespace bypass_max_speed {
		bool enabled{ false };
		float og_max_speed{ 0 };
		void init() {
			if (!enabled) return;
			if (og_max_speed == 0) {
				og_max_speed = VEHICLE::GET_VEHICLE_ESTIMATED_MAX_SPEED(g_utils->vehicle());
			}
			else {
				ENTITY::SET_ENTITY_MAX_SPEED(g_utils->vehicle(), 9999999.f);
			}
		}
		void on_disable() {
			ENTITY::SET_ENTITY_MAX_SPEED(g_utils->vehicle(), og_max_speed);
			og_max_speed = 0;
		}
	}
}
