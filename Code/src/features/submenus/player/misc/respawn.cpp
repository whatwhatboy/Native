#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	void fast_respawn::init() {
		if (!m_enabled) return;

		if (PED::IS_PED_DEAD_OR_DYING(g_utils->self(), true)) {
			PED::RESURRECT_PED(g_utils->self());
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_utils->self(), g_utils->coords().x, g_utils->coords().y, g_utils->coords().z, 0, 0, 0);
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(g_utils->self());
			MISC::FORCE_GAME_STATE_PLAYING();
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("respawn_controller");
		}
   }
}
