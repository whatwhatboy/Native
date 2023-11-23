#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include <src/framework/option_types/button.h>
#include "src/hooking/hooking.h"
#include <src/framework/option_types/icon_button.h>
#include <src/framework/option_types/submenu.h>
#include <src/features/utils/host.h>
#include "src/framework/option_types/toggle.h"
#include "src/framework/submenu_types/player_submenu.h"
#include "recovery.h"
#include "rid_toolkit.h"
#include "overseer.h"
#include "chat.h"
#include "src/core/script/player_manager/player_manager.h"
#include "players.h"
#include "protections.h"
#include "spoofing.h"
namespace Base::submenus::network {
	using namespace Framework;
	bool can_migrate{ false };
	void force_host2(const char* name) {
		force_host(rage::joaat(name));
		if (auto script{ find_script_thread(rage::joaat(name)) }; script && script->m_net_component)
			((CGameScriptHandlerNetComponent*)script->m_net_component)->block_host_migration(!can_migrate);
	}
	struct RegionType
	{
		uint32_t id;
		const char name[22];
	};

	const RegionType regions[] = {
		{0, "CIS"},
		{1, "Africa"},
		{2, "East"},
		{3, "Europe"},
		{4, "China"},
		{5, "Australia"},
		{6, "West"},
		{7, "Japan"},
	};
	struct session_context { str name; int id = 0; };
	std::vector<session_context> session_types = {
		{ "Solo", 0 },
		{ "Invite Only", 1 },
		{ "Closed Friend", 2 },
		{ "Closed Crew", 3 },
		{ "Crew", 4 },
		{ "Public" , 5 },
	};
	void main() {
		if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::network) return;

		click_ui::setup_col("network");
		draw->submenu("Players", "network_players", submenus::network::players::main);
		draw->submenu("Recovery", "network:recovery", submenus::network::recovery);
		draw->submenu("Spoofing", "network_spoofing", submenus::network::spoofing);
		draw->submenu("Overseer", "network_overseer", submenus::network::overseer::main);
		draw->submenu("Toolkit", "network:toolkit", [] {
			draw->submenu_second("Transactions", "network_transactions", [] {
				for (auto t : g_transactions) {
					str name{ std::format("{} ({})", t->m_transactions[0].m_id, t->m_transactions[0].m_price) };
					draw->submenu(name, name, [=] {
						draw->button("Replay", [=] {
							g_utils->invoke_transaction(t->m_category, t->m_transaction_id, t->m_action, t->m_transactions[0].m_price, t->m_target);
						});
					});
				}
			});
			draw->submenu_second("RID", "rid_toolkit", submenus::network::rid_toolkit::main);
			draw->submenu_second("Block Joining", "network:toolkit:block_joining", [] {
				draw->option("block_joins");
				draw->seperator("Message");
				for (auto i = 0; i < sizeof(g_hooking_features.reasons) / sizeof(g_hooking_features.reasons[0]); i++) {
					if (g_hooking_features.reasons_selected == i) {
						add_option<Framework::icon_button>(g_hooking_features.reasons[i], "", "On", [=] {
							g_hooking_features.reasons_selected = i;
							});
					}
					else {
						add_option<Framework::button>(g_hooking_features.reasons[i], "", [=] {
							g_hooking_features.reasons_selected = i;
							});
					}
				}
				});
			draw->submenu_second("Session Type", "network_session_type", [] {
				for (const auto type : session_types) {
					draw->button(type.name, [=] {
						(*g_pointers->m_network)->m_network_game_filter.m_matchmaking_component.m_session_type = (uint16_t)type.id;
						});
				}
				});
			draw->submenu_second("Blacklisted Players", "blacklisted_players", [] {
				bool empty{ false };
				auto players{ 16 - (*g_pointers->m_network)->m_blacklist.m_free_nodes };
				for (int i = 0; i < players; i++) {
					if (i > 0) {
						const CNetBlacklistNode& node{ (*g_pointers->m_network)->m_blacklist.m_nodes[i] };
						if (std::to_string(node.m_handle.m_rockstar_id) != "0") {
							draw->button(std::to_string(node.m_handle.m_rockstar_id), [] {});
						}
					}
					else {
						empty = true;
					}
				}
				});
			draw->option("force_thunder");
			inline_item
			draw->option("open_extra_slot");
			});
		draw->submenu("Friends", "network:friends", [] {
			for (u32 i = 0; i < g_pointers->m_friend_registry->m_friend_count; i++) {
				draw->submenu_second(std::format("{}", g_pointers->m_friend_registry->get(i)->m_name), std::format("network:friend:{}", g_pointers->m_friend_registry->get(i)->m_name), [=] {
					draw->button("Invite", [=] {
						rid_utils::invite_player(g_pointers->m_friend_registry->get(i)->m_rockstar_id);
						});
					});

			}
			});

