#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self {
	int max{ 0 };
	int max2{ 0 };
	int drawable[10];
	int texture[10];
	int get_from_name(str name) {
		if (name == "face") return 0;
		else if (name == "head") return 1;
		else if (name == "hair") return 2;
		else if (name == "torso") return 3;
		else if (name == "torso2") return 11;
		else if (name == "legs") return 4;
		else if (name == "hands") return 5;
		else if (name == "feet") return 6;
		else if (name == "eyes") return 7;
		else if (name == "accessories") return 8;
		else if (name == "vests") return 9;
		else if (name == "decals") return 10;
	}
	std::vector<ccp> component_names = {
			"Face",
			"Masks",
			"Hair",
			"Gloves",
			"Tops",
			"Legs",
			"Parachutes/Bags",
			"Feet",
			"Accessories",
			"Torso",
			"Body Armour",
			"Decals",
	};
	std::vector<ccp> component_names2 = {
			"face",
			"head",
			"hair",
			"torso",
			"torso2",
			"legs",
			"hands",
			"feet",
			"eyes",
			"accessories",
			"vests",
			"decals"
	};
	int selected_component{ 0 };
	void populate_drawable() {
		g_fiber_pool.queue([=] {
			max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(g_utils->self(), get_from_name(component_names2[selected_component]));

			drawable[get_from_name(component_names2[selected_component])] = PED::GET_PED_DRAWABLE_VARIATION(g_utils->self(), get_from_name(component_names2[selected_component]));
		});
	}
	void outfit_editor() {
		draw->choose("Component", component_names, &selected_component, true, populate_drawable);
		draw->number("Drawable", &drawable[get_from_name(component_names2[selected_component])], { 0, (float)max, 1, 0 }, true, [] {
			g_fiber_pool.queue([=] {
				PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), get_from_name(component_names2[selected_component]), drawable[get_from_name(component_names2[selected_component])], 0, 0);

				max2 = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(g_utils->self(), get_from_name(component_names2[selected_component]), drawable[get_from_name(component_names2[selected_component])]);
			});
		});
		draw->number("Texture", &texture[get_from_name(component_names2[selected_component])], { 0, (float)max2, 1, 0 }, true, [] {
			g_fiber_pool.queue([=] {
				PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), get_from_name(component_names2[selected_component]), drawable[get_from_name(component_names2[selected_component])], texture[get_from_name(component_names2[selected_component])], 0);
			});
		});
	}
}
