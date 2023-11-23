#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base {
	namespace vehicle_weapons {
		namespace settings {
			int selected{ 79 };
			Vector3 offset{ 0.80f, 1.90f, -0.10f };
			float speed{ -1 };
			float delay{ 150 };
			bool trajectory{ false };
		}
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			Vector3 modelDimensionsMin, modelDimensionsMax;
			MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(g_utils->vehicle()), &modelDimensionsMin, &modelDimensionsMax);

			auto startLeft{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_utils->vehicle(), -(modelDimensionsMax.x + 0.25f - settings::offset.x), modelDimensionsMax.y + 1.25f - settings::offset.y, 0.1 - settings::offset.z) };
			auto startRight{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_utils->vehicle(), -modelDimensionsMax.x, modelDimensionsMax.y + 100.0f, 0.1f) };
			auto endLeft{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_utils->vehicle(), (modelDimensionsMax.x + 0.25f - settings::offset.x), modelDimensionsMax.y + 1.25f - settings::offset.y, 0.1 - settings::offset.z) };
			auto endRight{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_utils->vehicle(), modelDimensionsMax.x, modelDimensionsMax.y + 100.0f, 0.1f) };
			if (settings::trajectory) {
				GRAPHICS::DRAW_LINE(startLeft.x, startLeft.y, startLeft.z, startRight.x, startRight.y, startRight.z, 255, 255, 255, 255);
				GRAPHICS::DRAW_LINE(endLeft.x, endLeft.y, endLeft.z, endRight.x, endRight.y, endRight.z, 255, 255, 255, 255);
			}
			if (PLAYER::IS_PLAYER_PRESSING_HORN(g_utils->self_id())) {
				auto hash{ all_weapons_hash[settings::selected] };
				if (!WEAPON::HAS_WEAPON_ASSET_LOADED(hash))
					WEAPON::REQUEST_WEAPON_ASSET(hash, 31, 0);

				g_utils->timed_function(settings::delay, [=] {
					auto c{ ENTITY::GET_ENTITY_BONE_POSTION(g_utils->vehicle(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(g_utils->vehicle(), "weapon_1a")) };
					auto c3{ ENTITY::GET_ENTITY_BONE_POSTION(g_utils->vehicle(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(g_utils->vehicle(), "weapon_1b")) };
					Vector3 c2{}; g_math->raycast(c2);
					if (!c.empty())
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(c.x, c.y, c.z, g_utils->get_tracer_coords().second.x, g_utils->get_tracer_coords().second.y, g_utils->get_tracer_coords().second.z, 250, 1, hash, g_utils->self(), 1, 0, settings::speed);
					if (!c3.empty())
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(c3.x, c3.y, c3.z, g_utils->get_tracer_coords().second.x, g_utils->get_tracer_coords().second.y, g_utils->get_tracer_coords().second.z, 250, 1, hash, g_utils->self(), 1, 0, settings::speed);

					if (c.empty() && c3.empty()) {
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startLeft.x, startLeft.y, startLeft.z, startRight.x, startRight.y, startRight.z, 250, 1, hash, g_utils->self(), 1, 0, settings::speed);
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(endLeft.x, endLeft.y, endLeft.z, endRight.x, endRight.y, endRight.z, 250, 1, hash, g_utils->self(), 1, 0, settings::speed);
					}
				});
			}
		}

	}
}
