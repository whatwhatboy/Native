#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base::triggerbot {
	namespace settings {
		namespace excludes {
			bool players{};
			bool police{};
			bool normal_peds{};
			bool enemys{};
		}
		std::vector<const char*> bone_lockon = { "None", "Head", "Chest"};
		int selected{ 0 };
		int delay = 0;
	}
	bool enabled{ false };
	void init() {
		if (g_utils->control_pressed(disable_pressed, eControllerInputs::INPUT_AIM) && enabled) {
			Entity target;
			if (g_math->raycast(target)) {
				Vector3 c;
				if (settings::excludes::players && PED::IS_PED_A_PLAYER(target)) return;
				if (settings::excludes::normal_peds && ENTITY::IS_ENTITY_A_PED(target)) return;
				if (settings::selected == 0) c = g_utils->coords(target);
				else if (settings::selected == 1) c = PED::GET_PED_BONE_COORDS(target, 31086, 0.1f, 0.0f, 0.0f);
				if (ENTITY::IS_ENTITY_A_PED(target) && !ENTITY::IS_ENTITY_DEAD(target, 0))
					PED::SET_PED_SHOOTS_AT_COORD(g_utils->self(), c.x, c.y, c.z, true);
			}
		}
	}
}
