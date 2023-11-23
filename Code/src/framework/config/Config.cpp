#include "src/framework/framework.h"
#include "src/Utility/Timer.h"
#include "src/Natives/Natives.h"
#include "src/fiber/fiber_helper.h"
#include "src/framework/direct_x/renderer.h"
#include <src/rage/draw_handlers/pgDictionary.hpp>
#include <src/rage/draw_handlers/grcTexture.hpp>
#include "src/Utility/Setting.h"
#include "src/Utility/Timer.h"
#include <fstream>
#include <iostream>
#include <JSON/json.hpp>

using json = nlohmann::json;

namespace Base::Framework {
	std::string GetThemesDirectory() {
		const char* homeDir = std::getenv("APPDATA");
			std::string themesDir = "C:\\Native\\Themes\\";
			return themesDir;
		return "";
	}
	std::string GetNativeDirectory() {
		const char* homeDir = std::getenv("APPDATA");
		std::string themesDir = "C:\\Native\\";
		return themesDir;
		return "";
	}

	void Interface::load_variables_from_json(const std::string& filePath) {
		std::ifstream file(filePath);
		if (file.is_open()) {
			json json_data = json::parse(file);
			// Load variables from JSON
			g_interface->m_opened = json_data["opened"];
			g_interface->m_pos_x = json_data["pos_x"];
			g_interface->m_pos_y = json_data["pos_y"];
			g_interface->m_width = json_data["width"];
			g_interface->m_options_per_page = json_data["options_per_page"];
			g_interface->m_sounds = json_data["sounds"];
			g_interface->m_open_delay = json_data["open_delay"];
			g_interface->m_back_delay = json_data["back_delay"];
			g_interface->m_enter_delay = json_data["enter_delay"];
			g_interface->m_vertical_delay = json_data["vertical_delay"];
			g_interface->m_horizontal_delay = json_data["horizontal_delay"];
			g_interface->m_has_header_loaded = json_data["has_header_loaded"];
			g_interface->m_header_image = json_data["header_image"];
			g_interface->m_header_height = json_data["header_height"];
			g_interface->m_header_text_size = json_data["header_text_size"];
			g_interface->m_header_font = static_cast<Font>(json_data["header_font"]);
			g_interface->m_header_background_color = { json_data["header_background_color"][0], json_data["header_background_color"][1], json_data["header_background_color"][2], json_data["header_background_color"][3] };
			g_interface->m_header_text_color = { json_data["header_text_color"][0], json_data["header_text_color"][1], json_data["header_text_color"][2], json_data["header_text_color"][3] };
			g_interface->m_smooth_scroll_speed = json_data["smooth_scroll_speed"];
			g_interface->m_submenu_bar_height = json_data["submenu_bar_height"];
			g_interface->m_submenu_bar_text_size = json_data["submenu_bar_text_size"];
			g_interface->m_submenu_bar_font = static_cast<Font>(json_data["submenu_bar_font"]);
			g_interface->m_submenu_bar_padding = json_data["submenu_bar_padding"];
			g_interface->m_submenu_bar_background_color = { json_data["submenu_bar_background_color"][0], json_data["submenu_bar_background_color"][1], json_data["submenu_bar_background_color"][2], json_data["submenu_bar_background_color"][3] };
			g_interface->m_submenu_bar_text_color = { json_data["submenu_bar_text_color"][0], json_data["submenu_bar_text_color"][1], json_data["submenu_bar_text_color"][2], json_data["submenu_bar_text_color"][3] };
			g_interface->m_break_font = static_cast<Font>(json_data["break_font"]);
			g_interface->m_toggle_size = json_data["toggle_size"];
			g_interface->m_option_height = json_data["option_height"];
			g_interface->m_option_text_size = json_data["option_text_size"];
			g_interface->m_submenu_arrow_size = json_data["submenu_arrow_size"];
			g_interface->m_option_break_size = json_data["option_break_size"];
			g_interface->m_option_icon_size = json_data["option_icon_size"];
			g_interface->m_submenu_rect_width = json_data["submenu_rect_width"];
			g_interface->m_toggle_on_color = { json_data["toggle_on_color"][0], json_data["toggle_on_color"][1], json_data["toggle_on_color"][2], json_data["toggle_on_color"][3] };
			g_interface->m_toggle_off_color = { json_data["toggle_off_color"][0], json_data["toggle_off_color"][1], json_data["toggle_off_color"][2], json_data["toggle_off_color"][3] };
			g_interface->m_submenu_rect_color = { json_data["submenu_rect_color"][0], json_data["submenu_rect_color"][1], json_data["submenu_rect_color"][2], json_data["submenu_rect_color"][3] };
			g_interface->m_option_font = static_cast<Font>(json_data["option_font"]);
			g_interface->m_option_padding = json_data["option_padding"];
			g_interface->m_option_selected_sprite_color = { json_data["option_selected_sprite_color"][0], json_data["option_selected_sprite_color"][1], json_data["option_selected_sprite_color"][2], json_data["option_selected_sprite_color"][3] };
			g_interface->m_option_unselected_sprite_color = { json_data["option_unselected_sprite_color"][0], json_data["option_unselected_sprite_color"][1], json_data["option_unselected_sprite_color"][2], json_data["option_unselected_sprite_color"][3] };
			g_interface->m_option_selected_text_color = { json_data["option_selected_text_color"][0], json_data["option_selected_text_color"][1], json_data["option_selected_text_color"][2], json_data["option_selected_text_color"][3] };
			g_interface->m_option_unselected_text_color = { json_data["option_unselected_text_color"][0], json_data["option_unselected_text_color"][1], json_data["option_unselected_text_color"][2], json_data["option_unselected_text_color"][3] };
			g_interface->m_option_selected_background_color = { json_data["option_selected_background_color"][0], json_data["option_selected_background_color"][1], json_data["option_selected_background_color"][2], json_data["option_selected_background_color"][3] };
			g_interface->m_option_unselected_background_color = { json_data["option_unselected_background_color"][0], json_data["option_unselected_background_color"][1], json_data["option_unselected_background_color"][2], json_data["option_unselected_background_color"][3] };
			g_interface->m_footer_sprite_size = json_data["footer_sprite_size"];
			g_interface->m_footer_height = json_data["footer_height"];
			g_interface->m_footer_background_color = { json_data["footer_background_color"][0], json_data["footer_background_color"][1], json_data["footer_background_color"][2], json_data["footer_background_color"][3] };
			g_interface->m_footer_sprite_color = { json_data["footer_sprite_color"][0], json_data["footer_sprite_color"][1], json_data["footer_sprite_color"][2], json_data["footer_sprite_color"][3] };
			g_interface->m_description_height_padding = json_data["description_height_padding"];
			g_interface->m_description_line_height = json_data["description_line_height"];
			g_interface->m_description_height = json_data["description_height"];
			g_interface->m_description_text_size = json_data["description_text_size"];
			g_interface->m_description_line_color = { json_data["description_line_color"][0], json_data["description_line_color"][1], json_data["description_line_color"][2], json_data["description_line_color"][3] };
			g_interface->m_description_font = static_cast<Font>(json_data["description_font"]);
			g_interface->m_description_background_color = { json_data["description_background_color"][0], json_data["description_background_color"][1], json_data["description_background_color"][2], json_data["description_background_color"][3] };
			g_interface->m_description_text_color = { json_data["description_text_color"][0], json_data["description_text_color"][1], json_data["description_text_color"][2], json_data["description_text_color"][3] };
			g_interface->m_description_sprite_size = json_data["description_sprite_size"];
			g_interface->m_description_padding = json_data["description_padding"];
			g_interface->m_description_sprite_color = { json_data["description_sprite_color"][0], json_data["description_sprite_color"][1], json_data["description_sprite_color"][2], json_data["description_sprite_color"][3] };
			g_interface->m_overlay_x = json_data["overlay_x"];
			g_interface->m_overlay_y = json_data["overlay_y"];
			g_interface->m_overlay_height = json_data["overlay_height"];
			g_interface->m_overlay_line_height = json_data["overlay_line_height"];
			g_interface->m_overlay_padding = json_data["overlay_padding"];
			g_interface->m_overlay_width = json_data["overlay_width"];

			g_interface->m_overlay_color = { json_data["m_OverlayColor"][0], json_data["m_OverlayColor"][1], json_data["m_OverlayColor"][2], json_data["m_OverlayColor"][3] };
			g_interface->m_overlay_text_size = json_data["m_OverlayTextSize"];
			g_interface->m_overlay_text_color = { json_data["overlay_text_color"][0], json_data["overlay_text_color"][1], json_data["overlay_text_color"][2], json_data["overlay_text_color"][3] };
			g_interface->m_overlay_line_color = { json_data["m_OverlayLineColor"][0], json_data["m_OverlayLineColor"][1], json_data["m_OverlayLineColor"][2], json_data["m_OverlayLineColor"][3] };
			g_interface->m_overlay_font = static_cast<Font>(json_data["overlay_font"]);
			g_interface->m_open_key_text_color = { json_data["m_OpenKeyTextColor"][0], json_data["m_OpenKeyTextColor"][1], json_data["m_OpenKeyTextColor"][2], json_data["m_OpenKeyTextColor"][3] };
			g_interface->m_open_key_text_size = json_data["m_OpenKeyTextSize"];
			g_interface->m_open_key_text_font = static_cast<Font>(json_data["overlay_font"]);
			g_interface->m_tooltip_color = { json_data["tooltipColor"][0], json_data["tooltipColor"][1], json_data["tooltipColor"][2], json_data["tooltipColor"][3] };
			g_interface->m_tooltip_text_size = json_data["tooltipTextSize"];
			g_interface->m_tooltip_font = static_cast<Font>(json_data["tooltipFont"]);

			LOG(Info, "Theme loaded from JSON.");
			file.close();
		}
		if (!g_interface->m_header_image.empty()) {
			g_interface->m_has_header_loaded = false;
			fs::path basePath{ fs::path("C:\\Native\\") };
			fs::path headerPath{ fs::path(basePath).append("Headers").append(g_interface->m_header_image) };
			g_renderer->m_header.clear();
			g_renderer->header_frame = 0;
			if (headerPath.extension().string() == ".gif") {
				g_renderer->m_header = g_renderer->create_gif_texture(fs::path(headerPath));
			}
			else {
				g_renderer->m_header.insert({ 0, { 0, g_renderer->create_texture(fs::path(headerPath)).first } });
			}
			g_interface->m_has_header_loaded = true;
		}
	}

