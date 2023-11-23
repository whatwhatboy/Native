#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/rage/script/globals/GlobalPlayerBD.hpp>
#include "classes.h"
#include "src/hooking/spoofing.h"
#include <src/rage/script/globals/GPBD_FM.hpp>
namespace Base {
	int id_self() {
		if (!*g_pointers->m_network_player_mgr || !(*g_pointers->m_network_player_mgr)->m_local_net_player || (*g_pointers->m_network_player_mgr)->m_local_net_player->m_player_id == -1)
			return 0;
		else
			return (*g_pointers->m_network_player_mgr)->m_local_net_player->m_player_id;
	}
	static inline const script_global gpbd_fm_1(1853988);
	void spoofingt::tick() {
		if (!g_spoofing.m_job_points.m_enabled && !g_spoofing.m_rank.m_enabled && !g_spoofing.m_kd_ratio.m_enabled) return;

		if (*g_pointers->m_is_session_started) {
			execute_as_script(rage::joaat("freemode"), [=] {
				if (NETWORK::NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT() && NETWORK::NETWORK_GET_SCRIPT_STATUS() == 2) {
					if (g_spoofing.m_rank.m_enabled) {
						gpbd_fm_1.as<GPBD_FM*>()->Entries[id_self()].PlayerStats.Rank = g_spoofing.m_rank.m_value;
					}

					if (g_spoofing.m_job_points.m_enabled)	
						gpbd_fm_1.as<GPBD_FM*>()->Entries[id_self()].JobPoints = g_spoofing.m_job_points.m_value;
					if (g_spoofing.m_kd_ratio.m_enabled)
						gpbd_fm_1.as<GPBD_FM*>()->Entries[id_self()].PlayerStats.KdRatio = g_spoofing.m_kd_ratio.m_value;

					//if (g.spoofing.spoof_blip)
					//{
					//	if (g.spoofing.blip_type == 0)// random
					//		scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].PlayerBlip.PlayerVehicleBlipType = (eBlipType)(rand() % 90);
					//	else
					//		scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].PlayerBlip.PlayerVehicleBlipType =
					//		(eBlipType)(g.spoofing.blip_type - 1);
					//}
				}
			});
		}
	}
}
