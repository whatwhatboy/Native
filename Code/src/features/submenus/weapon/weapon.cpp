#include "weapon.h"
#include "src/fiber/script/manager/script_manager.h"
#include "src/memory/pointers/pointers.h"
#include <src/utility/enum.h>
#include "src/features/feature_manager.h"
#include "misc/bullet_tracers.h"
#include "misc/impacts.h"
#include "misc/infinite.h"
#include "misc/magnet.h"
#include "misc/disables.h"
#include "misc/modifiers.h"
#include "misc/triggerbot.h"
#include "misc/aimbot.h"
#include "misc/force.h"
#include "misc/rapid_fire.h"
#include "misc/paint.h"
#include "misc/classes.hpp"
#include "misc/misc.h"
#include "misc/bullet_changer.h"
#include <src/hooking/hooking.h>
#include "misc/display_weapon_on_back.cpp"

namespace Base {
	struct weapon_info {
		uint64_t m_vmt; //0x0000
		char _0x0008[8]; //0x0008
		uint32_t m_name_hash; //0x0010
		uint32_t m_model_hash; //0x0014
		uint32_t m_audio; //0x0018
		uint32_t m_slot; //0x001C
		int m_damage_type; //0x0020
		uint32_t m_explosion_default; //0x0024
		uint32_t m_explosion_hit_car; //0x0028
		uint32_t m_explosion_hit_truck; //0x002C
		uint32_t m_explosion_hit_bike; //0x0030
		uint32_t m_explosion_hit_boat; //0x0034
		uint32_t m_explosion_hit_plane; //0x0038
		char _0x003C[24]; //0x003C
		int m_fire_type; //0x0054
		int m_wheel_slot; //0x0058
		uint32_t m_group_hash; //0x005C
		const char* m_ammo_info; //0x0060
		const char* m_aiming_info; //0x0068
		uint32_t m_clip_size; //0x0070
		float m_accuracy_spread; //0x0074
		float m_accurate_mode_accuracy_modifier; //0x0078
		float m_run_and_gun_accuracy_modifier; //0x007C
		float m_run_and_gun_accuracy_max_modifier; //0x0080
		float m_recoil_accuracy_max; //0x0084
		float m_recoil_error_time; //0x0088
		float m_recoil_recovery_rate; //0x008C
		float m_recoil_accuracy_to_allow_head_shot_a_i; //0x0090
		float m_min_head_shot_distance_a_i; //0x0094
		float m_max_head_shot_distance_a_i; //0x0098
		float m_head_shot_damage_modifier_a_i; //0x009C
		float m_recoil_accuracy_to_allow_head_shot_player; //0x00A0
		float m_min_head_shot_distance_player; //0x00A4
		float m_max_head_shot_distance_player; //0x00A8
		float m_head_shot_damage_modifier_player; //0x00AC
		float m_damage; //0x00B0
		float m_damage_time; //0x00B4
		float m_damage_time_in_vehicle; //0x00B8
		float m_damage_time_in_vehicle_head_shot; //0x00BC
		char _0x00C0[8]; //0x00C0
		float m_hit_limbs_damage_modifier; //0x00C8
		float m_network_hit_limbs_damage_modifier; //0x00CC
		float m_lightly_armoured_damage_modifier; //0x00D0
		float m_vehicle_damage_modifier; //0x00D4
		float m_force; //0x00D8
		float m_force_hit_ped; //0x00DC
		float m_force_hit_vehicle; //0x00E0
		float m_force_hit_flying_heli; //0x00E4
		uint64_t m_override_forces; //0x00E8
		int16_t m_override_forces_count; //0x00F0
		int16_t m_override_forces_capacity; //0x00F2
		char _0x00F4[4]; //0x00F4
		float m_force_max_strength_mult; //0x00F8
		float m_force_falloff_range_start; //0x00FC
		float m_force_falloff_range_end; //0x0100
		float m_force_falloff_min; //0x0104
		float m_projectile_force; //0x0108
		float m_frag_impulse; //0x010C
		float m_penetration; //0x0110
		float m_vertical_launch_adjustment; //0x0114
		float m_drop_forward_velocity; //0x0118
		float m_speed; //0x011C
		int m_bullets_in_batch; //0x0120
		float m_batch_spread; //0x0124
		float m_reload_time_m_p; //0x0128
		float m_reload_time_s_p; //0x012C
		float m_vehicle_reload_time; //0x0130
		float m_anim_reload_rate; //0x0134
		int m_bullets_per_anim_loop; //0x0138
		float m_time_between_shots; //0x013C
		float m_time_left_between_shots_where_should_fire_is_cached; //0x0140
		float m_spin_up_time; //0x0144
		float m_spin_time; //0x0148
		float m_spin_down_time; //0x014C
		float m_alternate_wait_time; //0x0150
		float m_bullet_bending_near_radius; //0x0154
		float m_bullet_bending_far_radius; //0x0158
		float m_bullet_bending_zoomed_radius; //0x015C
		float m_first_person_bullet_bending_near_radius; //0x0160
		float m_first_person_bullet_bending_far_radius; //0x0164
		float m_first_person_bullet_bending_zoomed_radius; //0x0168
		char _0x016C[4]; //0x016C
		int m_effect_group; //0x0170
		uint32_t m_flash_fx; //0x0174
		uint32_t m_flash_fx_alt; //0x0178
		uint32_t m_flash_fx_fp; //0x017C
		uint32_t m_flash_fx_alt_fp; //0x0180
		uint32_t m_muzzle_smoke_fx; //0x0184
		uint32_t m_muzzle_smoke_fx_fp; //0x0188
		float m_muzzle_smoke_fx_min_level; //0x018C
		float m_muzzle_smoke_fx_inc_per_shot; //0x0190
		float m_muzzle_smoke_fx_dec_per_sec; //0x0194
		char _0x0198[28]; //0x0198
		uint32_t m_shell_fx; //0x01B4
		uint32_t m_shell_fx_fp; //0x01B8
		uint32_t m_tracer_fx; //0x01BC
		uint32_t m_ped_damage_hash; //0x01C0
		float m_tracer_fx_chance_sp; //0x01C4
		float m_tracer_fx_chance_mp; //0x01C8
		char _0x01CC[4]; //0x01CC
		float m_flash_fx_chance_sp; //0x01D0
		float m_flash_fx_chance_mp; //0x01D4
		float m_flash_fx_alt_chance; //0x01D8
		float m_flash_fx_scale; //0x01DC
		char _0x01E0[76]; //0x01E0
		float m_ground_disturb_fx_dist; //0x022C
		char _0x0230[32]; //0x0230
		int m_initial_rumble_duration; //0x0250
		float m_initial_rumble_intensity; //0x0254
		float m_initial_rumble_intensity_trigger; //0x0258
		int m_rumble_duration; //0x025C
		float m_rumble_intensity; //0x0260
		float m_rumble_intensity_trigger; //0x0264
		float m_rumble_damage_intensity; //0x0268
		int m_initial_rumble_duration_fps; //0x026C
		float m_initial_rumble_intensity_fps; //0x0270
		int m_rumble_duration_fps; //0x0274
		float m_rumble_intensity_fps; //0x0278
		float m_network_player_damage_modifier; //0x027C
		float m_network_ped_damage_modifier; //0x0280
		float m_network_head_shot_player_damage_modifier; //0x0284
		float m_lock_on_range; //0x0288
		float weapon_range; //0x028C
		float m_ai_sound_range; //0x0290
		float m_ai_potential_blast_event_range; //0x0294
		float m_damage_fall_off_range_min; //0x0298
		float m_damage_fall_off_range_max; //0x029C
		char _0x02A0[8]; //0x02A0
		float m_damage_fall_off_modifier; //0x02A8
		char _0x02AC[4]; //0x02AC
		float m_damage_fall_off_modifier1; //0x02B0
		char _0x02B4[60]; //0x02B4
		int m_min_time_between_recoil_shakes; //0x02F0
		float m_recoil_shake_amptitude; //0x02F4
		float m_explosion_shake_amplitude; //0x02F8
		float m_camera_fov; //0x02FC
		char _0x0300[8]; //0x0300
		float m_first_person_scope_fov; //0x0308
		float m_first_person_scope_attachment_fov; //0x030C
		char _0x0310[736]; //0x0310
		char* m_label_text; //0x05F0
		char _0x05F8[872]; //0x05F8
	};
	void add_triggerbot() {
		g_feature_manager.add<toggle_option>("triggerbot", "Enabled", "", &triggerbot::enabled, triggerbot::init);
		g_feature_manager.add<choose_option>("triggerbot_bone", "Bone", "", triggerbot::settings::bone_lockon, &triggerbot::settings::selected);
	}
	void add_aimbot() {
		g_feature_manager.add<toggle_option>("aimbot", "Enabled", "", &aimbot::enabled, aimbot::init, aimbot::on_disable);
		g_feature_manager.add<toggle_option>("aimbot_draw_fov", "Draw FOV", "", &g_interface->m_aimbot);
		g_feature_manager.add<float_option>("aimbot_fov", "FOV", "", &g_interface->m_aimbot_fov, 0, 360, 1, 1);
		g_feature_manager.add<float_option>("aimbot_smoothing", "Smoothing", "", &aimbot::settings::smoothing_speed, 3, 100, 0.1, 1);

		g_feature_manager.add<toggle_option>("aimbot_only_players", "Only Players", "", &aimbot::settings::only_players);
		g_feature_manager.add<toggle_option>("aimbot_always_lockon", "Always Lockon", "", &aimbot::settings::always_lockon);
	}
	void add_magnet() {
		g_feature_manager.add<toggle_with_choose_option>("magnet", "Enabled", &magnet::enabled, magnet::settings::forceType, &magnet::settings::forcePos, false, magnet::init);
		g_feature_manager.add<float_option>("magnet_zoom", "Zoom", "", &magnet::settings::zoom, 0, 300, 1, 0);

		//excludes
		g_feature_manager.add<toggle_option>("magnet_exclude_vehicles", "Vehicle", "", &magnet::settings::excludes::vehicles);
		g_feature_manager.add<toggle_option>("magnet_exclude_peds", "Peds", "", &magnet::settings::excludes::peds);
		g_feature_manager.add<toggle_option>("magnet_exclude_objects", "Objects", "", &magnet::settings::excludes::objects);

		//sphere
		g_feature_manager.add<toggle_option>("magnet_sphere", "Enabled", "", &magnet::settings::sphere::enabled);
		g_feature_manager.add<float_option>("magnet_sphere_size", "Size", "", &magnet::settings::sphere::size, 0.1f, 50.f, 0.1f, 1);
		g_feature_manager.add<float_option>("magnet_sphere_pitch", "Pitch", "", &magnet::settings::sphere::rotation.x, 0, 360, 1, 0);
		g_feature_manager.add<float_option>("magnet_sphere_roll", "Roll", "", &magnet::settings::sphere::rotation.y, 0, 360, 1, 0);
		g_feature_manager.add<float_option>("magnet_sphere_yaw", "Yaw", "", &magnet::settings::sphere::rotation.z, 0, 360, 1, 0);
	}
	void add_force() {
		g_feature_manager.add<toggle_with_choose_option>("force", "Enabled", &force::enabled, force::settings::type, &force::settings::typePos, false, force::init);
		g_feature_manager.add<float_option>("force_speed", "Speed", "", &force::settings::force, 0, 1000, 0.1, 1);
	}
	void add_rapid_fire() {
		g_feature_manager.add<toggle_option>("rapid_fire", "Enabled", "", &rapid_fire::enabled, rapid_fire::init, rapid_fire::on_disable);
		g_feature_manager.add<toggle_option>("rapid_fire_disable_shooting", "Disable Shooting", "", & rapid_fire::settings::disable_shooting);
		g_feature_manager.add<toggle_option>("rapid_fire_disable_when_reloading", "Disable When Reloading", "", &rapid_fire::settings::disable_when_reloading);
		g_feature_manager.add<toggle_option>("rapid_fire_only_when_aiming", "Only When Aiming", "", &rapid_fire::settings::only_when_aiming);
		g_feature_manager.add<float_option>("rapid_fire_bullets", "Bullets", "", &rapid_fire::settings::bullets, 1, 100, 1, 0);
		g_feature_manager.add<float_option>("rapid_fire_delay", "Delay", "", &rapid_fire::settings::delay, 0, 5000, 1, 0);
	}
	void add_grenade() {
		g_feature_manager.add<toggle_option>("grenade_trail", "Enabled", "", &grenade_trail::enabled, grenade_trail::init);
		g_feature_manager.add<float_option>("grenade_trail_delay", "Delay", "", &grenade_trail::settings::delay, 0, 5000, 1, 0);
		g_feature_manager.add<float_option>("grenade_trail_scale", "Scale", "", &grenade_trail::settings::scale, 0, 1000, 0.1, 1);

		g_feature_manager.add<toggle_option>("instantly_explode_greandes", "Instantly Explode", "", &instanty_explode_grenades::enabled, instanty_explode_grenades::init);
	}
	void add_teleport() {
		g_feature_manager.add<toggle_with_choose_option>("teleport_gun", "Enabled", &impacts::teleport::enabled, impacts::teleport::settings::type, &impacts::teleport::settings::typePos, false, impacts::teleport::init);
		g_feature_manager.add<float_option>("teleport_x_offset", "X Offset", "", &impacts::teleport::settings::offset.x, 0, 100, 1, 0);
		g_feature_manager.add<float_option>("teleport_y_offset", "Y Offset", "", &impacts::teleport::settings::offset.y, 0, 100, 1, 0);
		g_feature_manager.add<float_option>("teleport_z_offset", "Z Offset", "", &impacts::teleport::settings::offset.z, 0, 100, 1, 0);
		g_feature_manager.add<float_option>("teleport_delay", "Delay (S)", "", &impacts::teleport::settings::delay, 0, 60, 1, 0);
	}
	void airstrike() {
		g_feature_manager.add<toggle_option>("airstrike_gun", "Enabled", "", &impacts::airstrike::enabled, impacts::airstrike::init);
		g_feature_manager.add<float_option>("airstrike_height", "Height", "", &impacts::airstrike::settings::height, 0, 1000, 1, 0);
		g_feature_manager.add<float_option>("airstrike_damage", "Damage", "", &impacts::airstrike::settings::damage, 0, 1000, 1, 0);
		g_feature_manager.add<float_option>("airstrike_speed", "Speed", "", &impacts::airstrike::settings::speed, -1, 1000, 1, 0);
	}
	void add_bullet_tracers() {
		g_feature_manager.add<toggle_option>("bullet_tracers", "Enabled", "", &bullet_tracers::enabled, bullet_tracers::init, bullet_tracers::on_disable);
		g_feature_manager.add<toggle_option>("bullet_tracers_rainbow", "Rainbow", "", &bullet_tracers::settings::rainbow);
		g_feature_manager.add<float_option>("bullet_tracer_fadeaway_speed", "Fadeaway Speed", "", &bullet_tracers::settings::fadeaway_speed, 0, 1000, 0.1, 1);
	}
	void add_gun_locker() {
		g_feature_manager.add<button_option>("give_all_weapons", "Give All", "", [] {
			g_fiber_pool.queue([=] {
				for (int i{ 0 }; i < sizeof(all_weapons_hash); i++)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(g_utils->self(), all_weapons_hash[i], 9999, false);
			});
		});

		g_feature_manager.add<button_option>("give_all_attachments", "Give All Attachments", "", [] {
			g_fiber_pool.queue([=] {
				int attached{ 0 };
				auto hashes{ g_utils->get_hash_list_from_hash_table(*(u32*)(g_pointers->m_weapon_components.m_count) - 1, g_pointers->m_weapon_components.m_list) };
				for (int i{ 0 }; i < sizeof(all_weapons_hash) - 1; i++) {
					if (WEAPON::HAS_PED_GOT_WEAPON(g_utils->self(), all_weapons_hash[i], false)) {
						for (u32 component : hashes) {
							if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(all_weapons_hash[i], component)) {
								WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(g_utils->self(), all_weapons_hash[i], component);
								attached++;
							}
						}
					}
				}
			});
		});
	}
	void add_bullet_changer() {
		g_feature_manager.add<toggle_with_choose_option>("bullet_changer_enabled", "Enabled", &bullet_changer::enabled, all_weapons_name, &bullet_changer::settings::selected, false, bullet_changer::init);
		g_feature_manager.add<float_option>("bullet_changer_speed", "Speed", "", &bullet_changer::settings::speed, -1.0, 5000, 1, 0);
		g_feature_manager.add<float_option>("bullet_changer_delay", "Delay", "", &bullet_changer::settings::delay, 0, 5000, 1, 0);
		g_feature_manager.add<float_option>("bullet_changer_bullets", "Bullets", "", &bullet_changer::settings::bullets, 0, 100, 1, 0);
	}
	void add_explosive_ammo() {
		g_feature_manager.add<toggle_with_choose_option>("explosive_ammo", "Enabled", &impacts::explosive_ammo::enabled, impacts::explosive_ammo::settings::explosion_type, &impacts::explosive_ammo::settings::explosion, false, impacts::explosive_ammo::init);
		g_feature_manager.add<toggle_option>("explosion_blame_random_person", "Blame Random Person", "", &impacts::explosive_ammo::settings::blame_random_person);
		g_feature_manager.add<toggle_option>("explosion_invisible", "Invisible", "", &impacts::explosive_ammo::settings::invisible);
		g_feature_manager.add<toggle_option>("explosion_sound", "Sound", "", &impacts::explosive_ammo::settings::sound);

		g_feature_manager.add<float_option>("explosion_camera_shake", "Camera Shake", "", &impacts::explosive_ammo::settings::camera_shake, 0, 1000, 1, 0);
		g_feature_manager.add<float_option>("explosion_damage", "Damage", "", &impacts::explosive_ammo::settings::damage, 0, 1000, 1, 0);
	}
	void add_particle_gun() {
		g_feature_manager.add<toggle_with_choose_option>("particle_gun", "Enabled", &g_particles.m_enabled, g_particles.m_settings.m_type, &g_particles.m_settings.m_type_selected, false, get_func(g_particles.init));
		g_feature_manager.add<choose_option>("particle_gun_selected_particle", "Enabled",  particles_data::names, &g_particles.m_settings.m_selected_particle);

		g_feature_manager.add<toggle_option>("particle_gun_color_enabled", "Rainbow", "", &g_particles.m_settings.m_color.m_enabled);
		g_feature_manager.add<toggle_option>("particle_gun_rainbow", "Rainbow", "", &g_particles.m_settings.m_color.rainbow);
		g_feature_manager.add<float_option>("particle_gun_r", "R", "", &g_particles.m_settings.m_color.m_value.r, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("particle_gun_g", "G", "", &g_particles.m_settings.m_color.m_value.g, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("particle_gun_b", "B", "", &g_particles.m_settings.m_color.m_value.b, 0, 255, 1, 0);

		g_feature_manager.add<float_option>("particle_gun_scale", "Scale", "", &g_particles.m_settings.m_scale, 0, 1000, 0.1, 1);
		g_feature_manager.add<toggle_option>("particle_gun_always", "Always", "", &g_particles.m_settings.m_always);
	}
	void add_missle_launcher() {
		g_feature_manager.add<toggle_option>("missle_launcher", "Enabled", "", &g_missle_launcher.m_enabled, get_func(g_missle_launcher.tick), get_func(g_missle_launcher.on_disable));

		g_feature_manager.add<choose_option>("missle_launcher_explosion_type", "Explosion Type", "", g_missle_launcher.m_settings.explosion_type, &g_missle_launcher.m_settings.pos);
		g_feature_manager.add<toggle_option>("missle_launcher_only_explode_on_impact", "Only Explode On Impact", "", &g_missle_launcher.m_settings.only_explode_on_impact);
		g_feature_manager.add<toggle_option>("missle_launcher_noclip", "No Clip", "", &g_missle_launcher.m_settings.noclip);

		g_feature_manager.add<toggle_option>("missle_launcher_hud", "Hud", "", &g_missle_launcher.m_settings.hud);
		g_feature_manager.add<toggle_option>("missle_launcher_meter", "Meter", "", &g_missle_launcher.m_settings.meter);
		g_feature_manager.add<toggle_option>("missle_launcher_vision", "Vision", "", &g_missle_launcher.m_settings.vision);
	}
	void add_entity_shooter() {
		g_feature_manager.add<toggle_with_choose_option>("entity_shooter", "Enabled", "", &g_entity_shooter.m_enabled, g_entity_shooter.m_settings.type, &g_entity_shooter.m_settings.pos, false, get_func(g_entity_shooter.tick));

		g_feature_manager.add<keyboard_option>("entity_shooter_vehicle", "Vehicle", "", &g_entity_shooter.m_selected_vehicle_name);
	}
	void add_aim_tracer() {
		g_feature_manager.add<toggle_option>("aim_tracer", "Enabled", "", &aim_tracer::enabled, aim_tracer::tick);

		g_feature_manager.add<toggle_option>("aim_tracer_rainbow", "Rainbow", "", &aim_tracer::settings::rainbow);
		g_feature_manager.add<float_option>("aim_tracer_r", "R", "", &aim_tracer::settings::col.r, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("aim_tracer_g", "G", "", &aim_tracer::settings::col.g, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("aim_tracer_b", "B", "", &aim_tracer::settings::col.b, 0, 255, 1, 0);
	}
	void add_gravity_gun() {
		g_feature_manager.add<toggle_option>("gravity_gun", "Enabled", "", &g_gravity_gun.m_enabled, get_func(g_gravity_gun.tick));

		g_feature_manager.add<toggle_option>("gravity_gun_save_on_unaim", "Save On Unaim", "", &g_gravity_gun.m_settings.m_save_on_unaim);
		g_feature_manager.add<float_option>("gravity_gun_force", "Force", "", &g_gravity_gun.m_settings.m_force, 0, 100, 0.1, 1);
		g_feature_manager.add<float_option>("gravity_gun_zoom", "Zoom", "", &g_gravity_gun.m_settings.m_zoom, 0, 300, 1, 0);
	}
	float opacity{ 255 };
	void weapon_options::add() {
		add_bullet_changer();
		add_gun_locker();
		add_bullet_tracers();
		airstrike();
		add_teleport();
		add_grenade();
		add_rapid_fire();
		add_force();
		add_magnet();
		add_aimbot();
		add_triggerbot();
		add_explosive_ammo();
		add_particle_gun();
		add_missle_launcher();
		add_entity_shooter();
		add_aim_tracer();
		add_gravity_gun();

		g_feature_manager.add<toggle_option>("clown_vfx", "Clown VFX", "", &clown_vfx::enabled, clown_vfx::init, clown_vfx::on_disable);
		
		g_feature_manager.add<toggle_option>("display_weapon_on_back", "Display Weapon On Back", "", &g_display_weapon_on_back.m_enabled, get_func(g_display_weapon_on_back.init), get_func(g_display_weapon_on_back.on_disable));

		g_feature_manager.add<toggle_with_choose_option>("paint_gun", "Enabled", &paint::enabled, paint::settings::type, &paint::settings::selected, false, paint::init);
		g_feature_manager.add<toggle_option>("paint_gun_rainbow", "Rainbow", "", &paint::settings::rainbow);
		g_feature_manager.add<float_option>("paint_gun_r", "R", "", &paint::settings::r, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("paint_gun_g", "G", "", &paint::settings::g, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("paint_gun_b", "B", "", &paint::settings::b, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("paint_gun_scale", "Scale", "", &paint::settings::scale, 0, 1.0, 0.1, 1);

		g_feature_manager.add<toggle_with_float_option>("weapon_scale", "Weapon Scale", "", &weapon::modifiers::weapon_scale::enabled, &weapon::modifiers::weapon_scale::scale, 0, 1000, 0.1, 1, true, weapon::modifiers::weapon_scale::init);

		g_feature_manager.add<toggle_option>("revolver_spam", "Revolver Spam", "", &weapon::modifiers::revolver_spam::enabled, weapon::modifiers::revolver_spam::tick, weapon::modifiers::revolver_spam::on_disable);
		
		//impacts
		g_feature_manager.add<toggle_option>("delete_gun", "Delete", "", &impacts::delete_gun::enabled, impacts::delete_gun::init);
		g_feature_manager.add<toggle_option>("freeze_gun", "Freeze", "", &impacts::freeze::enabled, impacts::freeze::init);
		g_feature_manager.add<toggle_option>("max_gun", "Max", "", &impacts::max::enabled, impacts::max::init);
		g_feature_manager.add<toggle_option>("recolor_gun", "Recolor", "", &impacts::recolor::enabled, impacts::recolor::init);
		g_feature_manager.add<toggle_option>("shrink_gun", "Shrink", "", &impacts::shrink::enabled, impacts::shrink::init);
		g_feature_manager.add<toggle_option>("create_random_ped", "Create Random Ped", "", &impacts::create_random_ped_toggle, impacts::create_random_ped::init);
		g_feature_manager.add<toggle_option>("create_random_vehicle", "Create Random Vehicle", "", &impacts::create_random_vehicle::enabled, impacts::create_random_vehicle::init);
		g_feature_manager.add<toggle_option>("money_gun", "Money", "", &impacts::money::enabled, impacts::money::init);
		g_feature_manager.add<toggle_option>("repair_gun", "Repair", "", &impacts::repair_gun::enabled, impacts::repair_gun::tick);
		g_feature_manager.add<toggle_option>("hijack_gun", "Hijack", "", &impacts::steal_gun::enabled, impacts::steal_gun::tick);

		g_feature_manager.add<toggle_option>("bypass_vehicle_restrictions", "Vehicle Restrictions", "", &g_hooking_features.any_weapon_in_vehicle);
		g_feature_manager.add<toggle_option>("bypass_interior_restrictions", "Interior Restrictions", "", &g_hooking_features.m_weapons_in_interiors);

		g_feature_manager.add<toggle_with_float_option>("grapple_hook", "Grapple Hook", "", &impacts::grapple_hook::enabled, &impacts::grapple_hook::speed, 0, 1000, 0.1, 1, false, impacts::grapple_hook::init);

		g_feature_manager.add<toggle_with_choose_option>("fire_gun", "Fire", &impacts::fire::enabled, impacts::fire::settings::type, &impacts::fire::settings::type_pos, false, impacts::fire::init);

		g_feature_manager.add<toggle_option>("infinite_clip", "Infinte Clip", "", &unlimited_clip::enabled, unlimited_clip::init, unlimited_clip::on_disable);
		g_feature_manager.add<toggle_option>("infinite_ammo", "Infinte Ammo", "", &unlimited_ammo::enabled, unlimited_ammo::init, unlimited_ammo::on_disable);
		g_feature_manager.add<toggle_option>("infinite_lockon_range", "Lockon Range", "", &infinte_lockon_range::enabled, infinte_lockon_range::init, infinte_lockon_range::on_disable);
		g_feature_manager.add<toggle_option>("infinite_range", "Range", "", &infinite_range::enabled, infinite_range::init, infinite_range::on_disable);
		g_feature_manager.add<toggle_option>("disable_recoil", "Recoil", "", &weapon_disables::recoil::enabled, weapon_disables::recoil::init, weapon_disables::recoil::on_disable);
		g_feature_manager.add<toggle_option>("disable_spread", "Spread", "", &weapon_disables::spread::enabled, weapon_disables::spread::init, weapon_disables::spread::on_disable);
		g_feature_manager.add<toggle_option>("throwable_limits", "Throwable Limits", "", &weapon_disables::throwable_limits::enabled, weapon_disables::throwable_limits::init);

		g_feature_manager.add<toggle_option>("instant_lockon", "Instant Lockon", "", &weapon::modifiers::instant_lockon::enabled, weapon::modifiers::instant_lockon::init, weapon::modifiers::instant_lockon::on_disable);
		g_feature_manager.add<toggle_option>("instant_kill", "Instant Kill", "", &weapon::modifiers::instant_kill::enabled, weapon::modifiers::instant_kill::init, weapon::modifiers::instant_kill::on_disable);
		g_feature_manager.add<toggle_option>("no_damage", "No Damage", "", &weapon::modifiers::no_damage::enabled, weapon::modifiers::no_damage::init, weapon::modifiers::no_damage::on_disable);

		g_feature_manager.add<toggle_option>("shotgun", "Shotgun", "", &weapon::modifiers::shotgun::enabled, weapon::modifiers::shotgun::init, weapon::modifiers::shotgun::on_disable);

		g_feature_manager.add<toggle_option>("invisble_weapon", "Invisible", "", &invisible_weapon::enabled, invisible_weapon::tick, invisible_weapon::on_disable);
		g_feature_manager.add<toggle_with_choose_option>("mk2_ammo", "MK2 Ammo", "", &mk2_ammo::enabled, mk2_ammo::settings::type, &mk2_ammo::settings::selected, false, mk2_ammo::tick, mk2_ammo::on_disable);

		g_feature_manager.add<float_option>("weapon_opacity", "Opacity", "", &opacity, 0, 255, 51, 0, true, [] {
			ENTITY::SET_ENTITY_ALPHA(g_utils->weapon(), opacity, false);
		});

	}
}