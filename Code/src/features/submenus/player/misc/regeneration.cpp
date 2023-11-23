#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	void regeneration::init() {
		if (!m_enabled || m_settings.m_in_cover && !PED::IS_PED_IN_COVER(g_utils->self(), false)) return;

		g_utils->timed_function(m_settings.m_delay, [=] {
			if (m_settings.m_armor) {
				g_utils->cped()->m_armor = PED::GET_PED_ARMOUR(g_utils->self()) + m_settings.m_amount;
			}

			if (m_settings.m_health) {
				g_utils->cped()->m_health = ENTITY::GET_ENTITY_HEALTH(g_utils->self()) + m_settings.m_amount, 0;
			}
		});
	}
}
