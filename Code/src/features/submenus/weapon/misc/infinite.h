#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base {
	namespace unlimited_ammo {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_inventory->m_infinite_ammo = true;
		}
		void on_disable() {
			g_utils->cped()->m_inventory->m_infinite_ammo = false;
		}
	}
	namespace unlimited_clip {
		bool enabled = false;
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_inventory->m_infinite_clip = true;
		}
		void on_disable() {
			g_utils->cped()->m_inventory->m_infinite_clip = false;
		}
	}
	namespace infinte_lockon_range {
		bool enabled = false;
		CWeaponInfo* modified_weapon = nullptr;
		float og_value = 0.0f;

		void init() {
			if (g_utils->cweapon() && enabled) {
				if (modified_weapon != g_utils->cweapon()) {
					if (modified_weapon)
						modified_weapon->m_lock_on_range = og_value;

					modified_weapon = g_utils->cweapon();

					if (g_utils->cweapon()) {
						og_value = g_utils->cweapon()->m_lock_on_range;
						g_utils->cweapon()->m_lock_on_range = 1000.0f;
					}
				}
			}
		}
		void on_disable() {
			if (modified_weapon) {
				modified_weapon->m_lock_on_range = og_value;
				modified_weapon = nullptr;
			}
		}
	}
	namespace infinite_range {
		bool enabled = false;
		CWeaponInfo* modified_weapon = nullptr;
		float og_value = 0.0f;

		void init() {
			if (g_utils->cweapon() && enabled) {
				if (modified_weapon != g_utils->cweapon()) {
					if (modified_weapon)
						modified_weapon->m_weapon_range = og_value;
					modified_weapon = g_utils->cweapon();
					if (g_utils->cweapon()) {
						og_value = g_utils->cweapon()->m_weapon_range;
						g_utils->cweapon()->m_weapon_range = 1000.0f;
					}
				}
			}
		}
		void on_disable() {
			if (modified_weapon) {
				modified_weapon->m_weapon_range = og_value;
				modified_weapon = nullptr;
			}
		}
	}
}