		draw->submenu("Modder Detection", "modder_detection", [] {
			draw->option("modder_detection");
			draw->seperator("Detections");
			draw->option("modder_detection_invalid_model");
			inline_item
			draw->option("modder_detection_speed");
			});
		draw->submenu("Streamer Mode", "stream_mode", [] {
			draw->toggle("Enabled", &g_hooking_features.m_streamer_mode.m_enabled);
			draw->keyboard("Prefix", g_hooking_features.m_streamer_mode.m_prefix);
			draw->seperator("Misc");
			draw->button("Make Name Red", [] {
				g_hooking_features.m_streamer_mode.m_prefix = "~r~" + g_hooking_features.m_streamer_mode.m_prefix + "~w~";
				});
			});
		click_ui::next_col();
		draw->submenu("Notifications", "notis", [] {
			draw->option("joining_players");
			inline_item
			draw->option("leaving_players");
			draw->option("kill_feed");
		}, 68);
		draw->submenu("Scripts", "network:scripts", [] {
			draw->submenu_second("Ongoing", "network:scripts:ongoing", [] {
				if (is_mission_started("am_criminal_damage")) {
					draw->submenu_second("Criminal Damage", "network:scripts:ongoing:criminal_damage", [] {
						draw->option("start_criminal_damage");
						draw->option("end_criminal_damage");
						draw->seperator("Other");
						draw->option("win_criminal_damage");
						});
				}
				else
					draw->text("None Found");
			});
			draw->seperator("Starter");

			draw->submenu_second("Freemode", "network:scripts:freemode", [] {
				draw->option("criminal_damage");
				draw->option("checkpoints");
				draw->option("business_battle");
				draw->option("king_of_the_castle");
				draw->option("hunt_the_beast");
				draw->option("hot_property");
				draw->option("hot_target");
				draw->option("kill_list");
				draw->option("penned_in");
				draw->option("challenges");
				});
			draw->submenu_second("Activites", "network:scripts:activites", [] {
				draw->option("golf");
				draw->option("flight_school");
				draw->option("one_on_one_deathmatch");
				draw->option("impromptu_race");
				draw->option("tutorial");
				draw->option("ghost_hunt");
				});
			draw->submenu_second("Arcade", "network:scripts:arcade", [] {
				draw->option("space_monkey");
				draw->option("wizard");
				draw->option("gunslinger");
				});
			});
		draw->submenu("Matchmaking", "network:matchmaking", [] {
			draw->submenu_second("Region Switcher", "network:matchmaking:region_switcher", [=] {
				for (const auto& region_type : regions) {
					if (*g_pointers->m_region_code == region_type.id) {
						add_option<Framework::icon_button>(region_type.name, "", "On", [=] {
							*g_pointers->m_region_code = region_type.id;
							});
					}
					else {
						add_option<Framework::button>(region_type.name, "", [=] {
							*g_pointers->m_region_code = region_type.id;
							});
					}
				}
				});
			draw->submenu_second("Limits", "network:matchmaking:limits", [] {
				draw->option("max_players");
				draw->option("max_spectators");
				});
			draw->submenu_second("Join Session", "join_session", [] {
				for (auto item : "join_session"_CF->m_items) {
					draw->button(item, [=] {
						rid_utils::join(item);
						});
				}
				});
			draw->option("bail");
			});
		draw->submenu("Chat", "network_chat", submenus::network::chat::main);
		draw->submenu("Host", "network:host", [] {
			draw->option("force_script_host");
			draw->seperator("List");
			add_option<Framework::toggle>("Can Migrate", "", &can_migrate);
			add_option(button("Freemode")
				.add_action([] {
					force_host2("freemode");
					}));
			add_option<Framework::button>("Launcher", "", [] {
				force_host2("fmmc_launcher");
				});
			add_option<Framework::button>("Criminal Damage", "", [] {
				force_host2("am_criminal_damage");
				});
			add_option<Framework::button>("Hunt The Beast", "", [] {
				force_host2("am_hunt_the_beast");
				});
			add_option<Framework::button>("King Of The Castle", "", [] {
				force_host2("am_king_of_the_castle");
				});
			add_option<Framework::button>("Collection", "", [] {
				force_host2("am_cp_collection");
				});
			add_option<Framework::button>("Casino", "", [] {
				force_host2("gb_casino");
				});
			});
		draw->submenu("Tunables", "network:tunables", [] {
			draw->option("disable_casino_region_lock");
			});
		draw->submenu("Globals", "network:globals", [] {
			draw->submenu_second("Off Radar", "network:globals:off_radar", [] {
				draw->option("off_radar");
				draw->seperator("Modifiers");
				draw->option("ghost_org");
				});
			draw->submenu_second("Requests", "network:globals:requests", [] {
				draw->submenu_second("Merryweather", "network:globals:requests:merryweather", [] {
					draw->option("bst");
					draw->option("airstrike");
					draw->option("ammo_crate");
					draw->option("backup_helicopter");
					draw->option("ballistic_armor");
					draw->option("boat_pickup");
					});
				draw->seperator("Other");
				draw->option("taxi");
				draw->option("dinghy");
				draw->option("avenger");
				draw->option("kosatka");
				draw->option("moc");
				draw->option("terrobyte");
				draw->option("acid_lab");
			});
		});
		click_ui::end_col();


	}
}
