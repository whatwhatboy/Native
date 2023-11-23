#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"

namespace Base {
	namespace take_less_damage {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			PED::SET_PED_SUFFERS_CRITICAL_HITS(g_utils->vehicle(), false);
		}
		void on_disable() {
			PED::SET_PED_SUFFERS_CRITICAL_HITS(g_utils->vehicle(), true);
		}
	}
	namespace upperbody_damage_only {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			PED::SET_PED_UPPER_BODY_DAMAGE_ONLY(g_utils->vehicle(), true);
		}
		void on_disable() {
			PED::SET_PED_UPPER_BODY_DAMAGE_ONLY(g_utils->vehicle(), false);
		}
	}
	namespace attack_friendly {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			PED::SET_CAN_ATTACK_FRIENDLY(g_utils->vehicle(), true, 0);
		}
		void on_disable() {
			PED::SET_CAN_ATTACK_FRIENDLY(g_utils->vehicle(), false, 0);
		}
	}
	namespace seatbelt {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_seatbelt = TRUE;
			PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_WillFlyThroughWindscreen, false);
		}
		void on_disable() {
			g_utils->cped()->m_seatbelt = FALSE;
			PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_WillFlyThroughWindscreen, true);
		}
	}
	namespace walk_underwater {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_navigation->m_damp->m_water_collision = 0;
		}
		void on_disable() {
			g_utils->cped()->m_navigation->m_damp->m_water_collision = 1;
		}
	}
	namespace mobile_radio {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(true);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
		}
		void on_disable() {
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(false);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
		}
	}
	namespace slide_run {
		bool enabled{ false };
		float speed{ 2.5 };
		void init() {
			if (!enabled) return;
			if (TASK::IS_PED_RUNNING(g_utils->self()) || TASK::IS_PED_SPRINTING(g_utils->self()) && !PED::IS_PED_RAGDOLL(g_utils->self())) {
				ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->self(), 1, 0.f, speed, 0.0f, 0.0f, 0.0f, 0.0f, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE);
			}
		}
	}
	namespace invisiblity {
		namespace settings {
			std::vector<const char*> type = { "Everyone", "Only Network", "Only Self" };
			int selected{ 0 };
		}
		bool enabled{ false };
		void init() {
			if (!enabled) return;

			if (settings::selected == 1) {
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(g_utils->self());
			}
			else if (settings::selected == 2) {
				NETWORK::SET_ENTITY_LOCALLY_INVISIBLE(g_utils->self());
				return;
			}

			ENTITY::SET_ENTITY_VISIBLE(g_utils->self(), false, false);
		}
		void on_disable() {
			ENTITY::SET_ENTITY_VISIBLE(g_utils->self(), true, false);
		}
	}
	namespace superman {
		namespace settings {
			float speed{ 2 };
			float upward_force{ 2 };
			bool rise_on_collison{};
		}
		void apply_force_to_entity(Entity entity, float x, float y, float z, float offX = 0, float offY = 0, float offZ = 0) {
			ENTITY::APPLY_FORCE_TO_ENTITY(entity, 1, x, y, z, offX, offY, offZ, 0, 1, 1, 1, 0, 1);
		}
		bool enabled{ false };
		void init() {
			if (enabled) {
				PED::SET_PED_CAN_RAGDOLL(g_utils->self(), false);
				WEAPON::GIVE_WEAPON_TO_PED(g_utils->self(), rage::joaat("GADGET_PARACHUTE"), 1, false, true);
				PED::SET_PED_TO_RAGDOLL_WITH_FALL(g_utils->self(), 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);

				if (PAD::IS_CONTROL_PRESSED(0, (int)eControllerInputs::INPUT_JUMP))
					apply_force_to_entity(g_utils->self(), 0, 0, settings::upward_force);

				if (ENTITY::IS_ENTITY_IN_AIR(g_utils->self()) && !PED::IS_PED_RAGDOLL(g_utils->self()))
					if (PAD::IS_CONTROL_PRESSED(0, (int)eControllerInputs::INPUT_VEH_BRAKE))
						apply_force_to_entity(g_utils->self(), 0, settings::speed, 0);

				if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(g_utils->self()) && settings::rise_on_collison) {
					ENTITY::SET_ENTITY_COORDS(g_utils->self(), g_utils->coords().x, g_utils->coords().y, g_utils->coords().z + 250, true, true, true, false);
				}

			}
		}
		void on_disable() {
			PED::SET_PED_CAN_RAGDOLL(g_utils->self(), true);
		}
	}
	namespace walk_on_air {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			PED::SET_PED_GRAVITY(g_utils->self(), false);
		}
		void on_disable() {
			PED::SET_PED_GRAVITY(g_utils->self(), true);
		}
	}

	namespace ignored_by_peds {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			for (auto ped : g_pools->peds()) {
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
				PED::SET_PED_FLEE_ATTRIBUTES(ped, 0, false);
				PED::SET_PED_COMBAT_ATTRIBUTES(ped, 17, true);
			}
			PLAYER::SET_POLICE_IGNORE_PLAYER(g_utils->self_id(), true);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(g_utils->self_id(), true);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(g_utils->self_id(), false);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(g_utils->self_id(), true);
		}
		void on_disable() {
			PLAYER::SET_POLICE_IGNORE_PLAYER(g_utils->self_id(), false);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(g_utils->self_id(), false);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(g_utils->self_id(), true);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(g_utils->self_id(), false);
		}
	}
	namespace snow_trails {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			GRAPHICS::USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(true);
		}
		void on_disable() {
			GRAPHICS::USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(false);
		}
	}
	namespace tiny_ped {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_UseAmbientModelScaling, true);
		}
		void on_disable() {
			PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_UseAmbientModelScaling, false);
		}
	}
	namespace explosive_melee {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_player_info->m_frame_flags = 1 << 13;
		}
	}
	namespace push_water_away {
		bool enabled{ false };
		void tick() {
			if (!enabled) return;

			for (int i{ -8 }; i <= 15; i++) {
				for (int j{ -8 }; j <= 15; j++) {
					WATER::MODIFY_WATER(g_utils->coords().x + i, g_utils->coords().y + j, -8, 8);
				}
			}
		}
	}

	namespace walk_on_water {
		bool enabled{ false };
		Object object;
		void tick() {
			if (!enabled) return;

			if (g_utils->in_vehicle()) {
				g_utils->delete_entity(object);
			}

			float water_height{ 0 };
			auto coords{ g_utils->coords() };

			WATER::GET_WATER_HEIGHT(coords.x, coords.y, coords.z, &water_height);
			Vector3 adjusted = { coords.x, coords.y, water_height - 1.9f };

			if (coords.z - water_height <= 3.f) {
				if (!ENTITY::DOES_ENTITY_EXIST(object)) {
					STREAMING::REQUEST_MODEL(0xC42C019A);
					if (STREAMING::HAS_MODEL_LOADED(0xC42C019A)) {
						if (object == 0) {
							object = OBJECT::CREATE_OBJECT(0xC42C019A, coords.x, coords.y, coords.z, true, false, false);
						}
					}
				}
				else {
					ENTITY::SET_ENTITY_VISIBLE(object, false, true);
					ENTITY::SET_ENTITY_ROTATION(object, 180.f, 90.f, 180.f, 2, false);
					ENTITY::SET_ENTITY_COORDS(object, adjusted.x, adjusted.y, adjusted.z, true, false, false, true);
					ENTITY::FREEZE_ENTITY_POSITION(object, true);
				}
			}
		}
		void on_disable() {
			g_utils->delete_entity(object);
			object = 0;
		}
	}

	namespace instantly_enter_vehicles {
		bool enabled{ false };
		void tick() {
			if (!enabled) return;

			auto vehicle{ PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(g_utils->self()) };

			if (vehicle) {
				if (!VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, -1, 0)) {
					auto ped{ VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1, 0) };

					if (!PED::IS_PED_A_PLAYER(ped)) {
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
					}
				}
				PED::SET_PED_INTO_VEHICLE(g_utils->self(), vehicle, -1);
			}
		}
	}

	namespace disable_drag_outs {
		bool enabled{ false };
		void tick() {
			if (!enabled) return;

			PED::SET_PED_CAN_BE_DRAGGED_OUT(g_utils->self(), false);
		}
		void on_disable() {
			PED::SET_PED_CAN_BE_DRAGGED_OUT(g_utils->self(), true);
		}
	}

	namespace crouched {
		bool enabled{ false };
		void tick() {
			if (!enabled) return;

			if (STREAMING::HAS_ANIM_SET_LOADED("move_ped_crouched")) {
				PED::SET_PED_MOVEMENT_CLIPSET(g_utils->self(), "move_ped_crouched", 2.0f);
			}
			else {
				STREAMING::REQUEST_ANIM_SET("move_ped_crouched");
			}
		}
		void on_disable() {
			PED::RESET_PED_MOVEMENT_CLIPSET(g_utils->self(), 1.0f);
		}
	}

	namespace wet {
		bool enabled{ false };
		float amount{ 10.0f };
		void tick() {
			if (!enabled) return;
			PED::SET_PED_WETNESS_ENABLED_THIS_FRAME(g_utils->self());
			PED::SET_PED_WETNESS_HEIGHT(g_utils->self(), amount);
		}
		void on_disable() {
			PED::SET_PED_WETNESS_HEIGHT(g_utils->self(), 0);
		}
	}

	namespace auto_open_parachute {
		bool enabled{ false };
		void tick() {
			if (!enabled) return;

			if (PED::GET_PED_PARACHUTE_STATE(g_utils->self()) == 0) {
				PED::FORCE_PED_TO_OPEN_PARACHUTE(g_utils->self());
			}
		}
	}

	namespace thermal_vision {
		namespace settings {
			bool color_enabled{};
			color<float> rear_color;

			bool modifiers{};
			float fade_start_distance;
			float fade_end_distance{ 10000 };
			float max_thickness{ 1.0 };
			float noise_min;
			float noise_max;
			float highlight_intensity;
			float highlight_noise;

			bool heatscale_modifiers{};
			float heatscale_intensty;
			float heatscale_index;
		}
		bool enabled{};
		void reset() {
			GRAPHICS::SEETHROUGH_SET_COLOR_NEAR(30, 15, 70);
			GRAPHICS::SEETHROUGH_RESET();
		}
		void tick() {
			if (!enabled) return;

			if (settings::modifiers) {
				GRAPHICS::SEETHROUGH_SET_FADE_STARTDISTANCE(settings::fade_start_distance);
				GRAPHICS::SEETHROUGH_SET_FADE_ENDDISTANCE(settings::fade_end_distance);
				GRAPHICS::SEETHROUGH_SET_MAX_THICKNESS(settings::max_thickness);
				GRAPHICS::SEETHROUGH_SET_NOISE_MIN(settings::noise_min);
				GRAPHICS::SEETHROUGH_SET_NOISE_MAX(settings::noise_max);
				GRAPHICS::SEETHROUGH_SET_HILIGHT_INTENSITY(settings::highlight_intensity);
				GRAPHICS::SEETHROUGH_SET_HIGHLIGHT_NOISE(settings::highlight_noise);
			}

			if (settings::heatscale_modifiers) {
				GRAPHICS::SEETHROUGH_SET_HEATSCALE(settings::heatscale_index, settings::heatscale_intensty);
			}

			if (settings::color_enabled) {
				GRAPHICS::SEETHROUGH_SET_COLOR_NEAR(settings::rear_color.r, settings::rear_color.g, settings::rear_color.b);
			}
			else {
				GRAPHICS::SEETHROUGH_SET_COLOR_NEAR(30, 15, 70);
			}

			GRAPHICS::SET_SEETHROUGH(true);
		}
		void on_disable() {
			GRAPHICS::SET_SEETHROUGH(false);
			reset();
		}
	}

	namespace tennis_mode {
		bool enabled{};
		void tick() {
			if (!enabled) return;

			if (!MISC::IS_TENNIS_MODE(g_utils->self())) {
				MISC::ENABLE_TENNIS_MODE(g_utils->self(), true, 0);
			}
		}
		void on_disable() {
			MISC::ENABLE_TENNIS_MODE(g_utils->self(), false, 0);
		}
	}

	namespace backward_walking {
		bool enabled{};
		void tick() {
			if (!enabled) return;
			g_utils->cped()->m_player_info->m_run_speed = -1.0;
		}
		void on_disable() {
			g_utils->cped()->m_player_info->m_run_speed = 1.0;
		}
	}

	namespace infinite_oxygen {
		bool enabled{};
		void tick() {
			if (!enabled) return;
			
			g_utils->cped()->m_ped_intelligence->m_oxygen_time = 0;
		}
	}
}
