#pragma once
#include "src/features/hotkeys/hotkeys.h"
#include "misc/util.h"

namespace Base::command_box {
	class engine {
	public:
		str get_closet_match(ccp keyword, bool id = false);
		str get_toggle_status(bool tog);
	public:
		bool is_valid_search(base_option* feature, ccp word);
		bool is_feature_and_search_valid(base_option* feature, ccp word);
	public:
		class processors {
		public:
			void toggle_with_choose_cmd(const str& keyword, const str& inputValue);
			void choose_cmd(const str& keyword, const str& inputValue);
			void float_cmd(const str& keyword, const str& inputValue);
			void toggle_with_float_cmd(const str& keyword, const str& inputValue);
		} m_processors;
	public:
		str m_this_id{};
	} inline g_engine{};

	inline bool found2{ false };
	inline bool inputFocused = true;
	inline void reset() {
		std::strcpy(g_interface->m_command_box_input, "");
		g_interface->m_command_box_opened = false;
	}
	
	inline void init() {
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5);
		ImGui::SetKeyboardFocusHere();

		ImGui::InputText("Input", g_interface->m_command_box_input, sizeof(g_interface->m_command_box_input), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCharFilter, [](ImGuiInputTextCallbackData* data) -> int {
				if (data->EventChar == '\r') return 1;
				return 0;
		});
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5);

		if (g_interface->m_command_box_input[0] != '\0') {
			ImGui::PushFont(g_renderer->m_ArialSmall);
			ImGui::Text(g_engine.get_closet_match(g_interface->m_command_box_input).c_str());
			ImGui::PopFont();
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 1 && util::is_focused_on_gta()) {
			reset();
		}
		if (GetAsyncKeyState(VK_RETURN) & 1 && util::is_focused_on_gta()) {	
			g_fiber_pool.queue([=] {
				if (g_engine.get_closet_match(g_interface->m_command_box_input) != "") {
					str keyword = g_interface->m_command_box_input;
					str keyword2 = g_interface->m_command_box_input;
					str inputValue = keyword2.substr(keyword2.find(' ') + 1);
					bool found_feature = false;
					keyword2 = keyword2.substr(0, keyword2.find(' '));

					for (auto& commands : g_feature_manager.m_commands) {
						if (auto feature{ (toggle_with_choose_option*)commands.second }) {
							if (feature && g_engine.is_feature_and_search_valid(feature, keyword.c_str()) && feature->is_type(eCommandType::toggle_with_choose)) {
								bool toggle_value{ *feature->m_toggle };
								*feature->m_toggle = !toggle_value;

								if (!*feature->m_toggle && feature->m_on_disable) {
									feature->m_on_disable();
								}

								found_feature = true;
								reset();
								break;
							}
						}
					}
					if (!found_feature) {
						for (auto& commands : g_feature_manager.m_commands) {
							if (auto feature{ (toggle_option*)commands.second }) {
								if (feature && g_engine.is_feature_and_search_valid(feature, keyword.c_str()) && feature->is_type(eCommandType::toggle)) {
									bool toggle_value{ *feature->m_toggle };
									*feature->m_toggle = !toggle_value;

									if (!*feature->m_toggle && feature->m_on_disable) {
										feature->m_on_disable();
									}

									found_feature = true;
									reset();
									break;
								}
							}
							else if (auto feature{ (button_option*)commands.second }) {
								if (feature && g_engine.is_feature_and_search_valid(feature, keyword.c_str()) && feature->is_type(eCommandType::button)) {
									if (feature->m_action) {
										feature->m_action();
									}

									found_feature = true;
									reset();
									break;
								}
							}
							else if (auto feature{ (toggle_with_float_option*)commands.second }) {
								if (feature && g_engine.is_feature_and_search_valid(feature, keyword.c_str()) && feature->is_type(eCommandType::toggle_with_number)) {
									bool toggle_value{ *feature->m_toggle };
									*feature->m_toggle = !toggle_value;

									if (!*feature->m_toggle) {
										if (feature->m_on_disable) {
											feature->m_on_disable();
										}
									}

									found_feature = true;
									reset();
									break;
								}
							}
						}
					}
					if (!found_feature) {
						g_engine.m_processors.float_cmd(keyword2, inputValue);
						g_engine.m_processors.choose_cmd(keyword2, inputValue);
						g_engine.m_processors.toggle_with_float_cmd(keyword2, inputValue);
						g_engine.m_processors.toggle_with_choose_cmd(keyword2, inputValue);
					}
					//found2 = false;
					reset();
				}
			});
		}
	}

}