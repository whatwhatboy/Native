#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "../classes.h"

namespace Base::camera {
	void gta_1::tick() {
		if (!m_enabled) return;
		if (CAM::DOES_CAM_EXIST(m_cam)) {
			auto coords{ g_utils->coords() };
			auto rotation{ ENTITY::GET_ENTITY_ROTATION(g_utils->self(), 2) };

			coords.z = g_utils->coords().z + m_settings.m_distance;
			CAM::SET_CAM_COORD(m_cam, coords.x, coords.y, coords.z);
			CAM::SET_CAM_ROT(m_cam, rotation.x, rotation.y, rotation.z, 2);
			CAM::POINT_CAM_AT_ENTITY(m_cam, g_utils->self(), 0, 0, 0, true);
		}
		else {
			m_cam = CAM::CREATE_CAMERA(26379945, true);
			CAM::SET_CAM_ACTIVE(m_cam, true);
			CAM::RENDER_SCRIPT_CAMS(true, true, 1000, true, false, 0);
		}
	}
	void gta_1::on_disable() {
		CAM::DESTROY_CAM(m_cam, true);
		CAM::RENDER_SCRIPT_CAMS(false, true, 1000, true, false, 0);
	}
}