	void Interface::load_settings_on_inject(const std::string& filePath) {
		std::ifstream file(filePath);
		if (file.is_open()) {
			json json_data = json::parse(file);
			g_interface->m_default_theme_name = json_data["default_theme"];
			file.close();
		}
		else {
			LOG(Warn, "Failed to load default theme");
		}
		
	}

	void Interface::save_variables_to_json(const std::string& themeName) {
			std::string theme_directory = GetThemesDirectory();
			std::string json_file_path = theme_directory + g_interface->m_theme_name + ".json";
			json m_json_data;
			m_json_data["opened"] = g_interface->m_opened;
			m_json_data["pos_x"] = g_interface->m_pos_x;
			m_json_data["pos_y"] = g_interface->m_pos_y;
			m_json_data["width"] = g_interface->m_width;
			m_json_data["m_options_per_page"] = g_interface->m_options_per_page;
			m_json_data["sounds"] = g_interface->m_sounds;
			m_json_data["m_open_delay"] = g_interface->m_open_delay;
			m_json_data["m_back_delay"] = g_interface->m_back_delay;
			m_json_data["m_enter_delay"] = g_interface->m_enter_delay;
			m_json_data["m_vertical_delay"] = g_interface->m_vertical_delay;
			m_json_data["m_horizontal_delay"] = g_interface->m_horizontal_delay;
			m_json_data["has_header_loaded"] = g_interface->m_has_header_loaded;
			m_json_data["m_header_image"] = g_interface->m_header_image;
			m_json_data["m_header_height"] = g_interface->m_header_height;
			m_json_data["m_header_text_size"] = g_interface->m_header_text_size;
			m_json_data["m_header_font"] = static_cast<int>(g_interface->m_header_font);
			m_json_data["m_header_background_color"] = { g_interface->m_header_background_color.r, g_interface->m_header_background_color.g, g_interface->m_header_background_color.b, g_interface->m_header_background_color.a };
			m_json_data["m_header_text_color"] = { g_interface->m_header_text_color.r, g_interface->m_header_text_color.g, g_interface->m_header_text_color.b, g_interface->m_header_text_color.a };
			m_json_data["m_smooth_scroll_speed"] = g_interface->m_smooth_scroll_speed;
			m_json_data["m_submenu_bar_height"] = g_interface->m_submenu_bar_height;
			m_json_data["m_submenu_bar_text_size"] = g_interface->m_submenu_bar_text_size;
			m_json_data["m_submenu_bar_font"] = static_cast<int>(g_interface->m_submenu_bar_font);
			m_json_data["m_submenu_bar_padding"] = g_interface->m_submenu_bar_padding;
			m_json_data["m_submenu_bar_background_color"] = { g_interface->m_submenu_bar_background_color.r, g_interface->m_submenu_bar_background_color.g, g_interface->m_submenu_bar_background_color.b, g_interface->m_submenu_bar_background_color.a };
			m_json_data["m_submenu_bar_text_color"] = { g_interface->m_submenu_bar_text_color.r, g_interface->m_submenu_bar_text_color.g, g_interface->m_submenu_bar_text_color.b, g_interface->m_submenu_bar_text_color.a };
			m_json_data["m_break_font"] = static_cast<int>(g_interface->m_break_font);
			m_json_data["m_toggle_size"] = g_interface->m_toggle_size;
			m_json_data["m_option_height"] = g_interface->m_option_height;
			m_json_data["m_option_text_size"] = g_interface->m_option_text_size;
			m_json_data["m_submenu_arrow_size"] = g_interface->m_submenu_arrow_size;
			m_json_data["m_option_break_size"] = g_interface->m_option_break_size;
			m_json_data["m_option_icon_size"] = g_interface->m_option_icon_size;
			m_json_data["m_submenu_rect_width"] = g_interface->m_submenu_rect_width;
			m_json_data["m_toggle_on_color"] = { g_interface->m_toggle_on_color.r, g_interface->m_toggle_on_color.g, g_interface->m_toggle_on_color.b, g_interface->m_toggle_on_color.a };
			m_json_data["m_toggle_off_color"] = { g_interface->m_toggle_off_color.r, g_interface->m_toggle_off_color.g, g_interface->m_toggle_off_color.b, g_interface->m_toggle_off_color.a };
			m_json_data["m_submenu_rect_color"] = { g_interface->m_submenu_rect_color.r, g_interface->m_submenu_rect_color.g, g_interface->m_submenu_rect_color.b, g_interface->m_submenu_rect_color.a };
			m_json_data["m_option_font"] = static_cast<int>(g_interface->m_option_font);
			m_json_data["m_option_padding"] = g_interface->m_option_padding;
			m_json_data["m_option_selected_sprite_color"] = { g_interface->m_option_selected_sprite_color.r, g_interface->m_option_selected_sprite_color.g, g_interface->m_option_selected_sprite_color.b, g_interface->m_option_selected_sprite_color.a };
			m_json_data["m_option_unselected_sprite_color"] = { g_interface->m_option_unselected_sprite_color.r, g_interface->m_option_unselected_sprite_color.g, g_interface->m_option_unselected_sprite_color.b, g_interface->m_option_unselected_sprite_color.a };
			m_json_data["m_option_selected_text_color"] = { g_interface->m_option_selected_text_color.r, g_interface->m_option_selected_text_color.g, g_interface->m_option_selected_text_color.b, g_interface->m_option_selected_text_color.a };
			m_json_data["m_option_unselected_text_color"] = { g_interface->m_option_unselected_text_color.r, g_interface->m_option_unselected_text_color.g, g_interface->m_option_unselected_text_color.b, g_interface->m_option_unselected_text_color.a };
			m_json_data["m_option_selected_background_color"] = { g_interface->m_option_selected_background_color.r, g_interface->m_option_selected_background_color.g, g_interface->m_option_selected_background_color.b, g_interface->m_option_selected_background_color.a };
			m_json_data["m_option_unselected_background_color"] = { g_interface->m_option_unselected_background_color.r, g_interface->m_option_unselected_background_color.g, g_interface->m_option_unselected_background_color.b, g_interface->m_option_unselected_background_color.a };
			m_json_data["m_footer_sprite_size"] = g_interface->m_footer_sprite_size;
			m_json_data["m_footer_height"] = g_interface->m_footer_height;
			m_json_data["m_footer_background_color"] = { g_interface->m_footer_background_color.r, g_interface->m_footer_background_color.g, g_interface->m_footer_background_color.b, g_interface->m_footer_background_color.a };
			m_json_data["m_footer_sprite_color"] = { g_interface->m_footer_sprite_color.r, g_interface->m_footer_sprite_color.g, g_interface->m_footer_sprite_color.b, g_interface->m_footer_sprite_color.a };
			m_json_data["m_description_height_padding"] = g_interface->m_description_height_padding;
			m_json_data["m_description_line_height"] = g_interface->m_description_line_height;
			m_json_data["m_description_height"] = g_interface->m_description_height;
			m_json_data["m_description_text_size"] = g_interface->m_description_text_size;
			m_json_data["m_description_line_color"] = { g_interface->m_description_line_color.r, g_interface->m_description_line_color.g, g_interface->m_description_line_color.b, g_interface->m_description_line_color.a };
			m_json_data["m_description_font"] = static_cast<int>(g_interface->m_description_font);
			m_json_data["m_description_background_color"] = { g_interface->m_description_background_color.r, g_interface->m_description_background_color.g, g_interface->m_description_background_color.b, g_interface->m_description_background_color.a };
			m_json_data["m_description_text_color"] = { g_interface->m_description_text_color.r, g_interface->m_description_text_color.g, g_interface->m_description_text_color.b, g_interface->m_description_text_color.a };
			m_json_data["m_description_sprite_size"] = g_interface->m_description_sprite_size;
			m_json_data["m_description_padding"] = g_interface->m_description_padding;
			m_json_data["m_description_sprite_color"] = { g_interface->m_description_sprite_color.r, g_interface->m_description_sprite_color.g, g_interface->m_description_sprite_color.b, g_interface->m_description_sprite_color.a };
			m_json_data["m_overlay_x"] = g_interface->m_overlay_x;
			m_json_data["m_overlay_y"] = g_interface->m_overlay_y;
			m_json_data["m_overlay_height"] = g_interface->m_overlay_height;
			m_json_data["m_overlay_line_height"] = g_interface->m_overlay_line_height;
			m_json_data["m_overlay_padding"] = g_interface->m_overlay_padding;
			m_json_data["m_overlay_width"] = g_interface->m_overlay_width;
			m_json_data["m_overlay_color"] = { g_interface->m_overlay_color.r, g_interface->m_overlay_color.g, g_interface->m_overlay_color.b, g_interface->m_overlay_color.a };
			m_json_data["m_overlay_text_size"] = g_interface->m_overlay_text_size;
			m_json_data["m_overlay_text_color"] = { g_interface->m_overlay_text_color.r, g_interface->m_overlay_text_color.g, g_interface->m_overlay_text_color.b, g_interface->m_overlay_text_color.a };
			m_json_data["m_overlay_line_color"] = { g_interface->m_overlay_line_color.r, g_interface->m_overlay_line_color.g, g_interface->m_overlay_line_color.b, g_interface->m_overlay_line_color.a };
			m_json_data["m_overlay_font"] = static_cast<int>(g_interface->m_overlay_font);
			m_json_data["m_open_key_text_color"] = { g_interface->m_open_key_text_color.r, g_interface->m_open_key_text_color.g, g_interface->m_open_key_text_color.b, g_interface->m_open_key_text_color.a };
			m_json_data["m_open_key_text_size"] = g_interface->m_open_key_text_size;
			m_json_data["m_open_key_text_font"] = static_cast<int>(g_interface->m_open_key_text_font);
			m_json_data["m_tooltip_color"] = { g_interface->m_tooltip_color.r, g_interface->m_tooltip_color.g, g_interface->m_tooltip_color.b, g_interface->m_tooltip_color.a };
			m_json_data["m_tooltip_text_size"] = g_interface->m_tooltip_text_size;
			m_json_data["m_tooltip_font"] = static_cast<int>(g_interface->m_tooltip_font);


			std::ofstream file(json_file_path);
			if (file.is_open()) {
				file << m_json_data.dump(4);
				LOG(Info, "Theme Created.");
				file.close();
			}
			else {
				LOG(Fatal, "Failed to create theme.");
			}
	}

