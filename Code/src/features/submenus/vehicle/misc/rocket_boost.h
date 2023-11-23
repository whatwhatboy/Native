#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"
#include <src/rage/vehicle/CVehicleModelInfo.hpp>

namespace Base::rocket_boost {
	float percentage;
	float refill_time;
	namespace infinite {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			if (VEHICLE::GET_HAS_ROCKET_BOOST(g_utils->vehicle()))
				VEHICLE::SET_ROCKET_BOOST_FILL(g_utils->vehicle(), 100.0f);
		}
	}
	namespace always_active {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			if (VEHICLE::GET_HAS_ROCKET_BOOST(g_utils->vehicle()))
				VEHICLE::SET_ROCKET_BOOST_ACTIVE(g_utils->vehicle(), true);
		}
	}
}
