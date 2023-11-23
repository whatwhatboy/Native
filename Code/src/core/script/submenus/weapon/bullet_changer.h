#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::weapon {
	void bullet_changer() {
		draw->option("bullet_changer_enabled");
		draw->seperator("Settings");
		draw->option("bullet_changer_delay");
		draw->option("bullet_changer_speed");
		draw->option("bullet_changer_bullets");
	}
}
