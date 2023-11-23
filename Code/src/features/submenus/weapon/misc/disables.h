#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base::weapon_disables {
	namespace recoil {
		bool enabled{ false };
		CWeaponInfo* modified_weapon = nullptr;
		float og_value = 0.0f;

		void init() {
			if (g_utils->cweapon() && enabled) {
				if (modified_weapon != g_utils->cweapon()) {
					if (modified_weapon)
						modified_weapon->m_explosion_shake_amplitude = og_value;

					modified_weapon = g_utils->cweapon();

					if (g_utils->cweapon()) {
						og_value = g_utils->cweapon()->m_explosion_shake_amplitude;
						g_utils->cweapon()->m_explosion_shake_amplitude = 0;
					}
				}
			}
		}
		void on_disable() {
			if (modified_weapon) {
				modified_weapon->m_explosion_shake_amplitude = og_value;
				modified_weapon = nullptr;
			}
		}
	}
	namespace spread {
		bool enabled{ false };
		CWeaponInfo* modified_weapon = nullptr;
		float og_value = 0.0f;

		void init() {
			if (g_utils->cweapon() && enabled) {
				if (modified_weapon != g_utils->cweapon()) {
					if (modified_weapon)
						modified_weapon->m_batch_spread = og_value;

					modified_weapon = g_utils->cweapon();

					if (g_utils->cweapon()) {
						og_value = g_utils->cweapon()->m_batch_spread;
						g_utils->cweapon()->m_batch_spread = 0;
					}
				}
			}
		}
		void on_disable() {
			if (modified_weapon) {
				modified_weapon->m_batch_spread = og_value;
				modified_weapon = nullptr;
			}
		}
	}
	namespace throwable_limits {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			g_utils->cped()->fired_sticky_bombs = 0;
			g_utils->cped()->fired_sticky_bombs = 0;
			g_utils->cped()->fired_unk_0 = 0;
			g_utils->cped()->fired_unk_1 = 0;
		}
	}

}
