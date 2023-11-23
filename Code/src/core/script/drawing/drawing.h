#pragma once
#include "src/framework/submenu_types/abstract_submenu.h"
#include "src/framework/submenu_types/player_submenu.h"
#include <src/Features/types/toggle.h>


#include "src/framework/option_types/choose.h"
#include "src/framework/option_types/toggle_with_choose.h"
#include "src/framework/option_types/toggle_with_number.h"

#include "src/framework/option_types/vehicle_button.h"

#include "src/features/utils/operator.h"
#define queue_function(item) g_fiber_pool.queue([=] { item(); });
namespace Base {

	template <typename T>
	struct number_modifers {
		T min;
		T max;
		T step{ 0.1 };
		T precision{ 1 };
	};
	template <typename T>
	using vector_pair = std::vector<std::pair<T, T>>;

	template <typename T, typename T2>
	using vector_pair_double = std::vector<std::pair<T, T2>>;

	template<typename T>
	inline std::unique_ptr<T> add_option(T option) {
		std::unique_ptr<T> ptr = std::make_unique<T>(std::move(option));
		Framework::g_options.push_back(std::move(ptr));
		return ptr;
	}
	template <typename T>
	class Singleton {
	public:
		static T* get() {
			static T instance;
			return &instance;
		}

		T* operator->() {
			return get();
		}

		T& operator*() {
			return *get();
		}

