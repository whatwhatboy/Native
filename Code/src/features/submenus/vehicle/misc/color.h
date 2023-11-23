#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"

namespace Base::vehicle_color {
	namespace primary {
		bool rainbow{ false };
		void init() {
			if (!rainbow) return;
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(g_utils->vehicle(), g_rainbow.r, g_rainbow.g, g_rainbow.b);
		}
	}
	namespace secondary {
		bool rainbow{ false };
		void init() {
			if (!rainbow) return;
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(g_utils->vehicle(), g_rainbow.r, g_rainbow.g, g_rainbow.b);
		}
	}
	namespace neons {
		bool rainbow{ false };
		void init() {
			if (!rainbow) return;
			VEHICLE::SET_VEHICLE_NEON_COLOUR(g_utils->vehicle(), g_rainbow.r, g_rainbow.g, g_rainbow.b);
		}
	}
}
