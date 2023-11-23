#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/button.h"
#include "src/framework/option_types/number.h"
#include <JSON/json.hpp>
#include "src/hooking/spoofing.h"

#define get_args(name) &g_spoofing.m_##name.m_enabled, g_spoofing.m_##name.m_vector, &g_spoofing.m_##name.m_selected
namespace Base::submenus::network {
	using namespace Framework;
	void spoofing() {
		draw->submenu_second("Detections", "spoofing_detections", [] {
			draw->toggle_with_choose("Godmode", get_args(godmode));
			draw->toggle_with_choose("Is Spectating", get_args(spectate));
			draw->toggle_with_choose("Super Jump", get_args(super_jump));
		});
		draw->submenu_second("Account", "spoofing_stats", [] {
			draw->submenu_second("Rank", "rank_spoofing", [=] {
				draw->toggle("Enabled", &g_spoofing.m_rank.m_enabled);
				add_option<Framework::number<int>>("Value", "", &g_spoofing.m_rank.m_value, -INT_MAX, INT_MAX, 1, 0);
			});
			draw->toggle_with_number<int>("Job Points", &g_spoofing.m_job_points.m_enabled, &g_spoofing.m_job_points.m_value, 0, 100, 1, 0);
			draw->toggle_with_number<float>("KD Ratio", &g_spoofing.m_kd_ratio.m_enabled, &g_spoofing.m_kd_ratio.m_value, INT_MAX, INT_MAX, 0.1, 1);
		});
		draw->submenu_second("Flags", "spoofing_flags", [] {
			draw->toggle_with_choose("Is Rockstar Dev", get_args(is_rockstar_dev));
			draw->toggle_with_choose("Is Rockstar QA", get_args(is_rockstar_qa));
			draw->toggle_with_choose("Is Cheater", get_args(is_cheater));
			draw->toggle_with_choose("Is Respawning", get_args(is_respawning));
			draw->toggle_with_choose("Battle Aware", get_args(battle_aware));
			draw->toggle_with_choose("Has Microphone", get_args(has_microphone));
		});
		draw->submenu_second("Proofs", "spoofing_proofs", [] {
			draw->toggle_with_choose("Bullet", get_args(bullet_proof));
			draw->toggle_with_choose("Collision", get_args(collision_proof));
			draw->toggle_with_choose("Explosion", get_args(explosion_proof));
			draw->toggle_with_choose("Fire", get_args(fire_proof));
			draw->toggle_with_choose("Melee", get_args(melee_proof));
			draw->toggle_with_choose("Steam", get_args(steam_proof));
			draw->toggle_with_choose("Water", get_args(water_proof));
		});
		draw->submenu_second("Session Attributes", "spoofing_session", [] {
			draw->toggle_with_number<int>("Player Count", &g_spoofing.m_player_count.m_enabled, &g_spoofing.m_player_count.m_value, 0, 32, 1, 0);
		});
		draw->toggle_with_choose("Game State", &g_spoofing.m_game_state.m_enabled, g_spoofing.m_game_state_names, &g_spoofing.m_game_state.m_value);
		draw->toggle_with_number<float>("Weapon Damage", &g_spoofing.m_weapon_damage.m_enabled, &g_spoofing.m_weapon_damage.m_value, 0, 1000, 1, 0);
		draw->toggle_with_number<float>("Melee Damage", &g_spoofing.m_melee_damage.m_enabled, &g_spoofing.m_melee_damage.m_value, 0, 1000, 1, 0);
	}
}
