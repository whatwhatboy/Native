#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	void spinbot::init() {
        if (!m_enabled) return;

        auto current_rotation{ ENTITY::GET_ENTITY_ROTATION(g_utils->hybrid(), 0) };
        if ((m_settings.m_direction_pos == 0 || m_settings.m_direction_pos == 1) && m_settings.m_first_rotation) {
            auto new_rotation{ current_rotation.z + (m_settings.m_direction_pos == 0 ? -m_settings.m_speed : m_settings.m_speed) };
            ENTITY::SET_ENTITY_ROTATION(g_utils->hybrid(), current_rotation.x, current_rotation.y, new_rotation, 0, 0);
        }

        if ((m_settings.m_direction_pos2 == 0 || m_settings.m_direction_pos2 == 1) && m_settings.m_second_rotation) {
            static int new_rotation = 0;
            auto heading{ ENTITY::GET_ENTITY_HEADING(g_utils->hybrid()) };
            new_rotation += (m_settings.m_direction_pos2 == 0 ? -m_settings.m_speed : m_settings.m_speed);
            ENTITY::SET_ENTITY_ROTATION(g_utils->hybrid(), new_rotation, current_rotation.y, heading, 0, 0);
        }
	}
}
