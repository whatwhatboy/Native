#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/features/utils/rid_utils.h"
#include "src/framework/option_types/keyboard.h"
#include "src/framework/option_types/button.h"
#include "src/features/other/bodyguard_manager/bodyguard_manager.h"

namespace Base::submenus::network::players {
	void draw_class_network(str name, int offset, bool is_all = false) {
		draw->submenu_second(name, name + std::to_string(offset), [=] {
			for (auto& veh : vehicle_hash_list) {
				if (strcmp(veh.m_class, name.c_str()) == 0) {
					draw->button(g_feature_manager.get_command<button_option>(std::to_string(veh.hash).c_str())->m_name, [=] {
						static int count{ g_utils->get_network_player_mgr()->m_player_count };
						if (is_all) {
							for (int i = 0; i < count; i++) {
								g_player_mgr.m_buttons.ram(get_context(i), veh.hash);
							}
						}
						else {
							g_player_mgr.m_buttons.ram(get_context(g_selected_player), veh.hash);
						}
					});
				}
			}
		});
	}
	int get_player_id(str name) {
		for (auto plr : get_players()) {
			if (plr && plr->is_valid() && (plr->get_name() == name))
				return plr->m_player_id;
		}
		return g_selected_player;
	}
	std::vector<ccp> cage_types {
		"Trolly",
			"Fence"
	};
	int cage_type{ 0 };

