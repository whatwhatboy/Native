#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base::world::pickups {
	namespace glowing {
		bool enabled{ false };
		bool rainbow{ false };
		color<float> m_color{0, 150, 255, 255};
		float intensity{ 1 };
		float range{ 1 };
		void init() {
			if (!enabled) return;
			
			if (rainbow) {
				m_color = g_rainbow.as<float>();
			}
			for (auto pickup : g_pools->pickups()) {
				auto c{ g_utils->coords(pickup) };
				GRAPHICS::DRAW_LIGHT_WITH_RANGE(c.x, c.y, c.z, m_color.r, m_color.g, m_color.b, range, intensity);
			}
		}
	}
}
