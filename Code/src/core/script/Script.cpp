#include "script.h"
#include "src/natives/natives.h"
#include "src/utility/timer.h"
#include "src/framework/framework.h"
#include "src/framework/option_types/toggle.h"
#include "src/framework/option_types/break.h"
#include "src/framework/option_types/choose.h"
#include "src/framework/option_types/number.h"
#include "src/framework/option_types/button.h"
#include "src/framework/option_types/submenu.h"
#include "src/framework/option_types/keyboard.h"
#include "src/framework/submenu_types/regular_submenu.h"
#include "src/framework/notifications/notifications.h"
#include "src/fiber/fiber_helper.h"
#include "src/utility/lists.h"
#include "src/discord/libary/handler.hpp"
#include "src/utility/setting.h"
#include <src/fiber/script/fiber_script.h>
#include <src/fiber/script/manager/script_manager.h>
#include "submenus/weapon/bullet_tracers.h"
#include "submenus/self/forcefield.h"
#include "submenus/weapon/teleport.h"
#include "submenus/weapon/impacts.h"
#include "submenus/vehicle/acceleration.h"
#include "submenus/weapon/general.h"
#include "submenus/vehicle/towtruck.h"
#include "submenus/weapon/magnet.h"
#include "submenus/vehicle/vehicle.h"
#include "submenus/self/self.h"
#include "submenus/weapon/weapon.h"

#pragma comment(lib, "Winmm.lib")

#define MENU(menu) menu = Joaat(#menu),

#include "drawing/drawing.h"
#include <src/framework/option_types/toggle_with_choose.h>
#include <src/framework/option_types/toggle_with_number.h>
#include "submenus/world/world.h"
#include "submenus/network/network.h"
#include <src/framework/option_types/color.h>
#include "submenus/teleport/teleport.h"
#include "submenus/misc/misc.h"
#include "submenus/spawner/spawner.h"
namespace Base {
	enum Submenu : uint32_t {
		//FEATURES
		MENU(player)
		//HOME
		MENU(home)
		//DEMO
		MENU(demo)
		//NETWORK
		MENU(network)
		MENU(network_players)
		MENU(network_players_selected)
		//SETTINGS
		MENU(settings)
		MENU(settings_header)
		MENU(settings_header_static)
		MENU(settings_header_gradient)
		MENU(settings_header_text)
		MENU(settings_submenu)
		MENU(settings_options)
		MENU(settings_tooltips)
		MENU(settings_footer)
		MENU(settings_description)
		MENU(settings_input)
		MENU(settings_themes)
		MENU(settings_injector)
		MENU(settings_sounds)
		MENU(settings_notifications)
		MENU(settings_player_info)
		MENU(settings_theme_settings)
		MENU(developer)
	};
	bool contains_picture_extension(fs::path path) {
		auto ext = path.extension().string();
		std::vector<std::string> supportedFormats = { "png", "jpeg", "bmp", "psd", "tga", "gif", "hdr", "pic", "ppm", "pgm","jpg"};
		for (auto& format : supportedFormats)
			if (ext == "." + format)
				return true;
	}
	bool containJsonExt(fs::path path) {
		auto ext = path.extension().string();
		std::vector<std::string> supportedFormats = { "json"};
		for (auto& format : supportedFormats)
			if (ext == "." + format)
				return true;
	}
	bool containModuleExt(fs::path path) {
		auto ext = path.extension().string();
		std::vector<std::string> supportedFormats = { "dll" };
		for (auto& format : supportedFormats)
			if (ext == "." + format)
				return true;
	}
	bool containSoundsExt(fs::path path) {
		auto ext = path.extension().string();
		std::vector<std::string> supportedFormats = { "mp3" };
		for (auto& format : supportedFormats)
			if (ext == "." + format)
				return true;
	}
	std::string command_prompt_input{};
	std::string menu_search{};
	std::vector<std::string> m_pluginFiles;
	std::vector<HMODULE> m_pluginHandles;

