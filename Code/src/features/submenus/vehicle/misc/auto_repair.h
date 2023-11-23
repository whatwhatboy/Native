#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base::auto_repair {
	namespace settings {
		std::vector<ccp> method = { "Smart", "Strong", "Constant", };
		int selected{ 0 };
	}
	bool enabled{ false };
	void init() {
		if (!enabled) return;

		if (settings::selected == 2) {
			VEHICLE::SET_VEHICLE_STRONG(g_utils->vehicle(), true);
			return;
		}

		if (!VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(g_utils->vehicle()) && settings::selected == 0) return;

		VEHICLE::SET_VEHICLE_FIXED(g_utils->vehicle());
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(g_utils->vehicle());
	}
	void on_disable() {
		VEHICLE::SET_VEHICLE_STRONG(g_utils->vehicle(), false);
	}
}
