#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::weapon::impacts {
	void teleport() {
		draw->option("teleport_gun");
		draw->seperator("Settings");
		draw->option("teleport_x_offset");
		draw->option("teleport_y_offset");
		draw->option("teleport_z_offset");
		draw->option("teleport_delay");
	}
}