#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "grenade.h"
namespace Base::bullet_tracers {
	struct tracer {
		Vector3 first, second;
		int alpha{ 255 };
		Vector3 color;
	};
	namespace settings {
		float fadeaway_speed{ 2 };
		bool rainbow{ false };
		Vector3 rainbow_color = { 255, 0, 0 };
		int time_to_fade_out{ 3000 };
	}
	bool enabled{ false };
	std::vector<tracer> tracers;
	void push_tracers() {
		if (!g_utils->shooting()) return;
		if (g_utils->weapon_bone_coords("gun_muzzle").empty()) return;
		tracers.push_back({ g_utils->get_tracer_coords().first, g_utils->get_tracer_coords().second, 255, settings::rainbow_color });
	}
	void init() {
		if (!enabled) return;

		if (settings::rainbow) {
			settings::rainbow_color.x = g_rainbow.r;
			settings::rainbow_color.y = g_rainbow.g;
			settings::rainbow_color.z = g_rainbow.b;
		}
		push_tracers();
		for (auto& get_tracer : tracers) {
			if (get_tracer.alpha > 0) {
				GRAPHICS::DRAW_LINE(get_tracer.first.x, get_tracer.first.y, get_tracer.first.z, get_tracer.second.x, get_tracer.second.y, get_tracer.second.z, get_tracer.color.x, get_tracer.color.y, get_tracer.color.z, get_tracer.alpha);

				if (get_tracer.alpha > 0) {
					get_tracer.alpha -= settings::fadeaway_speed;
				}
			}
		}

		grenade_trail::enabled = true;
	}
	void on_disable() {
		grenade_trail::enabled = false;
	}
}
