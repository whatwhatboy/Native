#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self {
	void disables() {
		draw->submenu_second("Reflections", "reflection_disables", [] {
			draw->option("disable_reflections_water");
			draw->option("disable_reflections_mirror");
		});
		draw->option("eletrocution_ragdoll");
		inline_item
		draw->option("disable_arrests");
		draw->option("disable_dragging_out");
	}
}
