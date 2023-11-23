#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base::paint {
	namespace settings {
		std::vector<const char*> type = { "Normal", "Blood", "Mud", "Oil", "Water", "Water 2", "Glass" };
		int selected{ 0 };
		float r{ 255 };
		float g{ 0 };
		float b{ 0 };
		float a{ 255 };
		bool rainbow{ false };
		float scale{ 0.5 };
	}
	bool enabled{ false };
	void init() {
		if (settings::rainbow) {
			settings::r = g_rainbow.r;
			settings::g = g_rainbow.g;
			settings::b = g_rainbow.b;
		}
		if (PLAYER::IS_PLAYER_FREE_AIMING(g_utils->self_id()) && enabled) {
			int types[7] = { decal_types::splatters_paint, decal_types::solidPool_blood, decal_types::splatters_mud, decal_types::solidPool_oil, decal_types::liquidTrail_water, decal_types::solidPool_water, decal_types::weapImpact_glass_blood };
			Vector3 c;
			if (g_math->raycast(c))
				GRAPHICS::ADD_DECAL(types[settings::selected], c.x, c.y, c.z, 0, 0, -1, 0, 1.f, 0.0, settings::scale, settings::scale - 0.1, settings::r / 255.f, settings::g / 255.f, settings::b / 255.f, 1, -1, true, false, false);
		}
	}
}
