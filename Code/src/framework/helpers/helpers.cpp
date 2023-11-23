#include "src/framework/framework.h"
#include "src/Utility/Timer.h"
#include "src/Natives/Natives.h"
#include "src/fiber/fiber_helper.h"
#include "src/framework/direct_x/renderer.h"
#include <src/rage/draw_handlers/pgDictionary.hpp>
#include <src/rage/draw_handlers/grcTexture.hpp>
#include "src/utility/Setting.h"
#include "src/utility/Timer.h"
#include "src/framework/animations/menu.hpp"

namespace Base::Framework {
	void Interface::smooth_lerp(float* current, float target, float speed) {
		if (*current != target)
			*current = *current * (1 - speed) + target * speed;
		if ((*current > target - 0.0005) && (*current < target + 0.0005))
			*current = target;
	}
	void Interface::bob_value(float* value, float min, float max, float increment) {
		int type = 0;

		if (std::fabs(*value - min) < std::numeric_limits<float>::epsilon()) {
			type = 0;
		}
		if (std::fabs(*value - max) < std::numeric_limits<float>::epsilon()) {
			type = 1;
		}

		switch (type) {
		case 0:
			if (*value + increment <= max) {
				*value += increment;
			}
			break;
		case 1:
			if (*value - increment >= min) {
				*value -= increment;
			}
			break;
		}
	}
	rect Interface::get_rect_bounds(float base_x, float base_y, float height, float width) {
		return { base_y, base_y + height, base_x - (width / 2.f), base_x + (width / 2.f) };
	}

