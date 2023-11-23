#include "chat_commands.h"
#include "src/features/utils/utils.h"
#include "src/features/hotkeys/hotkeys.h"
#include "src/framework/notifications/notifications.h"
#include "src/core/script/player_manager/player_manager.h"
namespace Base {
	enum class model_type {
		invalid,
		vehicle,
		ped,
		object
	};
	model_type get_hash_type(Hash hash) {
		if (STREAMING::IS_MODEL_VALID(hash)) {
			if (STREAMING::IS_MODEL_A_VEHICLE(hash)) return model_type::vehicle;
			else if (STREAMING::IS_MODEL_A_PED(hash)) return model_type::ped;
		}
		return model_type::invalid;
	}
	CNetworkPlayerMgr* chat_network_mgr() {
		return *g_pointers->m_network_player_mgr;
	}

	void chat_commands::add_commands() {
		m_commands.clear();
		m_commands.push_back({ "Spawn", m_prefix + "spawn [vehicle]\n-upgraded\n-color (red, blue)", m_prefix + "spawn", &m_chat_command_toggles.m_spawn });
		m_commands.push_back({ "Kill", m_prefix + "kill [player]", m_prefix + "kill", &m_chat_command_toggles.m_kill });
		m_commands.push_back({ "Give Weapons", m_prefix + "give_weapons [player]", m_prefix + "give_weapons", &m_chat_command_toggles.m_give_weapons });
		m_commands.push_back({ "Give Weapon", m_prefix + "give_weapon [player, weapon]", m_prefix + "give_weapon", &m_chat_command_toggles.m_give_weapon });
		m_commands.push_back({ "Set Prefix", "Adds a hotkey.\n/set_prefix", m_prefix + "set_prefix", &m_chat_command_toggles.m_set_prefix });
		m_commands.push_back({ "Repair", m_prefix + "repair", m_prefix + "repair", &m_chat_command_toggles.m_repair });
		m_commands.push_back({ "Suicide", m_prefix + "kms", m_prefix + "kms", &m_chat_command_toggles.m_kms });
		m_commands.push_back({ "Upgrade", m_prefix + "upgrade", m_prefix + "upgrade", &m_chat_command_toggles.m_upgrade });
		m_commands.push_back({ "Help", m_prefix + "help", m_prefix + "help", &m_chat_command_toggles.m_help });
	}