	void Interface::save_settings_on_unload() {
		std::string theme_directory = GetNativeDirectory();
		std::string jsonFilePath = theme_directory + "Settings.json";
		json json_data;
		json_data["default_theme"] = g_interface->m_default_theme_name;

		std::ofstream file(jsonFilePath);
		if (file.is_open()) {
			file << json_data.dump(4);
			file.close();
		}
	}

	void Interface::edit_variables_to_json(const std::string& file_path) {
		std::ifstream file(file_path);
		json json_data;

		// Store variables in JSON
		json_data["opened"] = m_opened;
		json_data["pos_x"] = m_pos_x;
		json_data["pos_y"] = m_pos_y;
		json_data["width"] = m_width;
		json_data["m_options_per_page"] = m_options_per_page;
		json_data["sounds"] = m_sounds;
		json_data["m_open_delay"] = m_open_delay;
		json_data["m_back_delay"] = m_back_delay;
		json_data["m_enter_delay"] = m_enter_delay;
		json_data["m_vertical_delay"] = m_vertical_delay;
		json_data["m_horizontal_delay"] = m_horizontal_delay;
		json_data["has_header_loaded"] = m_has_header_loaded;
		json_data["header_image"] = m_header_image;
		json_data["header_height"] = m_header_height;
		json_data["header_text_size"] = m_header_text_size;
		json_data["header_font"] = static_cast<int>(m_header_font);
		json_data["header_background_color"] = { m_header_background_color.r, m_header_background_color.g, m_header_background_color.b, m_header_background_color.a };
		json_data["header_text_color"] = { m_header_text_color.r, m_header_text_color.g, m_header_text_color.b, m_header_text_color.a };
		json_data["smooth_scroll_speed"] = m_smooth_scroll_speed;
		json_data["submenu_bar_height"] = m_submenu_bar_height;
		json_data["m_submenu_bar_text_size"] = m_submenu_bar_text_size;
		json_data["m_submenu_bar_font"] = static_cast<int>(m_submenu_bar_font);
		json_data["submenu_bar_padding"] = m_submenu_bar_padding;
		json_data["submenu_bar_background_color"] = { m_submenu_bar_background_color.r, m_submenu_bar_background_color.g, m_submenu_bar_background_color.b, m_submenu_bar_background_color.a };
		json_data["submenu_bar_text_color"] = { m_submenu_bar_text_color.r, m_submenu_bar_text_color.g, m_submenu_bar_text_color.b, m_submenu_bar_text_color.a };
		json_data["break_font"] = static_cast<int>(m_break_font);
		json_data["toggle_size"] = m_toggle_size;
		json_data["option_height"] = m_option_height;
		json_data["option_text_size"] = m_option_text_size;
		json_data["submenu_arrow_size"] = m_submenu_arrow_size;
		json_data["option_break_size"] = m_option_break_size;
		json_data["m_option_icon_size"] = m_option_icon_size;
		json_data["m_submenu_rect_width"] = m_submenu_rect_width;
		json_data["m_toggle_on_color"] = { m_toggle_on_color.r, m_toggle_on_color.g, m_toggle_on_color.b, m_toggle_on_color.a };
		json_data["m_toggle_off_color"] = { m_toggle_off_color.r, m_toggle_off_color.g, m_toggle_off_color.b, m_toggle_off_color.a };
		json_data["m_submenu_rect_color"] = { m_submenu_rect_color.r, m_submenu_rect_color.g, m_submenu_rect_color.b, m_submenu_rect_color.a };
		json_data["option_font"] = static_cast<int>(m_option_font);
		json_data["option_padding"] = m_option_padding;
		json_data["m_option_selected_sprite_color"] = { m_option_selected_sprite_color.r, m_option_selected_sprite_color.g, m_option_selected_sprite_color.b, m_option_selected_sprite_color.a };
		json_data["m_option_unselected_sprite_color"] = { m_option_unselected_sprite_color.r, m_option_unselected_sprite_color.g, m_option_unselected_sprite_color.b, m_option_unselected_sprite_color.a };
		json_data["option_selected_text_color"] = { m_option_selected_text_color.r, m_option_selected_text_color.g, m_option_selected_text_color.b, m_option_selected_text_color.a };
		json_data["option_unselected_text_color"] = { m_option_unselected_text_color.r, m_option_unselected_text_color.g, m_option_unselected_text_color.b, m_option_unselected_text_color.a };
		json_data["option_selected_background_color"] = { m_option_selected_background_color.r, m_option_selected_background_color.g, m_option_selected_background_color.b, m_option_selected_background_color.a };
		json_data["option_unselected_background_color"] = { m_option_unselected_background_color.r, m_option_unselected_background_color.g, m_option_unselected_background_color.b, m_option_unselected_background_color.a };
		json_data["footer_sprite_size"] = m_footer_sprite_size;
		json_data["footer_height"] = m_footer_height;
		json_data["footer_background_color"] = { m_footer_background_color.r, m_footer_background_color.g, m_footer_background_color.b, m_footer_background_color.a };
		json_data["footer_sprite_color"] = { m_footer_sprite_color.r, m_footer_sprite_color.g, m_footer_sprite_color.b, m_footer_sprite_color.a };
		json_data["description_height_padding"] = m_description_height_padding;
		json_data["m_description_line_height"] = m_description_line_height;
		json_data["description_height"] = m_description_height;
		json_data["description_text_size"] = m_description_text_size;
		json_data["m_description_line_color"] = { m_description_line_color.r, m_description_line_color.g, m_description_line_color.b, m_description_line_color.a };
		json_data["description_font"] = static_cast<int>(m_description_font);
		json_data["description_background_color"] = { m_description_background_color.r, m_description_background_color.g, m_description_background_color.b, m_description_background_color.a };
		json_data["description_text_color"] = { m_description_text_color.r, m_description_text_color.g, m_description_text_color.b, m_description_text_color.a };
		json_data["m_description_sprite_size"] = m_description_sprite_size;
		json_data["m_description_padding"] = m_description_padding;
		json_data["m_description_sprite_color"] = { m_description_sprite_color.r, m_description_sprite_color.g, m_description_sprite_color.b, m_description_sprite_color.a };
		json_data["m_overlay_x"] = m_overlay_x;
		json_data["m_overlay_y"] = m_overlay_y;
		json_data["m_overlay_height"] = m_overlay_height;
		json_data["m_overlay_line_height"] = m_overlay_line_height;
		json_data["m_overlay_padding"] = m_overlay_padding;
		json_data["m_overlay_width"] = m_overlay_width;
		json_data["m_overlay_color"] = { m_overlay_color.r, m_overlay_color.g, m_overlay_color.b, m_overlay_color.a };
		json_data["m_overlay_text_size"] = m_overlay_text_size;
		json_data["m_overlay_text_color"] = { m_overlay_text_color.r, m_overlay_text_color.g, m_overlay_text_color.b, m_overlay_text_color.a };
		json_data["m_overlay_line_color"] = { m_overlay_line_color.r, m_overlay_line_color.g, m_overlay_line_color.b, m_overlay_line_color.a };
		json_data["m_overlay_font"] = static_cast<int>(m_overlay_font);
		json_data["m_open_key_text_color"] = { m_open_key_text_color.r, m_open_key_text_color.g, m_open_key_text_color.b, m_open_key_text_color.a };
		json_data["m_open_key_text_size"] = m_open_key_text_size;
		json_data["m_open_key_text_font"] = static_cast<int>(m_open_key_text_font);
		json_data["m_tooltip_color"] = { m_tooltip_color.r, m_tooltip_color.g, m_tooltip_color.b, m_tooltip_color.a };
		json_data["m_tooltip_text_size"] = m_tooltip_text_size;
		json_data["m_tooltip_font"] = static_cast<int>(m_tooltip_font);

		std::ofstream file2(file_path);
		if (file.is_open()) {
			file2 << json_data.dump(4);
			LOG(Info, "Theme edited.");
			file.close();
		}
		else {
			LOG(Fatal, "Failed to edit theme file.");
		}
	}

}