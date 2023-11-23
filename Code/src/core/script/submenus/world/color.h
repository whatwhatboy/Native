#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "src/framework/option_types/number.h"

namespace Base::submenus::world {
	using namespace Framework;
	std::vector<const char*> liquid_names = { "Puddle", "Blood", "Oil", "Petrol", "Mud" };
	int selected{};
	struct color_var {
		int m_r;
		int m_g;
		int m_b;
		float m_intensity;
	};
	struct color_vars {
		struct sun {
			int m_r;
			int m_g;
			int m_b;
			int m_disc_r;
			int m_disc_g;
			int m_disc_b;
			float m_hdr;
			float m_miephase;
		} m_sun;
		color_var m_light_dir;
		color_var m_light_dir2;
		color_var m_light_base;
		color_var m_light_ray;
		color_var m_correction;
	} m_color_vars;
	void update_vars() {
		m_color_vars.m_sun.m_r = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_SKY_SUN_COL_R) * 255.f;
		m_color_vars.m_sun.m_g = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_SKY_SUN_COL_G) * 255.f;
		m_color_vars.m_sun.m_b = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_SKY_SUN_COL_B) * 255.f;
		m_color_vars.m_sun.m_hdr = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_SKY_SUN_HDR);

		m_color_vars.m_light_dir2.m_r = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_DIRECTIONAL_AMB_COL_R) * 255.f;
		m_color_vars.m_light_dir2.m_g = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_DIRECTIONAL_AMB_COL_G) * 255.f;
		m_color_vars.m_light_dir2.m_b = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_DIRECTIONAL_AMB_COL_B) * 255.f;

		m_color_vars.m_light_dir.m_r = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_DIR_COL_R) * 255.f;
		m_color_vars.m_light_dir.m_g = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_DIR_COL_G) * 255.f;
		m_color_vars.m_light_dir.m_b = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_DIR_COL_B) * 255.f;

		m_color_vars.m_light_base.m_r = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_NATURAL_AMB_BASE_COL_R) * 255.f;
		m_color_vars.m_light_base.m_g = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_NATURAL_AMB_BASE_COL_G) * 255.f;
		m_color_vars.m_light_base.m_b = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_NATURAL_AMB_BASE_COL_B) * 255.f;
		m_color_vars.m_light_base.m_intensity = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_NATURAL_AMB_BASE_INTENSITY);

		m_color_vars.m_light_ray.m_r = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_RAY_COL_R) * 255.f;
		m_color_vars.m_light_ray.m_g = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_RAY_COL_G) * 255.f;
		m_color_vars.m_light_ray.m_b = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_RAY_COL_B) * 255.f;
		m_color_vars.m_light_ray.m_intensity = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_LIGHT_RAY_MULT);

		m_color_vars.m_correction.m_r = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_POSTFX_CORRECT_COL_R) * 255.f;
		m_color_vars.m_correction.m_g = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_POSTFX_CORRECT_COL_G) * 255.f;
		m_color_vars.m_correction.m_b = g_pointers->m_timecycle->get_var(TimeCycleVar_e::TCVAR_POSTFX_CORRECT_COL_B) * 255.f;
	}
	void set_var(TimeCycleVar_e var, float value, bool int_color = true) {
		g_pointers->m_timecycle->set_var(var, int_color ? value / 255.f : value);
	}
	void draw_color(str name, int& col, TimeCycleVar_e var) {
		draw->number(name, col, { 0, 255, 1, 0 }, true, [=] {
			set_var(var, col);
		});
	}
	void color() {
		draw->submenu_second("Rainbow", "rainbow_color", [] {
			draw->toggle("Sky", &g_hooking_features.m_colors.m_rainbow_sky);
			draw->toggle("Clouds", &g_hooking_features.m_colors.m_rainbow_clouds);
			draw->toggle("Moon", &g_hooking_features.m_colors.m_rainbow_moon);
		});
		draw->submenu_second("Liquids", "vfx_liquids", [] {
			draw->option("rainbow_blood_pool");
			draw->seperator("Main");
			draw->choose("Type", liquid_names, &selected);
			add_option<Framework::number<uint8_t>>("R", "", &g_pointers->m_vfx_liquid[selected].r, 0, 255, 1, 1);
			add_option<Framework::number<uint8_t>>("G", "", &g_pointers->m_vfx_liquid[selected].g, 0, 255, 1, 1);
			add_option<Framework::number<uint8_t>>("B", "", &g_pointers->m_vfx_liquid[selected].b, 0, 255, 1, 1);
		});
		draw->submenu_second("Main", "main_colors", update_vars, [] {
			draw->submenu_second("Correction", "correct_colors", [] {
				draw->number("R", m_color_vars.m_correction.m_r, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_POSTFX_CORRECT_COL_R, m_color_vars.m_correction.m_r);
					});
				draw->number("G", m_color_vars.m_correction.m_g, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_POSTFX_CORRECT_COL_G, m_color_vars.m_correction.m_g);
					});
				draw->number("B", m_color_vars.m_correction.m_b, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_POSTFX_CORRECT_COL_B, m_color_vars.m_correction.m_b);
					});
			});
			draw->submenu_second("Sun", "sun_color", [] {
				draw->number("R", m_color_vars.m_sun.m_r, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_SKY_SUN_COL_R, m_color_vars.m_sun.m_r);
				});
				draw->number("G", m_color_vars.m_sun.m_g, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_SKY_SUN_COL_G, m_color_vars.m_sun.m_g);
				});
				draw->number("B", m_color_vars.m_sun.m_b, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_SKY_SUN_COL_B, m_color_vars.m_sun.m_b);
				});
				draw->number("HDR", m_color_vars.m_sun.m_hdr, { 0, 1000, 0.1, 1 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_SKY_SUN_HDR, m_color_vars.m_sun.m_hdr);
				});
			});
			draw->submenu_second("Light Directional", "light_dir", [] {
				draw->number("R", m_color_vars.m_light_dir.m_r, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_DIR_COL_R, m_color_vars.m_light_dir.m_r);
					});
				draw->number("G", m_color_vars.m_light_dir.m_g, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_DIR_COL_G, m_color_vars.m_light_dir.m_g);
					});
				draw->number("B", m_color_vars.m_light_dir.m_b, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_DIR_COL_B, m_color_vars.m_light_dir.m_b);
					});
				});
			draw->submenu_second("Light Directional 2", "light_dir2", [] {
				draw->number("R", m_color_vars.m_light_dir2.m_r, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_DIRECTIONAL_AMB_COL_R, m_color_vars.m_light_dir2.m_r);
					});
				draw->number("G", m_color_vars.m_light_dir2.m_g, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_DIRECTIONAL_AMB_COL_G, m_color_vars.m_light_dir2.m_g);
					});
				draw->number("B", m_color_vars.m_light_dir2.m_b, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_DIRECTIONAL_AMB_COL_B, m_color_vars.m_light_dir2.m_b);
					});
			});
			draw->submenu_second("Light Base", "light_base", [] {
				draw->number("R", m_color_vars.m_light_base.m_r, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_NATURAL_AMB_BASE_COL_R, m_color_vars.m_light_base.m_r);
					});
				draw->number("G", m_color_vars.m_light_base.m_g, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_NATURAL_AMB_BASE_COL_G, m_color_vars.m_light_base.m_g);
					});
				draw->number("B", m_color_vars.m_light_base.m_b, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_NATURAL_AMB_BASE_COL_B, m_color_vars.m_light_base.m_b);
					});
				draw->number("Intensity", m_color_vars.m_light_base.m_intensity, { 0, 1000, 0.1, 1 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_NATURAL_AMB_BASE_INTENSITY, m_color_vars.m_light_base.m_intensity);
					});
				});
			draw->submenu_second("Light Ray", "light_ray", [] {
				draw->number("R", m_color_vars.m_light_ray.m_r, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_RAY_COL_R, m_color_vars.m_light_ray.m_r);
					});
				draw->number("G", m_color_vars.m_light_ray.m_g, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_RAY_COL_G, m_color_vars.m_light_ray.m_g);
					});
				draw->number("B", m_color_vars.m_light_ray.m_b, { 0, 255, 1, 0 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_RAY_COL_B, m_color_vars.m_light_ray.m_b);
					});
				draw->number("Intensity", m_color_vars.m_light_ray.m_intensity, { 0, 1000, 0.1, 1 }, true, [] {
					set_var(TimeCycleVar_e::TCVAR_LIGHT_RAY_MULT, m_color_vars.m_light_ray.m_intensity);
					});
				});
		});
	}
}
