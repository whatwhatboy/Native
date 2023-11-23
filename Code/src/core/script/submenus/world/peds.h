#pragma once
#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "src/framework/option_types/number.h"
#include <src/framework/option_types/button.h>

namespace Base::submenus::world {
	void peds() {
		draw->button("Kill", [] {
			for (auto ped : g_pools->peds())
				PED::APPLY_DAMAGE_TO_PED(ped, PED::GET_PED_MAX_HEALTH(ped) * 2, false, 0);
		});
		draw->button("Hands Up", [] {
			for (auto ped : g_pools->peds())
				TASK::TASK_HANDS_UP(ped, 5000, g_utils->self(), 0, 0);
		});
		draw->button("Ragdoll", [] {
			for (auto ped : g_pools->peds()) {
				auto forward_vector{ ENTITY::GET_ENTITY_FORWARD_VECTOR(ped) };
				PED::SET_PED_TO_RAGDOLL_WITH_FALL(ped, 1500, 2000, 1, -forward_vector.x, -forward_vector.y, -forward_vector.z, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
			}
		});
	}
}
