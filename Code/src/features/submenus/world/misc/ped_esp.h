#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base::ped_esp {
	namespace settings {
		namespace excludes {
			bool players{};
			bool police{};
			bool normal_peds{};
			bool enemys;
		}
		const char* bone_lockon[3] = { "None", "Head", "Chest" };
		int selected{ 0 };
		int delay = 0;
	}
	bool enabled{ false };

	void init() {
		if (!enabled) return;
		for (auto ped : g_pools->peds()) {
			Vector3 offset;
			Color red{ 255, 0, 0, 255 };
			Color white{ 255, 255, 255, 255 };
			Color color{ PED::IS_PED_DEAD_OR_DYING(ped, 0) ? red : white };

			auto first_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, -(offset.x + 0.3f), offset.y - 0.3f, -0.9f) };
			auto first_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, -(offset.x + 0.3f), offset.y + 0.3f, -0.9f) };
			auto second_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, +(offset.x + 0.3f), offset.y - 0.3f, -0.9f) };
			auto second_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, +(offset.x + 0.3f), offset.y + 0.3f, -0.9f) };
			auto third_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + -0.3f, +(offset.y + 0.3f), -0.9f) };
			auto third_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + 0.3f, +(offset.y + 0.3f), -0.9f) };
			auto fourth_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + -0.3f, -(offset.y + 0.3f), -0.9f) };
			auto fourth_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + 0.3f, -(offset.y + 0.3f), -0.9f) };
			auto fith_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, -(offset.x + 0.3f), offset.y - 0.3f, 0.9f) };
			auto fith_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, -(offset.x + 0.3f), offset.y + 0.3f, 0.9f) };
			auto sixth_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, +(offset.x + 0.3f), offset.y - 0.3f, 0.9f) };
			auto sixth_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, +(offset.x + 0.3f), offset.y + 0.3f, 0.9f) };
			auto seventh_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + -0.3f, +(offset.y + 0.3f), 0.9f) };
			auto seventh_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + 0.3f, +(offset.y + 0.3f), 0.9f) };
			auto eigth_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + -0.3f, -(offset.y + 0.3f), 0.9f) };
			auto eigth_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + 0.3f, -(offset.y + 0.3f), 0.9f) };
			auto nineth_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + 0.3f, -(offset.y + 0.3f), -0.9f) };
			auto nineth_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + 0.3f, -(offset.y + 0.3f), 0.9f) };
			auto tenth_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + -0.3f, -(offset.y + -0.3f), -0.9f) };
			auto tenth_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + -0.3f, -(offset.y + -0.3f), 0.9f) };
			auto eleventh_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + -0.3f, +(offset.y + -0.3f), -0.9f) };
			auto eleventh_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + -0.3f, +(offset.y + -0.3f), 0.9f) };
			auto twelvth_from{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + 0.3f, +(offset.y + 0.3f), -0.9f) };
			auto twelvth_to{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, offset.x + 0.3f, +(offset.y + 0.3f), 0.9f) };


			GRAPHICS::DRAW_LINE(first_from.x, first_from.y, first_from.z, first_to.x, first_to.y, first_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(second_from.x, second_from.y, second_from.z, second_to.x, second_to.y, second_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(third_from.x, third_from.y, third_from.z, third_to.x, third_to.y, third_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(fourth_from.x, fourth_from.y, fourth_from.z, fourth_to.x, fourth_to.y, fourth_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(fith_from.x, fith_from.y, fith_from.z, fith_to.x, fith_to.y, fith_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(sixth_from.x, sixth_from.y, sixth_from.z, sixth_to.x, sixth_to.y, sixth_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(seventh_from.x, seventh_from.y, seventh_from.z, seventh_to.x, seventh_to.y, seventh_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(eigth_from.x, eigth_from.y, eigth_from.z, eigth_to.x, eigth_to.y, eigth_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(nineth_from.x, nineth_from.y, nineth_from.z, nineth_to.x, nineth_to.y, nineth_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(tenth_from.x, tenth_from.y, tenth_from.z, tenth_to.x, tenth_to.y, tenth_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(eleventh_from.x, eleventh_from.y, eleventh_from.z, eleventh_to.x, eleventh_to.y, eleventh_to.z, color.r, color.g, color.b, color.a);
			GRAPHICS::DRAW_LINE(twelvth_from.x, twelvth_from.y, twelvth_from.z, twelvth_to.x, twelvth_to.y, twelvth_to.z, color.r, color.g, color.b, color.a);
		}
	}
}
