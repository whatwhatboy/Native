#include "Player.h"
#include "src/Natives/Natives.h"
#include "src/fiber/script/manager/script_manager.h"
#include "src/memory/pointers/pointers.h"
#include <src/utility/enum.h>
#include <src/hooking/hooking.h>
#include "misc/reflections.h"
#include "misc/misc.h"
#include "misc/config_flags.hpp"
#include "misc/collison.h"
#include "misc/ped_matrix.h"
#include "misc/classes.h"
#include "src/features/feature_manager.h"
#include "misc/regeneration.cpp"
#include "misc/no_clip.cpp"
#include "misc/godmode.cpp"
#include "misc/ragdoll/ragdoll.hpp"
#include "misc/movement/movement.hpp"

namespace Base {
	void never_wanted() {
		if (!g_player_options.never_wanted_t) return;

		PLAYER::SET_PLAYER_WANTED_LEVEL(g_utils->self_id(), 0, 0);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(g_utils->self_id(), 0);
	}


	float heading{};
	bool forced_jump{};
	void add_reflections() {
		g_feature_manager.add<toggle_option>("disable_reflections_water", "Water", "", &reflections::water::enabled, reflections::water::init, reflections::water::on_disable);
		g_feature_manager.add<toggle_option>("disable_reflections_mirror", "Mirror", "", &reflections::mirror::enabled, reflections::mirror::init, reflections::mirror::on_disable);
	}
	void add_config_flags() {
		g_feature_manager.add<toggle_option>("disable_wanted_level_sharing", "Disable Sharing", "Disables wanted sharing", &config_flags::g_disable_wanted_level_sharing.m_enabled, get_func(config_flags::g_disable_wanted_level_sharing.init), get_func(config_flags::g_disable_wanted_level_sharing.on_disable));
		g_feature_manager.add<toggle_option>("eletrocution_ragdoll", "Eletrocution Ragdoll", "", &config_flags::g_electrocution_ragdoll.m_enabled, get_func(config_flags::g_electrocution_ragdoll.init), get_func(config_flags::g_electrocution_ragdoll.on_disable));

		g_feature_manager.add<toggle_option>("swimming", "Swimming", "", &config_flags::g_swimming.m_enabled, get_func(config_flags::g_swimming.init), get_func(config_flags::g_swimming.on_disable));
		g_feature_manager.add<toggle_option>("always_aiming", "Always Aiming", "Makes you aim you're gun.", &config_flags::g_always_aiming.m_enabled, get_func(config_flags::g_always_aiming.init), get_func(config_flags::g_always_aiming.on_disable));
		g_feature_manager.add<toggle_option>("disable_arrests", "Arrests", "", &config_flags::g_disable_arrests.m_enabled, get_func(config_flags::g_disable_arrests.init), get_func(config_flags::g_disable_arrests.on_disable));
		g_feature_manager.add<toggle_option>("disable_dragging_out", "Dragging Out", "", &disable_drag_outs::enabled, disable_drag_outs::tick, disable_drag_outs::on_disable);
	}
	void collision() {
		g_feature_manager.add<toggle_option>("collision_entity", "Enabled", "", &collison::entity::enabled, collison::entity::init);

		g_feature_manager.add<toggle_option>("collision_entity_self", "Self", "", &collison::entity::settings::ped);
		g_feature_manager.add<toggle_option>("collision_entity_vehicle", "Vehicle", "", &collison::entity::settings::vehicle);

		//excludes
		g_feature_manager.add<toggle_option>("collision_entity_exclude_vehicles", "Vehicles", "", &collison::entity::excludes::vehicle);
		g_feature_manager.add<toggle_option>("collision_entity_exclude_peds", "Peds", "", &collison::entity::excludes::ped);
		g_feature_manager.add<toggle_option>("collision_entity_exclude_objects", "Objects", "", &collison::entity::excludes::object);
	}
	void add_no_clip() {
		g_feature_manager.add<toggle_with_float_option>("no_clip", "Enabled", "Moves you around the map.", &g_noclip.m_enabled, g_noclip.m_settings.m_speed_num, true, get_func(g_noclip.init));

		g_feature_manager.add<toggle_option>("no_clip_set_rotation", "Set Rotation", "", &g_noclip.m_settings.m_set_rotation);
		g_feature_manager.add<choose_option>("no_clip_animation", "Animation", "", g_noclip.m_settings.m_types, &g_noclip.m_settings.m_type_pos);
		g_feature_manager.add<toggle_with_float_option>("no_clip_transparent", "Transparent", "", &g_noclip.m_settings.m_transparent, &g_noclip.m_settings.m_transparent_value, 0, 255, 1, 0);
	}
	void add_super_jump() {
		g_feature_manager.add<toggle_with_choose_option>("super_jump", "Enabled", &g_superjump.m_enabled, g_superjump.m_settings.m_type, &g_superjump.m_settings.m_type_pos, false, get_func(g_superjump.init), get_func(g_superjump.on_disable));
		g_feature_manager.add<float_option>("jump_forward_force", "Jump Forward Force", "", &g_superjump.m_settings.m_jump_forward_force, 0, 100, 0.5, 1);
		g_feature_manager.add<float_option>("jump_upward_force", "Jump Upward Force", "", &g_superjump.m_settings.m_jump_upward_force, 0, 100, 0.5, 1);
		g_feature_manager.add<float_option>("pushdown_force", "Pushdown Force", "", &g_superjump.m_settings.m_push_down_force, 0, 50, 0.5, 1);
		g_feature_manager.add<float_option>("max_jump_height", "Max Jump Height", "", &g_superjump.m_settings.m_max_jump_distance, 0, 15, 0.5, 1);
		g_feature_manager.add<toggle_option>("uses_super_jump", "Uses Super Jump", "", &g_superjump.m_settings.m_rolling.m_use_super_jump);
		g_feature_manager.add<toggle_option>("uses_super_jump_2", "Uses Super Jump", "", &g_superjump.m_settings.m_infinite_jump);
		g_feature_manager.add<toggle_with_float_option>("super_jump_force", "Force", "", &g_superjump.m_settings.m_add_force, &g_superjump.m_settings.m_force, 0, 50, 0.1, 1);
		g_feature_manager.add<float_option>("super_jump_rolling_speed", "Speed", "", &g_superjump.m_settings.m_rolling.m_speed, 0, 100, 1, 0);
		g_feature_manager.add<choose_option>("rolling_direction", "Direction", "", g_superjump.m_settings.m_rolling.m_flip_type, &g_superjump.m_settings.m_rolling.m_flip_pos);
	}
	void add_thresholds() {
		g_feature_manager.add<float_option>("hurt_threshold", "Hurt", "", &g_utils->cped()->m_hurt_health_threshold, 0, 400, 1, 0);
		g_feature_manager.add<float_option>("dying_threshold", "Dying", "", &g_utils->cped()->m_dying_health_threshold, 0, 400, 1, 0);
		g_feature_manager.add<float_option>("fatigued_threshold", "Fatigued", "", &g_utils->cped()->m_fatigued_health_threshold, 0, 400, 1, 0);
		g_feature_manager.add<float_option>("injured_threshold", "Injured", "", &g_utils->cped()->m_injured_health_threshold, 0, 400, 1, 0);
	}
	float wanted_level{};
	bool run_speed{ false };
	bool swim_speed{ false };
	void add_ped_matrix() {
		g_feature_manager.add<toggle_with_float_option>("ped_width", "Width", "", &ped_matrix::width::enabled, &ped_matrix::width::value, -100, 100, 0.1, 1, true, ped_matrix::width::init);
		g_feature_manager.add<toggle_with_float_option>("ped_height", "Height", "", &ped_matrix::height::enabled, &ped_matrix::height::value, -100, 100, 0.1, 1, true, ped_matrix::height::init);
		g_feature_manager.add<toggle_with_float_option>("ped_lean", "Lean", "", &ped_matrix::lean::enabled, &ped_matrix::lean::value, -100, 100, 0.1, 1, true, ped_matrix::lean::init);
	}
	void player_options::add_feature_subs() {
		m_feature_subs.push_back({ "forcefield", [] {
			g_feature_manager.add<toggle_with_choose_option>("forcefield", "Enabled", "", &g_forcefield.m_enabled, g_forcefield.m_settings.m_type, &g_forcefield.m_settings.m_type_pos, false, get_func(g_forcefield.init));
			g_feature_manager.add<toggle_option>("forcefield_show_radius", "Show Radius", "", &g_forcefield.m_settings.m_show_radius);

			g_feature_manager.add<float_option>("forcefield_radius", "Radius", "", &g_forcefield.m_settings.m_radius, 0, 100, 0.1, 1);
			g_feature_manager.add<float_option>("forcefield_force", "Force", "", &g_forcefield.m_settings.m_force_multiplier, 0, 100, 0.1, 1);
			g_feature_manager.add<toggle_option>("forcefield_exclude_vehicles", "Vehicles", "", &g_forcefield.m_settings.m_exclude_vehicles);
			g_feature_manager.add<toggle_option>("forcefield_exclude_peds", "Peds", "", &g_forcefield.m_settings.m_exclude_peds);
			g_feature_manager.add<toggle_option>("forcefield_exclude_objects", "Objects", "", &g_forcefield.m_settings.m_exclude_objects);
		} });
		
		m_feature_subs.push_back({ "spinbot", [] {
			g_feature_manager.add<toggle_option>("spinbot", "Enabled", "", &g_spinbot.m_enabled, [] { g_spinbot.init(); });
			g_feature_manager.add<toggle_with_choose_option>("spin_bot_first_rotation", "L/R", &g_spinbot.m_settings.m_first_rotation, g_spinbot.m_settings.m_direction, &g_spinbot.m_settings.m_direction_pos);
			g_feature_manager.add<toggle_with_choose_option>("spin_bot_second_rotation", "F/B", &g_spinbot.m_settings.m_second_rotation, g_spinbot.m_settings.m_direction_2, &g_spinbot.m_settings.m_direction_pos2);
			g_feature_manager.add<float_option>("spinbotSpeed", "Speed", "", &g_spinbot.m_settings.m_speed, 0, 100, 1, 0);
		} });

		m_feature_subs.push_back({ "camera", [] {
			g_feature_manager.add<toggle_with_float_option>("fov", "FOV", &g_fov.m_enabled, g_fov.m_settings.m_value_num, true, get_func(g_fov.init), get_func(g_fov.on_disable));
		} });

		m_feature_subs.push_back({ "regeneration", [=] {
			g_feature_manager.add<toggle_option>("regeneration", "Enabled", "", &g_regeneration.m_enabled, [] { g_regeneration.init(); });
			g_feature_manager.add<toggle_option>("regen_health", "Health", "", &g_regeneration.m_settings.m_health);
			g_feature_manager.add<toggle_option>("regen_armor", "Armor", "", &g_regeneration.m_settings.m_armor);

			g_feature_manager.add<float_option>("regen_delay", "Delay", "", &g_regeneration.m_settings.m_delay, 0, 5000, 1, 0);
			g_feature_manager.add<float_option>("regen_amount", "Amount", "", &g_regeneration.m_settings.m_amount, 0, 400, 1, 0);
		} });

		m_feature_subs.push_back({ "Movement", [] {
			g_feature_manager.add<toggle_with_float_option>("slide_run", "Slide", "", &slide_run::enabled, &slide_run::speed, 0, 100, 0.1, 1, false, slide_run::init);

			g_feature_manager.add<toggle_option>("walk_underwater", "Walk Underwater", "", &walk_underwater::enabled, walk_underwater::init, walk_underwater::on_disable);
			g_feature_manager.add<toggle_option>("walk_on_air", "Walk On Air", "", &walk_on_air::enabled, walk_on_air::init, walk_on_air::on_disable);

			g_feature_manager.add<toggle_option>("freeze_self", "Freeze", "", &movement::g_freeze.m_enabled, get_func(movement::g_freeze.init), get_func(movement::g_freeze.on_disable));
			g_feature_manager.add<toggle_option>("walk_on_water", "Walk On Water", "", &walk_on_water::enabled, walk_on_water::tick, walk_on_water::on_disable);

			g_feature_manager.add<float_option>("run_speed", "Run Speed", "", &g_utils->cped()->m_player_info->m_run_speed, 0, 100, 0.1, 1);
			g_feature_manager.add<float_option>("swim_speed", "Swim Speed", "", &g_utils->cped()->m_player_info->m_swim_speed, 0, 100, 0.1, 1);
		} });

		m_feature_subs.push_back({ "Superman", [] {
			g_feature_manager.add<toggle_option>("superman", "Enabled", "", &superman::enabled, superman::init, superman::on_disable);

			g_feature_manager.add<float_option>("forward_force", "Forward Force", "", &superman::settings::speed, 0, 100, 0.5, 1);
			g_feature_manager.add<float_option>("upward_force", "Upward Force", "", &superman::settings::upward_force, 0, 100, 0.5, 1);
			g_feature_manager.add<toggle_option>("rise_on_collision", "Rise On Collision", "", &superman::settings::rise_on_collison);
		} });

		m_feature_subs.push_back({ "Ragdoll", [] {
			g_feature_manager.add<toggle_option>("disable_ragdoll", "Disable", "", &ragdoll::g_no_ragdoll.m_enabled, get_func(ragdoll::g_no_ragdoll.init), get_func(ragdoll::g_no_ragdoll.on_disable));
			g_feature_manager.add<toggle_option>("bound_ankles", "Bound Ankles", "", &ragdoll::g_bound_ankles.m_enabled, get_func(ragdoll::g_bound_ankles.init), get_func(ragdoll::g_bound_ankles.on_disable));

			g_feature_manager.add<toggle_option>("ragdoll_on_q", "On Q", "", &ragdoll::g_on_q.m_enabled, get_func(ragdoll::g_on_q.init));
			g_feature_manager.add<toggle_option>("ragdoll_fly", "Fly", "", &ragdoll::g_fly.m_enabled, get_func(ragdoll::g_fly.init));
			g_feature_manager.add<toggle_option>("die_on_ragdoll", "Die", "", &ragdoll::g_die.m_enabled, get_func(ragdoll::g_die.tick));
		} });

		m_feature_subs.push_back({ "Thermal Vision", [] {
			g_feature_manager.add<toggle_option>("thermal_vision", "Enabled", "", &thermal_vision::enabled, thermal_vision::tick, thermal_vision::on_disable);

			g_feature_manager.add<toggle_option>("thermal_vision_modifiers", "Enabled", "", &thermal_vision::settings::modifiers);
			g_feature_manager.add<float_option>("thermal_vision_fade_start_distance", "Fade Start Distance", "", &thermal_vision::settings::fade_start_distance, 0, 5000, 1, 0);
			g_feature_manager.add<float_option>("thermal_vision_fade_end_distance", "Fade End Distance", "", &thermal_vision::settings::fade_end_distance, 0, 5000, 1, 0);
			g_feature_manager.add<float_option>("thermal_vision_fade_max_thickness", "Max Thickness", "", &thermal_vision::settings::max_thickness, 0, 10000.0, 1, 0);
			g_feature_manager.add<float_option>("thermal_vision_noise_min", "Noise Min", "", &thermal_vision::settings::noise_min, 0, 1000.0, 1, 0);
			g_feature_manager.add<float_option>("thermal_vision_noise_max", "Noise Max", "", &thermal_vision::settings::noise_max, 0, 1000.0, 1, 0);

			g_feature_manager.add<float_option>("thermal_vision_highlight_intensity", "Highlight Intensity", "", &thermal_vision::settings::highlight_intensity, 0, 1000.0, 1, 0);
			g_feature_manager.add<float_option>("thermal_vision_highlight_noise", "Highlight Noise", "", &thermal_vision::settings::highlight_noise, 0, 1000.0, 1, 0);

			g_feature_manager.add<toggle_option>("thermal_vision_heatscale", "Enabled", "", &thermal_vision::settings::heatscale_modifiers);
			g_feature_manager.add<float_option>("thermal_vision_heatscale_index", "Index", "", &thermal_vision::settings::heatscale_index, 0, 1000.0, 1, 0);
			g_feature_manager.add<float_option>("thermal_vision_heatscale_intensity", "Intensity", "", &thermal_vision::settings::heatscale_intensty, 0, 1000.0, 1, 0);

			g_feature_manager.add<toggle_option>("thermal_vision_color_enabled", "Enabled", "", &thermal_vision::settings::color_enabled);
			g_feature_manager.add<float_option>("thermal_vision_color_r", "R", "", &thermal_vision::settings::rear_color.r, color_modifiers);
			g_feature_manager.add<float_option>("thermal_vision_color_g", "G", "", &thermal_vision::settings::rear_color.g, color_modifiers);
			g_feature_manager.add<float_option>("thermal_vision_color_b", "B", "", &thermal_vision::settings::rear_color.b, color_modifiers);
		} });

		m_feature_subs.push_back({ "Outfit Editor", [] {
			g_feature_manager.add<toggle_option>("tron_loop", "Tron Loop", "", &g_tron_loop.m_enabled, get_func(g_tron_loop.init));
		} });

		m_feature_subs.push_back({ "Magnet", [] {
			g_feature_manager.add<toggle_with_float_option>("self_magnet", "Enabled", "", &g_magnet.m_enabled, &g_magnet.m_settings.m_main_velocity, 0, 1000, 0.1, 1, false, get_func(g_magnet.init));

			g_feature_manager.add<toggle_option>("self_magnet_exclude_vehicles", "Vehicles", "", &g_magnet.m_settings.m_excludes.m_vehicles);
			g_feature_manager.add<toggle_option>("self_magnet_exclude_objects", "Objects", "", &g_magnet.m_settings.m_excludes.m_objects);
			g_feature_manager.add<toggle_option>("self_magnet_exclude_peds", "Peds", "", &g_magnet.m_settings.m_excludes.m_peds);
			g_feature_manager.add<toggle_option>("self_magnet_exclude_pickups", "Pickups", "", &g_magnet.m_settings.m_excludes.m_pickups);

			g_feature_manager.add<float_option>("self_magnet_offset_x", "X", "", &g_magnet.m_settings.m_offset.x, -1000, 1000, 1, 0);
			g_feature_manager.add<float_option>("self_magnet_offset_y", "Y", "", &g_magnet.m_settings.m_offset.y, -1000, 1000, 1, 0);
			g_feature_manager.add<float_option>("self_magnet_offset_z", "Z", "", &g_magnet.m_settings.m_offset.z, -1000, 1000, 1, 0);
		} });

		m_feature_subs.push_back({ "Handtrails", [] {
			g_feature_manager.add<toggle_with_choose_option>("handtrails", "Enabled", "", &g_handtrails.m_enabled, g_handtrails.m_settings.m_type, &g_handtrails.m_settings.m_selected, false, get_func(g_handtrails.tick));

			g_feature_manager.add<float_option>("handtrails_scale", "Scale", "", &g_handtrails.m_settings.m_scale, 0, 1000, 0.1, 1);

			g_feature_manager.add<toggle_option>("handtrails_rainbow", "Rainbow", "", &g_handtrails.m_settings.m_rainbow);
			g_feature_manager.add<float_option>("handtrails_r", "R", "", &g_handtrails.m_settings.m_color.r, color_modifiers);
			g_feature_manager.add<float_option>("handtrails_g", "G", "", &g_handtrails.m_settings.m_color.g, color_modifiers);
			g_feature_manager.add<float_option>("handtrails_b", "B", "", &g_handtrails.m_settings.m_color.b, color_modifiers);
		} });

		m_feature_subs.push_back({ "Abilities", [] {
			g_feature_manager.add<toggle_option>("ironman", "Ironman", "", &g_ironman.m_enabled, get_func(g_ironman.tick), get_func(g_ironman.on_disable));
		} });
	}
	float self_opacity{ 255 };
	void player_options::add() {
		add_feature_subs();
		for (auto subs : m_feature_subs) {
			subs.second();
		}
		add_thresholds();
		add_super_jump();
		collision();
		add_no_clip();
		add_config_flags();
		add_reflections();
		add_ped_matrix();
		g_feature_manager.add<toggle_option>("fast_respawn", "Fast Respawn", "", &g_fast_respawn.m_enabled, get_func(g_fast_respawn.init));
		g_feature_manager.add<toggle_option>("neverWanted", "Never Wanted", "", &g_player_options.never_wanted_t, never_wanted);
		g_feature_manager.add<toggle_option>("collision_reduced", "Reduced", "", &collison::reduced::enabled, collison::reduced::init, collison::reduced::on_disable);
		g_feature_manager.add<toggle_option>("mobile_radio", "Mobile Radio", "", &mobile_radio::enabled, mobile_radio::init, mobile_radio::on_disable);
		g_feature_manager.add<toggle_option>("ignored_by_peds", "Ignored By Peds", "", &ignored_by_peds::enabled, ignored_by_peds::init, ignored_by_peds::on_disable);
		g_feature_manager.add<toggle_option>("snow_trails", "Snow Trails", "", &snow_trails::enabled, snow_trails::init, snow_trails::on_disable);
		g_feature_manager.add<toggle_option>("shrink", "Shrink", "", &tiny_ped::enabled, tiny_ped::init, tiny_ped::on_disable);
		g_feature_manager.add<toggle_with_choose_option>("invisible", "Invisibility", &invisiblity::enabled, invisiblity::settings::type, &invisiblity::settings::selected, false, invisiblity::init, invisiblity::on_disable);
		g_feature_manager.add<toggle_with_choose_option>("self_godmode", "Invincibility", "", &g_self_godmode.m_enabled, g_self_godmode.m_settings.m_type, &g_self_godmode.m_settings.m_position, false, get_func(g_self_godmode.init), get_func(g_self_godmode.on_disable));
		g_feature_manager.add<toggle_option>("take_less_damage", "Damage Reduction", "", &take_less_damage::enabled, take_less_damage::init, take_less_damage::on_disable);
		g_feature_manager.add<toggle_option>("upperbody_damage_only", "Upperbody Damage Only", "", &upperbody_damage_only::enabled, upperbody_damage_only::init, upperbody_damage_only::on_disable);
		g_feature_manager.add<toggle_option>("attack_friendly", "Attack Friendly", "", &attack_friendly::enabled, attack_friendly::init, attack_friendly::on_disable);
		g_feature_manager.add<toggle_option>("seatbelt", "Seatbelt", "", &seatbelt::enabled, seatbelt::init, seatbelt::on_disable);

		g_feature_manager.add<toggle_option>("explosive_melee", "Explosive Melee", "", &explosive_melee::enabled, explosive_melee::init);
		g_feature_manager.add<toggle_option>("push_water_away", "Push Away Water", "", &push_water_away::enabled, push_water_away::tick);
		g_feature_manager.add<toggle_option>("instantly_enter_vehicles", "Instantly Enter Vehicles", "", &instantly_enter_vehicles::enabled, instantly_enter_vehicles::tick);
		g_feature_manager.add<toggle_option>("crouched", "Crouched", "", &crouched::enabled, crouched::tick, crouched::on_disable);
		g_feature_manager.add<toggle_option>("auto_open_parachute", "Auto Open Parachute", "", &auto_open_parachute::enabled, auto_open_parachute::tick);
		g_feature_manager.add<toggle_with_float_option>("wet", "Wet", "", &wet::enabled, &wet::amount, 0, 10, 0.1, 1, false, wet::tick, wet::on_disable);

		g_feature_manager.add<toggle_option>("tennis_mode", "Tennis", "", &tennis_mode::enabled, tennis_mode::tick, tennis_mode::on_disable);
		g_feature_manager.add<toggle_option>("backward_walking", "Backward Walking", "", &backward_walking::enabled, backward_walking::tick, backward_walking::on_disable);
		g_feature_manager.add<toggle_option>("infinite_oxygen", "Infinite Oxygen", "", &infinite_oxygen::enabled, infinite_oxygen::tick);

		//fall editor
		g_feature_manager.add<toggle_option>("beast_landing", "Beast", "", &g_hooking_features.fall.beast);
		g_feature_manager.add<toggle_option>("dive_landing", "Dive", "", &g_hooking_features.fall.dive);
		g_feature_manager.add<toggle_option>("shake_camera_landing", "Shake Camera", "", &g_hooking_features.fall.shake_camera);
		g_feature_manager.add<toggle_option>("land", "Land", "", &g_hooking_features.fall.land);
		g_feature_manager.add<toggle_option>("super_landing", "Super", "", &g_hooking_features.fall.super);

		//jump editor
		g_feature_manager.add<toggle_option>("beast_jump", "Beast", "", &g_hooking_features.jump.beast);
		g_feature_manager.add<toggle_option>("dive_jump", "Dive", "", &g_hooking_features.jump.dive);
		g_feature_manager.add<toggle_option>("shake_camera_jump", "Shake Camera", "", &g_hooking_features.jump.shake_camera);
		g_feature_manager.add<toggle_option>("land_jump", "Land", "", &g_hooking_features.jump.land);
		g_feature_manager.add<toggle_option>("super_jump_editor", "Super", "", &g_hooking_features.jump.super);

		g_feature_manager.add<float_option>("wanted_level", "Level", "", &wanted_level, 0, 5, 1, 0, true, [] {
			g_utils->cped()->m_player_info->m_wanted_level = wanted_level;
		});
		g_feature_manager.add<float_option>("heading", "Heading", "", &heading, 0, 360, 1, 0, true, [] {
			ENTITY::SET_ENTITY_HEADING(g_utils->self(), heading);
		});
		g_feature_manager.add<float_option>("stamina_regen", "Stamina", "", &g_utils->cped()->m_player_info->m_stamina, 0, 500, 0.1, 1);
		g_feature_manager.add<toggle_option>("forced_jump", "Forced Jump", "", &forced_jump, [] {
			if (!forced_jump) return;
			MISC::SET_FORCED_JUMP_THIS_FRAME(g_utils->self_id());
		});

		g_feature_manager.add<button_option>("max_armor", "Max Armor", "", [] {
			g_utils->cped()->m_armor = PLAYER::GET_PLAYER_MAX_ARMOUR(g_utils->self_id());
		});
		g_feature_manager.add<button_option>("max_health", "Max Health", "", [] {
			g_utils->cped()->m_health = g_utils->cped()->m_maxhealth;
		});
		g_feature_manager.add<button_option>("suicide", "Suicide", "", [] {
			g_utils->cped()->m_health = 0;
		});
		g_feature_manager.add<button_option>("remove_armor", "Remove Armor", "", [] {
			g_utils->cped()->m_armor = 0;
		});
		g_feature_manager.add<button_option>("skydive", "Skydive", "", [] {
			g_fiber_pool.queue([=] {
				CAM::DO_SCREEN_FADE_OUT(500);
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(g_utils->self(), rage::joaat("gadget_parachute"), 1, false);
				fiber::current()->wait(3s);
				g_utils->teleport({ g_utils->coords().x, g_utils->coords().y, g_utils->coords().z + 500});
				TASK::TASK_SKY_DIVE(g_utils->self(), true);
				fiber::current()->wait(500ms);
				CAM::DO_SCREEN_FADE_IN(500);
			});
		});
		g_feature_manager.add<button_option>("clear_tasks", "Clear Tasks", "", [] {
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(g_utils->self());
		});

		g_feature_manager.add<float_option>("self_opacity", "Opacity", "", &self_opacity, 0, 255, 51, 0, true, [] {
			ENTITY::SET_ENTITY_ALPHA(g_utils->self(), self_opacity, false);
			});
	}
}