	void Interface::draw_background(abstract_submenu* sub) {
		auto visible_options{ sub->get_num_options() > m_options_per_page ? m_options_per_page : sub->get_num_options() };
		float bg_height{ m_option_height * visible_options };
		m_bg_target = bg_height;

		smooth_lerp(&m_bg_current, m_bg_target, m_speed);

		draw_rect(m_lerped_pos_x, m_draw_base_y + (m_bg_current / 2.f), m_width, m_bg_current, m_option_unselected_background_color);
	}
	void Interface::OnTick() {
		if (m_click_ui) return;
		check_for_input();
		handle_input();

		if (g_interface->m_fly_in) {
			if (m_menu_closing_animation) {
				smooth_lerp(&m_lerped_pos_x, 0, m_menu_animation_speed);
				smooth_lerp(&m_lerped_pos_y, 0, m_menu_animation_speed);
			}
		}
		if (m_opened) {
			if (!g_interface->m_menu_closing_animation) {
				smooth_lerp(&m_lerped_pos_x, m_pos_x, m_menu_animation_speed);
				smooth_lerp(&m_lerped_pos_y, m_pos_y, m_menu_animation_speed);
			}
			m_draw_base_y = m_lerped_pos_y;

			draw_header();
			if (!submenu_stack.empty()) {
				auto sub{ submenu_stack.top() };
				sub->Reset();
				sub->Execute();
				draw_submenu_bar(sub);
				draw_background(sub);

				if (m_scrollbar.m_enabled) {
					draw_scrollbar(sub);
				}
				if (sub->get_num_options() != 0) {
					std::size_t start_point{ 0 };
					std::size_t end_point{ sub->get_num_options() > m_options_per_page ? m_options_per_page : sub->get_num_options() };
					if (sub->get_num_options() > m_options_per_page && sub->get_selected_option() >= m_options_per_page - 6) {             
						for (int i = 0; i < 6; i++) {
							if (sub->get_selected_option() < sub->get_num_options() - i) {
								start_point = sub->get_selected_option() - m_options_per_page + i + 1;
								end_point = sub->get_selected_option() + i + 1;
							}
						}
					}
					for (std::size_t i = start_point, j = 0; i < end_point; ++i, ++j) {
						if (i == sub->get_selected_option()) {
							smooth_lerp(&m_current_coord, m_draw_base_y + (m_option_height / 2.f), m_smooth_scroll_speed);
							draw_rect(
								m_lerped_pos_x,
								m_current_coord,
								m_width,
								m_option_height,
								m_option_selected_background_color, ImGui::GetBackgroundDrawList(), m_rounded_options ? m_rounded_options_mult : 0);
						}
						if (m_bg_current >= m_option_height * i || (sub->get_num_options() > m_options_per_page && sub->get_selected_option() >= m_options_per_page - 6)) {
							draw_option(sub->get_option(i), sub, i == sub->get_selected_option());
						}
					}
				}
				if (m_footer.m_enabled) {
					if ((m_footer.m_dynamic && sub->get_num_options() > m_options_per_page)) {
						draw_footer();
					}

					if (!m_footer.m_dynamic) {
						draw_footer();
					}
				}
				draw_description();
				if (m_lines) {
					draw_lines();
				}
			}
		}
		else
			draw_tooltips();
		//draw_overlay();
	}
	int g_lastFrameCount{};
	void Interface::flip_through_frames(int delay) {
		static timer tick(0ms);
		tick.set_delay(delay);
		if (tick.update() && g_lastFrameCount != ImGui::GetFrameCount()) {
			g_lastFrameCount = ImGui::GetFrameCount();
			if (g_renderer->m_header.size() != 1)
				if (g_renderer->header_frame < g_renderer->m_header.size() - 1)
					g_renderer->header_frame++;
				else if (g_renderer->header_frame == g_renderer->m_header.size() - 1)
					g_renderer->header_frame = 0;
				else
					g_renderer->header_frame = 0;
		}
	}
	void Interface::check_for_input() {
	}
	void Interface::queue_sound(str name) {
		g_fiber_pool.queue([=] {
			if (m_sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, name.c_str(), "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		});
	}
	int vertical_count{ 0 };
	int horizontal_count{ 0 };
	bool get_og_values{ false };
	float delays[2];
	void Interface::handle_input() {
		if (!get_og_values) {
			delays[0] = m_vertical_delay;
			delays[1] = m_horizontal_delay;
			get_og_values = true;
		}
		static timer open_timer{ 0ms }, back_timer{ 0ms }, enter_timer{ 0ms }, vertical_timer{ 0ms }, horizontal_timer{ 0ms };
		open_timer.set_delay(std::chrono::milliseconds(m_open_delay));
		back_timer.set_delay(std::chrono::milliseconds(m_back_delay));
		enter_timer.set_delay(std::chrono::milliseconds(m_enter_delay));
		vertical_timer.set_delay(std::chrono::milliseconds(m_vertical_delay));
		horizontal_timer.set_delay(std::chrono::milliseconds(m_horizontal_delay));
		if (vertical_count > 20)
			m_vertical_delay--;
		else
			m_vertical_delay = delays[0];

		if (horizontal_count > 20)
			m_horizontal_delay--;
		else
			m_horizontal_delay = delays[1];

		if (m_open_key_pressed && open_timer.update()) {
			queue_sound(m_opened ? "SELECT" : "BACK");
			if (!m_menu_opening_animation) {
				if (m_opened)
					animations::close();
				else
					animations::open();
			}
		}
		if (m_opened) {
			static timer hotkey_timer(0ms);
			hotkey_timer.set_delay(std::chrono::milliseconds(m_back_delay));
			if (m_hotkey_key_pressed && hotkey_timer.update()) {
				queue_sound("BACK");
				m_hotkey_pressed = !m_hotkey_pressed;
			}
			if (m_back_key_pressed && back_timer.update() && !m_disable_input) {
				queue_sound("BACK");
				if (submenu_stack.size() <= 1) {
					m_opened = false;
				}
				else {
					submenu_stack.pop();
				}
			}
			if (!submenu_stack.empty()) {
				auto sub{ submenu_stack.top() };
				if (sub->get_num_options()) {
					if (auto opt = sub->get_option(sub->get_selected_option()); opt) {
						if (m_enter_key_pressed && back_timer.update()) {
							queue_sound("SELECT");
							opt->handle_action(option_action::EnterPress);
						}
						if (vertical_timer.update() && !m_disable_input) {
							if (m_up_key_pressed || m_down_key_pressed) {
								queue_sound("NAV_UP_DOWN");
								vertical_count++;
							}
							if (!m_up_key_pressed && !m_down_key_pressed)
								vertical_count = 0;

							if (m_up_key_pressed) {
								sub->scroll_backward();
								if (auto opt = sub->get_option(sub->get_selected_option())) {
									if (opt->get_flag(option_flag::Break)) {
										sub->scroll_backward();
									}
								}
							}
							if (m_down_key_pressed) {
								sub->scroll_forward();
								if (auto opt = sub->get_option(sub->get_selected_option())) {
									if (opt->get_flag(option_flag::Break)) {
										sub->scroll_forward();
									}
								}
							}
						}
						if (horizontal_timer.update() && !m_disable_input && !m_open_key_pressed) {
							if (m_left_key_pressed || m_right_key_pressed)
								horizontal_count++;

							if (!m_left_key_pressed && !m_right_key_pressed)
								horizontal_count = 0;

							if (m_sounds && !opt->get_flag(option_flag::Break))
								if (m_left_key_pressed || m_right_key_pressed)
									queue_sound("NAV_UP_DOWN");
							if (m_left_key_pressed)
								opt->handle_action(option_action::LeftPress);
							if (m_right_key_pressed)
								opt->handle_action(option_action::RightPress);
						}
					}
				}
			}
		}
	}

	void Interface::reset_input() {
		m_open_key_pressed = false;
		m_back_key_pressed = false;
		m_enter_key_pressed = false;
		m_up_key_pressed = false;
		m_down_key_pressed = false;
		m_left_key_pressed = false;
		m_right_key_pressed = false;
	}
	void Interface::draw_rect(float x, float y, float width, float height, color<int> color, ImDrawList* drawlist, float rounding, ImDrawFlags flags) {
		auto pos{ convert_to_pixels({ x, y }) };
		auto size{ convert_to_pixels({ width, height }) };
		auto final_pos{ pos - (size / 2.f) };
		drawlist->AddRectFilled(final_pos, final_pos + size, color.pack(), rounding, flags);
	}
	void Interface::draw_gradiant_rect(float x, float y, float width, float height, color<int> colorr, color<int> ccolor2, ImDrawList* drawlist) {
		auto pos{ convert_to_pixels({ x, y }) };
		auto size{ convert_to_pixels({ width, height }) };
		auto final_pos{ pos - (size / 2.f) };
		drawlist->AddRectFilledMultiColor(final_pos, final_pos + size, ccolor2.pack(), colorr.pack(), colorr.pack(), ccolor2.pack());
	}
	void Interface::draw_gradiant_rect2(float x, float y, float width, float height, color<int> colorr, color<int> ccolor2, ImDrawList* drawlist) {
		auto pos{ convert_to_pixels({ x, y }) };
		auto size{ convert_to_pixels({ width, height }) };
		auto final_pos{ pos - (size / 2.f) };
		drawlist->AddRectFilledMultiColor(final_pos, final_pos + size, colorr.pack(), colorr.pack(), ccolor2.pack(), ccolor2.pack());
	}
	void QueueSteamedDictionaryReuqest(str dict) {
		g_fiber_pool.queue([=] {
			auto hash = rage::joaat(dict);
			auto textureHash = rage::joaat("platform:/textures/" + dict);
			if (auto grcTextureStore = g_pointers->m_texture_store; grcTextureStore) {
				if (!grcTextureStore->FindDictionary(hash) && !grcTextureStore->FindDictionary(textureHash)) {
					GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict.c_str(), false);
				}
			}
		});
		
	}
	rage::pgDictionary* GetDictionary(str dictionary) {
		auto hash = rage::joaat(dictionary);
		auto textureHash = rage::joaat("platform:/textures/" + dictionary);
		if (auto grcTextureStore = g_pointers->m_texture_store; grcTextureStore) {
			if (auto pgDictionary = grcTextureStore->FindDictionary(hash); pgDictionary) {
				return pgDictionary;
			}
			if (auto pgDictionary = grcTextureStore->FindDictionary(textureHash); pgDictionary) {
				return pgDictionary;
			}
		}
		return nullptr;
	}
	rage::grcTexture* GetTexture(str dictionary, str texture) {
		auto hash = rage::joaat(dictionary);
		auto textureHash = rage::joaat("platform:/textures/" + dictionary);
		if (auto grcTextureStore = g_pointers->m_texture_store; grcTextureStore) {
			if (auto pgDictionary = grcTextureStore->FindDictionary(hash); pgDictionary)
				return pgDictionary->FindTexture(texture);
			if (auto pgDictionary = grcTextureStore->FindDictionary(textureHash); pgDictionary)
				return pgDictionary->FindTexture(texture);
		}
		return nullptr;
	}
	inline ImVec2 resolution() {
		return ImGui::GetIO().DisplaySize;
	}
	void Interface::draw_sprite(ImTextureID id, float x, float y, float width, float height, color<int> color, float rotation, ImDrawList* drawlist, float rounding, ImDrawFlags flags) {
		ImVec2 Pos{ convert_to_pixels({ x, y }) };
		ImVec2 Size{ convert_to_pixels({ width, height }) };
		ImVec2 FinalPos{ Pos - (Size / 2.f) };
		ImDrawList* DrawList{ ImGui::GetForegroundDrawList() };
		DrawList->AddImageRounded(id, FinalPos, FinalPos + Size, { 0.f, 0.f }, { 1.f, 1.f }, color.pack(), rounding, flags);
	}
	void Interface::draw_sprite_round(ImTextureID id, float x, float y, float width, float height, color<int> color, ImDrawList* drawlist, float rounding, ImDrawFlags flags) {
		ImVec2 Pos{ convert_to_pixels({ x, y }) };
		ImVec2 Size{ convert_to_pixels({ width, height }) };
		ImVec2 FinalPos{ Pos - (Size / 2.f) };
		ImDrawList* DrawList{ ImGui::GetForegroundDrawList() };
		DrawList->AddImageRounded(id, FinalPos, FinalPos + Size, { 0.f, 0.f }, { 1.f, 1.f }, color.pack(), rounding, flags);
	}
	void Interface::draw_sprite(str dict, str texture, float x, float y, float width, float height, color<int> color, float rotation, ImDrawList* drawlist, float rounding, ImDrawFlags flags) {
		if (rage::grcTexture* GameTexture = GetTexture(dict, texture))
			draw_sprite(GameTexture->m_shader, x, y, width, height, color, rotation, drawlist, rounding, flags);
		else
			QueueSteamedDictionaryReuqest(dict);
	}
	ImU32 InterpolateColor(ImU32 color1, ImU32 color2, float t) {
		ImVec4 col1 = ImGui::ColorConvertU32ToFloat4(color1);
		ImVec4 col2 = ImGui::ColorConvertU32ToFloat4(color2);

		ImVec4 result;
		result.x = col1.x + (col2.x - col1.x) * t;
		result.y = col1.y + (col2.y - col1.y) * t;
		result.z = col1.z + (col2.z - col1.z) * t;
		result.w = col1.w + (col2.w - col1.w) * t;
		return ImGui::ColorConvertFloat4ToU32(result);
	}
	void Interface::draw_ram_text(const str& text, ImVec2 pos, float size, ImFont* font, color<int> color, bool outline, bool shadow, float wrap, bool is_gradient) {
		ImDrawList* DrawList{ ImGui::GetForegroundDrawList() };
		if (is_gradient) {
			float step{ 1.0f / (strlen(text.c_str()) - 1) };

			for (int i{ 0 }; i < strlen(text.c_str()); ++i) {
				auto col{ InterpolateColor(IM_COL32(m_options.m_first_color.r, m_options.m_first_color.g, m_options.m_first_color.b, color.a), IM_COL32(m_options.m_second_color.r, m_options.m_second_color.g, m_options.m_second_color.b, color.a), step * i) };
				DrawList->AddText(font, font->FontSize * get_font_scale(size), pos, col, &text[i], &text[i + 1], wrap);

				pos.x += (ImGui::CalcTextSize(&text[i], &text[i + 1]).x + (resolution().x == 1920 ? (7.00 / resolution().x) : 7.00)); //did lazy way kys
			}
		}
		else {
			DrawList->AddText(font, font->FontSize * get_font_scale(size), pos, color.pack(), text.data(), NULL, wrap);
		}
	}
	void Interface::draw_left_text(str text, float x, float y, float size, Font font, color<int> color, bool outline, bool shadow, float wrap, bool is_gradient) {
		ImVec2 Wrap{ convert_to_pixels({ wrap, wrap }) };
		ImFont* Font{ get_font_from_id(font) };
		ImVec2 Pos{ convert_to_pixels({ x, y }) };
		draw_ram_text(text, Pos, size, Font, color, outline, shadow, Wrap.y, is_gradient);
	}
	void Interface::draw_centered_text(str text, float x, float y, float size, Font font, color<int> color, bool outline, bool shadow, float wrap, bool is_gradient) {
		ImVec2 Wrap{ convert_to_pixels({ wrap, wrap }) };
		Vector2 TextSize{ get_text_size(font, size, text, Wrap.y) };
		draw_left_text(text, x - (TextSize.x / 2.f), y, size, font, color, outline, shadow, wrap, is_gradient);
	}
	void Interface::draw_right_text(str text, float x, float y, float size, Font font, color<int> color, bool outline, bool shadow, float wrap) {
		ImVec2 Wrap{ convert_to_pixels({ wrap, wrap }) };
		Vector2 TextSize{ get_text_size(font, size, text, Wrap.y) };
		draw_left_text(text, x - TextSize.x, y, size, font, color, outline, shadow, wrap);
	}
	ImFont* Interface::get_font_from_id(Font font) {
		switch (font) {
			case Font::RobotoRegular: return g_renderer->m_Roboto; break;
			case Font::RobotoBold: return g_renderer->m_RobotoBold; break;
			case Font::RobotoItalic: return g_renderer->m_RobotoItalic; break;
			case Font::Arial: return g_renderer->m_Arial; break;
			case Font::ArialBold: return g_renderer->m_ArialBold; break;
			case Font::ArialItalic: return g_renderer->m_ArialItalic; break;
			case Font::ArialBoldItalic: return g_renderer->m_ArialBoldItalic; break;
			case Font::ArialBlack: return g_renderer->m_ArialBlack; break;
			case Font::Tahoma: return g_renderer->m_Tahoma; break;
			case Font::Notifcation: return g_renderer->m_notification_font; break;
		}
		return g_renderer->m_Arial;
	}
	Vector2 Interface::get_text_size(Font font, float size, str text, float wrap) {
		ImVec2 Res{ resolution() };
		ImFont* Font{ get_font_from_id(font) };
		ImVec2 TextSize{ Font->CalcTextSizeA(Font->FontSize * get_font_scale(size), FLT_MAX, wrap, text.c_str(), NULL) };
		TextSize.x = IM_FLOOR(TextSize.x + 0.99999999999f);
		return { TextSize.x / Res.x, TextSize.y / Res.y };
	}
	float Interface::get_text_height(Font font, float size, float wrap) {
		Vector2 FontSize{ get_text_size(font, size * 2.f, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", wrap) };
		return FontSize.x;
	}
	Vector2 Interface::get_sprite_scale(float size) {
		ImVec2 Res{ resolution() };
		return { (Res.y / Res.x) * size, size };
	}
	ImVec2 Interface::get_text_scale(str text) {
		return { ImGui::CalcTextSize(text.c_str()).x / resolution().x, ImGui::CalcTextSize(text.c_str()).y / resolution().y};
	}
	ImVec2 Interface::get_scale_sprite(float size) {
		return { (static_cast<float>(resolution().y) / static_cast<float>(resolution().x)) * size, size };
	}
	float Interface::get_font_scale(float size) {
		return size * (resolution().x / 1920.f);
	}
	ImVec2 Interface::convert_to_pixels(ImVec2 value) {
		return resolution() * value;
	}
	ImVec2 Interface::convert_to_floating_point(ImVec2 value) {
		return resolution() / value;
	}
	Vector2 Interface::get_mouse_pos() {
		POINT point;
		GetCursorPos(&point);
		return { (float)point.x, (float)point.y };
	}

	void Interface::switch_to_submenu(u32 id) {
		for (auto&& sub : all_submenus) {
			if (sub->get_id() == id) {
				submenu_stack.push(sub.get());
				break;
			}
		}

		if (m_fade_on_enter) {
			g_fiber_pool.queue([=] {
				m_option_unselected_text_color.a = 0;
				m_option_selected_text_color.a = 0;
				while (m_option_unselected_text_color.a < 255) {
					m_option_unselected_text_color.a += 10;
					m_option_selected_text_color.a += 10;
					fiber::current()->wait(1ms);
				}
			});

		}
		
	}
}