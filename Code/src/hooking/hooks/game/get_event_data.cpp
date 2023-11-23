#include "src/hooking/hooking.h"
#include "src/framework/notifications/notifications.h"
#include <src/features/utils/host.h>
#include "src/rage/script/globals/GPBD_FM_3.hpp"
namespace Base {
	void protection_notify2(str name, str plr_name) {
		g_notifications->send("Protections", std::format("Blocked '{}' crash from {}", name, plr_name));
	}
	void protection_notify_kick(str name, str plr_name) {
		g_notifications->send("Protections", std::format("Blocked '{}' kick from {}", name, plr_name));
	}
	bool is_player_our_boss(u8 sender) {
		static const script_global gpbd_fm_3(1895156);
		return sender == gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.Boss;
	}
	bool hooks::get_event_data(int32_t event_group, int32_t event_index, int64_t* args, uint32_t arg_count) {
		auto result{ CALL_DECL(get_event_data, event_group, event_index, args, arg_count) };
		if (result && *g_pointers->m_is_session_started) {
			auto sender{ g_pointers->m_get_net_player(args[1]) };

			switch (static_cast<eRemoteEvent>(args[0])) {
			case eRemoteEvent::MCTeleport:
				if (args[3] > 32) {
					if (g_protection_manager.m_crash.m_notify) {
						g_notifications->send("Protections", std::format("{} tried to send 'teleport crash'", sender->get_name()));
					}
					if (g_protection_manager.m_crash.m_block) {
						return false;
					}
				}

				if (!is_player_our_boss(sender->m_player_id)) {
					g_notifications->send("Protections", std::format("{} tried to send 'mc teleport'", sender->get_name()));
					return false;
				}
				break;
			case eRemoteEvent::Crash: {
				if (g_protection_manager.m_crashes.m_tse) {
					protection_notify2("TSE", sender->get_name());
					return false;
				}
				break;
			}
			case eRemoteEvent::NetworkBail: {
				if (g_protection_manager.m_kicks.m_bail) {
					protection_notify_kick("bail", sender->get_name());
					return false;
				}
				break;

			}
			case eRemoteEvent::Crash2:
				if (args[2] > 32) {
					if (g_protection_manager.m_crashes.m_tse) {
						protection_notify2("TSE", sender->get_name());
						return false;
					}
				}
				break;
			case eRemoteEvent::Crash3:
				if (isnan(*(float*)&args[3]) || isnan(*(float*)&args[4])) {
					if (g_protection_manager.m_crashes.m_tse) {
						protection_notify2("TSE", sender->get_name());
						return false;
					}
				}
				break;
			case eRemoteEvent::Notification:
				switch (static_cast<eRemoteEvent>(args[2])) {
				case eRemoteEvent::NotificationMoneyBanked:
				case eRemoteEvent::NotificationMoneyRemoved:
				case eRemoteEvent::NotificationMoneyStolen:
				case eRemoteEvent::NotificationCrash1:
					g_notifications->send("Protections", std::format("{} tried to crash you (notis)", sender->get_name()));
					return false;
				case eRemoteEvent::NotificationCrash2:
					if (!find_script_thread(rage::joaat("gb_salvage"))) {
						g_notifications->send("Protections", std::format("{} tried to crash you (notis 2)", sender->get_name()));
						return false;
					}
					break;
				}
			case eRemoteEvent::InteriorControl: {
				int interior{ (int)args[2] };
				if (interior < 0 || interior > 161) {
					if (g_protection_manager.m_kicks.m_interior) {
						protection_notify_kick("interior", sender->get_name());
						return false;
					}
				}

				if (NETWORK::NETWORK_IS_ACTIVITY_SESSION())
					break;

				//if (!g_local_player)
				//	break;

				//if (is_player_our_boss(plyr->id()))
				//	break;

				//if (is_player_driver_of_local_vehicle(plyr->id()))
				//	break;

				//if (!plyr->get_ped() || math::distance_between_vectors(*plyr->get_ped()->get_position(), *g_local_player->get_position()) > 75.0f)
				//{
				//	// g.reactions.send_to_interior.process(plyr); false positives
				//	return true; // this is fine, the game will reject our false positives anyway
				//}

				break;
			}
			}

		}
		return result;
	}

}