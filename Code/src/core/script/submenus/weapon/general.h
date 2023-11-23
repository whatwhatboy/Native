#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::weapon {
	void infinite() {
		draw->option("infinite_lockon_range");
		draw->option("infinite_range");
	}
}