#pragma once
#include "src/Utility/Types.h"
#include "src/framework/option_types/text_box.h"
#include "src/framework/submenu_types/abstract_submenu.h"
#include "src/framework/direct_x/Renderer.h"

namespace Base::Framework {
	inline const char* g_key_names[254] = {
"",
"F10",
"F10",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"BACKSPACE",
"TAB",
"TAB",
"TAB",
"NUM 5",
"ENTER",
"ENTER",
"ENTER",
"SHIFT",
"CTRL",
"ALT",
"ALT",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"ESC",
"ESC",
"ESC",
"ESC",
"ESC",
"SPACE",
"NUM 9",
"NUM 3",
"NUM 1",
"NUM 7",
"LEFT",
"UP",
"RIGHT",
"DOWN",
"NUM 2",
"NUM 2",
"NUM 2",
"NUM 2",
"NUM 0",
"DELETE",
"NUM DECIMAL",
"0",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"9",
"9",
"9",
"9",
"9",
"9",
"9",
"A",
"B",
"C",
"D",
"E",
"F",
"G",
"H",
"I",
"J",
"K",
"L",
"M",
"N",
"O",
"P",
"Q",
"R",
"S",
"T",
"U",
"V",
"W",
"X",
"Y",
"Z",
"Z",
"Z",
"Z",
"Z",
"Z",
"NUM 0",
"NUM 1",
"NUM 2",
"NUM 3",
"NUM 4",
"NUM 5",
"NUM 6",
"NUM 7",
"NUM 8",
"NUM 9",
"*",
"NUM PLUS",
"NUM PLUS",
"NUM SUB",
"NUM DECIMAL",
"/",
"F1",
"F2",
"F3",
"F4",
"F5",
"F6",
"F7",
"F8",
"F9",
"F10",
"F11",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"Pause",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SHIFT",
"RIGHT SHIFT",
"CTRL",
"CTRL",
"ALT",
"ALT",
"ALT",
"ALT",
"ALT",
"ALT",
"ALT",
"ALT",
"M",
"D",
"C",
"B",
"P",
"Q",
"J",
"G",
"G",
"G",
"G",
"F",
"F",
"F",
";",
"=",
",",
"-",
".",
"/",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"A",
"B",
"X",
"Y",
"Left Button",
"Right Button",
"Left Trigger",
"Right Trigger",
"Left Stick",
"Right Stick",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"[",
"null",
"]",
"ACUTE/CEDILLA",
"ACUTE/CEDILLA",
"ACUTE/CEDILLA",
"ACUTE/CEDILLA",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null"
	};
	struct bool_hotkey {
		int m_key;
		bool* m_pointer;
		str m_name;
		std::function<void()> m_on_disable;
	};
	struct button_hotkey {
		int m_key;
		std::function<void()> m_action;
		str m_name;
	};
	enum class Font : int32_t {
		RobotoRegular = 0,
		RobotoBold = 1,
		RobotoItalic = 2,
		Arial = 3,
		ArialBold = 4,
		ArialItalic = 5,
		ArialBoldItalic = 6,
		ArialBlack = 7,
		Tahoma = 8,
		Notifcation = 9,
	};
	enum class tab {
		none = -1,
		self = 0,
		network = 1,
		weapon = 2,
		vehicle = 3,
		spawner = 4,
		world = 5,
		teleport = 6,
		misc = 7,
		settings = 8,
		developer = 9,
		protections = 10,
	};
	struct rect {
		float m_top{};
		float m_bottom{};
		float m_left{};
		float m_right{};
	};
	class Interface {
	public:
		tab m_selected_tab{ tab::none };
		bool m_click_ui{ false };
		bool m_fade_on_enter{ false };

		template <typename submenu_type, typename ...targs>
		void add(targs&&... args) {
			if (m_click_ui) return;
			auto sub{ std::make_unique<submenu_type>(std::forward<targs>(args)...) };
			if (submenu_stack.empty()) {
				submenu_stack.push(sub.get());
			}
			all_submenus.push_back(std::move(sub));
		}

		template <typename t>
		t* get(u32 id) {
			for (auto&& sub : all_submenus) {
				if (sub->get_id() == id) {
					return (t*)sub.get();
				}
			}
			return (t*)nullptr;
		}
	public:
		void OnTick();
		void queue_sound(str name);

		bool m_disable_input{ false };
		float m_target = { 0.f };
		float m_current = { 0.f };
		float m_speed = { 0.10f };
		float m_menu_animation_speed{ 0.08f };

		float m_fadespeed = { 0.4281f };

