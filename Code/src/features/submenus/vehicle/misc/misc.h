#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base {
	namespace shaky_shell {
		bool enabled{ false };
		float multiplier{ 5000.f };
		void init() {
			if (!enabled) return;
			VEHICLE::SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER(multiplier);
		}
		void on_disable() {
			VEHICLE::SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER(1.0);
		}
	}

	namespace auto_flip {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			if (!ENTITY::IS_ENTITY_UPRIGHT(g_utils->vehicle(), 120)) {
				auto rotation{ ENTITY::GET_ENTITY_ROTATION(g_utils->vehicle(), false) };
				ENTITY::SET_ENTITY_ROTATION(g_utils->vehicle(), 0, rotation.y, rotation.z, 0, 1);
			}
		}
	}
	namespace acceleration {
		namespace torque {
			bool enabled{ false };
			float value{ 5.0 };
		}
		bool enabled{ false };
		float speed{ 2.5 };
		void init() {
			if (!enabled) return;
			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(g_utils->vehicle(), -1, 1) == g_utils->self()) {
				if (g_utils->control_pressed(pressed, 71) && !VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(g_utils->vehicle())))
					if (VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(g_utils->vehicle())) || VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(g_utils->vehicle()))
						ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), 1, 0.0, (float)(((speed - 1.0f) * 2.1f) / 69.0f), 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
			}
		}
		void init2() {
			if (!enabled) return;
			VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(g_utils->vehicle(), torque::value);
		}
		void on_disable() {
			VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(g_utils->vehicle(), 1.0);
		}
	}
	namespace explode_on_impact {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(g_utils->vehicle()))
				VEHICLE::EXPLODE_VEHICLE(g_utils->vehicle(), true, false);
		}
	}
	namespace invert_controls {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			VEHICLE::SET_INVERT_VEHICLE_CONTROLS(g_utils->vehicle(), true);
		}
		void on_disable() {
			VEHICLE::SET_INVERT_VEHICLE_CONTROLS(g_utils->vehicle(), false);
		}
	}
	namespace slipply_wheels {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(g_utils->vehicle(), true);
		}
		void on_disable() {
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(g_utils->vehicle(), false);
		}
	}
	namespace drive_underwater {
		bool enabled{ false };
		void init() {
			if (g_utils->cvehicle() && enabled) {
				g_utils->cvehicle()->m_navigation->m_damp->m_water_collision = 0;
			}
		}
		void on_disable() {
			if (g_utils->cvehicle()) {
				g_utils->cvehicle()->m_navigation->m_damp->m_water_collision = 1;
			}
		}
	}
	namespace headlight_multiplier {
		bool enabled{ false };
		float value{ 1.0 };
		void init() {
			if (!enabled) return;
			VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(g_utils->vehicle(), value);
		}
		void on_disable() {
			VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(g_utils->vehicle(), 1.0);
		}
	}
	namespace drift_tires {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			VEHICLE::SET_DRIFT_TYRES(g_utils->vehicle(), true);
		}
		void on_disable() {
			VEHICLE::SET_DRIFT_TYRES(g_utils->vehicle(), false);
		}
	}
	namespace mute_sirens {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(g_utils->vehicle(), true);
		}
		void on_disable() {
			VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(g_utils->vehicle(), false);
		}
	}

	namespace burned {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			ENTITY::SET_ENTITY_RENDER_SCORCHED(g_utils->vehicle(), true);
		}
		void on_disable() {
			ENTITY::SET_ENTITY_RENDER_SCORCHED(g_utils->vehicle(), false);
		}
	}

	namespace instant_brake {
		bool enabled{ false };
		void init() {
			if (!enabled) return;

			if (g_utils->control_pressed(just_pressed, eControllerInputs::INPUT_VEH_BRAKE)) {
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(g_utils->vehicle(), 0);
			}
		}
	}

	namespace break_deluxo {
		bool enabled{ false };
		void init() {
			if (!enabled) return;

			VEHICLE::SET_SPECIAL_FLIGHT_MODE_TARGET_RATIO(g_utils->vehicle(), 0.7);
		}
	}

	namespace always_extend_mk1_wings {
		bool enabled{ false };
		void init() {
			if (!enabled) return;

			VEHICLE::SET_GLIDER_ACTIVE(g_utils->vehicle(), true);
		}
	}

	namespace easy_to_land {
		bool enabled{ false };
		void init() {
			if (!enabled) return;;

			VEHICLE::SET_BIKE_EASY_TO_LAND(g_utils->vehicle(), true);
		}
		void on_disable() {
			VEHICLE::SET_BIKE_EASY_TO_LAND(g_utils->vehicle(), false);
		}
	}

	namespace moving_plate {
		namespace settings {
			float delay{ 200 };
			str text{ "Native" };
		}
		bool enabled{ false };
		void tick() {
			if (!enabled) return;
			static int increment{ 0 };

			g_utils->timed_function(settings::delay, [] {
				if (increment > strlen(settings::text.c_str()))
					increment = 0;

				char temp[8];
				for (int i{ 0 }; i < 8; i++)
					temp[i] = settings::text[i + increment];

				increment++;
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(g_utils->vehicle(), temp);
			});

		}
	}

	namespace vehicle_scale {
		namespace settings {
			float scale{ 0.5 };
		}
		bool enabled{};
		std::map<Vehicle, Vector3> sizes;
		bool equals(Vector3 vec1, Vector3 vec2) {
			return abs(vec1.x - vec2.x) < 0.01f && abs(vec1.y - vec2.y) < 0.01f && abs(vec1.z - vec2.z) < 0.01f;
		}
		void tick() {
			if (!enabled) return;

			g_utils->set_vehicle_scale(g_utils->vehicle(), settings::scale);
			
		}
		void on_disable() {
			sizes.clear();
		}
	}

	namespace rapid_fire_vehicle_weapons {
		bool enabled{};
		void tick() {
			if (!enabled) return;

			if (g_utils->control_pressed(pressed, 68) && g_utils->in_vehicle()) {
				VEHICLE::SET_VEHICLE_FIXED(g_utils->vehicle());
			}
		}
	}

}
