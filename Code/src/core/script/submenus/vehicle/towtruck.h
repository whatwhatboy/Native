#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::vehicle {
	void towtruck() {
		draw->option("towtruck");
		draw->seperator("Settings");
		draw->option("towtruck_draw_line");
		draw->option("towtruck_set_rotation");
		draw->option("towtruck_frequency");
		draw->option("towtruck_ratio");
	}
}