		float m_bg_target = { 0.f };
		float m_bg_current = { 0.f };
	public:
		//choose thing
		std::vector<ccp> m_choose_vector;
		str m_choose_name{ "None" };
		int* m_choose_selected;
	public:
		//poisitons
		float m_width22 = 0.730;
		float m_height22 = 0.720;
		float m_xmill = 0.001;
		float m_pedx = 0.060;
		float m_pedyy = 1.680f;
		float m_pedy = -0.224;
		float m_xoffset = 1.080;
		float m_yoffset = -2.550;
		float m_zoffset = 0.130;

		bool m_opened{};
		float m_pos_x{ 0.12f };
		float m_pos_y{ 0.15f };
		float m_width{ 0.18f };
		int m_options_per_page{ 11 };
		bool m_sounds{ true };
		bool m_overlay_on{ true };
		bool m_using_keyboard{};
		bool m_toggle{ false };
		int m_current_option{};
		float m_current_coord{ m_lerped_pos_y };

		float m_lerped_pos_x{ 0 };
		float m_lerped_pos_y{ 0 };
	public:
		// Animations
		bool m_fly_in{ false };
		bool m_menu_opening_animation = false;
		bool m_menu_closing_animation = false;
		int m_menu_alpha = 255;
		int m_g_menu_opacity = m_option_unselected_background_color.a;
	public:
		// Input
		i32 m_open_delay{ 200 };
		i32 m_back_delay{ 300 };
		i32 m_enter_delay{ 300 };
		i32 m_vertical_delay{ 120 };
		i32 m_horizontal_delay{ 120 };
	public:
		// Header
		bool m_has_header_loaded{ false };
		str m_header_image {};
		float m_header_height{ 0.1f };
		float m_header_text_size{ 1.f };
		Font m_header_font{ Font::RobotoBold };
		color<int> m_header_background_color{ 17, 17, 17, 255 };
		color<int> m_header_image_color{ 255, 255, 255, 255 };
		color<int> m_header_text_color{ 255, 255, 255, 255 };
	public:
		// Smooth Scroll
		float m_smooth_scroll_speed{ 0.13f };
		bool m_smooth_scroll_moves_text{ false };