	char vaBuffer[0x1000];
	char* va(const char* fmt, ...) {
		memset(vaBuffer, 0, 0x1000);
		va_list ap;
		va_start(ap, fmt);
		vsprintf_s(vaBuffer, sizeof(vaBuffer), fmt, ap);
		va_end(ap);
		return vaBuffer;
	}
	void LoadASI(std::string fileName) {
		auto themePath{ "C:\\Native\\Plugins" };
		LOG(Info, "{}\\{}", themePath, fileName.c_str());
		auto lib = LoadLibraryA(va("%s\\%s", themePath, fileName.c_str()));
		m_pluginHandles.push_back(lib);
	}
	ChatData* chat_data() {
		return *g_pointers->m_chat_data;
	}
	ImVec4 convert_color(int r, int g, int b) {
		return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, 1);
	}
	void menu::initialize() {
		using namespace Framework;
		if (g_interface->m_click_ui) {
			if (g_interface->m_opened) {
				ImGui::SetNextWindowSize(ImVec2(680, 578), ImGuiCond_Once);
				ImGui::PushFont(g_renderer->m_titlebar_font);
				click_ui::draw_border();
				if (ImGui::Begin("native", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
					click_ui::poswindow = ImGui::GetWindowPos();
					click_ui::window_scale = ImGui::GetWindowSize();
					add_option<submenu>("Settings", "", settings);
#if defined(DEBUG_MODE)
					add_option<submenu>("Developer", "", developer);
#endif
					add_option<keyboard>("Search", "", &menu_search, 999, [] {
						if (GetAsyncKeyState(VK_RETURN) && !Framework::keyboard_open)
							g_interface->switch_to_submenu("search"_joaat);
						});
					ImGui::PushFont(g_renderer->m_smaller_arial); // just incase idk

					ImGui::Columns(2, "main", true);
					ImGui::SetColumnWidth(0, 75);
					ImGui::SetColumnOffset(0, 0);
					click_ui::list_box("tabs", ImVec2(65, -1), g_renderer->m_smaller_arial, [=] {
						draw->submenu_tab(ICON_FA_USER, Framework::tab::self);
						draw->submenu_tab(ICON_FA_SHIELD_HALVED, Framework::tab::protections);
						draw->submenu_tab(ICON_FA_NETWORK_WIRED, Framework::tab::network);
						draw->submenu_tab(ICON_FA_GUN, Framework::tab::weapon);
						draw->submenu_tab(ICON_FA_CAR, Framework::tab::vehicle);
						draw->submenu_tab(ICON_FA_CUBES, Framework::tab::spawner);
						draw->submenu_tab(ICON_FA_GLOBE, Framework::tab::world);
						draw->submenu_tab(ICON_FA_LOCATION_DOT, Framework::tab::teleport);
						draw->submenu_tab(ICON_FA_WAND_MAGIC_SPARKLES, Framework::tab::misc);
						draw->submenu_tab(ICON_FA_GEAR, Framework::tab::settings);
						//draw->toggle("Click Ui", &g_interface->m_click_ui);
					});
					ImGui::NextColumn();
					click_ui::list_box("options", ImVec2(-1, -1), g_renderer->m_smaller_arial, [=] {
						submenus::self::main();
						submenus::network::protections();
						submenus::network::main();
						submenus::weapon::main();
						submenus::vehicle::main();
						submenus::spawner::main();
						submenus::world::main();
						submenus::teleport::main();
						submenus::misc::main();

						if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::settings) return;
						draw->submenu("Settings", "click_settings", [] {
							draw->toggle("Click Ui", &g_interface->m_click_ui);
						});
					});
					ImGui::Columns(1);
					ImGui::PopFont();

					ImGui::End();
				}
				ImGui::PopFont();
			}
		}
		else {
			draw->submenu("Home", "home", [] {
				draw->submenu("Self", "self", submenus::self::main);
				draw->submenu("Protections", "protections", submenus::network::protections);
				draw->submenu("Network", "network", submenus::network::main);
				draw->submenu("Weapon", "weapon", submenus::weapon::main);
				draw->submenu("Vehicle", "vehicle", submenus::vehicle::main);
				draw->submenu("Spawner", "spawner", submenus::spawner::main);
				draw->submenu("World", "world", submenus::world::main);
				draw->submenu("Teleport", "teleport", submenus::teleport::main);
				draw->submenu("Misc", "misc", submenus::misc::main);
				add_option<submenu>("Settings", "", settings);
				add_option<keyboard>("Search", "", &menu_search, 999, [] {
					if (GetAsyncKeyState(VK_RETURN) && !Framework::keyboard_open)
						g_interface->switch_to_submenu("search"_joaat);
					});
			});
		}
		
		g_interface->add<regular_submenu>("Search", "search"_joaat, [](regular_submenu* sub) {
			for (auto& feature : g_feature_manager.m_commands) {
				if (g_utils->has_string_attached(feature.second->m_name, menu_search) || g_utils->has_string_attached(feature.second->m_id, menu_search)) {
					draw->option(feature.second->m_id);
				}
			}
		});

		g_interface->add<regular_submenu>(g_interface->m_choose_name, "choose_menu"_joaat, [](regular_submenu* sub) {
			for (int i{ 0 }; i < g_interface->m_choose_vector.size(); i++) {
				if (g_interface->m_choose_vector[i] == g_interface->m_choose_vector[*g_interface->m_choose_selected]) {
					add_option<Framework::icon_button>(g_interface->m_choose_vector[i], "", "On", [=] {
						*g_interface->m_choose_selected = i;
					});
				}
				else {
					add_option<Framework::button>(g_interface->m_choose_vector[i], "", [=] {
						*g_interface->m_choose_selected = i;
					});
				}
			}
		});

		

		g_interface->add<regular_submenu>("Settings", settings, [](regular_submenu* sub) {
#if defined(DEV)
			add_option<submenu>("Developer", "", developer);
#endif
			sub->add_option<submenu>("Notifications", "", settings_notifications);
			sub->add_option<submenu>("Player Info", "", settings_player_info);
			sub->add_option<submenu>("Tooltips", "", settings_tooltips);
			sub->add_option<submenu>("Themes", "", settings_themes);
			//sub->add_option<submenu>("SHV", "", "shv"_joaat);
			draw->submenu("Main", "settings_main", [=] {
				draw->submenu("Header", "settings_main_header", [=] {
					draw->submenu("Textures", "smh_textures", [] {
						draw->button("Clear", [&] {
							g_renderer->m_header.clear();
							g_interface->m_has_header_loaded = false;
						});
						draw->seperator("Files");
						auto headerPath{ fs::path("C:\\Native\\Headers\\")};
						if (fs::exists(headerPath)) {
							fs::directory_iterator dirIt{ headerPath.string() };
							for (auto&& dirEntry : dirIt) {
								if (dirEntry.is_regular_file() && dirEntry.path().has_filename() && contains_picture_extension(dirEntry.path())) {
									char dir[64];
									sprintf(dir, "%s", dirEntry.path().filename().string());
									draw->button(dir, [=] {
										std::thread t([=] {
											g_interface->m_has_header_loaded = false;
											g_renderer->m_header.clear();
											g_renderer->header_frame = 0;
											if (dirEntry.path().extension().string() == ".gif")
												g_renderer->m_header = g_renderer->create_gif_texture(dirEntry.path());
											else
												g_renderer->m_header.insert({ 0, { 0, g_renderer->create_texture(dirEntry.path()).first } });
											g_interface->m_header_image = dirEntry.path().filename().string();
											g_interface->m_has_header_loaded = true;
											});
										t.detach();
									});
								}
							}
						}
					});
					draw->submenu("Colors", "settings_main_header_colors", [=] {
						draw->submenu("Background", "smhc_background", [=] {
							draw->number("R", g_interface->m_header_background_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_header_background_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_header_background_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_header_background_color.a, { 0, 255, 1, 0 });
						});
						draw->submenu("Text", "smhc_text", [] {
							draw->toggle("Uses Gradiant", &g_interface->m_header.m_uses_gradiant);
							draw->number("R", g_interface->m_header_text_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_header_text_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_header_text_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_header_text_color.a, { 0, 255, 1, 0 });
						});
					});
					draw->seperator("Other");
					sub->add_option<number<float>>("Height", "", &g_interface->m_header_height, 0.01f, 0.2f, 0.001f, 3);
					sub->add_option<number<float>>("Text Size", "", &g_interface->m_header_text_size, 0.1f, 2.f, 0.01f, 2);
				});
				draw->submenu("Infobar", "settings_main_infobar", [=] {
					draw->submenu("Colors", "smic", [] {
						draw->submenu("Background", "smic_background", [] {
							draw->number("R", g_interface->m_submenu_bar_background_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_submenu_bar_background_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_submenu_bar_background_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_submenu_bar_background_color.a, { 0, 255, 1, 0 });
						});
						draw->submenu("Text", "smic_text", [] {
							draw->number("R", g_interface->m_submenu_bar_text_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_submenu_bar_text_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_submenu_bar_text_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_submenu_bar_text_color.a, { 0, 255, 1, 0 });
						});
					});
					draw->seperator("Other");
					add_option<number<float>>("Height", "", &g_interface->m_submenu_bar_height, 0.01f, 0.1f, 0.001f, 3);
					add_option<number<float>>("Text Size", "", &g_interface->m_submenu_bar_text_size, 0.01f, 1.f, 0.01f, 2);
				});
				draw->submenu("Options", "settings_main_options", [=] {
					draw->submenu("Colors", "smoc", [] {
						draw->submenu("Selected Background", "smoc_sb", [] {
							draw->number("R", g_interface->m_option_selected_background_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_option_selected_background_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_option_selected_background_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_option_selected_background_color.a, { 0, 255, 1, 0 });
						});
						draw->submenu("Unselected Background", "smoc_ub", [] {
							draw->number("R", g_interface->m_option_unselected_background_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_option_unselected_background_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_option_unselected_background_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_option_unselected_background_color.a, { 0, 255, 1, 0 });
							});
						draw->submenu("Selected Text", "smoc_st", [] {
							draw->toggle("Gradiant", &g_interface->m_options.m_gradiant_selected_text);
							draw->number("R", g_interface->m_option_selected_text_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_option_selected_text_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_option_selected_text_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_option_selected_text_color.a, { 0, 255, 1, 0 });
						});
						draw->submenu("Unselected Text", "smoc_ut", [] {
							draw->number("R", g_interface->m_option_unselected_text_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_option_unselected_text_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_option_unselected_text_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_option_unselected_text_color.a, { 0, 255, 1, 0 });
						});
						draw->submenu("Gradiants", "smoc_bar", [] {
							draw->submenu("Top/Left", "bar_first", [] {
								draw->number("R", g_interface->m_options.m_first_color.r, { 0, 255, 1, 0 });
								draw->number("G", g_interface->m_options.m_first_color.g, { 0, 255, 1, 0 });
								draw->number("B", g_interface->m_options.m_first_color.b, { 0, 255, 1, 0 });
							});
							draw->submenu("Second/Right", "bar_second", [] {
								draw->number("R", g_interface->m_options.m_second_color.r, { 0, 255, 1, 0 });
								draw->number("G", g_interface->m_options.m_second_color.g, { 0, 255, 1, 0 });
								draw->number("B", g_interface->m_options.m_second_color.b, { 0, 255, 1, 0 });
							});
						});
					});
					draw->submenu("Chooses", "smo_chooses", [=] {
						sub->add_option<toggle_with_choose>("Show Count", "", &g_interface->m_chooses.m_show_count, g_interface->m_chooses.m_anchor, &g_interface->m_chooses.m_anchor_selected);
					});
					draw->seperator("Other");
					sub->add_option<toggle_with_number<float>>("Rounded", "", &g_interface->m_rounded_options, &g_interface->m_rounded_options_mult, 0, 1000, 0.1, 1);
					draw->toggle("Bar", &g_interface->m_options.m_bar);
					sub->add_option<number<float>>("Height", "", &g_interface->m_option_height, 0.01f, 0.1f, 0.001f, 3);
					sub->add_option<number<float>>("Text Size", "", &g_interface->m_option_text_size, 0.01f, 1.f, 0.01f, 2);
					sub->add_option<number<float>>("Toggle X", "", &g_interface->m_toggle_size_x_offset, -50, 50, 0.001f, 3);
					sub->add_option<number<float>>("Toggle Y", "", &g_interface->m_toggle_size_y_offset, -50, 50, 0.001f, 3);
				});
				draw->submenu("Footer", "settings_main_footer", [=] {
					draw->submenu("Colors", "smf_colors", [] {
						draw->submenu("Background", "smfc_background", [] {
							draw->number("R", g_interface->m_footer_background_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_footer_background_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_footer_background_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_footer_background_color.a, { 0, 255, 1, 0 });
						});
						draw->submenu("Sprite", "smfc_sprite", [] {
							draw->number("R", g_interface->m_footer_sprite_color.r, { 0, 255, 1, 0 });
							draw->number("G", g_interface->m_footer_sprite_color.g, { 0, 255, 1, 0 });
							draw->number("B", g_interface->m_footer_sprite_color.b, { 0, 255, 1, 0 });
							draw->number("A", g_interface->m_footer_sprite_color.a, { 0, 255, 1, 0 });
						});
					});
					draw->seperator("Other");
					sub->add_option<toggle_with_choose>("Freeze Icon", "", &g_interface->m_footer.m_freeze, g_interface->m_footer.m_freeze_state, &g_interface->m_footer.m_freeze_selected);
					draw->toggle("Dynamic", &g_interface->m_footer.m_dynamic);
					sub->add_option<number<float>>("Height", "", &g_interface->m_footer_height, 0.01f, 0.1f, 0.001f, 3);
					sub->add_option<number<float>>("Sprite Size", "", &g_interface->m_footer_sprite_size, 0.01f, 1.f, 0.001f, 3);
				});
			});
			draw->submenu("Scrollbar", "settings_scrollbar", [=] {
				sub->add_option<toggle_with_choose>("Enabled", "", &g_interface->m_scrollbar.m_enabled, g_interface->m_scrollbar.m_type, &g_interface->m_scrollbar.m_type_pos);
				draw->seperator("Other");
				draw->number("Width", g_interface->m_scrollbar.m_width, { 0, 5, 0.001, 3 });
				draw->number("Bar Width", g_interface->m_scrollbar.m_width2, { 0, 5, 0.001, 3 });
				draw->number("Offset", g_interface->m_scrollbar.m_offset, { -10, 10, 0.001, 3 });
				draw->number("Bar Offset", g_interface->m_scrollbar.m_bar_offset, { -10, 10, 0.001, 3 });
			});
			draw->submenu("Borders", "settings_borders", [] {
				draw->toggle("Main Lines", &g_interface->m_lines);
			});
			draw->submenu("Positions", "settings_positions", [=] {
				sub->add_option<number<float>>("X", "", &g_interface->m_pos_x, 0.f, 1.f, 0.01f, 2);
				sub->add_option<number<float>>("Y", "", &g_interface->m_pos_y, 0.f, 1.f, 0.01f, 2);
			});
			draw->submenu("Animations", "settings_animations", [=] {
				draw->toggle("Fade On Enter", &g_interface->m_fade_on_enter);
				draw->toggle("Smooth Scroll Moves Text", &g_interface->m_smooth_scroll_moves_text);
				draw->toggle("Fly In", &g_interface->m_fly_in);
				sub->add_option<number<float>>("Smooth Scroll Speed", "", &g_interface->m_smooth_scroll_speed, 0.01f, 1.f, 0.01f, 2);
				sub->add_option<number<float>>("Option Speed", "", &g_interface->m_speed, -1000, 1000, 0.01f, 2);
				draw->number("Menu Speed", &g_interface->m_menu_animation_speed, { -1000, 1000, 0.01f, 2 });
			});
			draw->submenu("Rounding", "rounding_menu", [] {
				draw->number("Header", g_interface->m_rounding.m_header, { 0, 100, 0.1, 1 });
				draw->number("Footer", g_interface->m_rounding.m_footer, { 0, 100, 0.1, 1 });
			});
			draw->submenu("Misc", "settings_misc", [=] {
				sub->add_option<number<float>>("Width", "", &g_interface->m_width, 0.01f, 1.f, 0.01f, 2);
				sub->add_option<number<int>>("Rainbow Speed", "", &rainbow_speed, 0, 255, 1, 0);
				draw->toggle("Sounds", &g_interface->m_sounds);
			});
			draw->toggle("Click Ui", &g_interface->m_click_ui);
			draw->button("Unload", [] {
				g_Running = false;
			});
		});
		g_interface->add<regular_submenu>("Description", settings_description, [](regular_submenu* sub) {
			sub->add_option<number<float>>("Padding", "", &g_interface->m_description_height_padding, 0.01f, 1.f, 0.001f, 3);
			sub->add_option<number<float>>("Height", "", &g_interface->m_description_height, 0.01f, 1.f, 0.001f, 3);
			sub->add_option<number<float>>("Text Size", "", &g_interface->m_description_text_size, 0.1f, 2.f, 0.01f, 2);
			});
		g_interface->add<regular_submenu>("Tool Tips", settings_tooltips, [](regular_submenu* sub) {
			sub->add_option<seperator>("Open Key Text");
			sub->add_option<number<float>>("Size", "", &g_interface->m_open_key_text_size, 0.01f, 1.f, 0.001f, 3);
			draw->number("Background R", g_interface->m_open_key_text_color.r, { 0, 255, 1, 0 });
			draw->number("Background G", g_interface->m_open_key_text_color.g, { 0, 255, 1, 0 });
			draw->number("Background B", g_interface->m_open_key_text_color.b, { 0, 255, 1, 0 });
			draw->number("Background A", g_interface->m_open_key_text_color.a, { 0, 255, 1, 0 });
			sub->add_option<seperator>("Tooltip Text");
			sub->add_option<number<float>>("Size", "", &g_interface->m_tooltip_text_size, 0.01f, 1.f, 0.001f, 3);
			draw->number("Background R", g_interface->m_tooltip_color.r, { 0, 255, 1, 0 });
			draw->number("Background G", g_interface->m_tooltip_color.g, { 0, 255, 1, 0 });
			draw->number("Background B", g_interface->m_tooltip_color.b, { 0, 255, 1, 0 });
			draw->number("Background A", g_interface->m_tooltip_color.a, { 0, 255, 1, 0 });
			});
		g_interface->add<regular_submenu>("Input", settings_input, [](regular_submenu* sub) {
			sub->add_option<number<std::int32_t>>("Open Delay", "", &g_interface->m_open_delay, 10, 1000, 10, 0);
			sub->add_option<number<std::int32_t>>("Back Delay", "", &g_interface->m_back_delay, 10, 1000, 10, 0);
			sub->add_option<number<std::int32_t>>("Enter Delay", "", &g_interface->m_enter_delay, 10, 1000, 10, 0);
			sub->add_option<number<std::int32_t>>("Vertical Delay", "", &g_interface->m_vertical_delay, 10, 1000, 10, 0);
			sub->add_option<number<std::int32_t>>("Horizontal Delay", "", &g_interface->m_horizontal_delay, 10, 1000, 10, 0);
			});
		g_interface->add<regular_submenu>("Notifications", settings_notifications, [](regular_submenu* sub) {
			sub->add_option<number<float>>("Height", "", &g_notifications->m_Height, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<number<float>>("Width", "", &g_notifications->width, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<number<float>>("Line Width", "", &g_notifications->m_LineWidth, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<number<float>>("Padding", "", &g_notifications->m_Padding, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<number<float>>("Text Size", "", &g_interface->m_notifications_text_size, 0.01f, 1.f, 0.01f, 2);
			sub->add_option<number<float>>("Text Size 2", "", &g_interface->m_notifications_text_size2, 0.01f, 1.f, 0.01f, 2);
			sub->add_option<seperator>("Background");
			draw->number("Background R", g_notifications->m_NotificationBackground.r, { 0, 255, 1, 0 });
			draw->number("Background G", g_notifications->m_NotificationBackground.g, { 0, 255, 1, 0 });
			draw->number("Background B", g_notifications->m_NotificationBackground.b, { 0, 255, 1, 0 });
			draw->number("Background A", g_notifications->m_NotificationBackground.a, { 0, 255, 1, 0 });
			sub->add_option<seperator>("Text");
			draw->number("Text R", g_notifications->m_NotificationText.r, { 0, 255, 1, 0 });
			draw->number("Text G", g_notifications->m_NotificationText.g, { 0, 255, 1, 0 });
			draw->number("Text B", g_notifications->m_NotificationText.b, { 0, 255, 1, 0 });
			draw->number("Text A", g_notifications->m_NotificationText.a, { 0, 255, 1, 0 });
			});
		g_interface->add<regular_submenu>("Player Info", settings_player_info, [](regular_submenu* sub) {
			sub->add_option<number<float>>("Player Info X", "", &g_interface->m_player_info_x, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<number<float>>("Player Info Line Height", "", &g_interface->m_player_info_line_height, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<number<float>>("Player Info Padding", "", &g_interface->m_player_info_padding, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<number<float>>("Player Info Height", "", &g_interface->m_player_info_height, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<number<float>>("Player Info Width", "", &g_interface->m_player_info_width, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<number<float>>("Player Info Text Size", "", &g_interface->m_player_info_text_size, 0.01f, 0.1f, 0.001f, 3);
			sub->add_option<seperator>("Background");
			draw->number("Background R", g_interface->m_player_info_color.r, { 0, 255, 1, 0 });
			draw->number("Background G", g_interface->m_player_info_color.g, { 0, 255, 1, 0 });
			draw->number("Background B", g_interface->m_player_info_color.b, { 0, 255, 1, 0 });
			draw->number("Background A", g_interface->m_player_info_color.a, { 0, 255, 1, 0 });
			sub->add_option<seperator>("Line");
			draw->number("Line R", g_interface->m_player_info_line_color.r, { 0, 255, 1, 0 });
			draw->number("Line G", g_interface->m_player_info_line_color.g, { 0, 255, 1, 0 });
			draw->number("Line B", g_interface->m_player_info_line_color.b, { 0, 255, 1, 0 });
			draw->number("Line A", g_interface->m_player_info_line_color.a, { 0, 255, 1, 0 });
			sub->add_option<seperator>("Text");
			draw->number("Text R", g_interface->m_player_info_text_color.r, { 0, 255, 1, 0 });
			draw->number("Text G", g_interface->m_player_info_text_color.g, { 0, 255, 1, 0 });
			draw->number("Text B", g_interface->m_player_info_text_color.b, { 0, 255, 1, 0 });
			draw->number("Text A", g_interface->m_player_info_text_color.a, { 0, 255, 1, 0 });
		});

		g_interface->add<regular_submenu>("Developer", developer, [](regular_submenu* sub) {
			sub->add_option<submenu>("Injector", "", settings_injector);
			sub->add_option<submenu>("Sounds", "", settings_sounds);
			sub->add_option<button>("Test Exception", "", [&] {
				throw std::runtime_error("");
			});
			sub->add_option<button>("Header Image Text", "", [&] {
				LOG(Info, "{}", g_interface->m_header_image);
			});
			sub->add_option<button>("Test Notification Info", "", [&] {
				g_notifications->send("Info", "Hello?");
			});
			sub->add_option<button>("Test Notification Success", "", [&] {
				g_notifications->send("Success", "Ur fat and gay!");
			});
			sub->add_option<button>("Test Notification Error", "", [&] {
				g_notifications->send("Error", "Your games dying what did you do?");
			});
			sub->add_option<button>("Test Noti doublelined", "", [&] {
				g_notifications->send("Test", "Nigger\nI hate niggers");
				});
			sub->add_option<button>("Test Notification Error Random", "", [&] {
				g_notifications->send("Error", std::format("{}", g_utils->get_random_value_in_range<int>(0, 1000)));
			});
			sub->add_option<button>("Restart Game", "", [&] {
				MISC::RESTART_GAME();
			});
		});
		g_interface->add<regular_submenu>("Sounds", settings_sounds, [](regular_submenu* sub) {
			std::string currentAlias; // Store the current alias for the playing MP3

			auto soundPath = fs::path("C:\\Native\\Sounds\\");
			if (fs::exists(soundPath)) {
				fs::directory_iterator dirIt{ soundPath.string() };
				for (auto&& dirEntry : dirIt) {
					if (dirEntry.is_regular_file() && dirEntry.path().has_filename() && containSoundsExt(dirEntry.path())) {
						char dir[64];
						sprintf(dir, "%s", dirEntry.path().filename().string());
						sub->add_option<button>(dir, "", [=] {
							std::thread t([=] {
								if (dirEntry.path().extension().string() == ".mp3") {
									std::string alias = "mp3" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
									std::string command = "open \"" + dirEntry.path().string() + "\" type mpegvideo alias " + alias;
									mciSendStringA(command.c_str(), nullptr, 0, nullptr);
									mciSendStringA(("play " + alias).c_str(), nullptr, 0, nullptr);
									currentAlias == alias; // Update the current alias
								}
								});
							t.detach();
							});
					}
				}
			}
			});
		g_interface->add<regular_submenu>("Injector", settings_injector, [](regular_submenu* sub) {
			HMODULE module_handle{};
			std::vector<HMODULE> module_handles;

			sub->add_option<button>("Unload Modules", "", [&] {
				std::vector<HMODULE> unloaded_modules;
				for (auto moduleHandle : module_handles) {
					if (moduleHandle != nullptr) {
						if (!FreeLibrary(moduleHandle)) {
							// Handle the error appropriately
							DWORD errorCode = GetLastError();
							LOG(Fatal, "Failed to unload module. Error code: {}", errorCode);
						}
						else {
							unloaded_modules.push_back(moduleHandle);
						}
					}
				}
				// Remove the unloaded module handles from the vector
				for (auto moduleHandle : unloaded_modules) {
					auto it = std::find(module_handles.begin(), module_handles.end(), moduleHandle);
					if (it != module_handles.end()) {
						module_handles.erase(it);
					}
				}
				});
			sub->add_option<seperator>("Modules");
			auto modulePath = fs::path("C:\\Native\\Modules\\");
			if (fs::exists(modulePath)) {
				fs::directory_iterator dirIt{ modulePath.string() };
				for (auto&& dirEntry : dirIt) {
					if (dirEntry.is_regular_file() && dirEntry.path().has_filename() && containModuleExt(dirEntry.path())) {
						char dir[64];
						sprintf(dir, "%s", dirEntry.path().filename().string());
						sub->add_option<button>(dir, "", [=]() mutable {
							std::thread t([=]() mutable {
								if (dirEntry.path().extension().string() == ".dll") {
									HMODULE module = LoadLibraryA(dirEntry.path().string().c_str());
									if (module == nullptr) {
										LOG(Fatal, "Failed to load module: {}", dirEntry.path().string());
									}
									else {
										module_handle = module;
										module_handles.push_back(module);
									}
								}
								});
							t.detach();
						});
					}
				}
			}
			});
		g_interface->add<regular_submenu>("Themes", settings_themes, [](regular_submenu* sub) {
			auto themePath = fs::path("C:\\Native\\Themes\\");
			add_option<keyboard>("Save", "", &g_interface->m_theme_name, 64, [] {
				if (GetAsyncKeyState(VK_RETURN) && !Framework::keyboard_open) {
					LOG(Info, g_interface->m_theme_name);
					std::string themeNameCopy = g_interface->m_theme_name;
					g_interface->save_variables_to_json(themeNameCopy);
				}
			});
			sub->add_option<seperator>("Themes");
			if (fs::exists(themePath)) {
				fs::directory_iterator dirIt{ themePath.string() };
				for (auto&& dirEntry : dirIt) {
					if (dirEntry.is_regular_file() && dirEntry.path().has_filename() && containJsonExt(dirEntry.path())) {
						char dir[64];
						sprintf(dir, "%s", dirEntry.path().filename().string().c_str());
						sub->add_option<submenu>(dir, "", settings_theme_settings);
						auto load_theme_function = [=]() {
							std::thread t([=]() {
								if (dirEntry.path().extension().string() == ".json")
									g_interface->load_variables_from_json(dirEntry.path().string());
								else
									LOG(Info, "Not a valid .json");
								});
							t.detach();
						};
						auto save_theme_function = [=]() {
							std::thread t([=]() {
								if (dirEntry.path().extension().string() == ".json")
									g_interface->edit_variables_to_json(dirEntry.path().string());
								else
									LOG(Info, "Not a valid .json");
								});
							t.detach();
						};
						auto default_theme_function = [=]() {
							std::thread t([=]() {
								if (dirEntry.path().extension().string() == ".json") {
									g_interface->load_variables_from_json(dirEntry.path().string());
									g_interface->m_default_theme_name = {};
									g_interface->m_default_theme_name = dirEntry.path().string();
									LOG(Info, g_interface->m_default_theme_name);
								}
								else {
									LOG(Info, "Not a valid theme");
								}
								});
							t.detach();
						};
						auto delete_theme_function = [=]() {
							std::thread t([=]() {
								if (dirEntry.path().extension().string() == ".json") {
									if (std::filesystem::remove(dirEntry.path())) {
										LOG(Info, "Theme deleted successfully");
									}
									else {
										LOG(Info, "Failed to delete theme");
									}
								}
								else {
									LOG(Info, "Not a valid .json");
								}
								});
							t.detach();
						};
						g_interface->add<regular_submenu>("Settings", settings_theme_settings, [=](regular_submenu* sub) {
							sub->add_option<button>("Load", "", load_theme_function);
							sub->add_option<button>("Edit", "", save_theme_function);
							sub->add_option<button>("Default Theme", "", default_theme_function);
							sub->add_option<button>("Delete", "", delete_theme_function);
						});
					}
				}
			}

		});

		g_interface->add<regular_submenu>("SHV", "shv"_joaat, [](regular_submenu* sub) {
			auto themePath = fs::path("C:\\Native\\plugins\\");
			add_option<keyboard>("Save", "", &g_interface->m_theme_name, 64, [] {
				if (GetAsyncKeyState(VK_RETURN) && !Framework::keyboard_open) {
					LOG(Info, g_interface->m_theme_name);
					std::string themeNameCopy = g_interface->m_theme_name;
					g_interface->save_variables_to_json(themeNameCopy);
				}
				});
			sub->add_option<seperator>("Themes");

			for (auto file : g_file_utils->get_all_files_from_dict(g_file_utils->get_main_directory() + "\\Plugins\\")) {
				sub->add_option<button>(file.name_without_extension.c_str(), "", [=] {
					LoadASI(file.full_name);
					});
			}
		});
	}
	void menu::destroy() {
		g_interface.reset();
	}
	std::optional<Player> m_player_to_use_complaint_kick = std::nullopt;
	auto get_self() {
		return g_utils->get_network_player_mgr()->m_local_net_player;
	}
	bool is_key_pressed(std::uint16_t key) {
		if (GetForegroundWindow() == g_pointers->m_game_window) {
			if (GetAsyncKeyState(key) & 0x8000) {
				return true;
			}
		}
		return false;
	}
	void menu::tick() {
		if (!g_interface->m_click_ui) {
			g_menu->initialize();
		}
		while (true) {
			g_discord->tick();
			//g_game_utils.on_tick();
			if (!g_interface->m_opened) {
				draw->redo_actions = true;
			}
			g_interface->m_open_key_pressed = (IsKeyPressed(VK_F4) || (!PAD::IS_USING_KEYBOARD_AND_MOUSE(0) && g_utils->control_pressed(disable_pressed, 175) && g_utils->control_pressed(disable_pressed, 206)));
			g_interface->m_back_key_pressed = g_utils->control_pressed(disable_pressed, 202);
			g_interface->m_enter_key_pressed = g_utils->control_pressed(disable_pressed, 201);
			g_interface->m_up_key_pressed = g_utils->control_pressed(disable_pressed, 172);
			g_interface->m_down_key_pressed = g_utils->control_pressed(disable_pressed, 173);
			g_interface->m_left_key_pressed = g_utils->control_pressed(disable_pressed, 174);
			g_interface->m_right_key_pressed = g_utils->control_pressed(disable_pressed, 175);
			g_interface->m_hotkey_key_pressed = is_key_pressed(VK_F12);

			g_interface->update_hotkeys();

			submenus::vehicle::m_has_custom_wheels = VEHICLE::GET_VEHICLE_MOD_VARIATION(g_utils->vehicle(), 23);

			if (g_protection_manager.m_desync_kicks && *g_pointers->m_is_session_started) {
				memset(&g_utils->network()->m_game_complaint_mgr.m_host_tokens_complained, 0, 64 * sizeof(uint64_t));

				g_utils->network()->m_game_complaint_mgr.m_num_tokens_complained = 0;

				auto old = g_utils->network()->m_game_complaint_mgr.m_host_token;

				if (g_utils->network()->m_game_session_state > 3 && g_utils->network()->m_game_session_state < 6 && m_player_to_use_complaint_kick && get_self()->is_valid() && !get_self()->is_host()) {
					g_pointers->m_reset_network_complaints(&g_utils->network()->m_game_complaint_mgr);
				}
			}

			g_player_mgr.tick();
			g_hotkey_manager.tick();

			if (g_interface->m_opened && g_settings.lock_mouse)
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			if (g_interface->m_opened) {
				PAD::DISABLE_CONTROL_ACTION(0, 27, true);
				PAD::DISABLE_CONTROL_ACTION(0, 0, true);
				PAD::DISABLE_CONTROL_ACTION(0, 19, true);
				PAD::DISABLE_CONTROL_ACTION(0, 140, true);
				PAD::DISABLE_CONTROL_ACTION(0, 20, true);
				PAD::DISABLE_CONTROL_ACTION(0, 27, true);
				PAD::DISABLE_CONTROL_ACTION(0, 80, true);
				PAD::DISABLE_CONTROL_ACTION(0, 337, true);
				PAD::DISABLE_CONTROL_ACTION(0, 27, true);
				PAD::DISABLE_CONTROL_ACTION(0, 85, true);
				PAD::DISABLE_CONTROL_ACTION(0, 74, true);
				PAD::DISABLE_CONTROL_ACTION(0, 58, true);
				PAD::DISABLE_CONTROL_ACTION(0, 70, true);
			}

			if (Framework::number_type_open || Framework::keyboard_open || g_interface->m_command_box_opened)
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);

			if (!cached && just_entered_model_changer) {
				int found{ 0 };
				auto count{ *(u16*)read_instruction(g_pointers->m_get_model_info) };
				hash_node** map{ *(hash_node***)read_instruction(g_pointers->m_get_model_info + 0x21) };
				for (u16 i{ 0 }; i < count; i++) {
					for (hash_node* current = map[i]; current; current = current->next) {
						if (STREAMING::IS_MODEL_A_PED(current->hash)) {
							ped_pool.push_back(current->hash);
							found++;
						}
					}
				}
				cached = (found == 1032);
			}
			g_utils->add_rainbow(&g_rainbow);
			tick_features();
			fiber::current()->wait();
			Script::GetCurrent()->ScriptYield();
		}
	}
	static int InputTextFilterNumbers(ImGuiInputTextCallbackData* data)
	{
		if (data->EventChar < '0' || data->EventChar > '9')
		{
			// Reject non-numeric characters
			return 1;
		}
		return 0;
	}
	void menu::dx_tick() {
		bool input_focused;
		while (true) {
			for (auto rect : submenus::weapon::rects) {
				g_interface->draw_rect(rect.m_x, rect.m_y, rect.m_width, rect.m_height, rect.m_color, ImGui::GetForegroundDrawList(), rect.m_rounding);
			}
			if (g_interface->m_click_ui) {
				if (g_utils->key_press(VK_F4, true)) {
					g_interface->m_opened = !g_interface->m_opened;
				}
				g_menu->initialize();
			}
			if (g_interface->m_command_box_opened) {
				ImVec2 windowSize(380, 120);
				ImVec2 screenSize = ImGui::GetIO().DisplaySize;
				ImVec2 windowPos(screenSize.x / 2 - windowSize.x / 2, screenSize.y / 2 - windowSize.y / 2 - 550);
				ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
				ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
				ImGui::PushFont(g_renderer->m_ArialSmall);
				if (ImGui::Begin("command box", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
					command_box::init();
					ImGui::End();
				}
				ImGui::PopFont();
			}
			if (g_interface->m_aimbot && g_interface->m_aimbot_is_on) {
				ImGui::Begin("##yuh", nullptr,
					ImGuiWindowFlags_::ImGuiWindowFlags_NoMove
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoResize
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar);
				auto draw{ ImGui::GetBackgroundDrawList() };
				ImVec2 screen_size{ ImGui::GetIO().DisplaySize };
				draw->AddCircle(ImVec2(screen_size.x / 2, screen_size.y / 2), g_interface->m_aimbot_fov, IM_COL32(255, 0, 0, 255), 100, 1);
				ImGui::End();
			}
			if (Framework::number_type_open) {
				ImGui::PushFont(g_renderer->m_ArialSmall);
				ImVec2 windowSize(0, 0);
				ImVec2 screenSize = ImGui::GetIO().DisplaySize;
				ImVec2 windowPos(100000000, 100000000);
				ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
				ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
				if (ImGui::Begin("Input", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse)) {
					ImGui::SetKeyboardFocusHere(0);
					ImGui::InputText("Enter a number", Framework::text_buffer, sizeof(Framework::text_buffer),
						ImGuiInputTextFlags_CallbackCharFilter, InputTextFilterNumbers);
					ImGui::End();
				}
				ImGui::PopFont();
			}
			if (Framework::keyboard_open) {
				ImGui::PushFont(g_renderer->m_ArialSmall);
				ImVec2 windowSize(0, 0);
				ImVec2 screenSize = ImGui::GetIO().DisplaySize;
				ImVec2 windowPos(100000000, 100000000);
				ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
				ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
				if (ImGui::Begin("Input", 0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse)) {
					ImGui::SetKeyboardFocusHere(0);
					static const int maxCharacters = Framework::keyboard_max_limit;

					ImGui::InputText("", Framework::keyboard_text_buffer, IM_ARRAYSIZE(Framework::keyboard_text_buffer));

					if (strlen(Framework::keyboard_text_buffer) > maxCharacters) {
						Framework::keyboard_text_buffer[maxCharacters] = '\0';
					}
					ImGui::End();
				}
				ImGui::PopFont();
			}
			if (g_interface->m_tracers) {
				ImGui::Begin("##yuh", nullptr,
					ImGuiWindowFlags_::ImGuiWindowFlags_NoMove
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoResize
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings
					| ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar);
				for (auto player : get_players()) {
					if (player && player->is_valid()) {
						if (player->m_player_info) {
							if (player->m_player_info->m_ped) {
								if (player->m_player_info->m_ped->m_navigation) {
									auto pos{ player->m_player_info->m_ped->m_navigation->get_position() };
									auto draw{ ImGui::GetBackgroundDrawList() };
									float screen_x, screen_y;
									if (g_pointers->m_get_screen_coords_for_world_coords(pos->data, &screen_x, &screen_y)) {
										ImVec2 screen_size{ ImGui::GetIO().DisplaySize };
										ImVec2 pos{ screen_size.x * screen_x,  screen_size.y * screen_y };
										float tracer_draw_position[2] = { 0.5f, 1.f };
										draw->AddLine({ screen_size.x * tracer_draw_position[0], screen_size.y * tracer_draw_position[1] }, pos, IM_COL32(255, 255, 255, 255));
										ImGui::PushFont(g_renderer->m_ArialSmall);
										draw->AddText(pos, IM_COL32(255, 255, 255, 255), player->get_name());
										ImGui::PopFont();
									}
									
								}
							}
						}
					}
				}
				ImGui::End();
			}
			g_interface->OnTick();
			g_notifications->Tick();
			fiber::current()->wait();
			Script::GetCurrent()->ScriptYield();
		}
	}
}