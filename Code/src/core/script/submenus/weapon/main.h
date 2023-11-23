#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/number.h"

namespace Base::submenus::weapon::modifiers {
	void main() {
		if (!g_utils->cweapon() || g_utils->cweapon() == nullptr) return;
		draw->number("Accuracy Spread", g_utils->cweapon()->m_accuracy_spread, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Accurate Mode Accuracy Modifier", g_utils->cweapon()->m_accurate_mode_accuracy_modifier, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("RNG Accuracy", g_utils->cweapon()->m_run_and_gun_accuracy, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("RNG Min Accuracy", g_utils->cweapon()->m_run_and_gun_min_accuracy, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Recoil Accuracy Max", g_utils->cweapon()->m_recoil_accuracy_max, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Recoil Error Time", g_utils->cweapon()->m_recoil_error_time, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Recoil Recovery Rate", g_utils->cweapon()->m_recoil_recovery_rate, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Recoil Accuracy To Allow Headshot AI", g_utils->cweapon()->m_recoil_accuracy_to_allow_headshot_ai, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Min Headshot Distance AI", g_utils->cweapon()->m_min_headshot_distance_ai, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Max Headshot Range AI", g_utils->cweapon()->m_max_headshot_distance_ai, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Headshot Damage Modifie AIr", g_utils->cweapon()->m_headshot_damage_modifier_ai, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Recoil Accuracy To Allow Headshot Player", g_utils->cweapon()->m_recoil_accuracy_to_allow_headshot_player, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Min Headshot Distance Player", g_utils->cweapon()->m_min_headshot_distance_player, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Max Headshot Distance Player", g_utils->cweapon()->m_max_headshot_distance_player, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Headshot Damage Modifier Player", g_utils->cweapon()->m_headshot_damage_modifier_player, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Damage", g_utils->cweapon()->m_damage, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Damage Time", g_utils->cweapon()->m_damage_time, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Damage Time In Vehicle", g_utils->cweapon()->m_damage_time_in_vehicle, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Damage Time In Vehicle Headshot", g_utils->cweapon()->m_damage_time_in_vehicle_headshot, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Hit Limbs Damage Modifier", g_utils->cweapon()->m_hit_limbs_damage_modifier, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Network Hit Limbs Damage Modifier", g_utils->cweapon()->m_network_hit_limbs_damage_modifier, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Lightly Armored Damage Modifier", g_utils->cweapon()->m_lightly_armoured_damage_modifier, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Vehicle Damage Modifier", g_utils->cweapon()->m_vehicle_damage_modifier, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Force", g_utils->cweapon()->m_force, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Force On Ped", g_utils->cweapon()->m_force_on_ped, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Force On Vehicle", g_utils->cweapon()->m_force_on_vehicle, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Force On Heli", g_utils->cweapon()->m_force_on_heli, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Force Max Strength Multiplier", g_utils->cweapon()->m_force_max_strength_mult, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Force Falloff Range Start", g_utils->cweapon()->m_force_falloff_range_start, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Force Falloff Range End", g_utils->cweapon()->m_force_falloff_range_end, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Force Falloff Range Min", g_utils->cweapon()->m_force_falloff_range_min, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Project Force", g_utils->cweapon()->m_project_force, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Frag Impulse", g_utils->cweapon()->m_frag_impulse, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Penetration", g_utils->cweapon()->m_penetration, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Vertical Launch Ajustment", g_utils->cweapon()->m_vertical_launch_adjustment, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Speed", g_utils->cweapon()->m_speed, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Batch Spread", g_utils->cweapon()->m_batch_spread, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Bullets In Batch", g_utils->cweapon()->m_bullets_in_batch, { 0, 1000, 1, 0 });
		draw->number("Reload Time MP", g_utils->cweapon()->m_reload_time_mp, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Reload Time SP", g_utils->cweapon()->m_reload_time_sp, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Vehicle Reload Time", g_utils->cweapon()->m_vehicle_reload_time, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Animation Reload Time", g_utils->cweapon()->m_anim_reload_time, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Time Betweeen Shots", g_utils->cweapon()->m_time_between_shots, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Time Left Between Shots", g_utils->cweapon()->m_time_left_between_shots_where_should_fire_is_cached, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Spinup Time", g_utils->cweapon()->m_spinup_time, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Spin Time", g_utils->cweapon()->m_spin_time, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Spin Down Time", g_utils->cweapon()->m_spindown_time, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Alternate Wait Time", g_utils->cweapon()->m_alternate_wait_time, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Network Player Damage Modifier", g_utils->cweapon()->m_network_player_damage_modifier, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Network Ped Damage Modifier", g_utils->cweapon()->m_network_ped_damage_modifier, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Network Headshot Modifier", g_utils->cweapon()->m_network_headshot_modifier, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Lock On Range", g_utils->cweapon()->m_lock_on_range, { 0.0f, 10000.f, 50.0f, 1 });
		draw->number("Weapon Range", g_utils->cweapon()->m_weapon_range, { 0.0f, 10000.f, 50.0f, 1 });
		draw->number("AI Sound Range", g_utils->cweapon()->m_ai_sound_range, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("AI Potential Blast Event Range", g_utils->cweapon()->m_ai_potential_blast_event_range, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Damage Fall Off Range Min", g_utils->cweapon()->m_damage_fall_off_range_min, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Damage Fall Off Range Max", g_utils->cweapon()->m_damage_fall_off_range_max, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Damage Fall Off Modifier", g_utils->cweapon()->m_damage_fall_off_modifier, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Min Time Between Recoil Shakes", g_utils->cweapon()->m_min_time_between_recoil_shakes, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Recoil Shake Amplitude", g_utils->cweapon()->m_recoil_shake_amplitude, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Explosion Shake Amplitude (Actual Recoil)", g_utils->cweapon()->m_explosion_shake_amplitude, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Camera FOV", g_utils->cweapon()->m_camera_fov, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("First Person Aim Fov Min", g_utils->cweapon()->m_first_person_aim_fov_min, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("First Person Aim Fov Max", g_utils->cweapon()->m_first_person_aim_fov_max, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("First Person Scope FOV", g_utils->cweapon()->m_first_person_scope_fov, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("First Person Scope Attachment FOV", g_utils->cweapon()->m_first_person_scope_attachment_fov, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Reticule Hud Position X", g_utils->cweapon()->m_reticule_hud_position.x, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Reticule Hud Position Y", g_utils->cweapon()->m_reticule_hud_position.y, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Reticule Hud Position POV Turret X", g_utils->cweapon()->m_reticule_hud_position_pov_turret.x, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Reticule Hud Position POV Turret Y", g_utils->cweapon()->m_reticule_hud_position_pov_turret.y, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Reticule Min Size Standing", g_utils->cweapon()->m_reticule_min_size_standing, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Reticule Min Size Crouched", g_utils->cweapon()->m_reticule_min_size_crouched, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Reticule Size", g_utils->cweapon()->m_reticule_scale, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("HUD Range", g_utils->cweapon()->m_hud_range, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Aiming Breathing Additive Weight", g_utils->cweapon()->m_aiming_breathing_additive_weight, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Firing Breathing Additive Weight", g_utils->cweapon()->m_firing_breathing_additive_weight, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Stealth Aiming Breathing Additive Weight", g_utils->cweapon()->m_stealth_aiming_breathing_additive_weight, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Stealth Firing Breathing Additive Weight", g_utils->cweapon()->m_stealth_firing_breathing_additive_weight, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Aiming Lean Additive Weight", g_utils->cweapon()->m_aiming_lean_additive_weight, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Firing Lean Additive Weight", g_utils->cweapon()->m_firing_lean_additive_weight, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Stealth Aiming Lean Additive Weight", g_utils->cweapon()->m_stealth_aiming_lean_additive_weight, { -1000.f, 1000.f, 0.1f, 1 });
		draw->number("Stealth Firing Lean Additive Weight", g_utils->cweapon()->m_stealth_firing_lean_additive_weight, { -1000.f, 1000.f, 0.1f, 1 });
	}
}