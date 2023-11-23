#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/number.h"
#include "src/rage/weapon/CAmmoProjectileInfo.hpp"
#include "src/rage/weapon/CAmmoRocketInfo.hpp"

namespace Base::submenus::weapon {
	void projectile_edtior() {
		if (g_utils->cped()->m_weapon_manager->m_selected_weapon_hash == 0xA2719263) return;

		auto e{ reinterpret_cast<CAmmoProjectileInfo*>(g_utils->cped()->m_weapon_manager->m_weapon_info->m_ammo_info) };
		auto e2{ reinterpret_cast<CAmmoRocketInfo*>(e) };
		draw->number("Damage", &e->m_damage, { 0.1f, 5000.f, 1.f });
		draw->number("Lifetime", &e->m_lifetime, { 0.1f, 5000.f, 1.f });
		draw->number("Lifetime (From Vehicle)", &e->m_from_vehicle_lifetime, { 0.1f, 5000.f, 1.f });
		draw->number("Lifetime (After Explosion)", &e->m_lifetime_after_explosion, { 0.1f, 5000.f, 1.f });
		draw->number("Time", &e->m_explosion_time, { 0.1f, 5000.f, 1.f });
		draw->number("Launch Speed", &e->m_launch_speed, { 0.1f, 5000.f, 1.f });
		draw->number("Seperation Time", &e->m_separation_time, { 0.1f, 5000.f, 1.f });
		draw->number("Time To Reach Target", &e->m_time_to_reach_target, { 0.1f, 5000.f, 1.f });
		draw->number("Amping", &e->m_amping, { 0.1f, 5000.f, 1.f });
		draw->number("Gravity", &e->m_gravity_factor, { 0.1f, 5000.f, 0.1f });
		draw->number("Ricochet Tolerance", &e->m_ricochet_tolerance, { 0.1f, 5000.f, 1.f });
		draw->number("Ped Ricochet Tolerance", &e->m_ped_ricochet_tolerance, { 0.1f, 5000.f, 1.f });
		draw->number("Vehicle Ricochet Tolerance", &e->m_vehicle_ricochet_tolerance, { 0.1f, 5000.f, 1.f });
		draw->number("Friction Multiplier", &e->m_friction_multiplier, { 0.1f, 5000.f, 1.f });
		draw->number("Trail FX Fade In Time", &e->m_trail_fx_fade_in_time, { 0.1f, 5000.f, 1.f });
		draw->number("Trail FX Fade Out Time", &e->m_trail_fx_fade_out_time, { 0.1f, 5000.f, 1.f });
		draw->number("Disturb Probe Dist", &e->m_disturb_fx_probe_dist, { 0.1f, 5000.f, 1.f });
		draw->number("Disturb Scale", &e->m_disturb_fx_scale, { 0.1f, 5000.f, 1.f });
		draw->number("Ground FX Probe Distance", &e->m_ground_fx_probe_distance, { 0.1f, 5000.f, 1.f });
		draw->number("Ground FX Probe Distance", &e->m_ground_fx_probe_distance, { 0.1f, 5000.f, 1.f });
		draw->toggle(("Alt Tint Colour"), &e->m_fx_alt_tint_colour);
		draw->toggle(("Light Only Active When Stuck"), &e->m_light_only_active_when_stuck);
		draw->toggle(("Light Flickers"), &e->m_light_flickers);
		draw->toggle(("Light Speeds Up"), &e->m_light_speeds_up);
		draw->number("Light Red", &e->m_light_colour.x, { 0, 255, 1, 0 });
		draw->number("Light Green", &e->m_light_colour.y, { 0, 255, 1, 0 });
		draw->number("Light Blue", &e->m_light_colour.z, { 0, 255, 1, 0 });
		draw->number("Light Intensity", &e->m_light_intensity, { 0.1f, 5000.f, 1.f });
		draw->number("Light Range", &e->m_light_range, { 0.1f, 5000.f, 1.f });
		draw->number("Light Falloff", &e->m_light_falloff_exp, { 0.1f, 5000.f, 1.f });
		draw->number("Light Frequency", &e->m_light_frequency, { 0.1f, 5000.f, 1.f });
		draw->number("Light Power", &e->m_light_power, { 0.1f, 5000.f, 1.f });
		draw->number("Corona Size", &e->m_corona_size, { 0.1f, 5000.f, 1.f });
		draw->number("Corona Intensity", &e->m_corona_intensity, { 0.1f, 5000.f, 1.f });
		draw->number("Corona Z Bias", &e->m_corona_z_bias, { 0.1f, 5000.f, 1.f });
		draw->toggle(("Proximity Affects Firing Player"), &e->m_proximity_affects_firing_player);
		draw->toggle(("Proximity Can Be Triggered By Peds"), &e->m_proximity_can_be_triggered_by_peds);
		draw->number("Proximity Activation Time", &e->m_proximity_activation_time, { 0.1f, 5000.f, 1.f });
		draw->number("Proximity Repeated Time", &e->m_proximity_repeated_detonation_activation_time, { 0.1f, 5000.f, 1.f });
		draw->number("Proximity Trigger Radius", &e->m_proximity_trigger_radius, { 0.1f, 5000.f, 1.f });
		draw->number("Proximity Fuse Time Ped", &e->m_proximity_fuse_time_ped, { 0.1f, 5000.f, 1.f });
		draw->number("Proximity Fuse Time Vehicle Min", &e->m_proximity_fuse_time_vehicle_min, { 0.1f, 5000.f, 1.f });
		draw->number("Proximity Fuse Time Vehicle Max", &e->m_proximity_fuse_time_vehicle_max, { 0.1f, 5000.f, 1.f });
		draw->number("Proximity Fuse Time Vehicle Speed", &e->m_proximity_fuse_time_vehicle_speed, { 0.1f, 5000.f, 1.f });
		draw->number("Proximity Light Colour Red", &e->m_proximity_light_colour_untriggered.x, { 0, 255, 1, 0 });
		draw->number("Proximity Light Colour Green", &e->m_proximity_light_colour_untriggered.y, { 0, 255, 1, 0 });
		draw->number("Proximity Light Colour Blue", &e->m_proximity_light_colour_untriggered.z, { 0, 255, 1, 0 });
		draw->number("Proximity Light Frequency", &e->m_proximity_light_frequency_multiplier_triggered, { 0, 5000, 1.f, 0 });
		draw->number("Proximity Radius", &e2->m_proximity_radius, { 0.1f, 5000.f, 1.f });
		draw->number("Time To Ignore Owner", &e->m_time_to_ignore_owner, { 0.1f, 5000.f, 1.f });
		draw->number("Charged Launch Time", &e->m_charged_launch_time, { 0.1f, 5000.f, 1.f });
		draw->number("Charged Launch Speed", &e->m_charged_launch_speed_mult, { 0.1f, 5000.f, 1.f });
		draw->number("Cluster Explosion Count", &e->m_cluster_explosion_count, { 0, 500, 1, 0 });
		draw->number("Cluster Radius (Min)", &e->m_cluster_min_radius, { 0.1f, 5000.f, 1.f });
		draw->number("Cluster Radius (Max)", &e->m_cluster_max_radius, { 0.1f, 5000.f, 1.f });
		draw->number("Cluster Initial Delay", &e->m_cluster_initial_delay, { 0.1f, 5000.f, 1.f });
		draw->number("Cluster Inbetween Delay", &e->m_cluster_inbetween_delay, { 0.1f, 5000.f, 1.f });
		draw->number("Forward Drag Coeff", &e2->m_forward_drag_coeff, { 0.1f, 5000.f, 1.f });
		draw->number("Side Drag Coeff", &e2->m_side_drag_coeff, { 0.1f, 5000.f, 1.f });
		draw->number("Time Before Homing", &e2->m_time_before_homing, { 0.1f, 5000.f, 1.f });
		draw->number("Time Before Switch Target Min", &e2->m_time_before_switch_target_min, { 0.1f, 5000.f, 1.f });
		draw->number("Time Before Switch Target Max", &e2->m_time_before_switch_target_max, { 0.1f, 5000.f, 1.f });
		draw->number("Pitch Change Rate", &e2->m_pitch_change_rate, { 0.1f, 5000.f, 1.f });
		draw->number("Yaw Change Rate", &e2->m_yaw_change_rate, { 0.1f, 5000.f, 1.f });
		draw->number("Roll Change Rate", &e2->m_roll_change_rate, { 0.1f, 5000.f, 1.f });
		draw->number("Max Roll Angle", &e2->m_max_roll_angle_sin, { 0.1f, 5000.f, 1.f });
		draw->number("Lifetime Player Locked Override", &e2->m_lifetime_player_vehicle_locked_override_mp, { 0.1f, 5000.f, 1.f });
		draw->toggle(("Should Use Homing Params"), &e2->m_homing_rocket_params.m_should_use_homing_params_from_info);
		draw->toggle(("Should Ignore Owner Combat"), &e2->m_homing_rocket_params.m_should_ignore_owner_combat_behaviour);
		draw->number("Time Before Starting Homing", &e2->m_homing_rocket_params.m_time_before_starting_homing, { 0.1f, 5000.f, 1.f });
		draw->number("Time Before Homing Angle Break", &e2->m_homing_rocket_params.m_time_before_homing_angle_break, { 0.1f, 5000.f, 1.f });
		draw->number("Turn Rate", &e2->m_homing_rocket_params.m_turn_rate_modifier, { 0.1f, 5000.f, 1.f });
		draw->number("Pitch Yaw Roll Clamp", &e2->m_homing_rocket_params.m_pitch_yaw_roll_clamp, { 0.1f, 5000.f, 1.f });
		draw->number("Break Lock Angle", &e2->m_homing_rocket_params.m_default_homing_rocket_break_lock_angle, { 0.1f, 5000.f, 1.f });
		draw->number("Break Lock Angle (Close)", &e2->m_homing_rocket_params.m_default_homing_rocket_break_lock_angle_close, { 0.1f, 5000.f, 1.f });
		draw->number("Break Lock Angle (Distance)", &e2->m_homing_rocket_params.m_default_homing_rocket_break_lock_close_distance, { 0.1f, 5000.f, 1.f });
	}
}