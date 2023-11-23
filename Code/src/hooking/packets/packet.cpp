#include "packet.h"

namespace Base
{
	inline Network* get_network() {
		return *g_pointers->m_network;
	}
	inline rage::snPlayer* get_session_player(CNetGamePlayer* player) {
		for (uint32_t i = 0; i < get_network()->m_game_session_ptr->m_player_count; i++) {
			if (get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token == player->get_net_data()->m_host_token) {
				return get_network()->m_game_session_ptr->m_players[i];
			}
		}

		if (get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token == player->get_net_data()->m_host_token)
			return &get_network()->m_game_session_ptr->m_local_player;

		return nullptr;
	}

	packet::packet() :
		m_buffer(m_data, 0x4000)
	{}

	void packet::send(uint32_t msg_id) {
		g_pointers->m_queue_packet(get_network()->m_game_session_ptr->m_net_connection_mgr, msg_id, m_data, (m_buffer.m_curBit + 7) >> 3, 1, nullptr);
	}

	void packet::send(CNetGamePlayer* player, int connection_id) {
		send(get_session_player(player)->m_player_data.m_peer_id_2, connection_id);
	}

	void packet::send(int peer_id, int connection_id) {
		auto mgr = get_network()->m_game_session_ptr->m_net_connection_mgr;
		auto peer = g_pointers->m_get_connection_peer(mgr, peer_id);
		g_pointers->m_send_packet(mgr, &peer->m_peer_address, connection_id, m_data, (m_buffer.m_curBit + 7) >> 3, 0x1000000);
	}
}