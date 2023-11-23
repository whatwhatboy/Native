#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base::stick_to_ground {
	namespace settings {
		const char* method[2] = { "Force", "Set" };
		int pos{ 0 };
		float force{ 5 };
	}
	bool enabled{ false };
	void init() {
		if (!enabled) return;
		switch (settings::pos) {
		case 0:
			if (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(g_utils->vehicle()))
				ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->vehicle(), true, 0, 0, -settings::force, 0, 0, 0, true, true, true, true, false, true);
			break;
		case 1:
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(g_utils->vehicle(), 0);
			break;
		}
	}
}
