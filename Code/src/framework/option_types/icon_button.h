#pragma once
#include "base.h"

namespace Base::Framework {
	class icon_button : public base_option<icon_button> {
	public:
		icon_button() = default;
		icon_button(str text, str description = "", str texture = "", std::function<void()> action = [] {}) {
			set_left_text(text);
			if (description != "")
				set_description(description);
			set_action(std::move(action));
			set_texture(texture);
		}

		bool get_flag(option_flag flag) override {
			if (flag == option_flag::On)
				return true;
			return base_option::get_flag(flag);
		}
	};
}