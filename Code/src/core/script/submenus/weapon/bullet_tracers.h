#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::weapon {
	void bullet_tracers() {
		draw->option("bullet_tracers");
		draw->seperator("Settings");
		draw->option("bullet_tracers_rainbow");
		draw->option("bullet_tracer_fadeaway_speed");
	}
}
