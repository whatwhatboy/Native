#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"

namespace Base::reflections {
	namespace water {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			ENTITY::SET_ENTITY_WATER_REFLECTION_FLAG(g_utils->vehicle(), false);
		}
		void on_disable() {
			ENTITY::SET_ENTITY_WATER_REFLECTION_FLAG(g_utils->vehicle(), true);
		}
	}
	namespace mirror {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			ENTITY::SET_ENTITY_MIRROR_REFLECTION_FLAG(g_utils->vehicle(), false);
		}
		void on_disable() {
			ENTITY::SET_ENTITY_MIRROR_REFLECTION_FLAG(g_utils->vehicle(), true);
		}
	}
}
