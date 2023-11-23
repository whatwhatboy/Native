#pragma once
#include "base.h"
#include "src/framework/framework.h"
#include "src/fiber/fiber_helper.h"

namespace Base::Framework {
	class submenu : public base_option<submenu> {
	public:
		submenu() = default;
		submenu(str text, str description, std::uint32_t subId, std::function<void()> action = [] {}, const char* path = "") : m_SubId(subId) {
			if (path != "")
				set_left_text(path);
			else
				set_left_text(text);
			if (description != "")
				set_description(description);
			set_action(std::move(action));
		}
	public:
		void handle_action(option_action action) override {
			switch (action) {
			case option_action::EnterPress:
				g_interface->switch_to_submenu(m_SubId);
				break;
			}
			base_option::handle_action(action);
		}
		bool get_flag(option_flag flag) override {
			switch (flag) {
			case option_flag::Enterable:
				return true;
				break;
			}
			return base_option::get_flag(flag);
		}
	private:
		std::uint32_t m_SubId{};
	};
}
