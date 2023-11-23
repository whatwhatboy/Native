#pragma once
#include "src/framework/command_box/command_box.h"

namespace Base::command_box {
	bool engine::is_valid_search(base_option* feature, ccp word) {
		return { (util::has_string_attached(feature->m_name, word) || util::has_string_attached(feature->m_description, word) || util::has_string_attached(feature->m_id, word)) };
	}
	bool engine::is_feature_and_search_valid(base_option* feature, ccp word) {
		return g_feature_manager.does_exist(feature->get_id()) && is_valid_search(feature, word) && get_closet_match(g_interface->m_command_box_input, true) == feature->m_id && m_this_id == feature->m_id;
	}
	str engine::get_toggle_status(bool tog) {
		return tog ? "off" : "on";
	}

	str engine::get_closet_match(ccp keyword, bool id) {
		for (auto& commands : g_feature_manager.m_commands) {
			auto feature{ commands.second };
			auto valid_search{ is_valid_search(feature, keyword) };
			if (g_feature_manager.does_exist(feature) && valid_search) {
				m_this_id = feature->m_id;
				return id ? feature->m_id : std::format("{} - {} | {}", feature->m_id, feature->m_name, util::get_description(feature->m_description));
			}
		}
		return "No results found.";
	}
}