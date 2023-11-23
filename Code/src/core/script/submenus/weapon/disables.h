#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::weapon {
	void disables() {
		draw->option("bypass_interior_restrictions");
		draw->option("bypass_vehicle_restrictions");
		draw->option("disable_recoil");
		draw->option("disable_spread");
		draw->option("throwable_limits");
	}
}