#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self {
	void collision() {
		draw->submenu_second("Entity", "collision:entity", [] {
			draw->option("collision_entity");
			draw->seperator("Settings");
			draw->submenu_second("Excludes", "collision:entity:excludes", [] {
				draw->option("collision_entity_exclude_vehicles");
				draw->option("collision_entity_exclude_peds");
				draw->option("collision_entity_exclude_objects");
			});
			draw->option("collision_entity_self");
			draw->option("collision_entity_vehicle");
		});
		draw->option("collision_reduced");
	}
}
 