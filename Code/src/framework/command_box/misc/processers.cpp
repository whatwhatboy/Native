#pragma once
#include "src/framework/command_box/command_box.h"


namespace Base::command_box {
	void engine::processors::toggle_with_choose_cmd(const str& keyword, const str& inputValue) {
		str id{ g_engine.get_closet_match(keyword.c_str(), true) };

		for (auto& commands : g_feature_manager.m_commands) {
			auto feature{ (toggle_with_choose_option*)commands.second };
			if (commands.second->is_type(eCommandType::toggle_with_choose) && feature->m_id == id && g_feature_manager.does_exist(feature->get_id())) {
				for (auto& item : feature->m_items) {
					if (util::has_string_attached(item, inputValue)) {
						*feature->m_current_item = (int)item;
						if (!*feature->m_toggle) {
							bool toggleValue{ *feature->m_toggle };
							*feature->m_toggle = !toggleValue;
						}
						if (!*feature->m_toggle && feature->m_on_disable) {
							feature->m_on_disable();
						}
						found2 = true;
						reset();
						return;
					}
				}
				break;
			}
		}
		reset();
	}
	void engine::processors::choose_cmd(const str& keyword, const str& inputValue) {
		str id{ g_engine.get_closet_match(keyword.c_str(), true) };

		for (auto& commands : g_feature_manager.m_commands) {
			auto feature{ (choose_option*)commands.second };
			if (commands.second->is_type(eCommandType::choose) &&  feature->m_id == id && g_feature_manager.does_exist(feature)) {
				for (int i = 0; i < sizeof(feature->m_items) / sizeof(feature->m_items[0]); i++) {
					if (util::has_string_attached(feature->m_items[i], inputValue)) {
						*feature->m_current_item = i;
						feature->m_action();
						found2 = true;
						reset();
						return;
					}
				}
				break;
			}
		}
		reset();
	}
	void engine::processors::float_cmd(const str& keyword, const str& inputValue) {
		str id{ g_engine.get_closet_match(keyword.c_str(), true) };

		for (auto& commands : g_feature_manager.m_commands) {
			auto feature{ (float_option*)commands.second };
			if (commands.second->is_type(eCommandType::number) && feature && util::has_string_attached(feature->m_id, util::remove_underscores_and_spaces(id)) && g_feature_manager.does_exist(feature)) {
				float value;
				std::istringstream iss(inputValue);
				if (iss >> value) {
					value = std::clamp(value, feature->m_min, feature->m_max);
					*feature->m_val = value;
					feature->m_action();
					found2 = true;
					reset();
					return;
				}
			}
		}
		reset();
	}
	void engine::processors::toggle_with_float_cmd(const str& keyword, const str& inputValue) {
		str id{ g_engine.get_closet_match(keyword.c_str(), true) };

		for (auto& commands : g_feature_manager.m_commands) {
			auto feature{ (toggle_with_float_option*)commands.second };
			if (commands.second->is_type(eCommandType::toggle_with_number) && util::has_string_attached(feature->m_id, util::remove_underscores_and_spaces(id)) && g_feature_manager.does_exist(feature)) {
				float value;
				std::istringstream iss(inputValue);
				if (iss >> value) {
					value = std::clamp(value, feature->m_min, feature->m_max);
					*feature->m_val = value;

					if (!*feature->m_toggle) {
						bool toggle_value{ *feature->m_toggle };
						*feature->m_toggle = !toggle_value;
					}
					if (!*feature->m_toggle && feature->m_on_disable) {
						feature->m_on_disable();
					}
					found2 = true;
					reset();
					return;
				}
			}
		}
		reset();
	}
}