#include "world.h"
#include "src/Natives/Natives.h"
#include "src/fiber/script/manager/script_manager.h"
#include "src/memory/pointers/pointers.h"
#include <src/utility/enum.h>
#include "src/features/feature_manager.h"
#include "misc/ped_esp.h"
#include "misc/weather.h"
#include "misc/waypoint_tracers.h"
#include "misc/alien_invasion.h"
#include "misc/vfx.h"
#include "misc/time.h"
#include "misc/glowing_pickups.h"
namespace Base {
	void register_script_patches() {
		
	}
	void add_alien_invasion() {
		g_feature_manager.add<toggle_option>("alien_invasion", "Enabled", "", &alien_invasion::enabled, alien_invasion::init);
	}
	void add_vfx() {
		g_feature_manager.add<toggle_option>("rainbow_blood_pool", "Rainbow Liquids", "", &world::vfx::blood::enabled, world::vfx::blood::init);

		//chams
		g_feature_manager.add<toggle_option>("chams_enabled", "Enabled", "", &world::vfx::chams::enabled, world::vfx::chams::init, world::vfx::chams::on_disable);
		g_feature_manager.add<toggle_option>("chams_rainbow", "Rainbow", "", &world::vfx::chams::rainbow);
		g_feature_manager.add<float_option>("chams_intensity", "Intensity", &world::vfx::chams::intensity, 0, 1000, 1, 0);

		g_feature_manager.add<toggle_option>("drain_ocean", "Drain", "", &world::vfx::remove_water::enabled, world::vfx::remove_water::tick);
	}
	void add_time() {
		g_feature_manager.add<toggle_option>("timelapse", "Timelapse", "", &world::time::timelapse::enabled, world::time::timelapse::init);

		g_feature_manager.add<toggle_option>("pause_time", "Pause", "", &world::time::pause::enabled, world::time::pause::tick);
	}
	void add_glowing_pickups() {
		g_feature_manager.add<toggle_option>("glowing_pickups", "Enabled", "", &world::pickups::glowing::enabled, world::pickups::glowing::init);
		g_feature_manager.add<toggle_option>("glowing_pickups_rainbow", "Rainbow", "", &world::pickups::glowing::rainbow);

		g_feature_manager.add<float_option>("glowing_pickups_intensity", "Intensity", &world::pickups::glowing::intensity, 0, 100, 0.1, 1);
		g_feature_manager.add<float_option>("glowing_pickups_range", "Range", &world::pickups::glowing::range, 0, 100, 0.1, 1);

		g_feature_manager.add<float_option>("glowing_pickups_r", "R", &world::pickups::glowing::m_color.r, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("glowing_pickups_g", "G", &world::pickups::glowing::m_color.g, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("glowing_pickups_b", "B", &world::pickups::glowing::m_color.b, 0, 255, 1, 0);
	}
	void world_options::add() {
		//add_alien_invasion();
		//register_script_patches();
		add_time();
		add_vfx();
		add_glowing_pickups();
		g_feature_manager.add<toggle_option>("ped_esp", "Ped ESP", "", &ped_esp::enabled, ped_esp::init);
		g_feature_manager.add<toggle_option>("disable_sky", "Disable Sky", "", &weather::disable_sky::enabled, weather::disable_sky::init, weather::disable_sky::on_disable);
		g_feature_manager.add<toggle_option>("waypoint_tracers", "Waypoint Tracers", "", &waypoint_tracers::enabled, waypoint_tracers::init);

		g_feature_manager.add<toggle_with_float_option>("lightning", "Lightning", &weather::lightning::enabled, &weather::lightning::delay, 0, 5000, 1, 0, false, weather::lightning::init);
		g_feature_manager.add<toggle_with_float_option>("game_pitch", "Game Pitch", &g_hooking_features.m_change_game_pitch, &g_hooking_features.m_game_pitch, 0, 5000, 1, 0);
	}
}