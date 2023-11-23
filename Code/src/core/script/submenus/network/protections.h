#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/button.h"
#include "src/framework/option_types/number.h"
#include <JSON/json.hpp>
namespace Base::submenus::network {
	using namespace Framework;
	void protections() {
		if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::protections) return;

		click_ui::setup_col("protections");
		draw->submenu("Crashes", "crashes_prots", [] {
			for (auto& se : g_protection_manager.m_crashes_vector) {
				draw->toggle(se.m_name, se.m_protection);
			}
		});
		draw->submenu("Kicks", "kick_prots", [] {
			draw->toggle("Desync", &g_protection_manager.m_desync_kicks);
			for (auto& se : g_protection_manager.m_kicks_vector) {
				draw->toggle(se.m_name, se.m_protection);
			}
		});
		click_ui::next_col();
		draw->submenu("Script Events", "se_events", [] {
			for (auto& se : g_protection_manager.m_protections) {
				draw->submenu_second(se.m_name, se.m_name, [=] {
					draw->toggle("Block", &se.m_protection->m_block);
					draw->toggle("Notify", &se.m_protection->m_notify);
					draw->toggle("Log", &se.m_protection->m_log);
					draw->toggle("Allow From Friends", &se.m_protection->m_allow_from_friends);
				});
			}
		});
		draw->submenu("Reactions", "protection_reactions", [] {
			for (auto& reaction : g_protection_manager.m_reaction) {
				draw->submenu_second(reaction.m_name, reaction.m_name, [=] {
					draw->toggle("Kick", &reaction.m_reaction->m_kick);
				});
			}
		});
		draw->submenu("Misc", "misc_prots", [] {
			draw->toggle("Pickups", &g_protection_manager.m_block_pickups);
			draw->toggle("Kick Chat Spammers", &g_protection_manager.m_kick_chat_spammers);
		});
		click_ui::end_col();
	}
}
