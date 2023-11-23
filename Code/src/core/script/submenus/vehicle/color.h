#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::vehicle {
	void color() {
		draw->submenu_second("Rainbow", "vehicle:color:rainbow", [] {
			draw->option("rainbow_primary");
		});
	}
}
