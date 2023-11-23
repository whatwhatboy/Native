#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/rage/script/globals/GlobalPlayerBD.hpp>
#include "classes.h"
#include "src/framework/option_types/keyboard.h"

namespace Base {
	void streamer_mode::tick() {
		if (!g_hooking_features.m_streamer_mode.m_enabled || Framework::keyboard_open) return;

		for (u32 i = 0; i < g_utils->get_network_player_mgr()->m_player_count; i++) {
			if (g_pointers->m_get_net_player(i) && g_pointers->m_get_net_player(i)->is_valid()) {
				if (g_pointers->m_get_net_player(i)->m_player_info) {
					if (auto check{ PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) }) {
						strncpy_s(g_pointers->m_get_net_player(i)->m_player_info->m_net_player_data.m_name, std::format("{} {}", g_hooking_features.m_streamer_mode.m_prefix, i).c_str(), sizeof(g_pointers->m_get_net_player(i)->m_player_info->m_net_player_data.m_name));
					}
				}
			}
		}
		
		
	}
}
