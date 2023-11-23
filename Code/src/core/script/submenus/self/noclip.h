#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::movement {
	void noclip() {
		draw->option("no_clip");
		draw->option("no_clip_animation");
		draw->seperator("Settings");
		draw->option("no_clip_set_rotation");
		draw->option("no_clip_transparent");
	}
}
