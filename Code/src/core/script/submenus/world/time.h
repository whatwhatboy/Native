#pragma once
#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "src/framework/option_types/number.h"
#include <src/framework/option_types/button.h>

namespace Base::submenus::world {
	using namespace Framework;
	int hour{ 0 };
	void time() {
		draw->option("timelapse");
		draw->option("pause_time");
		draw->number("Hour", hour, { 0, 23, 1, 0 }, true, [] {
			CLOCK::SET_CLOCK_TIME(hour, 0, 0);
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(hour, 0, 0);
		});
   }
}
