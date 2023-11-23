#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/icon_button.h"
#include "src/framework/option_types/button.h"
namespace Base::submenus::weapon {
	void particles() {
		draw->option("particle_gun");
		draw->option("particle_gun_always");
		draw->option("particle_gun_scale");
		draw->submenu_second("Color", "particle_gun_color", [] {
			draw->option("particle_gun_color_enabled");
			draw->option("particle_gun_rainbow");
			draw->seperator("Main");
			draw->option("particle_gun_r");
			draw->option("particle_gun_g");
			draw->option("particle_gun_b");
		});
		draw->seperator("List");
		for (int i = 0; i < "particle_gun_selected_particle"_CF->m_items.size(); i++) {
			if (particles_data::names[i] == particles_data::names[*"particle_gun_selected_particle"_CF->m_current_item]) {
				add_option<Framework::icon_button>(particles_data::names[i], "", "On", [=] {
					*"particle_gun_selected_particle"_CF->m_current_item = i;
				});
			}
			else {
				add_option<Framework::button>(particles_data::names[i], "", [=] {
					*"particle_gun_selected_particle"_CF->m_current_item = i;
				});
			}
		}
	}
}