#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"
#include <src/rage/vehicle/CVehicleModelInfo.hpp>

namespace Base {
	namespace drive_on_water {
		bool enabled{ false };
		Entity object;
		void init() {
			if (!enabled) return;
			g_fiber_pool.queue([] {
				if (!g_utils->in_vehicle()) {
					if (ENTITY::DOES_ENTITY_EXIST(object)) {
						g_utils->delete_entity(object);
					}
					return;
				}

				float water_height{ 0.0f };
				WATER::GET_WATER_HEIGHT(g_utils->coords().x, g_utils->coords().y, g_utils->coords().z, &water_height);

				Vector3 adjusted{ g_utils->coords().x, g_utils->coords().y, water_height - 1.9f };

				if (g_utils->coords().z - water_height <= 3.f) {
					if (!ENTITY::DOES_ENTITY_EXIST(object)) {
						while (!STREAMING::HAS_MODEL_LOADED(0xC42C019A)) {
							STREAMING::REQUEST_MODEL(0xC42C019A);
							fiber::current()->wait();
						}
						if (object == NULL)
							object = OBJECT::CREATE_OBJECT(0xC42C019A, g_utils->coords().x, g_utils->coords().y, g_utils->coords().z, true, false, false);
						ENTITY::SET_ENTITY_VISIBLE(object, false, true);
					}
					else {
						ENTITY::SET_ENTITY_VISIBLE(object, false, true);
						ENTITY::SET_ENTITY_ROTATION(object, 180.f, 90.f, 180.f, 2, false);
						ENTITY::SET_ENTITY_COORDS(object, adjusted.x, adjusted.y, adjusted.z, true, false, false, true);
						ENTITY::FREEZE_ENTITY_POSITION(object, true);
					}
				}
				});
		}
		void on_disable() {
			g_fiber_pool.queue([] {
				g_utils->delete_entity(object);
			});
		}
	}
}
