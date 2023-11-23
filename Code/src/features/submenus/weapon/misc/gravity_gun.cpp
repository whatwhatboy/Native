#pragma once
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>
#include "classes.hpp"
namespace Base {
	float get_velocity(float aim_x, float entity_x) {
		static float velocity;
		if (aim_x > 0 && entity_x > 0)
			velocity = aim_x - (entity_x);
		if (aim_x < 0 && entity_x < 0)
			velocity = aim_x - (entity_x);
		if (aim_x > 0 && entity_x < 0)
			velocity = aim_x + (entity_x);
		if (aim_x < 0 && entity_x > 0)
			velocity = aim_x + (entity_x);

		return velocity;
	}

	void gravity_gun::tick() {
		if (!m_enabled) return;

		if (m_data.m_has_entity && g_utils->aiming()) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(m_data.m_entity);

			auto rot{ CAM::GET_GAMEPLAY_CAM_ROT(0) };
			auto direction{ g_math->rotation_to_direction(&rot) };
			auto zoom{ direction * m_settings.m_zoom };
			auto spawn_position{ CAM::GET_GAMEPLAY_CAM_COORD() + zoom };
			auto aim_coords_x{ get_velocity(spawn_position.x, g_utils->coords(m_data.m_entity).x) };
			auto aim_coords_y{ get_velocity(spawn_position.y, g_utils->coords(m_data.m_entity).y) };
			auto aim_coords_z{ get_velocity(spawn_position.z, g_utils->coords(m_data.m_entity).z) };

			ENTITY::SET_ENTITY_VELOCITY(m_data.m_entity, aim_coords_x * m_settings.m_force, aim_coords_y * m_settings.m_force, aim_coords_z * m_settings.m_force);
		}
		else {
			if (g_utils->shooting()) {
				Entity e;
				if (g_math->raycast(e)) {
					m_data.m_entity = e;
					m_data.m_has_entity = true;
				}
			}
		}

		if (!g_utils->aiming() && !m_settings.m_save_on_unaim) {
			m_data.m_has_entity = false;
		}
	}
}
