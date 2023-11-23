#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"

namespace Base::collison {
	namespace reduced {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			PED::SET_PED_CAPSULE(g_utils->self(), 0.001);
		}
		void on_disable() {
			PED::SET_PED_CAPSULE(g_utils->self(), false);
		}
	}
	namespace entity {
		namespace excludes {
			bool vehicle{ false };
			bool ped{ false };
			bool object{ false };
		}
		namespace settings {
			bool vehicle{ false };
			bool ped{ true };
		}
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			for (auto ent : g_pools->all(excludes::vehicle, excludes::ped, excludes::object)) {
				if (settings::vehicle) 
					ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(ent, g_utils->vehicle(), true);

				if (settings::ped && !g_utils->in_vehicle())
					ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(ent, g_utils->self(), true);
			}
		}
	}
}
