#pragma once
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>
#include "classes.hpp"
namespace Base {
    void particles::init() {
        if (!m_enabled) return;

		if (m_settings.m_color.rainbow) {
			m_settings.m_color.m_value = g_rainbow.as<float>();
		}
		if (g_utils->shooting() || m_settings.m_always) {
			Vector3 c;
			switch (m_settings.m_type_selected) {
			case 0:
				c = g_utils->weapon_bone_coords("gun_muzzle");
				break;
			case 1:
				g_math->raycast(c);
				break;
			}
			if (c.empty()) return;
			g_utils->request(request_type::particle, particles_data::data[m_settings.m_selected_particle].dict, [=] {
				if (m_settings.m_color.m_enabled) {
					g_utils->particle_on_coord(particles_data::data[m_settings.m_selected_particle].dict, particles_data::data[m_settings.m_selected_particle].asset, c, m_settings.m_scale, true, m_settings.m_color.m_value.r / 255.f, m_settings.m_color.m_value.g / 255.f, m_settings.m_color.m_value.b / 255);
				}
				else {
					GRAPHICS::USE_PARTICLE_FX_ASSET(particles_data::data[m_settings.m_selected_particle].dict);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particles_data::data[m_settings.m_selected_particle].asset, c.x, c.y, c.z, 0.f, 0.f, 0.f, m_settings.m_scale, false, false, false, true);
				}
			});
			
		}
    }
}