		//Class
		bool m_scroll_forward{ false };
		bool m_scroll_backward{ false };
	public:
		//tooltips
		str m_tooltip{};
		std::vector<str> m_tooltips{};
		void add_tooltip(str str) {
			m_tooltips.push_back(str);
		}
		void add_tooltips_from_file(fs::path file, u32 numberOfTooltipsToAdd = -1) {
			std::ifstream f(file);
			str l{};
			std::vector<str> buf{};
			while (std::getline(f, l)) {
				buf.push_back(l);
			}
			for (u32 i{}; i != buf.size(); ++i) {
				m_tooltips.emplace_back(buf[i]);
			}
			f.close();
		}
		void remove_tooltip(str key) {
			for (size_t i{ m_tooltips.size() }; i; --i) {
				if (!m_tooltips[i].compare(key.data())) {
					m_tooltips.erase(m_tooltips.begin() + i);
					break;
				}
			}
		}
		color<int> m_open_key_text_color{ 17, 17, 17, 255 };
		color<int> m_tooltip_color{ 255, 255, 255, 255 };
		Font m_open_key_text_font{ Font::ArialBold };
		Font m_tooltip_font{ Font::Arial };
		float m_open_key_text_size{ 0.95f };
		float m_tooltip_text_size{ 0.95f };
	public:
		// Submenu bar
		float m_submenu_bar_height{ 0.035f };
		float m_submenu_bar_text_size{ 1 };
		Font m_submenu_bar_font{ Font::ArialBold };
		float m_submenu_bar_padding{ 2.1f };
		color<int> m_submenu_bar_background_color{ 0, 0, 0, 255 };
		color<int> m_submenu_bar_text_color{ 255, 255, 255, 255 };
	public:
		// Notifications
		Font m_notifications_font{ Font::ArialBold };
		Font m_notifications2_font{ Font::Notifcation };
		float m_notifications_text_size{ 0.81f };
		float m_notifications_text_size2{ 0.67f };
	public:
		// Options
		bool m_rounded_options{ false };
		float m_rounded_options_mult{ 10 };
		Font m_break_font{ Font::ArialItalic };
		float m_toggle_size{ 0.035f };
		float m_option_height{ 0.029 };
		float m_option_text_size{ 0.85f };
		float m_submenu_arrow_size{ 0.02f };
		float m_option_break_size{ 0.90f };
		float m_option_icon_size{ 0.027f };
		float m_submenu_rect_width{ 10.f };
		color<int> m_toggle_on_color{ 0, 0, 0, 255 };
		color<int> m_toggle_off_color{ 255, 255, 255, 255 };
		color<int> m_submenu_rect_color{ 94, 94, 94, 180 };
		Font m_option_font{ Font::Arial };
		float m_option_padding{ 2.1f };
		color<int> m_option_selected_sprite_color{ 10, 10, 10, 255 };
		color<int> m_option_unselected_sprite_color{ 255, 255, 255, 255 };
		color<int> m_option_selected_text_color{ 255, 255, 255, 255 };
		color<int> m_option_unselected_text_color{ 175, 175, 175, 255 };
		color<int> m_option_selected_background_color{ 20, 20, 20, 255 };
		color<int> m_option_unselected_background_color{ 0, 0, 0, 190 };
		color<int> m_red_color{ 255, 0, 0, 255 };
		float m_toggle_size_x_offset{ 0 };
		float m_toggle_size_y_offset{ 0 };
	public:
		// Footer
		float m_footer_sprite_size{ 0.025f };
		float m_footer_height{ 0.030f };
		color<int> m_footer_background_color{ 0, 0, 0, 255 };
		color<int> m_footer_sprite_color{ 255, 255, 255, 255 };
	public:
		// Description
		float m_description_height_padding{ 0.01f };
		float m_description_line_height = 0.004f;
		float m_description_height{ 0.030f };
		float m_description_text_size{ 0.93f };
		color<int> m_description_line_color{ 255, 255, 255, 255 };
		Font m_description_font{ Font::Arial };
		color<int> m_description_background_color{ 0, 0, 0, 190 };
		color<int> m_description_text_color{ 255, 255, 255, 255 };
		float m_description_sprite_size{ 0.025f };
		float m_description_padding{ 2.1f };
		color<int> m_description_sprite_color{ 255, 255, 255, 255 };
	public:
		//fov
		bool m_aimbot_is_on{ false };
		bool m_aimbot{ true };
		float m_aimbot_fov{ 150.f };
		bool m_color_picker_open{};
	public:
		// Overlay
		float m_overlay_x = 0.105f;
		float m_overlay_y = 0.03f;
		float m_overlay_y2 = m_overlay_y + 0.07;
		float m_overlay_height = 0.036f;
		float m_overlay_line_height = 0.0035f;
		float m_overlay_padding = 2.1f;
		float m_overlay_width = 0.20f;
		color<int> m_overlay_color{ 27, 28, 31, 255 };
		float m_overlay_text_size{ 0.30f };
		color<int> m_overlay_text_color{ 193, 192, 193, 255 };
		color<int> m_overlay_line_color{ 255, 255, 255, 255 };
		Font m_overlay_font{ Font::Arial };
	public:
		// Player Info
		float m_player_info_x = 0.22f;
		float m_player_info_line_height = 0.0035f;
		float m_player_info_padding = 2.1f;
		float m_player_info_height = 0.1f;
		float m_player_info_width = 0.20f;
		color<int> m_player_info_color{ 0, 0, 0, 190 };
		float m_player_info_text_size{ 0.30f };
		color<int> m_player_info_text_color{ 193, 192, 193, 255 };
		color<int> m_player_info_line_color{ 193, 192, 193, 255 };
		Font m_player_info_font{ Font::Arial };

		str m_keyboard_test{};
		bool m_is_keyboard_input_box_visible{};

		int m_flag{ 0 };

		bool m_command_box_opened{ false };
		char m_command_box_input[256];

		str m_default_theme_name;
		str m_theme_name;
		struct rounding {
			float m_footer{ 10.f };
			float m_header{ 10.f };
		} m_rounding;
		struct header {
			bool m_uses_gradiant{ true };
		} m_header;

		struct footer {
			bool m_enabled{ true };
			bool m_dynamic{};

			bool m_freeze{};
			std::vector<ccp> m_freeze_state{ "Both", "Up", "Down" };
			int m_freeze_selected{ 0 };
		} m_footer;

		struct chooses {
			bool m_show_count{};

			std::vector<ccp> m_anchor{ "Left", "Right" };
			int m_anchor_selected{ 0 };
			bool m_show_brackets{};
		} m_chooses;

		struct scrollbar {
			bool m_enabled{ false };

			float m_width{ 0.007 };
			float m_width2{ 0.003 };
			float m_offset{ 0.11 };
			float m_bar_offset{ 0 };

			std::vector<ccp> m_type{ "Option Count", "Selected Option" };
			int m_type_pos{ 0 };
		} m_scrollbar;

		struct options {
			bool m_bar{ true };
			
			color<int> m_first_color{ 240, 0, 0, 255 };
			color<int> m_second_color{ 255, 0, 0, 255 };

