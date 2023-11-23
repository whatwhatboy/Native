#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::weapon {
	void magnet() {
		draw->option("magnet");
		draw->seperator("Settings");
		draw->submenu_second("Sphere", "magnet:sphere_settings", [] {
			draw->option("magnet_sphere");
			draw->option("Settings");
			draw->option("magnet_sphere_size");
			draw->option("magnet_sphere_pitch");
			draw->option("magnet_sphere_roll");
			draw->option("magnet_sphere_yaw");
		});
		draw->submenu_second("Excludes", "magnet:excludes", [] {
			draw->option("magnet_exclude_vehicles");
			draw->option("magnet_exclude_peds");
			draw->option("magnet_exclude_objects");
		});
		draw->option("magnet_zoom");
	}
}