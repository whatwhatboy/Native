#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::vehicle {
	void tire_tracks_vfx() {
		vfx_wheel* vfx{ g_pointers->m_vfx_wheel.first };

		for (uint32_t i = 0; i < (uint32_t)(g_pointers->m_vfx_wheel.second * 4); i++) {
			draw->submenu(std::to_string(i), "vfx_wheel_" + std::to_string(i), [=] {
				draw->number("Slip Min", vfx[i].m_slip_min, {-1000, 1000, 0.1, 1});
				draw->number("Slip Max", vfx[i].m_slip_max, { -1000, 1000, 0.1, 1 });
				draw->number("Pressure Min", vfx[i].m_pressure_min, { -1000, 1000, 0.1, 1 });
				draw->number("Pressure Max", vfx[i].m_pressure_max, { -1000, 1000, 0.1, 1 });
				draw->number("Friction Threshold Min", vfx[i].m_friction_thresh_min, { -1000, 1000, 0.1, 1 });
				draw->number("Friction Threshold Max", vfx[i].m_friction_thresh_max, { -1000, 1000, 0.1, 1 });
				draw->number("Disp Threshold Min", vfx[i].m_disp_thresh_min, { -1000, 1000, 0.1, 1 });
				draw->number("Disp Threshold Max", vfx[i].m_disp_thresh_max, { -1000, 1000, 0.1, 1 });
				draw->number("Burn Friction Min", vfx[i].m_burn_friction_evo_min, { -1000, 1000, 0.1, 1 });
				draw->number("Burn Friction Max", vfx[i].m_burn_friction_evo_max, { -1000, 1000, 0.1, 1 });
				draw->number("Burn Temp Min", vfx[i].m_burn_temp_evo_min, { -1000, 1000, 0.1, 1 });
				draw->number("Burn Temp Max", vfx[i].m_burn_temp_evo_max, { -1000, 1000, 0.1, 1 });
				draw->number("Lights Min R", vfx[i].m_lights_col_min_r, { 0, 255, 1, 0 });
				draw->number("Lights Min G", vfx[i].m_lights_col_min_g, { 0, 255, 1, 0 });
				draw->number("Lights Min B", vfx[i].m_lights_col_min_b, { 0, 255, 1, 0 });
				draw->number("Lights Max R", vfx[i].m_lights_col_max_r, { 0, 255, 1, 0 });
				draw->number("Lights Max G", vfx[i].m_lights_col_max_g, { 0, 255, 1, 0 });
				draw->number("Lights Max B", vfx[i].m_lights_col_max_b, { 0, 255, 1, 0 });
				draw->number("Lights Intensity Min", vfx[i].m_lights_intensity_min, { -1000, 1000, 0.1, 1 });
				draw->number("Lights Intensity Max", vfx[i].m_lights_intensity_max, { -1000, 1000, 0.1, 1 });
				draw->number("Lights Range Min", vfx[i].m_lights_range_min, { -1000, 1000, 0.1, 1 });
				draw->number("Lights Range Max", vfx[i].m_lights_range_max, { -1000, 1000, 0.1, 1 });
				draw->number("Lights Falloff Min", vfx[i].m_lights_falloff_min, { -1000, 1000, 0.1, 1 });
				draw->number("Lights Falloff Max", vfx[i].m_lights_falloff_max, { -1000, 1000, 0.1, 1 });
				draw->number("R", vfx[i].m_r, { 0, 255, 1, 0 });
				draw->number("G", vfx[i].m_g, { 0, 255, 1, 0 });
				draw->number("B", vfx[i].m_b, { 0, 255, 1, 0 });
			});
		}
	}
}