	void options() {
		draw->submenu_second("Trolling", "selected_trolling", [] {
			draw->submenu_second("Ram", "ram_player", [] {
				for (auto& i : vehicle_classes) {
					draw_class_network(i, 5);
				}
			});
			draw->submenu_second("Script Events", "selected_script_events", [] {
				draw->toggle("Transaction Error", "", &g_player_mgr.m_players[g_selected_player].m_transaction_error);
				draw->button("CEO Kick", [] {
					int64_t event[4] = { (int64_t)eRemoteEvent::CeoKick, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				});
				inline_item
				draw->button("CEO Ban", [] {
					int64_t event[4] = { (int64_t)eRemoteEvent::CeoBan, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				});
				inline_item
				draw->button("Rotate Camera", [] {
					int64_t event[4] = { (int64_t)eRemoteEvent::TSECommandRotateCam, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				});
				draw->button("Banner", [] {
					int64_t event[4] = { (int64_t)eRemoteEvent::GtaBanner, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				});
				inline_item
				draw->button("10K (Must Be In CEO)", [] {
					int64_t event[4] = { (int64_t)eScriptEvents::ScriptEventBeenPaidGoonCash, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				});
				draw->button("Delete Old PVS", [] {
					int64_t event[4] = { (int64_t)eScriptEvents::GeneralEventDeleteOldPvs, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				});
				inline_item
				draw->button("Send To Cutscene", [] {
					int64_t event[4] = { (int64_t)eRemoteEvent::SendToCutscene, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				});
				draw->button("MC Teleport", [] {
					int64_t event[4] = { (int64_t)eRemoteEvent::MCTeleport, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				});
				inline_item
				draw->button("Transaction Error", [] {
					int64_t event[4] = { (int64_t)eRemoteEvent::TransactionError, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				});
				draw->button("Test", [] {
					const size_t arg_count = 8;
					int64_t args[arg_count] = { (int64_t)eRemoteEvent::SendTextLabelSMS, PLAYER::PLAYER_ID() };

					strcpy((char*)&args[2], "HUD_ROSBANPERM");

					g_pointers->m_trigger_script_event(1, args, arg_count, 1 << g_selected_player);
				});
			});
			draw->toggle("Taze", "Tazes the player.", &g_player_mgr.m_players[g_selected_player].m_taze);
			inline_item
			draw->toggle("Explode", "Explodes the player.", &g_player_mgr.m_players[g_selected_player].m_explode);
			draw->toggle("Hostile Vehicles", "Makes all the vehicles go towards you.", &g_player_mgr.m_players[g_selected_player].m_hostile_vehicles);
			inline_item
			draw->toggle("Rain Rockets", "Rains rockets on the player.", &g_player_mgr.m_players[g_selected_player].m_rain_rockets);
			draw->choose("Cage", cage_types, &cage_type, false, [] {
				g_player_mgr.m_buttons.cage(get_context(g_selected_player), cage_type);
			});
			draw->button("Kick From Vehicle", [] {
				g_player_mgr.m_buttons.kick_from_vehicle(get_context(g_selected_player));
				});
			inline_item
			draw->button("Clone", [] {
				g_player_mgr.m_buttons.clone(get_context(g_selected_player));
				});
			inline_item
			draw->button("Blame", [] {
				g_player_mgr.m_buttons.blame(get_context(g_selected_player));
			});
		});
		draw->submenu_second("Vehicle", "selected_vehicle", [] {
			draw->toggle("Slippy Tires", &g_player_mgr.m_players[g_selected_player].m_slipply_tires, [] {
				if (!g_player_mgr.m_players[g_selected_player].m_slipply_tires) {
					auto context{ get_context(g_selected_player) };

					g_utils->request_control(context.m_vehicle, [=] {
						VEHICLE::SET_VEHICLE_REDUCE_GRIP(context.m_vehicle, false);
					});
				}
			});
			inline_item
			draw->toggle("Freeze", &g_player_mgr.m_players[g_selected_player].m_freeze_vehicle, [] {
				if (!g_player_mgr.m_players[g_selected_player].m_freeze_vehicle) {
					auto context{ get_context(g_selected_player) };

					g_utils->request_control(context.m_vehicle, [=] {
						ENTITY::FREEZE_ENTITY_POSITION(context.m_vehicle, false);
					});
				}
			});
			draw->button("Boost", [] {
				g_player_mgr.m_buttons.boost(get_context(g_selected_player));
			});
			inline_item
			draw->button("Launch", [] {
				auto context{ get_context(g_selected_player) };

				g_utils->request_control(context.m_vehicle, [=] {
					ENTITY::APPLY_FORCE_TO_ENTITY(context.m_vehicle, 1, 0, 0, 300, 0, 0, 0, 1, false, true, true, true, true);
				});
			});
			inline_item
			draw->button("Kill Engine", [] {
				g_player_mgr.m_buttons.kill_engine(get_context(g_selected_player));
			});
			draw->button("Upgrade", [] {
				auto context{ get_context(g_selected_player) };

				g_utils->request_control(context.m_vehicle, [=] {
					g_utils->max_vehicle(context.m_vehicle);
				});
			});
			inline_item
			draw->button("Downgrade", [] {
				auto context{ get_context(g_selected_player) };

				g_utils->request_control(context.m_vehicle, [=] {
					g_utils->downgrade_vehicle(context.m_vehicle);
				});
			});
			inline_item
			draw->button("Repair", [] {
				auto context{ get_context(g_selected_player) };

				g_utils->request_control(context.m_vehicle, [=] {
					VEHICLE::SET_VEHICLE_FIXED(context.m_vehicle);
					VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(context.m_vehicle);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(context.m_vehicle, 0);
				});
			});
			draw->button("Lock Doors", [] {
				auto context{ get_context(g_selected_player) };

				g_utils->request_control(context.m_vehicle, [=] {
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(context.m_vehicle, true);
				});
			});
			inline_item
			draw->button("Burst Tires", [] {
				auto context{ get_context(g_selected_player) };

				g_utils->request_control(context.m_vehicle, [=] {
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(context.m_vehicle, true);
					for (int i = 5; i--;)
						VEHICLE::SET_VEHICLE_TYRE_BURST(context.m_vehicle, i, true, 1000.f);
				});
			});
			inline_item
			draw->button("Stop", [] {
				auto context{ get_context(g_selected_player) };

				g_utils->request_control(context.m_vehicle, [=] {
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(context.m_vehicle, 0);
				});
			});
		});
		draw->submenu_second("Removals", "selected_removals", [] {
			draw->button("Task Crash", [] { g_player_mgr.m_buttons.task_crash(get_context(g_selected_player)); });
			inline_item
			draw->button("Spam Kick", [] {
				static std::vector<int64_t> broken_events {
					{ (int64_t)eScriptEvents::GeneralEventKickIdlePlayers },
					{ (int64_t)eScriptEvents::TickerEventLeaveLoc },
					{ (int64_t)eScriptEvents::ScriptEventBailMeForSctv },
				};
				for (auto se : broken_events) {
					int64_t event[4] = { se, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				}

				for (int i = 0; i < 5; i++) {
					int64_t event[4] = { (int64_t)eRemoteEvent::MCTeleport, PLAYER::PLAYER_ID(), 0, 0 };
					g_pointers->m_trigger_script_event(1, event, 4, 1 << g_selected_player);
				}
			});
			inline_item
			draw->button("Basic Kick", [] {
				g_fiber_pool.queue([] {
					if (force_host(rage::joaat("freemode"))) {
						*script_global(1885447).at(g_selected_player, 1).as<bool*>() = true;
					}
					else {
						g_notifications->send("Basic Kick", std::format("Failed kicking {}.", g_pointers->m_get_player_name(g_selected_player)));
					}
				});
			});
		});
		draw->submenu_second("Bodyguards", "selected_bodyguards", [] {
			static bodyguard_manager mgr;
			mgr.m_owner = g_selected_player;
			draw->toggle("Godmode", &mgr.m_godmode);
			draw->choose("Model", model_changer_table, &mgr.m_selected_hash);
			draw->choose("Weapon", all_weapons_name, &mgr.m_weapon);
			draw->number("Accuracy", &mgr.m_accuracy, { 0, 100, 1, 0 });
			draw->button("Spawn", [=] {
				mgr.spawn();
			});
		});
		draw->submenu_second("Misc", "selected_misc", [] {
			draw->button("Set Waypoint", [] {
				auto context{ get_context(g_selected_player) };
				HUD::SET_NEW_WAYPOINT(g_utils->coords(context.m_ped).x, g_utils->coords(context.m_ped).y);
			});
		});
		draw->submenu_second("Teleport", "selected_teleport", [] {
			draw->button("To Player", [] {
				auto c{ g_utils->coords(PLAYER::GET_PLAYER_PED(g_selected_player)) };
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_utils->self(), c.x, c.y, c.z, true, true, true);
			});
			draw->button("Into Vehicle", [] {
				auto context{ get_context(g_selected_player) };
				PED::SET_PED_INTO_VEHICLE(g_utils->self(), context.m_vehicle, g_utils->get_open_seat(context.m_vehicle));
			});
			draw->button("Their Vehicle To Me", [] {
				auto context{ get_context(g_selected_player) };

				g_utils->request_control(context.m_vehicle, [=] {
					ENTITY::SET_ENTITY_COORDS(context.m_vehicle, g_utils->coords().x, g_utils->coords().y, g_utils->coords().z, 0, true, true, true);
				});
			});
			
		});
		draw->toggle("Spectate", &g_player_mgr.m_players[g_selected_player].m_spectate, [] {
			if (!g_player_mgr.m_players[g_selected_player].m_spectate) {
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, -1);
				HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);
				ENTITY::FREEZE_ENTITY_POSITION(g_utils->self(), false);
				ENTITY::FREEZE_ENTITY_POSITION(g_utils->vehicle(), false);
				STREAMING::SET_FOCUS_ENTITY(g_utils->self());
			}
		});
	}
	void all_options() {
		static int count{ g_utils->get_network_player_mgr()->m_player_count };
		draw->submenu_second("Trolling", "all_trolling", [] {
			draw->submenu_second("Ram", "ram_player", [] {
				for (auto& i : vehicle_classes) {
					draw_class_network(i, 5, true);
				}
			});
			draw->toggle("Taze", "Tazes the player.", &g_player_mgr.m_players[g_selected_player].m_taze);
			draw->toggle("Explode", "Explodes the player.", &g_player_mgr.m_players[g_selected_player].m_explode);
			draw->toggle("Hostile Vehicles", "Makes all the vehicles go towards you.", &g_player_mgr.m_players[g_selected_player].m_hostile_vehicles);
			draw->toggle("Rain Rockets", "Rains rockets on the player.", &g_player_mgr.m_players[g_selected_player].m_rain_rockets);
			draw->choose("Cage", cage_types, &cage_type, false, [] {
				for (int i = 0; i < count; i++) {
					g_player_mgr.m_buttons.cage(get_context(i), cage_type);
				}
			});
			draw->button("Kick From Vehicle", [] {
				for (int i = 0; i < count; i++) {
					g_player_mgr.m_buttons.kick_from_vehicle(get_context(i));
				}
			});
			draw->button("Clone", [] {
				for (int i = 0; i < count; i++) {
					g_player_mgr.m_buttons.clone(get_context(i));
				}
			});
		});
		draw->submenu_second("Vehicle", "all_vehicle", [] {
			draw->button("Boost", [] {
				for (int i = 0; i < count; i++) {
					g_player_mgr.m_buttons.boost(get_context(i));
				}
			});
			draw->button("Kill Engine", [] {
				for (int i = 0; i < count; i++) {
					g_player_mgr.m_buttons.kill_engine(get_context(i));

				}
			});
		});
		draw->submenu_second("Removals", "all_removals", [] {
			draw->button("Task Crash", [=] {
				for (int i = 0; i < count; i++) {
					g_player_mgr.m_buttons.task_crash(get_context(i));
				}
			});
		});
	}
	void main() {
		draw->submenu_second("All", "all_players", all_options);
		draw->seperator("Indiviual");
		if (*g_pointers->m_is_session_started) {
			for (auto& plr : get_players()) {
				str name{ plr->get_name() };
				if (plr->is_host())
					name.append(" [H]");

				if (plr->m_is_cheater)
					name.append(" [C]");

				if (plr->m_is_rockstar_dev)
					name.append(" [R* DEV]");

				if (plr->m_player_id == (*g_pointers->m_network_player_mgr)->m_local_net_player->m_player_id)
					name.append(" [ME]");

				draw->submenu_second(name, "network_players_selected", [=] {
					g_selected_player = plr->m_player_id;
				}, options);
			}
		}
		else {
			draw->submenu_second(g_utils->cped()->m_player_info->m_net_player_data.m_name, "network_players_selected", [=] {
				g_selected_player = PLAYER::PLAYER_ID();
			}, options);
		}
	}
}