		T& operator=(const T& other) {
			*get() = other;
			return *get();
		}
	};
	void change_mouse_on_hover(str text = "") {
		if (ImGui::IsItemHovered()) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

			if (text != "")
				ImGui::SetTooltip(text.c_str());
		}
	}
	namespace click_ui {
		void setup_col(str name, int width = 300) {
			if (!g_interface->m_click_ui) return;

			ImGui::Columns(2, name.c_str(), false);
			ImGui::SetColumnWidth(0, width);
			ImGui::SetColumnOffset(0, 0);
		}
		void next_col() {
			if (!g_interface->m_click_ui) return;

			ImGui::NextColumn();
		}
		void end_col() {
			if (!g_interface->m_click_ui) return;

			ImGui::Columns(1);
		}
		// we do a little athena skidding
		Vector2 pos = { 330.f, 11.5f };
		Vector2 widthHeight = { 300.f, 13.f };
		ImVec2 addVecs(ImVec2 vectorA, ImVec2 vectorB) {
			ImVec2 result;
			result.x = vectorA.x; result.y = vectorA.y;
			result.x += vectorB.x; result.y += vectorB.y;
			return result;
		}
		ImU32 InterpolateColor(ImU32 color1, ImU32 color2, float t) {
			// Extract the color components (RGBA) from the colors
			ImVec4 col1 = ImGui::ColorConvertU32ToFloat4(color1);
			ImVec4 col2 = ImGui::ColorConvertU32ToFloat4(color2);

			// Interpolate each component separately
			ImVec4 result;
			result.x = col1.x + (col2.x - col1.x) * t;
			result.y = col1.y + (col2.y - col1.y) * t;
			result.z = col1.z + (col2.z - col1.z) * t;
			result.w = col1.w + (col2.w - col1.w) * t;

			// Convert the interpolated float color back to ImU32
			return ImGui::ColorConvertFloat4ToU32(result);
		}
		void RenderTextWithGradient(const char* text, ImVec2 position, ImU32 startColor, ImU32 endColor) {
			float gradientStep = 1.0f / (strlen(text) - 1); // Adjust gradient step

			for (int i = 0; i < strlen(text); ++i) {
				ImU32 currentColor = InterpolateColor(startColor, endColor, gradientStep * i);
				ImGui::GetWindowDrawList()->AddText(position, currentColor, &text[i], &text[i + 1]); // Render a single character
				position.x += ImGui::CalcTextSize(&text[i], &text[i + 1]).x; // Update position based on the size of the character
			}
		}

		void text(str text, ImVec2 pos, ImU32 color, ImFont* font) {
			auto drawList = ImGui::GetCurrentWindow()->DrawList;
			ImGui::PushFont(font);
			RenderTextWithGradient(text.c_str(), pos, IM_COL32(g_interface->m_options.m_first_color.r, g_interface->m_options.m_first_color.g, g_interface->m_options.m_first_color.b, 255), IM_COL32(g_interface->m_options.m_second_color.r, g_interface->m_options.m_second_color.g, g_interface->m_options.m_second_color.b, 255));
			ImGui::PopFont();
		}
		void renderMulticolorRect(ImVec2 pos, ImVec2 size, ImU32 color1, ImU32 color2, ImU32 color3, ImU32 color4) {
			auto drawList = ImGui::GetCurrentWindow()->DrawList;
			const ImRect rec(pos, addVecs(pos, ImGui::CalcItemSize(size, 0.f, 0.f)));
			drawList->AddRectFilledMultiColor(rec.Max, rec.Min, color1, color2, color3, color4);
		}
		void renderMulticolorRect2(ImVec2 pos, ImVec2 size, ImU32 color1, ImU32 color2, ImU32 color3, ImU32 color4, ImDrawList* drawList) {
			const ImRect rec(pos, addVecs(pos, ImGui::CalcItemSize(size, 0.f, 0.f)));
			drawList->AddRectFilledMultiColor(rec.Max, rec.Min, color1, color2, color3, color4);
		}
		ImVec2 poswindow{};
		ImVec2 window_scale{};
		void draw_border() {
			ImColor m_firstGradiant = IM_COL32(g_interface->m_options.m_first_color.r, g_interface->m_options.m_first_color.g, g_interface->m_options.m_first_color.b, 255);
			ImColor m_secondGradiant = IM_COL32(g_interface->m_options.m_second_color.r, g_interface->m_options.m_second_color.g, g_interface->m_options.m_second_color.b, 255);
			int border_size{ 2 };
			//left
			renderMulticolorRect2(ImVec2(poswindow.x, poswindow.y), ImVec2(border_size, window_scale.y), m_secondGradiant, m_secondGradiant, m_firstGradiant, m_firstGradiant, ImGui::GetForegroundDrawList());
			//right
			renderMulticolorRect2(ImVec2(poswindow.x + window_scale.x, poswindow.y), ImVec2(border_size, window_scale.y), m_firstGradiant, m_firstGradiant, m_secondGradiant, m_secondGradiant, ImGui::GetForegroundDrawList());
			//top
			renderMulticolorRect2(ImVec2(poswindow.x, poswindow.y), ImVec2(window_scale.x, border_size), m_secondGradiant, m_firstGradiant, m_firstGradiant, m_secondGradiant, ImGui::GetForegroundDrawList());
			//bottom
			renderMulticolorRect2(ImVec2(poswindow.x, poswindow.y + window_scale.y), ImVec2(window_scale.x + 2, border_size), m_firstGradiant, m_secondGradiant, m_secondGradiant, m_firstGradiant, ImGui::GetForegroundDrawList());
		}
		void list_box(str id, ImVec2 size, ImFont* font, std::function<void()> func) {
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4());
			if (ImGui::BeginListBox(("##" + id).c_str(), size)) {
				ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(37, 37, 37, 255));
				ImGui::PushFont(font);
				func();
				ImGui::PopFont();
				ImGui::PopStyleColor();
				ImGui::EndListBox();
			}
			ImGui::PopStyleColor();
		}
		void child(str name, float length, std::function<void()> func) {
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 10);

			float size_length{ length };
			list_box(name + "_", ImVec2(300.f, size_length + 30.f), g_renderer->m_smaller_arial, [=] {
				ImColor m_firstGradiant = IM_COL32(g_interface->m_options.m_first_color.r, g_interface->m_options.m_first_color.g, g_interface->m_options.m_first_color.b, 255);
				ImColor m_secondGradiant = IM_COL32(g_interface->m_options.m_second_color.r, g_interface->m_options.m_second_color.g, g_interface->m_options.m_second_color.b, 255);
				auto style{ (*GImGui).Style };
				auto size{ ImFloor(ImGui::CalcItemSize(ImVec2(290.f, size_length), ImGui::CalcItemWidth(), ImGui::GetTextLineHeightWithSpacing() * 7.25f + style.FramePadding.y * 2.0f)) };
				auto frameBb = ImRect(ImGui::GetCurrentWindow()->DC.CursorPos, addVecs(ImGui::GetCurrentWindow()->DC.CursorPos, ImVec2(size.x, ImMax(size.y, ImGui::CalcTextSize(name.c_str(), NULL, true).y))));
				auto textPos{ ImVec2(frameBb.Max.x + style.ItemInnerSpacing.x, frameBb.Min.y + style.FramePadding.y) };
				text(name, ImVec2(textPos.x - 293.f, textPos.y - 3.f), IM_COL32(255, 255, 255, 255), g_renderer->m_title_font);

				ImGui::Dummy(ImVec2(0.f, 15.0));
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);
				if (ImGui::BeginListBox(("##" + name).c_str(), ImVec2(300.f, size_length))) {
					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
					ImGui::Dummy(ImVec2(0.f, 8.f));
					func();
					// middle = left
					renderMulticolorRect(ImVec2(textPos.x - 300.f, textPos.y + pos.y), ImVec2(widthHeight.x, widthHeight.y), m_secondGradiant, m_firstGradiant, m_firstGradiant, m_secondGradiant);
					ImGui::PopStyleVar();

					ImGui::EndListBox();
				}
				ImGui::PopStyleVar();
			});
		}
		void sameline() {
			if (ImGui::GetCursorPosX() + 300.f < ImGui::GetContentRegionMax().x) {
				ImGui::SameLine();
			}
		}
		void same_line() {
			if (g_interface->m_click_ui) {
				ImGui::SameLine();
			}
		}
	}
	namespace drawer {
		bool get_from_id(std::string id) {
			if (!g_feature_manager.does_exist(id)) return false;

			for (auto& cmds : g_feature_manager.m_commands) {
				if (cmds.first != id) continue;

				switch (cmds.second->m_type) {
					case eCommandType::toggle: {
						auto t = g_feature_manager.get_command<toggle_option>(id.c_str());
						if (g_interface->m_click_ui) {
							ImGui::PushID(t->get_id());
							//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
							if (ImGui::Checkbox(t->get_name().c_str(), t->m_toggle)) {
								if (!t->is_toggled()) {
									g_fiber_pool.queue([=] {
										if (t->m_on_disable)
											t->m_on_disable();
										});
								}
							}
							click_ui::sameline();
							change_mouse_on_hover(t->m_description);
							ImGui::PopID();
						}
						else {
							add_option<Framework::toggle>(t->get_name(), t->get_description(), t->m_toggle, [=] {
								g_fiber_pool.queue([=] {
									if (t->m_on_disable && !*t->m_toggle)

										t->m_on_disable();
									});
								});
						}
						break;
					}
					case eCommandType::number: {
						auto n = g_feature_manager.get_command<float_option>(id.c_str());
						if (g_interface->m_click_ui) {
							//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
							ImGui::PushID(n->get_id());
							ImGui::PushItemWidth(135.f);
							if (ImGui::SliderFloat(n->get_name().c_str(), n->m_val, n->m_min, n->m_max)) {
								if (n->m_action) {
									std::invoke(std::move(n->m_action));
								}
							}
							change_mouse_on_hover(n->m_description);
							ImGui::PopItemWidth();
							ImGui::PopID();
						}
						else {
							add_option<Framework::number<float>>(n->get_name(), n->get_description(), n->m_val, n->m_min, n->m_max, n->m_step, n->m_precision, n->m_active_on_horizontal, "", (n->m_name == "Delay") ? "ms" : "", n->m_action);
						}

						break;
					}
					case eCommandType::choose: {
						auto c = g_feature_manager.get_command<choose_option>(id.c_str());
						if (g_interface->m_click_ui) {
							//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
							if (ImGui::Combo(c->get_name().c_str(), c->m_current_item, c->m_items.data(), c->m_items.size())) {
								if (c->m_action) {
									c->m_action();
								}
							}
							change_mouse_on_hover(c->m_description);
						}
						else {
							add_option<Framework::choose>(c->get_name(), c->get_description(), c->m_items, c->m_current_item, c->m_active_on_horizontal, c->m_action);
						}
						break;
					}
					case eCommandType::toggle_with_choose: {
						auto twc{ g_feature_manager.get_command<toggle_with_choose_option>(id.c_str()) };
						if (g_interface->m_click_ui) {
							ImGui::PushID(twc->get_id());
							//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
							if (ImGui::Checkbox(twc->get_name().c_str(), twc->m_toggle)) {
								if (!twc->is_toggled()) {
									g_fiber_pool.queue([=] {
										if (twc->m_on_disable && !*twc->m_toggle)
											twc->m_on_disable();
										});
								}
							}
							change_mouse_on_hover(twc->m_description);
							ImGui::SameLine();
							ImGui::Combo("", twc->m_current_item, twc->m_items.data(), twc->m_items.size());
							change_mouse_on_hover(twc->m_description);
							ImGui::PopID();
						}
						else {
							add_option<Framework::toggle_with_choose>(twc->get_name(), twc->get_description(), twc->m_toggle, twc->m_items, twc->m_current_item, twc->m_active_on_horizontal, [=] {
								g_fiber_pool.queue([=] {
									if (!twc->m_on_disable) return;

									if (!twc->is_toggled())
										twc->m_on_disable();
								});
							});
						}
						break;
					}
					case eCommandType::toggle_with_number: {
						auto twn{ g_feature_manager.get_command<toggle_with_float_option>(id.c_str()) };
						if (g_interface->m_click_ui) {
							ImGui::PushID(twn->get_id());
							//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
							if (ImGui::Checkbox(twn->get_name().c_str(), twn->m_toggle)) {
								if (!twn->is_toggled()) {
									g_fiber_pool.queue([=] {
										if (twn->m_on_disable && !*twn->m_toggle)
											twn->m_on_disable();
									});
								}
							}
							change_mouse_on_hover(twn->m_description);
							ImGui::SameLine();
							ImGui::PushItemWidth(135.f);
							ImGui::SliderFloat("", twn->m_val, twn->m_min, twn->m_max);
							change_mouse_on_hover(twn->m_description);
							ImGui::PopItemWidth();
							ImGui::PopID();
						}
						else {
							add_option<Framework::toggle_with_number<float>>(twn->get_name(), twn->get_description(), twn->m_toggle, twn->m_val, twn->m_min, twn->m_max, twn->m_step, twn->m_precision, twn->m_active_on_horizontal, "", "", [=] {
								g_fiber_pool.queue([=] {
									if (!twn->m_on_disable) return;

									if (!twn->is_toggled())
										twn->m_on_disable();
								});
							});
						}
						break;
					}
					case eCommandType::button: {
						auto b{ g_feature_manager.get_command<button_option>(id.c_str()) };
						if (g_interface->m_click_ui) {
							//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
							if (ImGui::Button(b->get_name().c_str())) {
								g_fiber_pool.queue([=] {
									std::invoke(std::move(b->m_action));
								});
							}
							change_mouse_on_hover(b->m_description);
						}
						else {
							add_option<Framework::button>(b->get_name(), b->get_description(), [=] {
								g_fiber_pool.queue([=] {
									b->m_action();
								});
							});
						}
						break;
					}
					case eCommandType::keyboard: {
						auto k{ g_feature_manager.get_command<keyboard_option>(id.c_str()) };
						if (g_interface->m_click_ui) {
							
						}
						else {
							add_option<Framework::keyboard>(k->m_name, "", k->m_str, 9999, k->m_action);
						}
						break;
					}
					
					
				}
			}
			return true;
		}

	}
	class current_sub {
	public:
		void option(str id) {
			if (!drawer::get_from_id(id)) {
				add_option<Framework::button>(id + " does not exist.", "");
			}
		}
		void text(str text) {
			add_option<Framework::button>(text, "");
		}
		void text_right(str text, str right) {
			add_option<Framework::button>(Framework::button(text, "").set_right_text(right));
		}
		void toggle(str name, str description, bool* tog) {
			if (g_interface->m_click_ui) {
				ImGui::Checkbox(name.c_str(), tog);
				change_mouse_on_hover();
			}
			else {
				add_toggle(name, description, tog);
			}
		}
		void toggle(str name, str description, bool& tog) {
			if (g_interface->m_click_ui) {
				ImGui::Checkbox(name.c_str(), &tog);
				change_mouse_on_hover();
			}
			else {
				add_toggle(name, description, &tog);
			}
		}
		void toggle(str name, bool* tog, std::function<void()> action = [] {}) {
			if (g_interface->m_click_ui) {
				if (ImGui::Checkbox(name.c_str(), tog)) {
					g_fiber_pool.queue([=] {
						action();
					});
				}
				change_mouse_on_hover();
			}
			else {
				add_toggle(name, "", tog, [=] {
					g_fiber_pool.queue([=] {
						action();
					});
				});
			}
		}
		void choose(str name, std::vector<ccp> ar, int* curr, bool active_on_horizontal = false, std::function<void()> action = [] {}) {
			if (g_interface->m_click_ui) {
				if (ImGui::Combo(name.c_str(), curr, ar.data(), ar.size())) {
					if (action) {
						action();
					}
				}
				change_mouse_on_hover();
			}
			else {
				add_option<Framework::choose>(name, "", ar, curr, active_on_horizontal, action);
			}
		}
		template <typename t>
		void toggle_with_number(str name, bool* tog, t* val, t min, t max, t step, t per) {
			add_option<Framework::toggle_with_number<t>>(name, "", tog, val, min, max, step, per);
		}
		void toggle_with_choose(str name, bool* tog, std::vector<ccp> vec, int* sel) {
			add_option<Framework::toggle_with_choose>(name, "", tog, vec, sel);
		}
		void submenu(str name, str id) {
			add_submenu(name, "", rage::joaat(id));
		}
		void submenu(str name, str desc, str id) {
			add_submenu(name, desc, rage::joaat(id));
		}
		void submenu(str name, str id, std::function<void()> submenu, float length = 190.f, bool tabbb = false) {
			static int itemCount = 0;

			if (g_interface->m_click_ui) {
				click_ui::child(name, length, [=] {
					std::invoke(std::move(submenu));
				});
				itemCount++;
			}
			else {
				if (!tabbb) {
					add_submenu(name == "Misc" ? "Miscellaneous" : name, "", rage::joaat(id), [] {});
				}
				g_interface->add<Framework::regular_submenu>(name == "Misc" ? "Miscellaneous" : name, rage::joaat(id), [=](Framework::regular_submenu* sub) {
					std::invoke(std::move(submenu));
				});
			}
		}

		void submenu_second(str name, str id, std::function<void()> submenu) {
			if (g_interface->m_click_ui) {
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 5);
				if (ImGui::TreeNode(name.c_str())) {
					submenu();
					ImGui::TreePop();
				}
			}
			else {
				add_submenu(name == "Misc" ? "Miscellaneous" : name, "", rage::joaat(id), [] {});
				g_interface->add<Framework::regular_submenu>(name == "Misc" ? "Miscellaneous" : name, rage::joaat(id), [=](Framework::regular_submenu* sub) {
					std::invoke(std::move(submenu));
				});
			}
		}
		void submenu(str name, str id, str desc, std::function<void()> submenu) {
			if (g_interface->m_click_ui) {
				//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150);
				if (ImGui::TreeNode(name.c_str())) {
					submenu();
					ImGui::TreePop();
				}
				change_mouse_on_hover();
			}
			else {
				add_submenu(name == "Misc" ? "Miscellaneous" : name, desc, rage::joaat(id), [] {});
				g_interface->add<Framework::regular_submenu>(name == "Misc" ? "Miscellaneous" : name, rage::joaat(id), [=](Framework::regular_submenu* sub) {
					std::invoke(std::move(submenu));
					});
			}
		}
		bool redo_actions{ false };
		void submenu(str name, str id, std::function<void()> action, std::function<void()> submenu) {
			if (g_interface->m_click_ui) {
				static bool invoked_action{ false };
				if (!invoked_action) {
					g_fiber_pool.queue([=] {
						action();
					});
					invoked_action = true;
				}
				if (redo_actions) {
					invoked_action = false;
					redo_actions = false;
				}
				click_ui::child(name, 190.f, [=] {
					std::invoke(std::move(submenu));
				});
			}
			else {
				add_submenu(name == "Misc" ? "Miscellaneous" : name, "", rage::joaat(id), [=] {
					g_fiber_pool.queue([=] {
						action();
						});
					});
				g_interface->add<Framework::regular_submenu>(name == "Misc" ? "Miscellaneous" : name, rage::joaat(id), [=](Framework::regular_submenu* sub) {
					std::invoke(std::move(submenu));
					});
			}
		}
		void submenu_second(str name, str id, std::function<void()> action, std::function<void()> submenu) {
			static bool is_opened{ false };
			if (g_interface->m_click_ui) {
				if (ImGui::TreeNode(name.c_str())) {
					if (!is_opened) {
						is_opened = true;
						g_fiber_pool.queue([=] {
							std::invoke(std::move(action));
						});
					}

					submenu();
					ImGui::TreePop();
				}
				else {
					is_opened = false;
				}
			}
			else {
				add_submenu(name == "Misc" ? "Miscellaneous" : name, "", rage::joaat(id), [=] {
					g_fiber_pool.queue([=] {
						action();
						});
					});
				g_interface->add<Framework::regular_submenu>(name == "Misc" ? "Miscellaneous" : name, rage::joaat(id), [=](Framework::regular_submenu* sub) {
					std::invoke(std::move(submenu));
				});
			}
		}
		void submenu_plr(u8* player, str id, std::function<void()> action, std::function<void()> submenu) {
			add_submenu(g_pointers->m_get_net_player(*player)->get_name(), "", rage::joaat(id), [=] {
				g_fiber_pool.queue([=] {
					action();
					});
			});
			g_interface->add<Framework::player_submenu>(player, rage::joaat(id), [=](Framework::player_submenu* sub) {
				std::invoke(std::move(submenu));
			});
		}
		void submenu2(str name, str id, std::function<void()> submenu) {
			if (g_interface->m_click_ui) {
				if (ImGui::TreeNode(name.c_str())) {
					submenu();
					ImGui::TreePop();
				}
			}
			else {
				add_submenu(name, "", rage::joaat(id));
				std::invoke(std::move(submenu));
			}
		}
		void submenu_tab(str name, Framework::tab selected_tab) {
			ImGui::PushFont(g_renderer->m_icon_font);
			auto selected{ g_interface->m_selected_tab == selected_tab };
			auto& colors{ ImGui::GetStyle().Colors };
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(72 / 255.f, 117 / 255.f, 230 / 255.f, 255 / 255.f));
			selected ? ImGui::PushStyleColor(ImGuiCol_Button, colors[ImGuiCol_ButtonActive]) : ImGui::PushStyleColor(ImGuiCol_Button, colors[ImGuiCol_Button]);
			if (ImGui::Button(name.c_str(), ImVec2(50.f, 50.f))) {
				g_interface->m_selected_tab = selected_tab;
			}
			change_mouse_on_hover();
			ImGui::PopStyleColor(2);
			ImGui::PopFont();
		}
		
		template <typename T>
		void number(str name, str description, T& val, number_modifers<T> modifiers, bool active_on_horizontal = true, std::function<void()> action = [] {}) {
			add_option<Framework::number<T>>(name, description, &val, modifiers.min, modifiers.max, modifiers.step, modifiers.precision, active_on_horizontal, "", name == "Delay" ? "ms" : "", [=] {
				g_fiber_pool.queue([=] {
					action();
				});
			});
		}
		template <typename T>
		void number(str name, T& val, number_modifers<float> modifiers, bool active_on_horizontal = true, std::function<void()> action = [] {}) {
			if (g_interface->m_click_ui) {
				ImGui::PushItemWidth(135.f);
				ImGui::SliderScalar(name.c_str(), ImGuiDataType_Float, &val, &modifiers.min, &modifiers.max);
				if (action) {
					if (ImGui::IsItemEdited()) {
						queue_function(action)
					}
				}
				ImGui::PopItemWidth();
			}
			else {
				add_option<Framework::number<T>>(name, "", &val, modifiers.min, modifiers.max, modifiers.step, modifiers.precision, active_on_horizontal, "", name == "Delay" ? "ms" : "", [=] {
					g_fiber_pool.queue([=] {
						action();
						});
					});
			}
		}
		template <typename T>
		void number(str name, T* val, number_modifers<float> modifiers, bool active_on_horizontal = true, std::function<void()> action = [] {}) {
			if (g_interface->m_click_ui) {
				ImGui::PushItemWidth(135.f);
				ImGui::SliderScalar(name.c_str(), ImGuiDataType_Float, val, &modifiers.min, &modifiers.max);
				if (action) {
					if (ImGui::IsItemEdited()) {
						queue_function(action)
					}
				}
				ImGui::PopItemWidth();
			}
			else {
				add_option<Framework::number<T>>(name, "", val, modifiers.min, modifiers.max, modifiers.step, modifiers.precision, active_on_horizontal, "", name == "Delay" ? "ms" : "", [=] {
					g_fiber_pool.queue([=] {
						action();
					});
				});
			}
		}
		void number_float(str name, float* val, number_modifers<float> modifiers, bool active_on_horizontal = true, std::function<void()> action = [] {}) {
			add_option<Framework::number<float>>(name, "", val, modifiers.min, modifiers.max, modifiers.step, modifiers.precision, active_on_horizontal, "", name == "Delay" ? "ms" : "", [=] {
				g_fiber_pool.queue([=] {
					action();
				});
			});
		}
		void vehicle_button(str id, str name) {
			if (g_feature_manager.does_exist(id.c_str())) {
				auto feature{ g_feature_manager.get_command<button_option>(id.c_str()) };
				if (g_interface->m_click_ui) {
					if (ImGui::Button(feature->get_name().c_str())) {
						g_fiber_pool.queue([=] {
							std::invoke(std::move(feature->m_action));
						});
					}
					change_mouse_on_hover();
				}
				else {
					add_option<Framework::vehicle_button>(feature->get_name(), name, feature->m_action);
				}
			}
		}
		void keyboard(str name, str& board, std::function<void()> action = [] {}) {
			add_option<Framework::keyboard>(name, "", &board, 9999, action);
		}
		void button(str name, std::function<void()> action) {
			if (g_interface->m_click_ui) {
				if (ImGui::Button(name.c_str())) {
					g_fiber_pool.queue([=] {
						std::invoke(std::move(action));
					});
				}
				change_mouse_on_hover();
			}
			else {
				add_option<Framework::button>(name, "", [=] {
					g_fiber_pool.queue([=] {
						action();
					});
				});
			}
		}

		//athena moment!!
		ImVec2 getCenteredTextPosition(const char* text, ImVec2 rectMin, ImVec2 rectMax) {
			ImVec2 textSize = ImGui::CalcTextSize(text);
			ImVec2 textPos;
			textPos.x = rectMin.x + ((rectMax.x - rectMin.x) - textSize.x) * 0.443f;
			textPos.y = rectMin.y + ((rectMax.y - rectMin.y) - textSize.y) * 0.5f;
			return textPos;
		}
		void seperator(str name) {
			if (g_interface->m_click_ui) {
				ImVec2 contentRegionMin = ImGui::GetWindowContentRegionMin();
				ImVec2 contentRegionMax = ImGui::GetWindowContentRegionMax();
				ImVec2 textPosition = getCenteredTextPosition(name.c_str(), contentRegionMin, contentRegionMax);
				ImGui::SetCursorPosX(textPosition.x);
				ImGui::Text(name.c_str());
			}
			else {
				add_seperator(name);
			}
		}
	public:
		template <typename ...TArgs>
		inline void add_seperator(TArgs&&... args) {
			Framework::g_options.push_back(std::make_unique<Framework::seperator>(std::forward<TArgs>(args)...));
		}
	private:
		template <typename ...TArgs>
		inline void add_choose(TArgs&&... args) {
			if (g_interface->m_click_ui) return;

			Framework::g_options.push_back(std::make_unique<Framework::choose>(std::forward<TArgs>(args)...));
		}
		template <typename ...TArgs>
		inline void add_toggle(TArgs&&... args) {
			if (g_interface->m_click_ui) return;

			Framework::g_options.push_back(std::make_unique<Framework::toggle>(std::forward<TArgs>(args)...));
		}
		template <typename ...TArgs>
		inline void add_submenu(TArgs&&... args) {
			if (g_interface->m_click_ui) return;

			Framework::g_options.push_back(std::make_unique<Framework::submenu>(std::forward<TArgs>(args)...));
		}
	};
	Singleton<current_sub> draw;

	void add_submenu(str name, str id, std::function<void()> action, std::function<void()> submenu) {
		draw->submenu(name, id, action, submenu);
	}
	void add_submenu(str name, str id, std::function<void()> submenu) {
		draw->submenu(name, id, submenu);
	}
}

#define inline_item click_ui::same_line();
