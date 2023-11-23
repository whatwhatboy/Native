#include "hotkeys.h"

namespace Base {
	void hotkey_manager::add(hotkey h) {
		for (auto& h : m_hotkeys) {
			if (h.second->m_id == h.second->m_id) return;
		}

		m_hotkeys.insert({ h.m_id, &h });
	}
	void hotkey_manager::remove(str id) {
		if (auto it{ m_hotkeys.find(id) }; it != m_hotkeys.end()) {
			delete it->second;
			m_hotkeys.erase(it);
		}
	}

	int hotkey_manager::get_keycode_from_letter(str letter) {
		if (letter == "z") return 0x5A;

		return 0x5A;
	}
	void hotkey_manager::tick() {
		for (auto& f : g_feature_manager.m_commands) {
			for (auto h : m_hotkeys) {
				if (GetAsyncKeyState(0x5A) & 1) {
					if (h.second->m_keycode != 0) {
						auto t{ (toggle_option*)f.second };
						if (t) {
							if (f.first == h.first) {
								*t->m_toggle = true;
							}
						}
					}
					else {
						LOG(Info, "Returned false at keycode.");
					}
				}
			}
		}
		
	}
}