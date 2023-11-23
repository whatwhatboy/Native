#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/submenu_types/regular_submenu.h"

namespace Base::submenus::misc {
	void main() {
		if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::misc) return;

		draw->submenu("Core", "core_misc", [] {
			draw->option("gta_1_cam");
			draw->toggle("Online Checks", g_pointers->m_has_game_been_altered);
			draw->option("instant_alt_f4");
		});
		draw->submenu("Graphics", "graphics", [] {
			draw->option("reduce_ped_budget");
			draw->option("reduce_vehicle_budget");
			draw->option("render_hd_only");
			});
		draw->submenu("Vibration", "pad_vibration", [] {
			draw->option("disable_vibration");
			draw->seperator("Other");
			if (!"disable_vibration"_TF->is_toggled()) {
				draw->option("shake");
				draw->option("shake_delay");
			}
		});
		draw->submenu("Cutscene", "cutscene", [] {
			draw->option("disable_cutscenes");
			draw->seperator("Other");
			if (!"disable_cutscenes"_TF->is_toggled()) {
				draw->option("stop_cutscene");
				draw->option("set_cutscene_skippable");
			}
		});
		
	}
}
