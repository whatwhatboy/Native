#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self {
	void regeneration() {
		draw->option("regeneration");
		draw->seperator("Settings");
		draw->option("regen_health");
		inline_item
		draw->option("regen_armor");
		draw->option("regen_delay");
		draw->option("regen_amount");
		draw->seperator("Game");
		draw->option("stamina_regen");
	}
}
