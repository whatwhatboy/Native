#pragma once
#include "natives/natives.h"
#include "features/utils/utils.h"
#include <utility/enum.h>

namespace Base::world::disables {
	namespace hotwiring {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			for (auto veh : g_pools->vehicles())
				VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(veh, false);
		}
	}
}
