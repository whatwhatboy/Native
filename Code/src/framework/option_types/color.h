#pragma once
#include "base.h"
#include <src/framework/framework.h>

namespace Base::Framework {
	class color_picker : public base_option<color_picker> {
	public:
		color_picker() = default;
		color_picker(str text, str description, int* r, int* g, int* b, std::function<void()> action = [] {}) :
			r(r),
			g(g),
			b(b)
		{
			set_left_text(text);
			if (description != "")
				set_description(description);
			set_action(std::move(action));
			set_color({ (uint8_t)r, (uint8_t)g, (uint8_t)b });
		}
	public:
		bool get_flag(option_flag flag) override {
			if (g_interface->m_color_picker_open) {
				if (ImGui::Begin("##yuh", nullptr)) {
					static float color[3] = { static_cast<float>(*r) / 255.0f, static_cast<float>(*g) / 255.0f, static_cast<float>(*b) / 255.0f };
					if (ImGui::ColorPicker3("", color)) {
						*r = static_cast<int>(color[0] * 255.0f);
						*g = static_cast<int>(color[1] * 255.0f);
						*b = static_cast<int>(color[2] * 255.0f);
					}
					ImGui::End();
				}
			}
			set_color({ (uint8_t)r, (uint8_t)g, (uint8_t)b });
			if (flag == option_flag::ColorPicker)
				return true;
			return Base::get_flag(flag);
		}

		void handle_action(option_action action) override {
			if (action == option_action::EnterPress) {
				g_interface->m_color_picker_open = !g_interface->m_color_picker_open;
			}
			Base::handle_action(action);
		}
	private:
		int* r;
		int* g;
		int* b;
	private:
		std::string* buffer;
		int max;
		using Base = base_option<color_picker>;
	};
}