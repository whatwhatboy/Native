#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	void noclip::init() {
		if (!m_enabled) return;

		auto is_in_interior{ INTERIOR::GET_INTERIOR_FROM_ENTITY(g_utils->self()) != 0 };
		auto start_coords{ g_utils->coords() };
		auto cam{ g_utils->get_cam() };
		auto start_distance{ std::distance(&cam.coords, &start_coords) };
		Vector3 new_coords{};

		if (is_in_interior && m_settings.m_change_speed)
			new_coords = cam.direction * m_settings.m_interior_speed;
		else
			new_coords = cam.direction * m_settings.m_speed;

		switch (m_settings.m_type_pos) {
		case 0:
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_utils->hybrid(), start_coords.x, start_coords.y, start_coords.z, false, false, false);
			break;
		case 1:
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_utils->hybrid(), start_coords.x, start_coords.y, start_coords.z, true, true, true);
			break;
		}
		if (g_utils->control_pressed(pressed, 32)) {
			auto newC{ start_coords + new_coords };
			switch (m_settings.m_type_pos) {
			case 0:
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_utils->hybrid(), newC.x, newC.y, newC.z, false, false, false);
				break;
			case 1:
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_utils->hybrid(), newC.x, newC.y, newC.z, true, true, true);
				break;
			}
		}
		if (m_settings.m_set_rotation || g_utils->in_vehicle())
			ENTITY::SET_ENTITY_ROTATION(g_utils->hybrid(), cam.rotation.x, cam.rotation.y, cam.rotation.z, 2, 1);
		if (m_settings.m_transparent)
			ENTITY::SET_ENTITY_ALPHA(g_utils->hybrid(), m_settings.m_transparent_value, false);
		else
			ENTITY::SET_ENTITY_ALPHA(g_utils->hybrid(), 255, false);
		if (m_settings.m_spin)
			ENTITY::SET_ENTITY_HEADING(g_utils->hybrid(), ENTITY::GET_ENTITY_HEADING(g_utils->hybrid()) + m_settings.m_spin_speed);
	}
}
