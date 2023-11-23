#pragma once
#include "base.h"
#include <src/framework/framework.h>

namespace Base::Framework {
	inline bool keyboard_open{ false };
	inline static char keyboard_text_buffer[256] = "";
	inline int keyboard_max_limit = 0;
	class keyboard : public base_option<keyboard> {
	public:
		keyboard() = default;
		keyboard(str text, str description, std::string* buf, int max_limit = 9999, std::function<void()> action = [] {}) :
			max(max_limit),
			buffer(buf)
		{
			set_left_text(text);
			if (description != "")
				set_description(description);
			set_action(std::move(action));
		}
	public:
		str get_right_text() override {
			keyboard_max_limit = max;
			Base::m_right_text = *buffer;
			return Base::get_right_text();
		}
		bool get_flag(option_flag flag) override {
			if (keyboard_open)
				*buffer = keyboard_text_buffer;
			if (flag == option_flag::Keyboard)
				return true;
			return Base::get_flag(flag);
		}

		void handle_action(option_action action) override {
			if (action == option_action::EnterPress) {
				if (strlen(keyboard_text_buffer) > 0 && keyboard_open) {
					if (Base::m_Action)
						std::invoke(Base::m_Action);
					keyboard_open = false;
					g_interface->m_disable_input = false;
					Base::handle_action(action);
					return;
				}
				if (!keyboard_open) {
					std::snprintf(keyboard_text_buffer, sizeof(keyboard_text_buffer), "", *buffer);
					g_interface->m_disable_input = true;
					keyboard_open = true;
				}

			}
			Base::handle_action(action);
		}
	private:
		std::string* buffer;
		int max;
		using Base = base_option<keyboard>;
	};
}