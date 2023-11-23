#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"

namespace Base {
	namespace vehicle_godmode {
		void reset() {
			if (g_utils->cvehicle()->m_damage_bits != 0)
				g_utils->cvehicle()->m_damage_bits = 0;
		}
		namespace settings {
			std::vector<const char*> type = { "Normal", "Set", "Native", "Semi-Legit" };
			int position{ 0 };
		}
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			if (g_utils->cvehicle()) {
				uint32_t last_bits{ 0 };
				uint32_t proof_mask{ 0 };
				proof_mask |= static_cast<int>(1 << 8);
				auto bits{ proof_mask };
				auto changed_bits{ bits ^ last_bits };
				auto changed_or_enabled_bits{ bits | changed_bits };
				auto ped{ g_utils->cvehicle() };
				switch (settings::position) {
				case 0:
					if (changed_or_enabled_bits) {
						uint32_t unchanged_bits{ ped->m_damage_bits & ~changed_or_enabled_bits };
						ped->m_damage_bits = unchanged_bits | bits;
						last_bits = bits;
					}
					break;
				case 1:
					reset();
					ped->m_health = ped->m_maxhealth;
					break;
				case 2:
					reset();
					ENTITY::SET_ENTITY_INVINCIBLE(g_utils->vehicle(), true);
					break;
				case 3:
					reset();
					if (ped->m_health < 10)
						ped->m_health = 10;
					break;
				}
			}
		}
		void on_disable() {
			if (g_utils->vehicle()) {
				g_utils->cvehicle()->m_damage_bits = 0;
				ENTITY::SET_ENTITY_INVINCIBLE(g_utils->vehicle(), false);
			}
		}
	}
}