	void complete_vehicle_spawn(Vehicle vehicle, std::vector<str> args) {
		if (g_chat_commands.check_args_for_string(args, "upgraded")) {
			g_utils->max_vehicle(vehicle);
		}
		if (g_chat_commands.check_args_for_string(args, "fade")) {
			NETWORK::NETWORK_FADE_IN_ENTITY(vehicle, 1, 1);
		}
		for (auto color : g_colors_with_names) {
			if (g_chat_commands.check_args_for_string(args, color.m_name)) {
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, color.m_color.r, color.m_color.g, color.m_color.b);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, color.m_color.r, color.m_color.g, color.m_color.b);
			}
		}
	}
	void command_functions::spawn(command cmd) {
		auto hash{ rage::joaat(cmd.m_args[0]) };
		if (STREAMING::IS_MODEL_VALID(hash)) {
			switch (get_hash_type(hash)) {
				case model_type::vehicle: {
					auto ped{ PLAYER::GET_PLAYER_PED(cmd.m_plr) };
					g_utils->request(request_type::model, hash, [=] {
						auto heading{ ENTITY::GET_ENTITY_HEADING(ped) };
						auto pos{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0, 5, 0) };
						auto vehicle{ VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, heading, true, true, 0) };

						g_utils->make_networked(vehicle);
						complete_vehicle_spawn(vehicle, cmd.m_args);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						if (m_chat_command_toggles.m_spawn.m_notify) {
							g_notifications->send("Chat Commands", std::format("{} spawned a {}", g_pointers->m_get_player_name(cmd.m_plr), cmd.m_args[0]));
						}
					});
					break;
				}
				case model_type::ped: {
					auto ped{ PLAYER::GET_PLAYER_PED(cmd.m_plr) };
					auto heading{ ENTITY::GET_ENTITY_HEADING(ped) };
					auto pos{ g_utils->coords(ped) };
					g_utils->request_model(hash, [=] {
						auto spawned{ PED::CREATE_PED(hash, pos.x, pos.y, pos.z, heading, true, true, 0) };
					});
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
					break;
				}
			}
			
		}
	}


	void command_functions::kill(command cmd) {
		auto ped{ PLAYER::GET_PLAYER_PED(cmd.m_plr) };
		if (cmd.m_args[0] == "") return;
		for (auto player : chat_network_mgr()->m_player_list) {
			if (player && player->is_valid()) {
				if (player->get_name() == cmd.m_args[0]) {
					const auto target{ PLAYER::GET_PLAYER_PED(player->m_player_id) };
					const auto invisible{ g_chat_commands.check_args_for_string(cmd.m_args, "invis") };
					const auto no_sound{ g_chat_commands.check_args_for_string(cmd.m_args, "nosound") };
					auto c{ g_utils->coords(target) };
					FIRE::ADD_EXPLOSION(c.x, c.y, c.z, eExplosionTag::GRENADE, 9999, !no_sound, invisible, 0, 0);
					if (m_chat_command_toggles.m_kill.m_notify) {
						g_notifications->send("Chat Commands", std::format("{} killed {}", g_pointers->m_get_player_name(cmd.m_plr), player->get_name()));
					}
				}
			}
		}
	}

	void command_functions::give_weapons(command cmd) {
		auto ped{ PLAYER::GET_PLAYER_PED(cmd.m_plr) };
		const auto self{ cmd.m_args[0].empty() };
		if (self) {
			for (int i = 0; i < sizeof(all_weapons_hash); i++)
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, all_weapons_hash[i], 9999, false);
		}
		for (auto player : chat_network_mgr()->m_player_list) {
			if (player && player->is_valid()) {
				if (player->get_name() == cmd.m_args[0]) {
					auto target{ PLAYER::GET_PLAYER_PED(player->m_player_id) };
					for (int i = 0; i < sizeof(all_weapons_hash); i++)
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(target, all_weapons_hash[i], 9999, false);
				}
			}
		}
	}
	void command_functions::give_weapon(command cmd) {
		auto ped{ PLAYER::GET_PLAYER_PED(cmd.m_plr) };
		const auto self{ cmd.m_args[0].empty() };
		if (self) {
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, rage::joaat(cmd.m_args[1]), 9999, false);
			return;
		}
		for (auto player : chat_network_mgr()->m_player_list) {
			if (player && player->is_valid()) {
				if (player->get_name() == cmd.m_args[0]) {
					auto target{ PLAYER::GET_PLAYER_PED(player->m_player_id) };
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(target, rage::joaat(cmd.m_args[1]), 9999, false);
				}
			}
		}
	}

	void command_functions::remove_weapons(command cmd) {
		auto ped{ PLAYER::GET_PLAYER_PED(cmd.m_plr) };
		const auto self{ cmd.m_args[0].empty() };
		if (self) {
			for (int i = 0; i < sizeof(all_weapons_hash); i++)
				WEAPON::REMOVE_WEAPON_FROM_PED(ped, all_weapons_hash[i]);
			return;
		}

		for (auto player : chat_network_mgr()->m_player_list) {
			if (player && player->is_valid()) {
				if (player->get_name() == cmd.m_args[0]) {
					auto target{ PLAYER::GET_PLAYER_PED(player->m_player_id) };
					for (int i = 0; i < sizeof(all_weapons_hash); i++)
						WEAPON::REMOVE_WEAPON_FROM_PED(target, all_weapons_hash[i]);
				}
			}
		}
	}

	void command_functions::repair(command cmd) {
		auto ped{ PLAYER::GET_PLAYER_PED(cmd.m_plr) };
		auto vehicle{ g_utils->vehicle(cmd.m_plr) };
		g_utils->request_control(vehicle, [vehicle] {
			VEHICLE::SET_VEHICLE_FIXED(vehicle);
			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle);
		});
	}

	void command_functions::kms(command cmd) {
		auto ped{ PLAYER::GET_PLAYER_PED(cmd.m_plr) };
		auto c{ g_utils->coords(ped) };
		FIRE::ADD_EXPLOSION(c.x, c.y, c.z, eExplosionTag::GRENADE, 9999, false, true, 0, 0);
	}

	void command_functions::help(command cmd) {
		str message;
		for (auto& cmdd : g_chat_commands.m_commands) {
			message.append(cmdd.m_description + "\n");
		}
		g_utils->send_chat_msg(message);
	}

	void command_functions::set_prefix(command cmd) {
		if (cmd.m_plr == PLAYER::PLAYER_ID()) {
			g_chat_commands.m_prefix = cmd.m_args[0];
			g_chat_commands.add_commands();
		}
	}

	void command_functions::upgrade(command cmd) {
		g_player_mgr.m_buttons.upgrade(get_context(cmd.m_plr));
	}
}