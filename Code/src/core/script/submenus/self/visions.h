#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self {
	vector_pair<str> cycles = {
			{ "Damage", "damage" },
			{ "Cops", "CopsSPLASH" },
			{ "Barry Fade Out", "BarryFadeOut" },
			{ "Water Lab", "WATER_lab" },
			{ "Dying", "dying" },
			{ "Red Mist", "REDMIST" },
			{ "Prologue Shootout", "prologue_shootout" },
			{ "Secret Camera", "secret_camera" },
			{ "Spectator Camera", "Multipayer_spectatorCam" },
			{ "UFO", "ufo" },
			{ "UFO Deathray", "ufo_deathray" },
			{ "Wobbly", "drug_wobbly" },
			{ "Killstreak", "MP_Killstreak" },
			{ "Hint", "Hint_cam" },
			{ "Black & White", "blackNwhite" },
			{ "Sniper", "sniper" },
			{ "Crane", "crane_cam" },
			{ "Bikers", "BikersSPLASH" },
			{ "Vagos", "VagosSPLASH" },
			{ "Vagos 2", "vagos" },
			{ "Cops", "cops" },
			{ "Spectator 1", "spectator1" },
			{ "Sunglasses", "sunglasses" },
			{ "Blurry", "CHOP" },
			{ "Stoned", "stoned" },
	};
	float vision_strength{ 1 };
	void visions() {
		draw->submenu("Thermal Vision", "thermal_vision", [] {
			draw->option("thermal_vision");
			draw->seperator("Settings");
			draw->submenu("Modifiers", "thermal_vision_modifiers", [] {
				draw->option("thermal_vision_modifiers");
				draw->seperator("Main");
				draw->option("thermal_vision_fade_start_distance");
				draw->option("thermal_vision_fade_end_distance");
				draw->option("thermal_vision_fade_max_thickness");
				draw->option("thermal_vision_noise_min");
				draw->option("thermal_vision_noise_max");
				draw->option("thermal_vision_highlight_intensity");
				draw->option("thermal_vision_highlight_noise");
			});
			draw->submenu("Heatscale", "thermal_vision_heatscale", [] {
				draw->option("thermal_vision_heatscale");
				draw->seperator("Main");
				draw->option("thermal_vision_heatscale_index");
				draw->option("thermal_vision_heatscale_intensity");
			});
			draw->submenu("Color", "thermal_vision_color", [] {
				draw->option("thermal_vision_color_enabled");
				draw->seperator("Main");
				draw->option("thermal_vision_color_r");
				draw->option("thermal_vision_color_g");
				draw->option("thermal_vision_color_b");
			});
		});
		draw->button("Clear", [] {
			GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
		});
		draw->seperator("List");
		draw->number("Strength", vision_strength, { 0, 1000, 1, 0 });
		for (auto tc : cycles) {
			draw->button(tc.first, [=] {
				GRAPHICS::SET_TIMECYCLE_MODIFIER(tc.second.c_str());
				GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(vision_strength);
			});
		}
	}
}
