#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/option_types/keyboard.h>
#include <src/framework/option_types/button.h>
namespace Base::submenus::vehicle {
	void draw_class222(const char* name) {
		draw->submenu_second(name, name + std::to_string(1), [=] {
			for (auto& veh : vehicle_hash_list) {
				if (strcmp(veh.m_class, name) == 0) {
					add_option<Framework::button>(g_feature_manager.get_command<button_option>(std::to_string(veh.hash).c_str())->m_name, "", [=] {
						auto index{ AUDIO::GET_PLAYER_RADIO_STATION_INDEX() };
						AUDIO::FORCE_USE_AUDIO_GAME_OBJECT(g_utils->vehicle(), VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(veh.hash));
						AUDIO::SET_RADIO_TO_STATION_INDEX(index);
					});
				}
			}
		});
	}
	void engine_sound() {
		draw->submenu_second("Search", "vehicle:audio:engine_sound:search", [] {
			static std::string search;
			add_option<Framework::keyboard>("Input", "", &search, 9999, [] {});
			draw->seperator("Results");
			if (search == "") return;
			for (auto& veh : vehicle_hash_list) {
				if (g_utils->has_string_attached(veh.name, search)) {
					add_option<Framework::button>(g_feature_manager.get_command<button_option>(std::to_string(veh.hash).c_str())->m_name, "", [=] {
						auto index{ AUDIO::GET_PLAYER_RADIO_STATION_INDEX() };
						AUDIO::FORCE_USE_AUDIO_GAME_OBJECT(g_utils->vehicle(), VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(veh.hash));
						AUDIO::SET_RADIO_TO_STATION_INDEX(index);
					});
				}
			}
		});
		draw->seperator("Categories");
		for (auto& i : vehicle_classes) {
			draw_class222(i.c_str());
		}

	}
}
