#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self {
	void magnet() {
		draw->option("self_magnet");
		draw->submenu_second("Excludes", "self_magnet_excludes", [] {
			draw->option("self_magnet_exclude_vehicles");
			draw->option("self_magnet_exclude_objects");
			draw->option("self_magnet_exclude_peds");
			draw->option("self_magnet_exclude_pickups");
		});
		draw->submenu_second("Offsets", "self_magnet_offsets", [] {
			draw->option("self_magnet_offset_x");
			draw->option("self_magnet_offset_y");
			draw->option("self_magnet_offset_z");
		});
	}
}
