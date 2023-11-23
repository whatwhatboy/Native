#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self {
	void ped_matrix() {
		draw->option("ped_width");
		draw->option("ped_height");
		draw->option("ped_lean");
	}
}
