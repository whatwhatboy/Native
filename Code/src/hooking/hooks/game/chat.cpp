#include "src/hooking/hooking.h"
#include "src/hooking/dat_bit_buffer/dat_bit_buffer.h"
#include "src/features/chat_commands/chat_commands.h"
#include <src/natives/natives.h>
#include "src/hooking/packets/packet.h"

namespace Base {
	inline CNetworkPlayerMgr* network_mgr() {
		return *g_pointers->m_network_player_mgr;
	}
	inline Network* get_network() {
		return *g_pointers->m_network;
	}
	void gamer_handle_serialize(rage::rlGamerHandle& hnd, dat_bit_buffer& buf) {
		buf.Write<uint8_t>(3, 8);
		buf.WriteInt64(*(int64_t*)&hnd.m_rockstar_id, 64);
		buf.Write<uint8_t>(hnd.unk_0009, 8);
	}
	rage::snPlayer* get_session_player(CNetGamePlayer* player) {
		if (player && get_network() && get_network()->m_game_session_ptr && player->get_net_data()) {
			for (u32 i = 0; i < get_network()->m_game_session_ptr->m_player_count; i++) {
				if (get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token == player->get_net_data()->m_host_token) {
					return get_network()->m_game_session_ptr->m_players[i];
				}
			}

			if (get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token == player->get_net_data()->m_host_token)
				return &get_network()->m_game_session_ptr->m_local_player;

			return nullptr;
		}
	}
	bool hooks::send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, char* message, bool is_team) {
		packet msg{};
		msg.write_message(eNetMessage::MsgTextMessage);
		msg.m_buffer.WriteString(message, 256);
		gamer_handle_serialize(g_pointers->m_get_net_player(PLAYER::PLAYER_ID())->get_net_data()->m_gamer_handle, msg.m_buffer);
		msg.write<bool>(is_team, 1);

		str msgt{ std::string(message) };
		if (g_hooking_features.m_chat.m_log)
			LOG(Info, "{} | {}", g_utils->cped()->m_player_info->m_net_player_data.m_name, msgt);

		for (auto& player : network_mgr()->m_player_list) {
			if (player && player->is_valid() && get_session_player(player)) {
				if (auto ped{ PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->m_player_id) }) {
					if (get_session_player(player)->m_msg_id) {
						msg.send(get_session_player(player)->m_msg_id);
					}
				}
			}
		}

		if (g_chat_commands.is_command(msgt)) {
			g_chat_commands.execute(PLAYER::PLAYER_ID(), msgt);
		}

		return true;
	}
	int hooks::check_chat_profanity(u64 rcx, u64 input, u64 output) {
		if (g_hooking_features.m_chat.m_profanity) return -1;

		RET_CALL_DECL(check_chat_profanity, rcx, input, output);
	}
}