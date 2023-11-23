#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::movement {
	void super_jump() {
		draw->option("super_jump");
		draw->seperator("Settings");
		draw->option("super_jump_force");
		draw->submenu_second("Rolling", "super_jump:rolling", [] {
			draw->option("uses_super_jump");
			draw->option("rolling_direction");
			draw->option("super_jump_rolling_speed");
		});
		draw->submenu_second("Custom", "super_jump:custom", [] {
			draw->option("uses_super_jump_2");
			draw->option("jump_forward_force");
			draw->option("jump_upward_force");
			draw->option("pushdown_force");
			draw->option("max_jump_height");
		});
	}
}
