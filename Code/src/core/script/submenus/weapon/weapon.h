#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "disables.h"
#include "main.h"
#include "gun_locker.h"
#include "explosion_data.h"
#include "bullet_changer.h"
#include "particles.h"
#include "projectile_editor.h"
#include "crosshair.h"
namespace Base::submenus::weapon {
	void draw_class_shooter(const char* name) {
		draw->submenu_second(name, name + std::to_string(55), [=] {
			for (auto& veh : vehicle_hash_list) {
				if (strcmp(veh.m_class, name) == 0) {
					if (*"entity_shooter_vehicle"_KF->m_str == veh.name) {
						add_option<Framework::icon_button>(g_feature_manager.get_command<button_option>(std::to_string(veh.hash).c_str())->m_name, "", "On", [=] {
							*"entity_shooter_vehicle"_KF->m_str = veh.name;
						});
					}
					else {
						add_option<Framework::button>(g_feature_manager.get_command<button_option>(std::to_string(veh.hash).c_str())->m_name, "", [=] {
							*"entity_shooter_vehicle"_KF->m_str = veh.name;
							});
					}
				}
			}
			});
	}
	void main() {
		if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::weapon) return;

		click_ui::setup_col("weapon");
		draw->submenu("Core", "weapon_core", [] {
			draw->option("infinite_ammo");
			draw->option("infinite_clip");
			draw->option("instant_lockon");
			draw->option("instant_kill");
		});
		draw->submenu("Locker", "weapon:gun_locker", submenus::weapon::gun_locker);
		draw->submenu("Modifiers", "Home/Weapon/Modifiers", [] {
			draw->submenu_second("Fired", "fired_weapons", [] {
				draw->number("Sticky Bombs", g_utils->cped()->fired_sticky_bombs, { 0, 500, 1, 0 });
				draw->number("Flares", g_utils->cped()->fired_flares, { 0, 500, 1, 0 });
				draw->number("Unknown", g_utils->cped()->fired_unk_0, { 0, 500, 1, 0 });
				draw->number("Acid Packages", g_utils->cped()->fired_unk_1, { 0, 500, 1, 0 });
				});
			draw->submenu_second("Infinite", "weapon:modifiers:infinite", submenus::weapon::infinite);
			draw->submenu_second("Editor", "weapon:modifiers:main", submenus::weapon::modifiers::main);
			draw->submenu_second("Projectile Editor", "projectile_editor", submenus::weapon::projectile_edtior);
			draw->option("mk2_ammo");
			draw->option("revolver_spam");
			draw->option("no_damage");
			draw->option("shotgun");
			});
		draw->submenu("Impacts", "weapon:impacts", submenus::weapon::impacts::main);
		draw->submenu("Visuals", "weapon:visuals", [] {
			draw->submenu_second("Grenade", "weapon:misc:grenade", [] {
				draw->option("instantly_explode_greandes");
				});
			draw->submenu_second("Particles", "particle_gun", submenus::weapon::particles);
			draw->submenu_second("Aim Tracer", "aim_tracer", [] {
				draw->option("aim_tracer");
				draw->seperator("Color");
				draw->option("aim_tracer_rainbow");
				draw->option("aim_tracer_r");
				draw->option("aim_tracer_g");
				draw->option("aim_tracer_b");
			});
			draw->submenu_second("Crosshair", "crosshair", submenus::weapon::crosshair);
			draw->option("clown_vfx");
			draw->option("display_weapon_on_back");
			draw->option("invisble_weapon");
			//draw->toggle_with_number("weapon_scale");
			draw->option("weapon_opacity");
		});
		draw->submenu("Aimbot", "weapon:modifiers:aimbot", [] {
			draw->option("aimbot");
			draw->seperator("Settings");
			draw->option("aimbot_only_players");
			draw->option("aimbot_always_lockon");
			draw->option("aimbot_draw_fov");
			draw->option("aimbot_fov");
			draw->option("aimbot_smoothing");
			});
		draw->submenu("Tracers", "weapon:bullet_tracers", submenus::weapon::bullet_tracers);
		draw->submenu("Gravity", "gravity_gun", [] {
			draw->option("gravity_gun");
			draw->seperator("Settings");
			draw->option("gravity_gun_save_on_unaim");
			draw->option("gravity_gun_force");
			draw->option("gravity_gun_zoom");
		});
		click_ui::next_col();
		draw->submenu("Triggerbot", "weapon:modifiers:triggerbot", [] {
			draw->option("triggerbot");
			draw->option("triggerbot_bone");
			});
		draw->submenu("Rapid Fire", "weapon:modifiers:rapid_fire", [] {
			draw->option("rapid_fire");
			draw->seperator("Settings");
			draw->option("rapid_fire_disable_shooting");
			draw->option("rapid_fire_disable_when_reloading");
			draw->option("rapid_fire_only_when_aiming");
			draw->option("rapid_fire_bullets");
			draw->option("rapid_fire_delay");
			});
		draw->submenu("Missile Launcher", "missle_launcher", [] {
			draw->option("missle_launcher");
			draw->seperator("Settings");
			draw->submenu_second("Elements", "missle_launcher_elements", [] {
				draw->option("missle_launcher_vision");
				draw->option("missle_launcher_meter");
				draw->option("missle_launcher_hud");
				});
			draw->option("missle_launcher_noclip");
			draw->option("missle_launcher_only_explode_on_impact");
			draw->option("missle_launcher_explosion_type");
			//slight spelling mistake lol
			});
		draw->submenu("Entity Shooter", "entity_shooter", [] {
			draw->option("entity_shooter");
			draw->seperator("Settings");
			draw->submenu_second("Vehicle", "entity_shooter_vehicle", [] {
				for (auto& i : vehicle_classes) {
					draw_class_shooter(i.c_str());
				}
			});
			draw->seperator("Shot");
			draw->button("Delete", [] {
				for (auto item : m_entity_shooter_shot) {
					VEHICLE::DELETE_VEHICLE(&item.m_id);
					m_entity_shooter_shot.clear();
				}
				});
			for (auto item : m_entity_shooter_shot) {
				draw->button(item.m_name, [] {});
			}
		});
		draw->submenu("Disables", "weapon:misc:disables", submenus::weapon::disables);
		draw->submenu("Magnet", "weapon:magnet", submenus::weapon::magnet);
		draw->submenu("Bullet Changer", "weapon:modifiers:bullet_changer", submenus::weapon::bullet_changer);
		//draw->submenu("Explosion Test", "weapon:explosion", submenus::weapon::explosion_data_sub);
		click_ui::end_col();
		
	}
}