			bool m_gradiant_selected_text{ false };
		} m_options;
	public:
		bool m_tracers{ false };
		bool m_lines{ true };
	public:
		void load_variables_from_json(const str& filePath);
		void save_variables_to_json(const str& themeName);
		void edit_variables_to_json(const str& filePath);
		void load_settings_on_inject(const str& filePath);
		void save_settings_on_unload();
		void draw_left_text(str text, float x, float y, float size, Font font, color<int> color, bool outline, bool shadow, float wrap = -1.f, bool is_gradient = false);
		ImVec2 get_text_scale(str text);
		void draw_rect(float x, float y, float width, float height, color<int> color, ImDrawList* drawlist = ImGui::GetBackgroundDrawList(), float rounding = 0.f, ImDrawFlags flags = ImDrawFlags_None);
		void draw_gradiant_rect(float x, float y, float width, float height, color<int> colorr, color<int> ccolor2, ImDrawList* drawlist = ImGui::GetBackgroundDrawList());
		void draw_gradiant_rect2(float x, float y, float width, float height, color<int> colorr, color<int> ccolor2, ImDrawList* drawlist = ImGui::GetBackgroundDrawList());
		void draw_player_info(std::int32_t player, bool show);
		void draw_vehicle_info(str name);
		void switch_to_submenu(u32 id);
		ImVec2 convert_to_pixels(ImVec2 value);
		ImVec2 convert_to_floating_point(ImVec2 value);
		void draw_background(abstract_submenu* sub);
		Vector2 get_text_size(Font font, float size, str text, float wrap = -1.f);
		void smooth_lerp(float* current, float target, float speed);
		void bob_value(float* val, float min, float max, float increment);
		rect get_rect_bounds(float base_x, float base_y, float height, float width);
		void draw_sprite(ImTextureID id, float x, float y, float width, float height, color<int> color, float rotation, ImDrawList* drawlist = ImGui::GetBackgroundDrawList(), float rounding = 0.f, ImDrawFlags flags = ImDrawFlags_None);
		void draw_sprite_round(ImTextureID id, float x, float y, float width, float height, color<int> color, ImDrawList* drawlist, float rounding, ImDrawFlags flags);
		void draw_sprite(str dict, str texture, float x, float y, float width, float height, color<int> color, float rotation, ImDrawList* drawlist = ImGui::GetBackgroundDrawList(), float rounding = 0.f, ImDrawFlags flags = ImDrawFlags_None);
	private:
		void check_for_input();
		void handle_input();
		void reset_input();

		void draw_header();
		void draw_submenu_bar(abstract_submenu* sub);
		void draw_option(abstract_option* opt, abstract_submenu* sub, bool selected);
		void draw_footer();
		void draw_description();
		void draw_overlay();
		void draw_tooltips();
		void draw_lines();
		void draw_scrollbar(abstract_submenu* sub);


		void flip_through_frames(int delay);

		void draw_ram_text(const str& text, ImVec2 pos, float size, ImFont* font, color<int> color, bool outline, bool shadow, float wrap = -1.f, bool is_gradient = false);
		void draw_centered_text(str text, float x, float y, float size, Font font, color<int> color, bool outline, bool shadow, float wrap = -1.f, bool is_gradient = false);
		void draw_right_text(str text, float x, float y, float size, Font font, color<int> color, bool outline, bool shadow, float wrap = -1.f);
		ImFont* get_font_from_id(Font font);
		Vector2 get_sprite_scale(float size);
		Vector2 get_mouse_pos();
		float get_font_scale(float size);
		float get_text_height(Font font, float size, float wrap = -1.f);
		ImVec2 get_scale_sprite(float size);
	public:
		std::unordered_map<u32, bool_hotkey> m_bool_hotkeys{};
		std::unordered_map<u32, button_hotkey> m_button_hotkeys{};
		void update_hotkeys();
	public:
		bool m_open_key_pressed;
		bool m_back_key_pressed;
		bool m_enter_key_pressed;
		bool m_up_key_pressed;
		bool m_down_key_pressed;
		bool m_left_key_pressed;
		bool m_right_key_pressed;

		bool m_hotkey_key_pressed;
		bool m_hotkey_pressed;
		int m_last_key_pressed{ 86 };

		float m_draw_base_y;

		std::vector<std::unique_ptr<abstract_submenu>> all_submenus;
		std::stack<abstract_submenu*, std::vector<abstract_submenu*>> submenu_stack;
	};
}

namespace Base {
	inline std::unique_ptr<Framework::Interface> g_interface{};
	template <typename OptionType, typename ...TArgs>
	void add_option(TArgs&&... args) {
		if (g_interface->m_click_ui) return;
		Framework::g_options.push_back(std::make_unique<OptionType>(std::forward<TArgs>(args)...));
	}
}