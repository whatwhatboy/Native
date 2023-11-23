#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"
#include <src/rage/vehicle/CVehicleModelInfo.hpp>

namespace Base::vehicle_particles {
	namespace settings {
		float scale[5] = { 0.5, 0.5, 0.5, 0.5, 0.5 };
		int delay[5] = { 0, 0, 0, 0, 0 };

		int selected[5];

		bool color_enabled[5] = { false, false, false, false, false };
		ColorInt color[5] = { {255, 255, 255, 255}, {255, 255, 255, 255} , {255, 255, 255, 255}, {255, 255, 255, 255}, {255, 255, 255, 255} };
		bool rainbow[5] = { false, false, false, false, false };

		bool selected_enabled[5] = { true, false, false, false, false };

	}
	void particle_on_bone(const char* bone, int selected) {
		STREAMING::REQUEST_NAMED_PTFX_ASSET(particles_data::data[selected].dict);
		GRAPHICS::USE_PARTICLE_FX_ASSET(particles_data::data[selected].dict);
		GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD2(particles_data::data[selected].asset, g_utils->vehicle_bone_coords(bone), { 0.f, 0.f, 0.f }, settings::scale[selected], false, false, false, true);
		if (settings::color_enabled[selected])
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(settings::color[selected].r / 255.f, settings::color[selected].g / 255.f, settings::color[selected].b / 255.f);
	}
	bool enabled{ false };
	void init() {
		if (!enabled) return;
		for (int i = 0; i < 5; i++) {
			if (settings::rainbow[i]) {
				settings::color[i].r = g_rainbow.r;
				settings::color[i].g = g_rainbow.g;
				settings::color[i].b = g_rainbow.b;
			}
		}

		if (settings::selected_enabled[0])
			particle_on_bone("wheel_lf", settings::selected[0]);
		if (settings::selected_enabled[1])
			particle_on_bone("wheel_lr", settings::selected[1]);
		if (settings::selected_enabled[2])
			particle_on_bone("wheel_rf", settings::selected[2]);
		if (settings::selected_enabled[3])
			particle_on_bone("wheel_rr", settings::selected[3]);
		if (settings::selected_enabled[4])
			particle_on_bone("exhaust", settings::selected[4]);
	}
}
