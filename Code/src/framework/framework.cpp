#include "Framework.h"
#include "src/Utility/Timer.h"
#include "src/Natives/Natives.h"
#include "src/fiber/fiber_helper.h"
#include "src/framework/direct_x/renderer.h"
#include <src/rage/draw_handlers/pgDictionary.hpp>
#include <src/rage/draw_handlers/grcTexture.hpp>
#include "src/Utility/Setting.h"
#include "src/Utility/Timer.h"
#include "option_types/keyboard.h"
#include "option_types/number.h"
#include <src/features/utils/utils.h>
#include "notifications/notifications.h"

namespace Base::Framework {
	void Interface::draw_tooltips() {
		if (m_command_box_opened) return;

		if (m_tooltip.empty()) {
			m_tooltip = m_tooltips.empty() ? ("No Tooltips Certified L") : m_tooltips[rng(NULL, m_tooltips.size() - 1).get<size_t>()];
		}
		auto open_key_text = std::string(m_using_keyboard ? "F4 + Get A Controller" : "RB + Get A KB And Mouse");
		draw_centered_text(m_tooltip, 0.5f, 0.06f, m_tooltip_text_size, m_tooltip_font, m_tooltip_color, false, true);
		draw_centered_text(open_key_text, 0.5f, 0.09f, m_open_key_text_size, m_open_key_text_font, m_open_key_text_color, false, true);
	}
	void Interface::draw_header() {
		float mouse_pos_x{ (1.f / ImGui::GetIO().DisplaySize.x) * get_mouse_pos().x };
		float mouse_pos_y{ (1.f / ImGui::GetIO().DisplaySize.y) * get_mouse_pos().y };
		auto rect{ get_rect_bounds(m_lerped_pos_x, m_draw_base_y, m_header_height, m_width) };
		if (mouse_pos_x > rect.m_left && mouse_pos_x < rect.m_right && mouse_pos_y > rect.m_top && mouse_pos_y < rect.m_bottom && g_settings.lock_mouse) {
			if (GetAsyncKeyState(VK_LBUTTON)) {
				m_pos_x = mouse_pos_x;
				m_pos_y = mouse_pos_y - (m_header_height / 2.f);
			}
		}
		if (m_has_header_loaded) {
			flip_through_frames(g_renderer->m_header[g_renderer->header_frame].m_frame_delay);
			draw_sprite_round(g_renderer->m_header[g_renderer->header_frame].m_shader.m_resource_view, m_lerped_pos_x, m_draw_base_y + (m_header_height / 2.f), m_width, m_header_height, m_header_image_color, ImGui::GetBackgroundDrawList(), m_rounding.m_header, ImDrawFlags_RoundCornersTop);
		}
		else {
			draw_rect(m_lerped_pos_x, m_draw_base_y + (m_header_height / 2.f), m_width, m_header_height, m_header_background_color, ImGui::GetBackgroundDrawList(), m_rounding.m_header, ImDrawFlags_RoundCornersTop);
			draw_centered_text(BRANDING, m_lerped_pos_x, m_draw_base_y + (m_header_height / 2.f) - (get_text_height(m_header_font, m_header_text_size, m_width) / 2.f), m_header_text_size, m_header_font, m_header_text_color, false, true, m_width, m_header.m_uses_gradiant);
		}
		m_draw_base_y += m_header_height;
	}
	void Interface::draw_submenu_bar(abstract_submenu* sub) {
		str left_text{ sub->get_name() };
		str right_text{ std::format("{} / {}", sub->get_selected_option() + 1, sub->get_num_options()) };
		std::transform(left_text.begin(), left_text.end(), left_text.begin(), [](char c) { return static_cast<char>(toupper(c)); });

		draw_rect(m_lerped_pos_x, m_draw_base_y + (m_submenu_bar_height / 2.f), m_width, m_submenu_bar_height, m_submenu_bar_background_color);
		draw_left_text(left_text, m_lerped_pos_x - (m_width / m_submenu_bar_padding), m_draw_base_y + (m_submenu_bar_height / 2.f) - (get_text_height(m_submenu_bar_font, m_submenu_bar_text_size, m_width) / 2.f), m_submenu_bar_text_size, m_submenu_bar_font, m_submenu_bar_text_color, false, true);
		draw_right_text(right_text, m_lerped_pos_x + (m_width / m_submenu_bar_padding), m_draw_base_y + (m_submenu_bar_height / 2.f) - (get_text_height(m_submenu_bar_font, m_submenu_bar_text_size, m_width) / 2.f), m_submenu_bar_text_size, m_submenu_bar_font, m_submenu_bar_text_color, false, true);
		m_draw_base_y += m_submenu_bar_height;
	}
	void Interface::draw_scrollbar(abstract_submenu* sub) {
		float background_y{ m_lerped_pos_y + m_header_height / 2 + m_submenu_bar_height + m_bg_current / 2 };
		float slider_top{ background_y - m_bg_current / 2 };
		float slider_bottom{ background_y + m_bg_current / 2 };
		float slider_position{ ((float)sub->get_selected_option() / ((float)sub->get_num_options() - 1)) * (m_bg_current - m_option_height) + m_option_height / 2 };
		if (sub->get_num_options() < 2) {
			slider_position = m_bg_current - m_option_height + m_option_height / 2;
		}

		static float position{ slider_position };
		static float offset{ m_scrollbar.m_offset };

		smooth_lerp(&position, slider_position, m_smooth_scroll_speed);
		smooth_lerp(&offset, m_scrollbar.m_offset, m_menu_animation_speed);

		draw_rect(m_lerped_pos_x - offset + (m_scrollbar.m_width / 2), m_draw_base_y + (m_bg_current / 2.f), m_scrollbar.m_width, m_bg_current, m_option_unselected_background_color, ImGui::GetBackgroundDrawList(), 5.f);
		draw_rect(m_lerped_pos_x - offset + (m_scrollbar.m_width / 2) - m_scrollbar.m_bar_offset, (m_scrollbar.m_type_pos == 0 ? slider_top + position + 0.05f : m_current_coord), m_scrollbar.m_width2, m_option_height - 0.006f, m_option_selected_background_color, ImGui::GetBackgroundDrawList(), 5.f);
	}
	float get_rect_base(float rect_height, float draw_base = g_interface->m_draw_base_y) {
		return draw_base + (rect_height / 2.f);
	}
	void Interface::draw_lines() {
		draw_gradiant_rect(m_lerped_pos_x, m_lerped_pos_y + (m_header_height + m_submenu_bar_height), m_width, 0.001, { m_options.m_second_color.r, m_options.m_second_color.g, m_options.m_second_color.b, m_header_text_color.a }, { m_options.m_first_color.r, m_options.m_first_color.g, m_options.m_first_color.b, m_header_text_color.a });
		draw_gradiant_rect(m_lerped_pos_x, m_lerped_pos_y + m_header_height + m_submenu_bar_height + m_bg_current - 0.001, m_width, 0.001, { m_options.m_second_color.r, m_options.m_second_color.g, m_options.m_second_color.b, m_header_text_color.a }, { m_options.m_first_color.r, m_options.m_first_color.g, m_options.m_first_color.b, m_header_text_color.a });
	}
	bool is_key_pressed(std::uint16_t key) {
		if (GetForegroundWindow() == g_pointers->m_game_window) {
			if (GetAsyncKeyState(key) & 0x8000) {
				return true;
			}
		}
		return false;
	}
	void Interface::draw_option(abstract_option* opt, abstract_submenu* sub, bool selected) {
		float new_y{ m_current_coord - (get_text_height(m_option_font, m_option_text_size, m_width) / 2.f) };

		if (m_options.m_bar) {
			float width{ 0.003f };
			draw_gradiant_rect2(m_lerped_pos_x - (m_width / 2.f) + (width / 2.f), m_current_coord, width, m_option_height, { m_options.m_first_color.r, m_options.m_first_color.g, m_options.m_first_color.b, m_header_text_color.a }, { m_options.m_second_color.r, m_options.m_second_color.g, m_options.m_second_color.b, m_header_text_color.a });
		}
		draw_left_text(opt->get_left_text(), m_lerped_pos_x - (m_width / m_option_padding) + (selected && m_options.m_bar ? 0.00201f : 0), (m_smooth_scroll_moves_text && selected) ? new_y : m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_text_size, m_width) / 2.f), m_option_text_size, m_option_font, selected ? m_option_selected_text_color : m_option_unselected_text_color, false, false, -1.0f, (selected && m_options.m_gradiant_selected_text) ? true : false);

		if (opt->get_flag(option_flag::Horizontal)) {
			bool keyboard_open{ (number_type_open && selected) };
			color<int> col{ selected ? m_option_selected_text_color : m_option_unselected_text_color };
			color<int> col2{ selected ? m_red_color : m_option_unselected_text_color };
			auto texture{ g_renderer->m_resources[keyboard_open ? "Keyboard" : "ArrowsLeftRight"] };
			auto sizeX{ keyboard_open ? 0.011f - m_toggle_size_x_offset : get_sprite_scale(0.033).x };
			auto sizeY{ keyboard_open ? 0.018f - m_toggle_size_y_offset : get_sprite_scale(0.030).y };
			auto offset{ selected ? 0.012 : 0 };
			color<int> first{ selected ? m_option_selected_text_color : m_option_unselected_text_color };
			color<int> second{ 255, 0, 0, 255 };

			if (selected)
				draw_sprite(texture, m_lerped_pos_x + (m_width / m_option_padding) - 0.005f, m_draw_base_y + (m_option_height / 2.f), sizeX, sizeY, keyboard_open ? col2 : col, 90.0);

			draw_right_text(opt->get_right_text(), m_lerped_pos_x + (m_width / m_option_padding) - offset, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_text_size, m_width) / 2.f) - 0.001, m_option_text_size, m_option_font, keyboard_open ? col2 : col, false, false);
		}
		else if (opt->get_flag(option_flag::ToggleWithChoose)) {
			auto size{ get_sprite_scale(m_toggle_size) };
			auto texture{ g_renderer->m_resources["ArrowsLeftRight"] };
			if (selected)
				draw_sprite(texture, m_lerped_pos_x + (m_width / m_option_padding) - 0.0173f, m_draw_base_y + (m_option_height / 2.f), get_sprite_scale(0.033).x, get_sprite_scale(0.030).y, m_option_selected_text_color, 90.0);

			draw_sprite(m_toggle ? g_renderer->m_resources["On"] : g_renderer->m_resources["Off"], m_lerped_pos_x + (m_width / m_option_padding) - (size.x / 4.f), m_draw_base_y + (m_option_height / 2.f), 0.011f - m_toggle_size_x_offset, 0.018f - m_toggle_size_y_offset, selected ? m_option_selected_text_color : m_option_unselected_text_color, 0.f);
			draw_right_text(opt->get_right_text(), m_lerped_pos_x + (m_width / m_option_padding) - (selected ? 0.024f : 0.012), m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_text_size, m_width) / 2.f), m_option_text_size, m_option_font, selected ? m_option_selected_text_color : m_option_unselected_text_color, false, false);
		}
		else if (opt->get_flag(option_flag::Keyboard)) {
			color<int> col{ selected ? m_option_selected_text_color : m_option_unselected_text_color };
			color<int> col2{ selected ? m_red_color : m_option_unselected_text_color };
			auto size{ get_sprite_scale(m_toggle_size) };
			draw_sprite(g_renderer->m_resources["Keyboard"], m_lerped_pos_x + (m_width / m_option_padding) - (size.x / 4.f), m_draw_base_y + (m_option_height / 2.f), 0.011f - m_toggle_size_x_offset, 0.018f - m_toggle_size_y_offset, keyboard_open ? col2 : col, 0.f);
			draw_right_text(opt->get_right_text(), m_lerped_pos_x + (m_width / m_option_padding) - 0.012, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_text_size, m_width) / 2.f), m_option_text_size, m_option_font, keyboard_open ? col2 : col, false, false);
		}
		else
			draw_right_text(opt->get_right_text(), m_lerped_pos_x + (m_width / m_option_padding), m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_option_font, m_option_text_size, m_width) / 2.f), m_option_text_size, m_option_font, selected ? m_option_selected_text_color : m_option_unselected_text_color, false, false);

		if (opt->get_flag(option_flag::Toggle)) {
			auto size{ get_sprite_scale(m_toggle_size) };
			draw_sprite(m_toggle ? g_renderer->m_resources["On"] : g_renderer->m_resources["Off"], m_lerped_pos_x + (m_width / m_option_padding) - (size.x / 4.f), m_draw_base_y + (m_option_height / 2.f), 0.011f - m_toggle_size_x_offset, 0.018f - m_toggle_size_y_offset, selected ? m_option_selected_text_color : m_option_unselected_text_color, 0.f);
		}

		if (opt->get_flag(option_flag::On) || (opt->get_texture() == "on")) {
			auto size{ get_sprite_scale(m_toggle_size) };
			draw_sprite(g_renderer->m_resources["On"], m_lerped_pos_x + (m_width / m_option_padding) - (size.x / 4.f), m_draw_base_y + (m_option_height / 2.f), 0.011f - m_toggle_size_x_offset, 0.018f - m_toggle_size_y_offset, selected ? m_option_selected_text_color : m_option_unselected_text_color, 0.f);
		}

		if (opt->get_flag(option_flag::Enterable)) {
			auto size{ get_sprite_scale(m_submenu_arrow_size) };
			draw_sprite(g_renderer->m_resources["ArrowRight"], m_lerped_pos_x + (m_width / m_option_padding) - (size.x / 4.f), m_draw_base_y + (m_option_height / 2.f), size.x, size.y, selected ? m_option_selected_text_color : m_option_unselected_text_color, 0.f);
		}

		if (opt->get_flag(option_flag::ColorPicker)) {
			auto res{ get_sprite_scale(m_submenu_arrow_size) };
			auto res2{ get_sprite_scale(m_submenu_arrow_size) };
			draw_sprite(g_renderer->m_resources["ArrowRight"], m_lerped_pos_x + (m_width / m_option_padding) - (res.x / 4.f), m_draw_base_y + (m_option_height / 2.f), res.x, res.y, opt->get_color().as<int>(), 0.f);
		}

		if (opt->get_flag(option_flag::VehicleButton) && selected) {
			draw_vehicle_info(opt->get_arg());
		}

		if (opt->get_flag(option_flag::Break)) {
			draw_centered_text(opt->get_centered_text(), m_lerped_pos_x, m_draw_base_y + (m_option_height / 2.f) - (get_text_height(m_break_font, m_option_break_size, m_width) / 2.f), m_option_break_size, m_break_font, m_option_unselected_text_color, m_width, false, true);
			if (selected) {
				if (m_scroll_forward)
					sub->scroll_forward();
				else if (m_scroll_backward)
					sub->scroll_backward();
			}
		}

		if (m_hotkey_pressed && selected && opt->get_bool()) {
			draw_centered_text("Press any key to set hotkey...", 0.5f, 0.5f, 0.90f, m_option_font, { 255, 255, 255, 255 }, false, false);

			static int delay_tick;
			static bool waiting_for_key{ true };

			if (GetTickCount64() - delay_tick > 150 && waiting_for_key) {
				for (int key = 0; key < 256; key++) {
					if (is_key_pressed(key) && key != VK_F12) {
						m_last_key_pressed = key;
						waiting_for_key = false;
						break;
					}
				}
			}

			if (!waiting_for_key) {

				m_bool_hotkeys.insert({ rage::joaat(opt->get_left_text()), { m_last_key_pressed, opt->get_bool(), opt->get_left_text(), opt->get_toggle_action() ? opt->get_toggle_action() : [] {} } });

				g_notifications->send("Hotkeys", std::format("Added {} as a hotkey. (Key: {})", opt->get_left_text(), g_key_names[m_last_key_pressed]));

				m_hotkey_pressed = false;
				delay_tick = GetTickCount64();
				waiting_for_key = true;
			}
		}

		if (m_hotkey_pressed && selected && opt->get_button_action()) {
			draw_centered_text("Press any key to set hotkey...", 0.5f, 0.5f, 0.90f, m_option_font, { 255, 255, 255, 255 }, false, false);

			static int delay_tick;
			static bool waiting_for_key{ true };

			if (GetTickCount64() - delay_tick > 150 && waiting_for_key) {
				for (int key = 0; key < 256; key++) {
					if (is_key_pressed(key) && key != VK_F12) {
						m_last_key_pressed = key;
						waiting_for_key = false;
						break;
					}
				}
			}

			if (!waiting_for_key) {
				m_button_hotkeys.insert({ rage::joaat(opt->get_left_text()), { m_last_key_pressed, opt->get_button_action(), opt->get_left_text() } });

				g_notifications->send("Hotkeys", std::format("Added {} as a hotkey. (Key: {})", opt->get_left_text(), g_key_names[m_last_key_pressed]));

				m_hotkey_pressed = false;
				delay_tick = GetTickCount64();
				waiting_for_key = true;
			}
		}

		m_draw_base_y += m_option_height;
	}
	void Interface::update_hotkeys() {
		if (!m_bool_hotkeys.empty()) {
			static int delay_tick;
			for (auto pair : m_bool_hotkeys) {
				if (GetTickCount64() - delay_tick > 500) {
					if (is_key_pressed(pair.second.m_key)) {
						*pair.second.m_pointer = !*pair.second.m_pointer;

						AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);

						if (*pair.second.m_pointer) {
							g_notifications->send("Hotkeys", std::format("Enabled {}", pair.second.m_name));
						}
						else {
							g_notifications->send("Hotkeys", std::format("Disabled {}", pair.second.m_name));
							if (pair.second.m_on_disable) {
								pair.second.m_on_disable();
							}
						}

						delay_tick = GetTickCount64();
					}
				}
			}
		}
		if (!m_button_hotkeys.empty()) {
			static int delay_tick;
			for (auto pair : m_button_hotkeys) {
				if (GetTickCount64() - delay_tick > 500) {
					if (is_key_pressed(pair.second.m_key)) {
						pair.second.m_action();

						AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
						g_notifications->send("Hotkeys", std::format("Invoked {}", pair.second.m_name));

						delay_tick = GetTickCount64();
					}
				}
			}
		}
	}
	void Interface::draw_footer() {
		draw_rect(m_lerped_pos_x, m_lerped_pos_y + m_header_height + m_submenu_bar_height + m_bg_current + (m_footer_height / 2), m_width, m_footer_height, m_footer_background_color, ImGui::GetForegroundDrawList(), m_rounding.m_footer, ImDrawFlags_RoundCornersBottom);
		float size{ m_footer_sprite_size };
		float rotation{};
		auto texture{ g_renderer->m_resources["Arrows"] };
		if (!submenu_stack.empty() && !m_footer.m_freeze) {
			auto sub{ submenu_stack.top() };
			if (!sub->get_selected_option()) {
				texture = g_renderer->m_resources["ArrowDown"];
				size *= 0.8f;
			}
			else if (sub->get_selected_option() + 1 == sub->get_num_options()) {
				texture = g_renderer->m_resources["ArrowUp"];
				size *= 0.8f;
			}
		}
		if (m_footer.m_freeze) {
			switch (m_footer.m_freeze_selected) {
			case 0:
				texture = g_renderer->m_resources["Arrows"];
				break;
			case 1:
				texture = g_renderer->m_resources["ArrowUp"];
				break;
			case 2:
				texture = g_renderer->m_resources["ArrowDown"];
				break;
			}
		}
		auto scale{ get_sprite_scale(size) };
		draw_sprite(texture, m_lerped_pos_x, get_rect_base(m_footer_height, m_lerped_pos_y + m_header_height + m_bg_current + m_option_height + 0.0039), scale.x, scale.y, m_footer_sprite_color, rotation);
		m_draw_base_y += m_footer_height;
	}
	inline ImVec2 resolution() {
		return ImGui::GetIO().DisplaySize;
	}
	ImVec2 get_text_scale2(str text, float wrap) {
		return { ImGui::CalcTextSize(text.c_str(), nullptr, false, wrap).x / resolution().x, ImGui::CalcTextSize(text.c_str(), nullptr, false, wrap).y / resolution().y };
	}
	float adjusted_description_height{ 0 };
	void Interface::draw_description() {
		str description;
		if (!submenu_stack.empty()) {
			auto sub{ submenu_stack.top() };
			if (sub->get_num_options()) {
				if (auto opt = sub->get_option(sub->get_selected_option())) {
					description = opt->get_description();
				}
			}
		}
		if (description == "") {
			return;
		}
		auto text_size{ get_text_scale(description) };
		smooth_lerp(&adjusted_description_height, m_description_height_padding + (text_size.y * 0.45f), m_speed);

		m_draw_base_y += m_description_height_padding;
		draw_rect(m_lerped_pos_x, get_rect_base(m_footer_height, m_lerped_pos_y + m_header_height + m_bg_current + m_option_height + 0.022 + 0.005) + (adjusted_description_height / 2), m_width, adjusted_description_height, m_option_unselected_background_color, ImGui::GetForegroundDrawList(), 8.f, ImDrawFlags_RoundCornersBottom);
		draw_left_text(description, m_lerped_pos_x - (m_width / m_description_padding), get_rect_base(m_footer_height, m_lerped_pos_y + m_header_height + m_bg_current + m_option_height + 0.037 + 0.005) - (get_text_height(m_description_font, m_description_text_size, m_width) / 2.f), m_description_text_size, m_description_font, m_header_text_color, false, false);
		draw_gradiant_rect(m_lerped_pos_x, get_rect_base(m_footer_height, m_lerped_pos_y + m_header_height + m_bg_current + m_option_height + 0.022 + 0.005) + 0.0015, m_width, m_description_line_height, { m_options.m_second_color.r, m_options.m_second_color.g, m_options.m_second_color.b, m_header_text_color.a }, { m_options.m_first_color.r, m_options.m_first_color.g, m_options.m_first_color.b, m_header_text_color.a }, ImGui::GetForegroundDrawList());
		m_draw_base_y += adjusted_description_height;
	}
	auto& get_vehicle_pool() {
		return ***g_pointers->m_vehicle_pool;
	}
	auto& get_object_pool() {
		return **g_pointers->m_object_pool;
	}
	auto& get_ped_pool() {
		return **g_pointers->m_ped_pool;
	}
	auto& get_pickup_pool() {
		return **g_pointers->m_pickup_pool;
	}
	int get_online_friend_count() {
		int count{ 0 };
		for (uint32_t i = 0; i < g_pointers->m_friend_registry->m_friend_count; i++)
			if (g_pointers->m_friend_registry->get(i)->m_friend_state != 0)
				count++;
		return count;
	}

	void Interface::draw_overlay() {
		static int highest;
		static int fps;
		static char buffer[80];
		static timer update_timer(0ms);
		update_timer.set_delay(std::chrono::seconds(1));
		if (update_timer.update()) {
			fps = ImGui::GetIO().Framerate;
			std::time_t current_time{ time(0) }; struct std::tm tstruct;
			tstruct = *localtime(&current_time);
			strftime(buffer, sizeof(buffer), "%c", &tstruct);
		}
		if (fps > highest)
			highest = fps;
		std::string format{ std::format("{} | {}", BRANDING, (std::string)buffer) };
		draw_rect(m_overlay_x, m_overlay_y, m_overlay_width, m_overlay_height, m_overlay_color, ImGui::GetForegroundDrawList(), 10.f, ImDrawFlags_RoundCornersBottom);
		draw_left_text(format.c_str(), m_overlay_x - (m_overlay_width / m_overlay_padding), m_overlay_y - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.02, m_overlay_font, m_overlay_text_color, false, false);
		draw_rect(m_overlay_x, m_overlay_y - (m_overlay_line_height / 2.f) - (m_overlay_height / 2.f), m_overlay_width, m_overlay_line_height, m_overlay_line_color);

		draw_rect(m_overlay_x - 0.049 - 0.003, m_overlay_y2, (m_overlay_width / 2) - 0.005, m_overlay_height * 2, m_overlay_color, ImGui::GetForegroundDrawList(), 10.f, ImDrawFlags_RoundCornersBottom);
		draw_left_text("Vehicles", m_overlay_x - 0.049 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 - 0.025 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_left_text("Objects", m_overlay_x - 0.049 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 - 0.009 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_left_text("Peds:", m_overlay_x - 0.049 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 + 0.007 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_left_text("Pickups:", m_overlay_x - 0.049 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 + 0.023 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}/{}", get_vehicle_pool().m_item_count, get_vehicle_pool().m_size).c_str(), m_overlay_x + 0.040 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 - 0.025 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}/{}", get_object_pool().get_item_count(), get_object_pool().m_size).c_str(), m_overlay_x + 0.040 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 - 0.009 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}/{}", get_ped_pool().get_item_count(), get_ped_pool().m_size).c_str(), m_overlay_x + 0.040 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 + 0.007 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}/{}", get_pickup_pool().get_item_count(), get_pickup_pool().m_size).c_str(), m_overlay_x + 0.040 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 + 0.023 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_rect(m_overlay_x - 0.049 - 0.003, m_overlay_y2 - (m_overlay_line_height / 2.f) - (m_overlay_height * 2 / 2.f), (m_overlay_width / 2) - 0.005, m_overlay_line_height, m_overlay_line_color);

		auto mgr{ g_utils->get_network_player_mgr() };
		draw_rect(m_overlay_x + 0.049 + 0.003, m_overlay_y2, (m_overlay_width / 2) - 0.005, m_overlay_height * 2, m_overlay_color, ImGui::GetForegroundDrawList(), 10.f, ImDrawFlags_RoundCornersBottom);
		draw_left_text("FPS", m_overlay_x + 0.055 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 - 0.025 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_left_text("Highest FPS", m_overlay_x + 0.055 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 - 0.009 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_left_text("Online Friends", m_overlay_x + 0.055 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 + 0.007 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_left_text("Player Count:", m_overlay_x + 0.055 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 + 0.023 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}", fps).c_str(), m_overlay_x + 0.144 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 - 0.025 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}", highest).c_str(), m_overlay_x + 0.144 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 - 0.009 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}/{}", get_online_friend_count(), g_pointers->m_friend_registry->m_friend_count).c_str(), m_overlay_x + 0.144 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 + 0.007 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}/{}", mgr->m_player_count, mgr->m_player_limit).c_str(), m_overlay_x + 0.144 - (m_overlay_width / 2 / m_overlay_padding), m_overlay_y2 + 0.023 - (get_text_scale(format.c_str()).y / 6.f), m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_rect(m_overlay_x + 0.049 + 0.003, m_overlay_y2 - (m_overlay_line_height / 2.f) - (m_overlay_height * 2 / 2.f), (m_overlay_width / 2) - 0.005, m_overlay_line_height, m_overlay_line_color);
	}
	CNetGamePlayer* get_player(std::int32_t id) {
		auto network{ *g_pointers->m_network_player_mgr };
		for (auto& player : network->m_player_list)
			if (player->is_valid())
				if (player->m_player_id == id) return player;
		return nullptr;
	}
	struct scene_preset {
		struct scene_preset_element {
			char _0x0000[24];
			rage::fvector4 m_position;
			rage::fvector4 m_position_43;
			rage::fvector4 m_rotation_xyz;
			rage::fvector4 m_bg_rect_xywh;
			rage::fvector4 m_bg_rect_xywh_43;
			uint32_t m_bg_rect_color;
			uint32_t m_blend_color;
			bool m_enabled;
			char _0x0071[15];
		};

		uint32_t m_name;
		char _0x0004[4];
		scene_preset_element m_elements[5];
		char _0x0288[8];
		int32_t m_element_count;
		char _0x0294[12];

		void set_element_rot(uint32_t element, Vector3 rot) {
			if (element >= 0 && element < 5) {
				m_elements[element].m_rotation_xyz.x = rot.x;
				m_elements[element].m_rotation_xyz.y = rot.y;
				m_elements[element].m_rotation_xyz.z = rot.z;
			}
		}

		void set_element_pos(uint32_t element, Vector2 xy, Vector2 wh) {
			if (element >= 0 && element < 5) {
				m_elements[element].m_bg_rect_xywh.z = wh.x; // make fullscreen
				m_elements[element].m_bg_rect_xywh.w = wh.y; // make fullscreen
				m_elements[element].m_bg_rect_xywh.x = xy.x; // convert and set pos
				m_elements[element].m_bg_rect_xywh.y = xy.y; // convert and set pos
				m_elements[element].m_bg_rect_xywh_43.z = wh.x; // make fullscreen
				m_elements[element].m_bg_rect_xywh_43.w = wh.y; // make fullscreen
				m_elements[element].m_bg_rect_xywh_43.x = xy.x; // convert and set pos
				m_elements[element].m_bg_rect_xywh_43.y = xy.y; // convert and set pos
				m_elements[element].m_bg_rect_color = 0x0;
			}
		}
	};
	template<typename T>
	static T call(uint64_t address) { return ((T(*)())address)(); }

	template<typename T, typename P1>
	static T call(uint64_t address, P1 p1) { return ((T(*)(P1))address)(p1); }

	template<typename T, typename P1, typename P2>
	static T call(uint64_t address, P1 p1, P2 p2) { return ((T(*)(P1, P2))address)(p1, p2); }

	template<typename T, typename P1, typename P2, typename P3>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3) { return ((T(*)(P1, P2, P3))address)(p1, p2, p3); }

	template<typename T, typename P1, typename P2, typename P3, typename P4>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4) { return ((T(*)(P1, P2, P3, P4))address)(p1, p2, p3, p4); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) { return ((T(*)(P1, P2, P3, P4, P5))address)(p1, p2, p3, p4, p5); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) { return ((T(*)(P1, P2, P3, P4, P5, P6))address)(p1, p2, p3, p4, p5, p6); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7))address)(p1, p2, p3, p4, p5, p6, p7); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8))address)(p1, p2, p3, p4, p5, p6, p7, p8); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9))address)(p1, p2, p3, p4, p5, p6, p7, p8, p9); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10))address)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	void draw_on_screen_ped(CPed* ped, Vector2 pos, Vector2 scale, Vector3 position_offset) {
		uint32_t scene_hash = 0x390DCCF5;
		uint32_t element = 0;

		uintptr_t ui_3d_draw_manager{ *(uint64_t*)(g_pointers->m_ui_3d_draw_manager) };
		if (ui_3d_draw_manager) {

			*(uint8_t*)((uint64_t)ped + 0x1163) |= 0x40u;
			*(uint32_t*)((uint64_t)ped + 0x114C) |= 0xC0u;
			scene_preset* preset{ call<scene_preset*>(g_pointers->m_get_scene_preset, ui_3d_draw_manager, &scene_hash) };
			if (preset) {
				preset->m_elements[element].m_rotation_xyz.x = 0.0f;
				preset->m_elements[element].m_rotation_xyz.y = 0.0f;
				preset->m_elements[element].m_rotation_xyz.z = 0.0f;
				preset->set_element_pos(element, pos, scale);
			}

			if (call<bool>(g_pointers->m_push_scene_preset_manager, ui_3d_draw_manager, &scene_hash)) {
				if (call<bool>(g_pointers->m_add_element_to_scene, ui_3d_draw_manager, &scene_hash, element, ped, position_offset, 1.0f)) {
					call<bool>(g_pointers->m_set_scene_element_lighting, ui_3d_draw_manager, &scene_hash, element, 1.0f);
				}
			}
		}
	}

	CPlayerInfo* get_player_info(std::int32_t player)
	{
		if (get_player(player) != nullptr && get_player(player)->m_player_info != nullptr)
			return get_player(player)->m_player_info;
		return nullptr;
	}
	CPed* get_ped(std::int32_t player)
	{
		if (const auto player_info = get_player_info(player); player_info != nullptr)
			if (const auto ped = player_info->m_ped; ped != nullptr)
				return ped;
		return nullptr;
	}
	void Interface::draw_player_info(std::int32_t player, bool show) {
		if (get_player(player) == nullptr) return;
		if (!get_player(player)->is_valid()) return;
		/*if (ImGui::Begin("Nigger")) {
			ImGui::SliderFloat("Ped X", &pedx, -2, 2);
			ImGui::SliderFloat("Ped Y", &pedy, -2, 2);
			ImGui::SliderFloat("X Offset", &xoffset, -2, 2);
			ImGui::SliderFloat("Y Offset", &yoffset, -2, 2);
			ImGui::SliderFloat("Z Offset", &zoffset, -2, 2);
			ImGui::SliderFloat("Width", &width22, -2, 2);
			ImGui::SliderFloat("Height", &height22, -2, 2);
			ImGui::End();
		}

		draw_on_screen_ped(
			get_ped(player),
			{ g_interface->pos_x + pedx + (g_interface->width / 2.f), g_interface->pos_y + pedy },
			{ width22, height22 },
			{ xoffset, yoffset, zoffset }
		);*/

		draw_rect(m_lerped_pos_x + m_player_info_x, m_current_coord + (m_player_info_height / 2.f) - 0.015, m_width, m_player_info_height, m_player_info_color, ImGui::GetForegroundDrawList(), 10.f, ImDrawFlags_RoundCornersBottom);
		draw_rect(m_lerped_pos_x + m_player_info_x, m_current_coord + 0.056f - (m_header_height / 2.f) - m_player_info_line_height - 0.016, m_width, m_player_info_line_height, m_player_info_line_color, ImGui::GetForegroundDrawList());

		draw_left_text("Infinite Ammo", m_lerped_pos_x + m_player_info_x - m_width + 0.11, m_current_coord + (m_player_info_height / 2.f) - 0.015 - 0.09, m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(get_player(player)->m_player_info->m_ped->m_inventory->m_infinite_ammo ? "Yes" : "No", m_lerped_pos_x + m_player_info_x + 0.1, m_current_coord + (m_player_info_height / 2.f) - 0.015 - 0.09, m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);

		draw_left_text("Wanted Level", m_lerped_pos_x + m_player_info_x - m_width + 0.11, m_current_coord + (m_player_info_height / 2.f) - 0.015 - 0.075, m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::to_string(get_player(player)->m_player_info->m_wanted_level).c_str(), m_lerped_pos_x + m_player_info_x + 0.1, m_current_coord + (m_player_info_height / 2.f) - 0.015 - 0.075, m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);

		draw_left_text("Health", m_lerped_pos_x + m_player_info_x - m_width + 0.11, m_current_coord + (m_player_info_height / 2.f) - 0.015 - 0.060, m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}/{}", get_player(player)->m_player_info->m_ped->m_health, get_player(player)->m_player_info->m_ped->m_maxhealth).c_str(), m_lerped_pos_x + m_player_info_x + 0.1, m_current_coord + (m_player_info_height / 2.f) - 0.015 - 0.060, m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);

		draw_left_text("Armor", m_lerped_pos_x + m_player_info_x - m_width + 0.11, m_current_coord + (m_player_info_height / 2.f) - 0.015 - 0.045, m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
		draw_right_text(std::format("{}/{}", get_player(player)->m_player_info->m_ped->m_armor, 100).c_str(), m_lerped_pos_x + m_player_info_x + 0.1, m_current_coord + (m_player_info_height / 2.f) - 0.015 - 0.045, m_overlay_text_size - 0.05, m_overlay_font, m_overlay_text_color, false, false);
	}
}