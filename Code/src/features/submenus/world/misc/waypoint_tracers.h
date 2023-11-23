#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base {
	namespace waypoint_tracers {
		bool enabled{ false };
		void init() {
			if (g_pointers->m_waypoint_data && enabled) {
				if (g_pointers->m_waypoint_data->m_points && g_pointers->m_waypoint_data->m_count) {
					for (uint32_t i = 0; i < g_pointers->m_waypoint_data->m_count; i++) {
						vector4<float> point{ g_pointers->m_waypoint_data->m_points[i] };
						vector4<float> next_point{ g_pointers->m_waypoint_data->m_points[i + 1] };
						if (!next_point.is_empty()) {
							GRAPHICS::DRAW_LINE(point.x, point.y, point.z + 2, next_point.x, next_point.y, next_point.z + 2, 255, 0, 0, 255);
						}
					}
				}
			}
		}
	}
}
