#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	void handtrails::tick() {
		if (!m_enabled) return;

		if (m_settings.m_rainbow) {
			m_settings.m_color = g_rainbow.as<float>();
		}

		color<float> color{ m_settings.m_color.r / 255.f, m_settings.m_color.g / 255.f, m_settings.m_color.b / 255.f, m_settings.m_color.a / 255.f};
		switch (m_settings.m_selected) {
		case 0:
			g_utils->particle_on_self("scr_powerplay", "sp_powerplay_beast_appear_trails", SKEL_L_Hand, m_settings.m_scale, true, color.r, color.g, color.b);
			g_utils->particle_on_self("scr_powerplay", "sp_powerplay_beast_appear_trails", SKEL_R_Hand, m_settings.m_scale, true, color.r, color.g, color.b);
			break;
		case 1:
			g_utils->particle_on_self("scr_indep_fireworks", "scr_indep_firework_sparkle_spawn", SKEL_L_Hand, m_settings.m_scale, true, color.r, color.g, color.b);
			g_utils->particle_on_self("scr_indep_fireworks", "scr_indep_firework_sparkle_spawn", SKEL_R_Hand, m_settings.m_scale, true, color.r, color.g, color.b);
			break;
		case 2:
			g_utils->particle_on_self("scr_rcpaparazzo1", "scr_mich4_firework_sparkle_spawn", SKEL_L_Hand, m_settings.m_scale, true, color.r, color.g, color.b);
			g_utils->particle_on_self("scr_rcpaparazzo1", "scr_mich4_firework_sparkle_spawn", SKEL_R_Hand, m_settings.m_scale, true, color.r, color.g, color.b);
			break;
		}
	}
}
