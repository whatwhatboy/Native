#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/keyboard.h"
namespace Base::submenus::weapon {
	struct rect {
		str m_name{};
		float m_x{};
		float m_y{};
		float m_width{};
		float m_height{};
		float m_rounding{};
		color<int> m_color{};
	};
	std::vector<rect> rects;
	void crosshair() {
		draw->submenu("Builder", "crosshair_builder", [] {
			static str add{};
			draw->keyboard("Add", add, [=] {
				if (GetAsyncKeyState(VK_RETURN) && !Framework::keyboard_open) {
					rects.push_back({ add, 0, 0, 0, 0, 0, {255, 255, 255, 255} });
					add = "";
				}
			});
			draw->seperator("List");
			for (auto rect : rects) {
				draw->submenu(rect.m_name, rect.m_name, [&] {
					draw->number("X", rect.m_x, { -10000, 10000, 0.01, 2 });
					draw->number("Y", rect.m_y, { -10000, 10000, 0.01, 2 });
					draw->number("Width", rect.m_width, { -10000, 10000, 0.01, 2 });
					draw->number("Height", rect.m_height, { -10000, 10000, 0.01, 2 });
					draw->number("Rounding", rect.m_rounding, { 0, 500, 1, 0 });
					draw->seperator("Color");
					draw->number("R", rect.m_color.r, { 0, 255, 1, 0 });
					draw->number("G", rect.m_color.g, { 0, 255, 1, 0 });
					draw->number("B", rect.m_color.b, { 0, 255, 1, 0 });
					draw->number("A", rect.m_color.a, { 0, 255, 1, 0 });
				});
			}
		});
	}
}