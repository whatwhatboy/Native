#pragma once
#include "base.h"

namespace Base::Framework {
	class vehicle_button : public base_option<vehicle_button> {
	public:
		vehicle_button() = default;
		vehicle_button(str text, str arg, std::function<void()> action = [] {}) {
			set_left_text(text);
			set_arg(arg);
			set_action(std::move(action));
		}

		bool get_flag(option_flag flag) override {
			if (flag == option_flag::VehicleButton) return true;
			return base_option::get_flag(flag);
		}
	};
}