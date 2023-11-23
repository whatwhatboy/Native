#pragma once
#include "src/utility/common/common.h"
namespace Base {
	struct spoofing_var_hash {
		bool m_enabled{};
		Hash m_value;
	};
	struct spoofing_var_int {
		bool m_enabled;
		int m_value;
	};
	struct spoofing_var_float {
		bool m_enabled;
		float m_value;
	};
	struct spoofing_var_choose {
		bool m_enabled;
		std::vector<ccp> m_vector {
			"On",
			"Off"
		};
		int m_selected;
	};
	class spoofing {
	public:
		spoofing_var_int m_rank;
		spoofing_var_int m_cash;
		spoofing_var_hash m_model;
		spoofing_var_int m_job_points;
	public:
		spoofing_var_float m_melee_damage;
		spoofing_var_float m_weapon_damage;
		spoofing_var_float m_kd_ratio;
	public:
		spoofing_var_int m_game_state;
		std::vector<ccp> m_game_state_names = {
			"Invalid",
			"Playing",
			"Died",
			"Arrested",
			"Failed Mission",
			"Left Game",
			"Respawn",
			"In MP Cutscene"
		};
	public:
		//session
		spoofing_var_int m_player_count;
	public:
		spoofing_var_choose m_is_respawning;
		spoofing_var_choose m_godmode;
		spoofing_var_choose m_spectate;
		spoofing_var_choose m_super_jump;
		spoofing_var_choose m_battle_aware;
		spoofing_var_choose m_has_microphone;
		spoofing_var_choose m_no_collision;
	public:
		spoofing_var_choose m_is_rockstar_dev;
		spoofing_var_choose m_is_rockstar_qa;
		spoofing_var_choose m_is_cheater;
	public:
		spoofing_var_choose m_bullet_proof;
		spoofing_var_choose m_collision_proof;
		spoofing_var_choose m_explosion_proof;
		spoofing_var_choose m_fire_proof;
		spoofing_var_choose m_melee_proof;
		spoofing_var_choose m_steam_proof;
		spoofing_var_choose m_water_proof;
	} inline g_spoofing;
}