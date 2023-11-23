#include "src/hooking/hooking.h"
#include "src/memory/Pointers/Pointers.h"
#include "src/hooking/spoofing.h"
#include "src/natives/natives.h"
#include <src/features/utils/utils.h>
namespace Base {
	bool get_from_int(int sel) {
		if (sel == 0) return true;
		else if (sel == 1) return false;
	}

	netGameEvent* hooks::send_player_card_stats(netGameEvent* a1, CPlayerCardStats* stats) {
		if (g_spoofing.m_rank.m_enabled)
			stats->m_rank = g_spoofing.m_rank.m_value;

		if (g_spoofing.m_spectate.m_enabled) {
			stats->m_is_spectating = get_from_int(g_spoofing.m_spectate.m_selected);
		}

		if (g_spoofing.m_kd_ratio.m_enabled)
			stats->m_kd_ratio = g_spoofing.m_kd_ratio.m_value;

		/*if (g.spoofing.spoof_bad_sport)
		{
			switch (g.spoofing.badsport_type)
			{
			case 0: stats->m_overall_badsport = 0.0f; break;
			case 1: stats->m_overall_badsport = 46.0f; break;
			case 2: stats->m_overall_badsport = 1000.0f; break;
			}
		}*/

		RET_CALL_DECL(send_player_card_stats, a1, stats);
	}

	bool hooks::send_session_matchmaking_attributes(void* a1, rage::rlSessionInfo* info, u64 session_id, bool use_session_id, MatchmakingAttributes* attributes) {
		/*if (g.spoofing.spoof_session_region_type)
			attributes->m_param_values[4] = g.spoofing.session_region_type;

		if (g.spoofing.spoof_session_language)
			attributes->m_param_values[3] = g.spoofing.session_language;*/

		if (g_spoofing.m_player_count.m_enabled)
			attributes->m_param_values[7] = g_spoofing.m_player_count.m_value;

		//if (g.spoofing.spoof_session_bad_sport_status)
		//{
		//	if (g.spoofing.session_bad_sport)
		//		attributes->m_param_values[0] |= (1 << 14);
		//	else
		//		attributes->m_param_values[0] &= ~(1 << 14);
		//}

		RET_CALL_DECL(send_session_matchmaking_attributes, a1, info, session_id, use_session_id, attributes);
	}

	void hooks::serialize_stats(CStatsSerializationContext* context, rage::joaat_t* stats, u32 stat_count) {
		CALL_DECL(serialize_stats, context, stats, stat_count);

		uint32_t* data = reinterpret_cast<uint32_t*>(context->m_entries);

		for (int i = 0; i < context->m_size / 4; i++)
		{
			CStatSerializationEntry* entry = reinterpret_cast<CStatSerializationEntry*>(&data[i]);

			if (g_spoofing.m_rank.m_enabled && (entry->m_hash == rage::joaat("MP0_CHAR_RANK_FM") || entry->m_hash == rage::joaat("MP1_CHAR_RANK_FM")))
			{
				entry->m_int_value = g_spoofing.m_rank.m_value;
			}

			//if (g.spoofing.spoof_bad_sport && entry->m_hash == rage::joaat("MPPLY_OVERALL_BADSPORT"))
			//{
			//	switch (g.spoofing.badsport_type)
			//	{
			//	case 0: entry->m_float_value = 0.0f; break;
			//	case 1: entry->m_float_value = 46.0f; break;
			//	case 2: entry->m_float_value = 1000.0f; break;
			//	}
			//}

			if (g_spoofing.m_kd_ratio.m_enabled)
			{
				if (entry->m_hash == rage::joaat("MPPLY_KILLS_PLAYERS"))
					entry->m_int_value = g_spoofing.m_kd_ratio.m_value;

				if (entry->m_hash == rage::joaat("MPPLY_DEATHS_PLAYER"))
					entry->m_int_value = 1;

				if (entry->m_hash == rage::joaat("MPPLY_DEATHS_PLAYER_SUICIDE"))
					entry->m_int_value = 0;
			}
		}
	}

	void hooks::write_player_appearance_data_node(rage::netObject* player, CPlayerAppearanceDataNode* node)
	{
		CALL_DECL(write_player_appearance_data_node, player, node);

		if (g_spoofing.m_model.m_enabled)
		{
			if (const auto model_hash = g_spoofing.m_model.m_value; STREAMING::IS_MODEL_VALID(model_hash))
			{
				node->m_model_hash = model_hash;
			}
			node->m_has_head_blend_data = false;
			node->components.m_component_bitset = 0;
		}
	}

	void hooks::write_player_creation_data_node(rage::netObject* player, CPlayerCreationDataNode* node)
	{
		CALL_DECL(write_player_creation_data_node, player, node);

		if (g_spoofing.m_model.m_enabled)
			node->m_model = g_spoofing.m_model.m_value;
	}

	auto is_in_cutscene() {
		if (g_utils->cped() && g_utils->cped()->m_player_info) {
			return (g_utils->cped()->m_player_info->m_game_state == eGameState::InMPCutscene);
		}
		return false;
	}

