#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/keyboard.h"
#include "src/framework/option_types/button.h"
#include <src/framework/option_types/break.h>
#include <src/framework/option_types/submenu.h>
#include "src/features/utils/rid_utils.h"
#include <src/features/chat_commands/chat_commands.h>
#include <src/hooking/xor.h>

namespace Base::submenus::network::chat {
    using namespace Framework;
	int delay{ 250 };
	void sing_txt(str path) {
		g_fiber_pool.queue([=] {
			std::ifstream file(path);
			if (!file.is_open()) {
				g_notifications->send("Singing", "Failed to open file.");
				return;
			}

			std::string line;
			for (;;) {
				if (std::getline(file, line)) {
					if (!line.empty()) {
						g_utils->send_chat_msg(line);
						fiber::current()->wait(std::chrono::milliseconds(delay));
					}
				}
				else {
					break;
				}
			}

			file.close();
		});
	}
	std::vector<str> preset_messages = {
		"yessir",
		"ur bad",
		xorstr_("native best mod menu??"),
		"use the chat commands"
	};
	Vector2 old_pos;
    void main() {
		draw->submenu_second("Commands", "chat_commands", [] {
			draw->option("chat_commands_enabled");
			draw->seperator("Commands");
			for (auto& command : g_chat_commands.m_commands) {
				draw->submenu(command.m_name, command.m_name, command.m_description, [=] {
					draw->toggle("Enabled", command.m_description, command.m_toggle->m_enabled);
					draw->toggle("Notify", command.m_description, command.m_toggle->m_notify);
					draw->toggle("Log", command.m_description, command.m_toggle->m_log);
				});
			}
			static str from_menu;
			draw->keyboard("From Menu", from_menu, [] {
				if (GetAsyncKeyState(VK_RETURN) && !Framework::keyboard_open) {
					g_chat_commands.execute(PLAYER::PLAYER_ID(), from_menu);
				}
			});
		});
		draw->submenu_second("Spammer", "chat_spammer", [] {
			draw->option("chat_spammer");
			draw->option("chat_spammer_show");
			draw->keyboard("Message", g_hooking_features.m_chat.m_spammer_message);
			draw->seperator("Presets");
			for (auto preset : preset_messages) {
				if (g_hooking_features.m_chat.m_spammer_message == preset) {
					add_option<Framework::icon_button>(preset, "", "On", [=] {
						g_hooking_features.m_chat.m_spammer_message = preset;
						});
				}
				else {
					draw->button(preset, [=] {
						g_hooking_features.m_chat.m_spammer_message = preset;
					});
				}
			}
		});
		draw->submenu_second("Misc", "chat_misc", [] {
			draw->submenu_second("Singing", "chat_singing", [] {
				draw->number("Delay", delay, { 0, 5000, 1, 0 });
				draw->seperator("Files");
				for (auto file : g_file_utils->get_all_files_from_dict("C:\\Native\\Singing\\")) {
					draw->button(file.name_without_extension, [=] {
						sing_txt("C:\\Native\\Singing\\" + file.full_name);
					});
				}
			});
			draw->option("chat_profanity");
			draw->option("chat_mocking");
		});
		draw->submenu("Word Blacklist", "word_blacklist", [] {
			static str add{};
			draw->keyboard("Add", add, [=] {
				if (GetAsyncKeyState(VK_RETURN) && !Framework::keyboard_open) {
					g_word_blacklist.add({ add, { true, false, false } });
					add = "";
				}
			});
			draw->seperator("List");
			for (auto& word : g_word_blacklist.m_words) {
				draw->submenu_second(word.m_keyword, word.m_keyword, [&] {
					draw->toggle("Notify", &word.m_action.m_notify);
					draw->toggle("Kick", &word.m_action.m_kick);
					draw->toggle("Crash", &word.m_action.m_crash);
					draw->button("Delete", [=] {
						g_word_blacklist.remove(word.m_keyword);
						g_interface->submenu_stack.pop();
					});
				});
			}
		});
		draw->option("chat_log");
    }
}
