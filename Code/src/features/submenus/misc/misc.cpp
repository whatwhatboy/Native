#include "misc.h"
#include "src/Natives/Natives.h"
#include "src/fiber/script/manager/script_manager.h"
#include "src/memory/pointers/pointers.h"
#include <src/utility/enum.h>
#include "src/features/feature_manager.h"
#include <src/hooking/hooking.h>
#include "misc/classes.h"
namespace Base {
	void add_vibration() {
		g_feature_manager.add<toggle_with_float_option>("shake", "Shake", &vibration::g_shake.m_enabled, &vibration::g_shake.m_settings.m_intensity, 0, 1000, 0.1, 1, false, get_func(vibration::g_shake.tick));
		g_feature_manager.add<float_option>("shake_delay", "Delay", &vibration::g_shake.m_settings.m_delay, 0, 5000, 1, 0);

		g_feature_manager.add<toggle_option>("disable_vibration", "Disable", "", &vibration::g_disable.m_enabled, get_func(vibration::g_disable.tick));
	}
	void add_cutscene() {
		g_feature_manager.add<toggle_option>("disable_cutscenes", "Disable", "", &cutscene::g_disable.m_enabled, get_func(cutscene::g_disable.tick));

		g_feature_manager.add<button_option>("stop_cutscene", "Stop", "", get_func(cutscene::g_buttons.stop));
		g_feature_manager.add<button_option>("set_cutscene_skippable", "Set Skippable", "", get_func(cutscene::g_buttons.set_skippable));
	}
	void add_graphics() {
		g_feature_manager.add<toggle_option>("reduce_ped_budget", "Reduce Ped Budget", "", &graphics::g_reduce_ped_budget.m_enabled, get_func(graphics::g_reduce_ped_budget.tick), get_func(graphics::g_reduce_ped_budget.on_disable));
		g_feature_manager.add<toggle_option>("reduce_vehicle_budget", "Reduce Vehicle Budget", "", &graphics::g_reduce_vehicle_budget.m_enabled, get_func(graphics::g_reduce_vehicle_budget.tick), get_func(graphics::g_reduce_vehicle_budget.on_disable));

		g_feature_manager.add<toggle_option>("render_hd_only", "Render HD Only", "", &graphics::g_render_hd_only.m_enabled, get_func(graphics::g_render_hd_only.tick), get_func(graphics::g_render_hd_only.on_disable));
	}
	void misc_options::add() {
		add_vibration();
		add_cutscene();
		add_graphics();
		g_feature_manager.add<toggle_with_float_option>("gta_1_cam", "GTA 1", &camera::g_gta_1.m_enabled, &camera::g_gta_1.m_settings.m_distance, 0, 100, 0.1, 1, false, get_func(camera::g_gta_1.tick), get_func(camera::g_gta_1.on_disable));
		g_feature_manager.add<toggle_option>("instant_alt_f4", "Instant Alt F4", "", &misc::random::g_instant_alt_f4.m_enabled, get_func(misc::random::g_instant_alt_f4.tick));

	}
}