	bool is_in_interior() {
		return INTERIOR::GET_INTERIOR_FROM_ENTITY(PLAYER::PLAYER_PED_ID()) != 0;
	}

	void hooks::write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node)
	{
		CALL_DECL(write_player_game_state_data_node, player, node);

		if (g_spoofing.m_game_state.m_enabled) {
			node->m_player_state = (g_spoofing.m_game_state.m_value == 0 ? -1 : g_spoofing.m_game_state.m_value);
		}
		if (g_spoofing.m_is_respawning.m_enabled) {
			node->m_respawning = get_from_int(g_spoofing.m_is_respawning.m_selected);
		}
		if (g_spoofing.m_godmode.m_enabled && !is_in_cutscene() && !is_in_interior()) {
			node->m_is_invincible = get_from_int(g_spoofing.m_godmode.m_selected);
			node->m_bullet_proof = get_from_int(g_spoofing.m_godmode.m_selected);
			node->m_collision_proof = get_from_int(g_spoofing.m_godmode.m_selected);
			node->m_explosion_proof = get_from_int(g_spoofing.m_godmode.m_selected);
			node->m_fire_proof = get_from_int(g_spoofing.m_godmode.m_selected);
			node->m_melee_proof = get_from_int(g_spoofing.m_godmode.m_selected);
			node->m_steam_proof = get_from_int(g_spoofing.m_godmode.m_selected);
			node->m_water_proof = get_from_int(g_spoofing.m_godmode.m_selected);
		}

		if (g_spoofing.m_spectate.m_enabled) {
			node->m_is_spectating = get_from_int(g_spoofing.m_spectate.m_selected);
			node->m_spectating_net_id = 0;
		}

		if (g_spoofing.m_melee_damage.m_enabled) {
			node->m_melee_weapon_damage_modifier = g_spoofing.m_melee_damage.m_value;
		}

		if (g_spoofing.m_weapon_damage.m_enabled) {
			node->m_weapon_damage_modifier = g_spoofing.m_weapon_damage.m_value;
		}

		if (g_spoofing.m_battle_aware.m_enabled) {
			node->m_battle_aware = get_from_int(g_spoofing.m_battle_aware.m_selected);
		}

		if (g_spoofing.m_has_microphone.m_enabled) {
			node->m_has_microphone = get_from_int(g_spoofing.m_has_microphone.m_selected);
		}

		if (g_spoofing.m_no_collision.m_enabled) {
			node->m_no_collision = get_from_int(g_spoofing.m_no_collision.m_selected);
		}

		if (g_spoofing.m_bullet_proof.m_enabled) {
			node->m_bullet_proof = get_from_int(g_spoofing.m_bullet_proof.m_selected);
		}
		if (g_spoofing.m_collision_proof.m_enabled) {
			node->m_collision_proof = get_from_int(g_spoofing.m_collision_proof.m_selected);
		}
		if (g_spoofing.m_explosion_proof.m_enabled) {
			node->m_explosion_proof = get_from_int(g_spoofing.m_explosion_proof.m_selected);
		}
		if (g_spoofing.m_fire_proof.m_enabled) {
			node->m_fire_proof = get_from_int(g_spoofing.m_fire_proof.m_selected);
		}
		if (g_spoofing.m_melee_proof.m_enabled) {
			node->m_melee_proof = get_from_int(g_spoofing.m_melee_proof.m_selected);
		}
		if (g_spoofing.m_steam_proof.m_enabled) {
			node->m_steam_proof = get_from_int(g_spoofing.m_steam_proof.m_selected);
		}
		if (g_spoofing.m_water_proof.m_enabled) {
			node->m_water_proof = get_from_int(g_spoofing.m_water_proof.m_selected);
		}
	}

	void hooks::write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node) {
		CALL_DECL(write_player_gamer_data_node, player, node);

		if (g_spoofing.m_is_rockstar_dev.m_enabled) {
			node->m_is_rockstar_dev =  get_from_int(g_spoofing.m_is_rockstar_dev.m_selected);
		}

		if (g_spoofing.m_is_rockstar_qa.m_enabled) {
			node->m_is_rockstar_qa = get_from_int(g_spoofing.m_is_rockstar_qa.m_selected);
		}

		if (g_spoofing.m_is_cheater.m_enabled) {
			node->m_is_cheater = get_from_int(g_spoofing.m_is_cheater.m_selected);
		}

		/*if (g.spoofing.spoof_crew_data)
		{
			node->m_clan_data.m_clan_member_id = 1;
			node->m_clan_data.m_clan_id = 41564112;
			node->m_clan_data.m_clan_id_2 = 41564112;
			node->m_clan_data.m_clan_color = 420;
			node->m_clan_data.m_clan_member_count = 15;
			node->m_clan_data.m_clan_created_time = 420;

			strcpy(node->m_clan_data.m_clan_tag, g.spoofing.crew_tag.c_str());
			node->m_clan_data.m_is_system_clan = g.spoofing.rockstar_crew;
			node->m_clan_data.m_is_clan_open = g.spoofing.square_crew_tag;

			if (g.spoofing.rockstar_crew)
			{
				strcpy(node->m_clan_data.m_clan_name, "Rockstar");
			}
		}*/
	}
}
