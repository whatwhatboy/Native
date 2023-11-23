#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"
#include "src/rage/vehicle/CCarHandlingData.hpp"

namespace Base {
	namespace vehicle_flags {
		namespace handbrake {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_HANDBRAKE(g_utils->vehicle(), true);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_HANDBRAKE(g_utils->vehicle(), false);
			}
		}
		namespace brake {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_BRAKE(g_utils->vehicle(), true);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_BRAKE(g_utils->vehicle(), false);
			}
		}
		namespace higher_jump {
			bool enabled{ false };
			float multiplier{ 5 };
			void init() {
				if (!enabled) return;
				if (VEHICLE::IS_THIS_MODEL_A_CAR(g_utils->get_hash(g_utils->vehicle())) && VEHICLE::GET_CAR_HAS_JUMP(g_utils->vehicle()) && g_utils->cvehicle() && g_utils->cvehicle()->m_handling_data) {
					for (auto d : g_utils->cvehicle()->m_handling_data->m_sub_handling_data) {
						if (d && d->GetHandlingType() == eHandlingType::HANDLING_TYPE_CAR) {
							auto const dc{ (CCarHandlingData*)d };
							if (dc->m_jumpforce_scale)
								dc->m_jumpforce_scale = multiplier;
							break;
						}
					}
				}
			}
			void on_disable() {
				if (VEHICLE::IS_THIS_MODEL_A_CAR(g_utils->get_hash(g_utils->vehicle())) && VEHICLE::GET_CAR_HAS_JUMP(g_utils->vehicle()) && g_utils->cvehicle() && g_utils->cvehicle()->m_handling_data) {
					for (auto d : g_utils->cvehicle()->m_handling_data->m_sub_handling_data) {
						if (d && d->GetHandlingType() == eHandlingType::HANDLING_TYPE_CAR) {
							auto const dc{ (CCarHandlingData*)d };
							if (dc->m_jumpforce_scale)
								dc->m_jumpforce_scale = 1.0;
							break;
						}
					}
				}
			}
		}
		namespace disable_charge {
			bool enabled{ false };
			void init() {
				if (!g_utils->cvehicle() || !enabled) return;
				g_utils->cvehicle()->m_jump_boost_charge = 5;
			}
		}
		namespace racing {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_IS_RACING(g_utils->vehicle(), true);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_IS_RACING(g_utils->vehicle(), false);
			}
		}
		namespace ceo {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_GOON_BOSS_VEHICLE(g_utils->vehicle(), true);
			}
			void on_disable() {
				VEHICLE::SET_GOON_BOSS_VEHICLE(g_utils->vehicle(), false);
			}
		}
		namespace can_wheelie {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				if (VEHICLE::IS_THIS_MODEL_A_CAR(g_utils->get_hash(g_utils->vehicle()))) {
					for (auto d : g_utils->cvehicle()->m_handling_data->m_sub_handling_data) {
						if (d && d->GetHandlingType() == eHandlingType::HANDLING_TYPE_CAR) {
							auto const dc{ (CCarHandlingData*)d };
							if (dc && dc->m_advanced_flags)
								dc->m_advanced_flags = eAdvancedFlags::CF_CAN_WHEELIE;
							break;
						}
					}
				}
			}
			void on_disable() {
				if (VEHICLE::IS_THIS_MODEL_A_CAR(g_utils->get_hash(g_utils->vehicle()))) {
					for (auto d : g_utils->cvehicle()->m_handling_data->m_sub_handling_data) {
						if (d && d->GetHandlingType() == eHandlingType::HANDLING_TYPE_CAR) {
							auto const dc{ (CCarHandlingData*)d };
							if (dc && dc->m_advanced_flags)
								dc->m_advanced_flags = eAdvancedFlags::NONE;
							break;
						}
					}
				}
			}
		}
		namespace can_save_in_garage {
			bool enabled{ false };
			void init() {
				if (!enabled) return;
				VEHICLE::SET_VEHICLE_CAN_SAVE_IN_GARAGE(g_utils->vehicle(), true);
			}
			void on_disable() {
				VEHICLE::SET_VEHICLE_CAN_SAVE_IN_GARAGE(g_utils->vehicle(), false);
			}
		}
	}
}
