#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "color.h"
#include "src/framework/option_types/toggle.h"
#include "clouds.h"
#include "weather.h"
#include "time.h"
#include "peds.h"
#include "ocean.h"
#include "dispatch.h"
namespace Base::submenus::world {
	using namespace Framework;
	void main() {
		if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::world) return;

		click_ui::setup_col("world");
		draw->submenu("Core", "world_core", [] {
			draw->option("game_pitch");
			draw->option("ped_esp");
			draw->option("waypoint_tracers");
		});
		draw->submenu("VFX", "world:vfx_engine", [] {
			auto settings{ g_pointers->m_ui_visual_settings };
			draw->submenu_second("Main", "world:color", submenus::world::color);
			draw->toggle_with_number<float>("Star Intensity", &g_hooking_features.m_colors.m_star_intensity_toggle, &g_hooking_features.m_colors.m_star_intensity, 0, 5000, 0.1, 1);
			draw->option("disable_sky");
			draw->number("Sky Multiplier", settings->m_sky_multiplier, { 0, 1000 });
			draw->number("Saturation", settings->m_desaturation, { 0, 1000 });
			draw->number("Reflection", settings->m_global_environment_reflection, { 0, 1000 });
			draw->number("Fog", g_pointers->m_game_visuals->m_fog_level, { 0, 1000, 0.0001, 4 });
			});
		draw->submenu("Ocean", "world_ocean", submenus::world::ocean);
		draw->submenu("Weather", "world_weather", submenus::world::weather);
		draw->submenu("Clouds", "world_clouds", submenus::world::clouds);
		click_ui::next_col();
		draw->submenu("Time", "world_time", submenus::world::time);
		draw->submenu("Dispatch", "world_dispatch", submenus::world::dispatch_on_click, submenus::world::dispatch_init);
		draw->submenu("Chams", "world_chams", [] {
			draw->option("chams_enabled");
			draw->seperator("Settings");
			draw->option("chams_rainbow");
			draw->option("chams_intensity");
			});
		draw->submenu("Glowing Pickups", "glowing_pickups", [] {
			draw->option("glowing_pickups");
			draw->seperator("Settings");
			draw->submenu_second("Color", "glowing_pickups_color", [] {
				draw->option("glowing_pickups_rainbow");
				draw->seperator("Main");
				draw->option("glowing_pickups_r");
				draw->option("glowing_pickups_g");
				draw->option("glowing_pickups_b");
				});
			draw->option("glowing_pickups_intensity");
			draw->option("glowing_pickups_range");
			});
		draw->submenu("Nearby", "nearby_entities", [] {
			draw->submenu_second("Peds", "nearby_peds", submenus::world::peds);
			draw->submenu_second("Pickups", "nearby_pickups", [] {
				draw->button("Teleport To Me", [] {
					for (auto pickup : g_pools->pickups()) {
						auto coords{ g_utils->coords() };
						ENTITY::SET_ENTITY_COORDS(pickup, coords.x, coords.y, coords.z, 0, 0, 0, false);
					}
				});
			});
		});
		click_ui::end_col();
	}
}
