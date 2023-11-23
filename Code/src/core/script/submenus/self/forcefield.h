#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self {
	void forcefield() {
		draw->option("forcefield");
		draw->seperator("Settings");
		draw->submenu_second("Excludes", "forcefield_excludes", [] {
			draw->option("forcefield_exclude_vehicles");
			inline_item
			draw->option("forcefield_exclude_peds");
			inline_item
			draw->option("forcefield_exclude_objects");
		});
		draw->option("forcefield_show_radius");
		draw->option("forcefield_radius");
		draw->option("forcefield_force");
	}
}
