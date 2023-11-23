#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "movement.h"
#include "disables.h"
#include "regeneration.h"
#include "collision.h"
#include "model_changer.h"
#include "clipsets.h"
#include "ped_matrix.h"
#include "scenarios.h"
#include "magnet.h"
#include "config_flags.h"
#include "visions.h"
#include "outfit_editor.h"
namespace Base::submenus::self {
	void main() {
		if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::self) return;

		click_ui::setup_col("self");
		draw->submenu("Core", "self_core", [] {
			draw->option("self_godmode");
			draw->option("invisible");
			draw->option("fov");
			draw->option("seatbelt");
			inline_item
			draw->option("attack_friendly");
			draw->option("explosive_melee");
			inline_item
			draw->option("mobile_radio");
			draw->option("instantly_enter_vehicles");
			draw->option("upperbody_damage_only");
			draw->option("take_less_damage");
			inline_item
			draw->option("ignored_by_peds");
			draw->option("push_water_away");
			draw->option("skydive");
			inline_item
			draw->option("max_health");
			inline_item
			draw->option("max_armor");
			inline_item
			draw->option("suicide");
			draw->option("remove_armor");
			inline_item
			draw->option("clear_tasks");
		}, 270);
		draw->submenu("Movement", "self_movementtab", submenus::self::movement);
		draw->submenu("Forcefield", "self_forcefield", submenus::self::forcefield);
		draw->submenu("Misc", "self_misc", [] {
			draw->submenu_second("Collision", "self_misc:collision", submenus::self::collision);
			draw->submenu_second("Thresholds", "self_misc:thresholds", [] {
				draw->option("hurt_threshold");
				draw->option("dying_threshold");
				draw->option("fatigued_threshold");
				draw->option("injured_threshold");
				});
			draw->submenu_second("Magnet", "self_magnet", submenus::self::magnet);
			draw->option("fast_respawn");
			inline_item
			draw->option("always_aiming");
			draw->option("auto_open_parachute");
			inline_item
			draw->option("crouched");
			draw->option("infinite_oxygen");
			draw->option("heading");
		}, 150);
		draw->submenu("Appearance", "self_appearance", [] {
			draw->submenu_second("Outfit Editor", "self_outfit_editor", submenus::self::outfit_editor);
			draw->submenu_second("Model Changer", "self_model_changer", submenus::self::model_changer);
			draw->submenu_second("Wardrobe", "self_wardrobe", [] {
				draw->option("tron_loop");
				draw->button("Clear Props", [] {
					PED::CLEAR_ALL_PED_PROPS(g_utils->self());
					});
				draw->seperator("Random");
				draw->button("Props", [] {
					PED::SET_PED_RANDOM_PROPS(g_utils->self());
					}); 
				draw->button("Components", [] {
					for (int i = 0; i < 12; i++)
						PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), i, MISC::GET_RANDOM_INT_IN_RANGE(0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(g_utils->self(), i)), MISC::GET_RANDOM_INT_IN_RANGE(0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(g_utils->self(), i, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(g_utils->self(), i))), 0);
					});
				});
			});
		click_ui::next_col();
		draw->submenu("Wanted Level", "self_wanted_level", [] {
			draw->option("neverWanted");
			inline_item
			draw->option("disable_wanted_level_sharing");
			draw->option("wanted_level");
		}, 68);
		draw->submenu("Animations", "self_animations", [] {
			draw->submenu_second("Scenarios", "self_scenarios", submenus::self::scenarios);
			draw->submenu_second("Clipsets", "self_clipsets", submenus::self::clipsets);
		}, 50);
		draw->submenu("Visual", "self_visuals", [] {
			draw->submenu_second("Matrix", "self/matrix", submenus::self::ped_matrix);
			draw->submenu_second("Visions", "visions", submenus::self::visions);
			draw->submenu_second("Handtrails", "handtrails", [] {
				draw->option("handtrails");
				draw->seperator("Settings");
				draw->option("handtrails_scale");
				draw->submenu_second("Color", "handtrails_color", [] {
					draw->option("handtrails_rainbow");
					draw->seperator("Main");
					draw->option("handtrails_r");
					draw->option("handtrails_g");
					draw->option("handtrails_b");
				});
			});
			draw->option("wet");
			draw->option("snow_trails");
			inline_item
			draw->option("shrink");
			draw->option("self_opacity");
		}, 95);
		draw->submenu("Regeneration", "self_health:regeneration", submenus::self::regeneration);
		draw->submenu("Disables", "self_disables", submenus::self::disables, 70);
		draw->submenu("Spinbot", "self_spin_bot", [] {
			draw->option("spinbot");
			draw->seperator("Settings");
			draw->option("spin_bot_first_rotation");
			inline_item
			draw->option("spin_bot_second_rotation");
			draw->option("spinbotSpeed");
		}, 110);
		draw->submenu("Abilities", "abilites_self", [] {
			draw->option("ironman");
		}, 45);
		draw->submenu("Flags", "config_flags", submenus::self::config_flags::on_click, submenus::self::config_flags::init);
		click_ui::end_col();
	}
}

