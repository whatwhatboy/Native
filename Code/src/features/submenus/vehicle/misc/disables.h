#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base {
	namespace disables {
		namespace lock_on {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				auto vehicle{ g_utils->cped()->m_vehicle };
				if (!vehicle || !g_utils->cped()) return;

				vehicle->m_is_targetable = false;
			}
			void on_disable() {
				auto vehicle = g_utils->cped()->m_vehicle;
				if (!vehicle || !g_utils->cped()) return;
				vehicle->m_is_targetable = true;
			}
		}
		namespace brake_lights {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_BRAKE_LIGHTS(g_utils->vehicle(), false);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_BRAKE_LIGHTS(g_utils->vehicle(), true);
			}
		}
		namespace oil_leaking {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_CAN_LEAK_OIL(g_utils->vehicle(), false);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_CAN_LEAK_OIL(g_utils->vehicle(), true);
			}
		}
		namespace petrol_leaking {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_CAN_LEAK_PETROL(g_utils->vehicle(), false);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_CAN_LEAK_PETROL(g_utils->vehicle(), true);
			}
		}
		namespace fire {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				FIRE::STOP_ENTITY_FIRE(g_utils->vehicle());
			}
		}
		namespace wheel_deforming {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_CAN_DEFORM_WHEELS(g_utils->vehicle(), false);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_CAN_DEFORM_WHEELS(g_utils->vehicle(), true);
			}
		}
		namespace glass_breaking {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_DONT_PROCESS_VEHICLE_GLASS(g_utils->vehicle(), true);
			}
			void on_disable() {
				VEHICLE::SET_DONT_PROCESS_VEHICLE_GLASS(g_utils->vehicle(), false);
			}
		}
		namespace bmx_extra_trick_forces {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_DISABLE_BMX_EXTRA_TRICK_FORCES(g_utils->vehicle());
			}
		}
		namespace sirens {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(g_utils->vehicle(), true);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(g_utils->vehicle(), false);
			}
		}
		namespace pad_effects {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_SPEED_BOOST_EFFECT_DISABLED(true);
				VEHICLE::SET_SLOW_DOWN_EFFECT_DISABLED(true);
			}
			void on_disable() {
				VEHICLE::SET_SPEED_BOOST_EFFECT_DISABLED(false);
				VEHICLE::SET_SLOW_DOWN_EFFECT_DISABLED(true);
			}
		}
		namespace parts_breaking_off {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::DISABLE_VEHICLE_EXPLOSION_BREAK_OFF_PARTS();
			}
		}
		namespace detachable_bumpers {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::HIDE_TOMBSTONE(g_utils->vehicle(), true);
			}
			void on_disable() {
				VEHICLE::HIDE_TOMBSTONE(g_utils->vehicle(), false);
			}
		}
		namespace weapon_blades {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_DISABLE_RETRACTING_WEAPON_BLADES(true);
			}
			void on_disable() {
				VEHICLE::SET_DISABLE_RETRACTING_WEAPON_BLADES(false);
			}
		}
		namespace bike_wheelie {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				if (!VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(g_utils->vehicle()))) return;
				VEHICLE::SET_WHEELIE_ENABLED(g_utils->vehicle(), false);
			}
			void on_disable() {
				if (!VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(g_utils->vehicle()))) return;
				VEHICLE::SET_WHEELIE_ENABLED(g_utils->vehicle(), true);
			}
		}
		namespace gravity {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_GRAVITY(g_utils->vehicle(), false);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_GRAVITY(g_utils->vehicle(), true);
			}
		}
		namespace deformation {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(g_utils->vehicle());
			}
		}
		namespace turret_movement {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::DISABLE_VEHICLE_TURRET_MOVEMENT_THIS_FRAME(g_utils->vehicle());
			}
		}
		namespace slipstream {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_ENABLE_VEHICLE_SLIPSTREAMING(false);
			}
			void on_disable() {
				VEHICLE::SET_ENABLE_VEHICLE_SLIPSTREAMING(true);
			}
		}
		namespace neon_lights {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SUPPRESS_NEONS_ON_VEHICLE(g_utils->vehicle(), true);
			}
			void on_disable() {
				VEHICLE::SUPPRESS_NEONS_ON_VEHICLE(g_utils->vehicle(), false);
			}
		}
	}
}
