#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::vehicle {
	void stick_to_ground() {
		draw->option("stick_to_ground");
		draw->seperator("Settings");
		draw->option("stick_to_ground_force");
	}
}
