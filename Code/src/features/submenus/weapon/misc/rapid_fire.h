#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base {
	namespace rapid_fire {
		bool aiming() {
			return PLAYER::IS_PLAYER_FREE_AIMING(g_utils->self_id());
		}
		namespace settings {
			float delay{ 0 };
			bool disable_shooting{ false };
			bool disable_when_reloading{ false };
			bool only_when_aiming{ false };
			float bullets{ 1 };
		}
		bool enabled{ false };
		void init() {
			if (g_utils->control_pressed(pressed, 24) && enabled) {
				if (settings::disable_when_reloading && PED::IS_PED_RELOADING(g_utils->self())) return;
				if (settings::disable_shooting) PLAYER::DISABLE_PLAYER_FIRING(g_utils->self(), true);
				if (settings::only_when_aiming && !aiming()) return;
				if (settings::disable_shooting) g_utils->fake_shoot();

				g_utils->timed_function(settings::delay, [] {
					for (int i = 0; i < settings::bullets; i++) g_utils->shoot_single_bullet_out_of_muzzle(g_utils->cped()->m_weapon_manager->m_selected_weapon_hash, -1.0, 250);
				});
			}
		}
		void on_disable() {
			PLAYER::DISABLE_PLAYER_FIRING(g_utils->self(), false);
		}
	}
}
