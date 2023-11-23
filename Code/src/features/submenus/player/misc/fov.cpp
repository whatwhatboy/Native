#pragma once
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	void fov::init() {
		if (!m_enabled) return;
		g_pointers->m_game_visuals->m_fov = m_settings.m_value / 3000;
	}
	void fov::on_disable() {
		g_pointers->m_game_visuals->m_fov = 0.0175;
	}
}
