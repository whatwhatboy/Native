#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::vehicle::movement {
	void acceleration() {
		draw->option("acceleration");
		draw->option("acceleration_speed");
	}
}
