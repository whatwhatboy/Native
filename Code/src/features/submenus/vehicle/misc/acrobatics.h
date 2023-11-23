#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base::acrobatics {
	namespace settings {
		std::vector<const char*> type = { "Backflip", "Frontflip", "Kickflip", "Slingshot", "Leap", "Slow Flip", "Swipe (L)", "Swipe (R)", "Dash" };
		int pos{ 0 };
		float force{ 7.0 };
		bool reverse{ false };
		bool randomize{ false };
		bool on_horn{ false };
	}
	void start() {
		Vector3 force{ settings::reverse ? -6.0f : 6.0f, 0, 2.0f };
		Vector3 force2{ settings::reverse ? -9.0f : 9.0f, 0, -2.0f };
		Vector2 force3{ settings::reverse ? -10.0f : 10.0f, 20.0f };
		Vector2 force4{
			settings::reverse ? 0 - ENTITY::GET_ENTITY_FORWARD_X(g_utils->vehicle()) * settings::force : 0 + ENTITY::GET_ENTITY_FORWARD_X(g_utils->vehicle()) * settings::force,
			settings::reverse ? 0 - ENTITY::GET_ENTITY_FORWARD_Y(g_utils->vehicle()) * settings::force : 0 + ENTITY::GET_ENTITY_FORWARD_Y(g_utils->vehicle()) * settings::force
		};
		float dive_force{ 30.0f };
		float lateral_force{ 5.0f };
		float forward_force{ 80.0f };
		float kick_force{ 50.0f };
		switch (settings::pos) {
		case 0:
			for (int i = 0; i < 3; i++)
				ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, 0, 0, force.x, force.y, force.z, 0, true, true, true, true, false, true);
			break;
		case 1:
			for (int i = 0; i < 3; i++)
				ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, 0, 0, force2.x, force2.y, force2.z, 0, true, true, true, true, false, true);
			break;
		case 2:
			ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, 0, 0, force3.x, force3.y, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
			break;
		case 3:
			ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, 0, 0, settings::reverse ? -settings::force : settings::force, 0, 0, 0, true, true, true, true, false, true);
			break;
		case 4:
			ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), 1, force4.x, force4.y, settings::force, 0, 0, 0, 1, 0, 1, 1, 1, 1);
			break;
		case 5:
			ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, 0, 0, dive_force, 0, 0, 0, true, true, true, true, false, true);
			ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, 0, 0, 0, lateral_force, 0, 0, true, true, true, true, false, true);
			break;
		case 6:
			ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, -settings::force, 0, 0, 0, 0, 0, true, true, true, true, false, true);
			break;
		case 7:
			ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, settings::force, 0, 0, 0, 0, 0, true, true, true, true, false, true);
			break;
		case 8:
			ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, 0, forward_force, 0, 0, kick_force, 0, true, true, true, true, false, true);
			break;
		}
	}
	void random() {
		if (!settings::randomize) return;
		if (!ENTITY::IS_ENTITY_IN_AIR(g_utils->vehicle())) {
			if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(g_utils->vehicle())) {
				settings::pos = g_utils->get_random_value_in_range<int>(0, sizeof(settings::type) / sizeof(settings::type[0]));
				start();
			}
		}
	}
	void on_horn() {
		if (PLAYER::IS_PLAYER_PRESSING_HORN(g_utils->self_id()) && settings::on_horn)
			start();
	}
}
