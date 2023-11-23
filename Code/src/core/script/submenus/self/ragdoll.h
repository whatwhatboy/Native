#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self {
	void ragdoll() {
		draw->option("disable_ragdoll");
		draw->option("ragdoll_fly");
		draw->option("bound_ankles");
		draw->option("ragdoll_on_q");
		draw->option("die_on_ragdoll");
		draw->seperator("Once");
		draw->button("Activate", [] {
			auto forward_vector{ ENTITY::GET_ENTITY_FORWARD_VECTOR(g_utils->self()) };
			PED::SET_PED_TO_RAGDOLL_WITH_FALL(g_utils->self(), 1500, 2000, 1, -forward_vector.x, -forward_vector.y, -forward_vector.z, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
		});
	}
}
