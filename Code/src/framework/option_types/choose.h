#pragma once
#include "base.h"
#include "../framework.h"

namespace Base::Framework {
	class choose : public base_option<choose> {
	public:
		choose() = default;
		choose(str text, str description, std::vector<const char*> vec, int* position, bool action_on_horizontal = false, std::function<void()> action = [] {}) :
			m_data(vec), m_data_size(vec.size()), m_position(position), m_action_on_horizontal(action_on_horizontal) {
			Base::set_left_text(text);
			if (description != "")
				Base::set_description(description);
			Base::set_action(std::move(action));
		}
		choose(str text, std::vector<const char*> vec, int* position, bool action_on_horizontal = false, std::function<void()> action = [] {}) :
			m_data(vec), m_data_size(vec.size()), m_position(position), m_action_on_horizontal(action_on_horizontal) {
			Base::set_left_text(text);
			Base::set_action(std::move(action));
		}
	public:
		str get_right_text() override {
			str buf{};
			if (!m_data.empty()) {
				if (g_interface->m_chooses.m_show_count) {
					switch (g_interface->m_chooses.m_anchor_selected) {
					case 0:
						buf = std::format("[{}/{}] {}", std::to_string(*m_position + 1), std::to_string(m_data_size), m_data[*m_position]);
						break;
					case 1:
						buf = std::format("{} [{}/{}]", m_data[*m_position], std::to_string(*m_position + 1), std::to_string(m_data_size));
						break;
					}
				}
				else {
					buf = m_data[*m_position];
				}
			}
			else
				buf = "No Data [0/0]";
			Base::m_right_text = buf;
			return Base::get_right_text();
		}
		bool get_flag(option_flag flag) override {
			if (flag == option_flag::Horizontal)
				return true;
			return Base::get_flag(flag);
		}
		void handle_action(option_action action) override {
			if (action == option_action::LeftPress) {
				if (!m_data.empty()) {
					if (*m_position > 0)
						--(*m_position);
					else
						*m_position = static_cast<int>(m_data_size - 1);
					if (m_action_on_horizontal && Base::m_Action)
						std::invoke(Base::m_Action);
				}
			}
			else if (action == option_action::RightPress) {
				if (!m_data.empty()) {
					if (*m_position < m_data_size - 1)
						++(*m_position);
					else
						*m_position = 0;
					if (m_action_on_horizontal && Base::m_Action)
						std::invoke(Base::m_Action);
				}
			}
			else if (action == option_action::EnterPress) {
				if (m_action_on_horizontal) {
					g_interface->m_choose_name = m_name;
					g_interface->m_choose_vector = m_data;
					g_interface->m_choose_selected = m_position;
					g_interface->switch_to_submenu("choose_menu"_joaat);
				}
			}
			if (!m_data.empty()) Base::handle_action(action);
		}
	public:
		str m_name{};
	private:
		std::vector<const char*> m_data{};
		int m_data_size{};
		int* m_position{};
		bool m_action_on_horizontal{};
	private:
		using Base = base_option<choose>;
	};
}