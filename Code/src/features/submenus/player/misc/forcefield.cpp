#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	void forcefield::move(Entity vehicle, bool pull) {
		Vector3 force;
		if (pull) {
			force = (g_utils->coords(vehicle) + g_utils->coords());
		}
		else {
			force = (g_utils->coords(vehicle) - g_utils->coords());
		}
		force *= m_settings.m_force_multiplier;

		ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 3, force.x, force.y, force.z, 0, 0, 0, 0, false, true, true, false, true);
	}
	void forcefield::init() {
		if (!m_enabled) return;

		if (m_settings.m_show_radius) {
			GRAPHICS::DRAW_MARKER(28, g_utils->coords().x, g_utils->coords().y, g_utils->coords().z, 0, 0, 0, 0, 0, 0, m_settings.m_radius, m_settings.m_radius, m_settings.m_radius, 255, 0, 0, 160, false, false, 0, false, NULL, NULL, false);
		}

		for (auto obj : g_pools->all(m_settings.m_exclude_vehicles, m_settings.m_exclude_peds, m_settings.m_exclude_objects)) {
			if (ENTITY::DOES_ENTITY_EXIST(obj)) {
				auto position{ g_utils->coords(obj) };
				auto distance{ g_math->distance(g_utils->coords(), position) };
				if (distance <= m_settings.m_radius) {
					move(obj, m_settings.m_type_pos == 1);
				}
			}
		}
	}
}
