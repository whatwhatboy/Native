#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base {
	namespace bullet_changer {
		namespace settings {
			float bullets{ 1 };
			float delay{ 0 };
			int selected{ 79 };
			float speed{ -1.0 };
		}
		bool enabled{ false };
		void init() {
			if (!enabled) return;

			if (g_utils->shooting()) {
				g_utils->timed_function(settings::delay, [] {
					for (int i = 0; i < settings::bullets; i++) g_utils->shoot_single_bullet_out_of_muzzle(all_weapons_hash[settings::selected], settings::speed, 250);
				});
			}
		}
	}
}
