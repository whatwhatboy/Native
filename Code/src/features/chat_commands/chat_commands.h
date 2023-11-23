#include <src/core/logger/logger.h>
#include "types.h"
#include "src/features/utils/utils.h"

namespace Base {
	class command_functions {
	public:
		void spawn(command cmd);
		void kill(command cmd);
		void give_weapons(command cmd);
		void give_weapon(command cmd);
		void remove_weapons(command cmd);
		void repair(command cmd);
		void kms(command cmd);
		void help(command cmd);
		void set_prefix(command cmd);
		void upgrade(command cmd);
	} inline g_command_functions;

	class chat_command_toggles {
	public:
		bool m_enabled{ true };
	public:
		command_toggle m_spawn;
		command_toggle m_kill;
		command_toggle m_give_weapons;
		command_toggle m_remove_weapons;
		command_toggle m_give_weapon;
		command_toggle m_repair;
		command_toggle m_kms;
		command_toggle m_help;
		command_toggle m_set_prefix;
		command_toggle m_upgrade;
	} inline m_chat_command_toggles;

	class chat_commands {
	private:
		bool contains_string(const str& mainString, const str& substring) {
			return mainString.find(substring) != str::npos;
		}
	public:
		str m_prefix{ "/"};
		std::vector<chat_command> m_commands;
		void add_commands();
	public:
		std::vector<str> get_args(const str& full_command) {
			std::vector<str> args;
			size_t start_pos{ full_command.find(" ") };
			if (start_pos != str::npos) {
				size_t end_pos{ start_pos };
				for (;;) {
					end_pos = full_command.find(" ", end_pos + 1);
					str arg{ full_command.substr(start_pos + 1, end_pos - start_pos - 1) };
					args.push_back(arg);
					if (end_pos == str::npos) {
						break;
					}
					start_pos = end_pos;
				}
			}
			return args;
		}
		chat_command get_type(str command) {
			for (auto name : m_commands) {
				if (contains_string(command, name.m_command)) return name;
			}
			return { "null", "null", "null", { 0 } };
		}
		bool check_args_for_string(std::vector<str> args, str check) {
			for (auto arg : args) {
				if (arg == check) return true;
			}
		}
		bool is_command(str command) {
			return get_type(command).m_name != "null";
		}
	public:
		void execute(Player plr, str cmd_name) {
			g_fiber_pool.queue([=] {
				chat_command cmd{ get_type(cmd_name) };
				command function{ plr, get_args(cmd_name) };

				if (!m_chat_command_toggles.m_enabled) return;
				if (cmd.m_command == m_prefix + "spawn" && m_chat_command_toggles.m_spawn.m_enabled) {
					g_command_functions.spawn(function);
				}
				else if (cmd.m_command == m_prefix + "kill" && m_chat_command_toggles.m_kill.m_enabled) {
					g_command_functions.kill(function);
				}
				else if (cmd.m_command == m_prefix + "give_weapons" && m_chat_command_toggles.m_give_weapons.m_enabled) {
					g_command_functions.give_weapons(function);
				}
				else if (cmd.m_command == m_prefix + "give_weapon" && m_chat_command_toggles.m_give_weapon.m_enabled) {
					g_command_functions.give_weapon(function);
				}
				else if (cmd.m_command == m_prefix + "remove_weapons" && m_chat_command_toggles.m_remove_weapons.m_enabled) {
					g_command_functions.remove_weapons(function);
				}
				else if (cmd.m_command == m_prefix + "repair" && m_chat_command_toggles.m_repair.m_enabled) {
					g_command_functions.repair(function);
				}
				else if (cmd.m_command == m_prefix + "kms" && m_chat_command_toggles.m_kms.m_enabled) {
					g_command_functions.kms(function);
				}
				else if (cmd.m_command == m_prefix + "help" && m_chat_command_toggles.m_help.m_enabled) {
					g_command_functions.help(function);
				}
				else if (cmd.m_command == m_prefix + "set_prefix" && m_chat_command_toggles.m_set_prefix.m_enabled) {
					g_command_functions.set_prefix(function);
				}
				else if (cmd.m_command == m_prefix + "upgrade" && m_chat_command_toggles.m_upgrade.m_enabled) {
					g_command_functions.upgrade(function);
				}
			});
		}
	};
	inline chat_commands g_chat_commands;
	inline void add_chat_commands() {
		g_chat_commands.add_commands();
	}
}