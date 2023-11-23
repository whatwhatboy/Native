#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "src/core/script/submenus/vehicle/stick_to_ground.h"
#include "disables.h"
#include <src/rage/vehicle/CVehicleModelInfo.hpp>
#include "engine_sound.h"
#include "los_santos_customs.h"
#include "particles.h"
#include "color.h"
#include "src/core/script/configs/gravity.h"
#include "auto_pilot.h"
#include "handling.h"
#include "parachute.h"
#include "tire_tracks_vfx.h"
#include "ramp.h"
#include <src/memory/pointers/scanning.h>
#include "src/memory/cdeclstub.h"
namespace Base::submenus::vehicle {
	bool ramp2{ false };
	bool rocket_boost{ false };
	bool jump{ false };
	std::string save_vehicle_gravity;
	bool m_has_custom_wheels;
	int forward_speed{ 100 };
	int backward_speed{ 100 };
	static cdecl_stub<void(void*, int, float, float, float, bool, bool)> breakOffVehicleWheel([]
		{
			return get_call(g_pointers->m_break_off_wheels);
		});
	void main() {
		if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::vehicle) return;

		click_ui::setup_col("vehicle");
		draw->submenu("Core", "vehicle_core", [] {
			draw->option("vehicle_godmode");
			draw->option("explode_on_impact");
			draw->option("always_extend_mk1_wings");
			draw->option("easy_to_land");
			draw->option("invert_controls");
			draw->option("reduce_grip");
			static float rust;
			static float dirt_level{ 1.0f };
			draw->number("Dirt Level", dirt_level, { -100.0f, 100.f, 0.1f, 1 }, true, [=] {
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(g_utils->vehicle(), dirt_level);
				});
			draw->number("Rust", "Only works in vehicles like the besra", rust, { 0.0f, 1.f, 0.1f, 1 }, true, [=] {
				VEHICLE::SET_VEHICLE_ENVEFF_SCALE(g_utils->vehicle(), rust);
				});
			draw->option("helicopter_lag_rate");
			draw->option("forklift_height");
		});
		draw->submenu("Abilities", "vehicle:modifiers", [=] {
			draw->submenu_second("Ramp Buggy", "vehicle:ramp_buggy", [=] {
				add_option<Framework::toggle>("Override", "", &ramp2, [=] {
					if (ramp2)
						g_interface->m_flag += 512;
					else
						g_interface->m_flag -= 512;
					});
				draw->seperator("Modifiers");
				draw->option("sideways_launch_motion");
				draw->option("upward_launch_motion");
			});
			draw->submenu_second("Rocket Boost", "vehicle:rocket_boost", [=] {
				add_option<Framework::toggle>("Override", "", &rocket_boost, [=] {
					if (rocket_boost)
						g_interface->m_flag += 64;
					else
						g_interface->m_flag -= 64;

					});
				draw->seperator("Modifiers");
				draw->option("infinite_rocket_boost");
				draw->option("rocket_boost_always_active");
				draw->option("rocket_boost_percentage");
				draw->option("rocket_boost_refill_time");
				});
			draw->submenu_second("Jump", "vehicle:jump", [=] {
				add_option<Framework::toggle>("Override", "", &jump, [=] {
					if (jump)
						g_interface->m_flag += 32;
					else
						g_interface->m_flag -= 32;
					});
				draw->seperator("Modifiers");
				draw->option("flags_higher_jump");
				draw->option("double_click_for_jump");
				draw->option("no_charge");
				draw->number("Charge", g_utils->cvehicle()->m_jump_boost_charge, { 0, 100, 0.1, 1 });
				});
			draw->submenu_second("Parachute", "vehicle_parachute", submenus::vehicle::parachute);
			});
		draw->submenu("Gravity", "vehicle/gravity", [] {
			draw->submenu_second("Config", "vehicle/gravity/config", [] {
				add_option<Framework::keyboard>("Save", "", &save_vehicle_gravity, 64, [] {
					if (GetAsyncKeyState(VK_RETURN) && !Framework::keyboard_open)
						configs::vehicle_gravity::save(save_vehicle_gravity);
					});
				draw->seperator("List");
				for (auto file : g_file_utils->get_all_files_from_dict(g_file_utils->get_main_directory() + "\\Configs\\Gravity\\")) {
					add_option<Framework::button>(file.name_without_extension.c_str(), "", [=] {
						configs::vehicle_gravity::load(file.name_without_extension);
						});
				}
				});
			draw->option("vehicle_gravity_presets");
			draw->seperator("Main");
			draw->option("vehicle_gravity_global");
			draw->option("vehicle_gravity");
			});
		draw->submenu("Movement", "vehicle:movement", [=] {
			draw->submenu_second("Boost", "vehicle:movement:horn_boost", [=] {
				draw->submenu_second("Horn", "horn_boost", [=] {
					draw->option("horn_boost");
					draw->seperator("Settings");
					draw->option("horn_boost_smooth");
					draw->option("horn_boost_only_on_ground");
					draw->option("horn_boost_speed");
					draw->option("horn_boost_power");
					});
				draw->number("Forward", forward_speed, { 0, 300, 1, 0 }, false, [=] {
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(g_utils->vehicle(), forward_speed);
					});
				draw->number("Backward", backward_speed, { 0, 300, 1, 0 }, false, [=] {
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(g_utils->vehicle(), -backward_speed);
					});
				});
			draw->submenu_second("Acceleration", "vehicle:movement:acceleration", submenus::vehicle::movement::acceleration);
			draw->submenu_second("Stick To Ground", "vehicle:stick_to_ground", submenus::vehicle::stick_to_ground);
			draw->option("negitive_torque");
			draw->option("drive_underwater");
			draw->option("drive_on_water");
			draw->option("auto_flip");
			draw->option("drift_tires");
			draw->option("bypass_max_speed");
			draw->option("instant_brake");
			});
		draw->submenu("Visual", "vehicle:visuals", [] {
			draw->submenu_second("Wheels", "veh_visuals_wheels", [] {
				draw->submenu_second("Tracks", "vehicle:visual:tire_tracks", [] {
					draw->submenu_second("VFX", "tire_tracks_vfx", submenus::vehicle::tire_tracks_vfx);
					draw->option("tire_tracks");
					draw->seperator("Settings");
					draw->submenu_second("Color", "vehicle:visual:tire_tracks:color", [] {
						draw->option("tire_tracks_rainbow");
						draw->option("tire_tracks_match_car");
						draw->seperator("Main");
						draw->option("tire_tracks_r");
						draw->option("tire_tracks_g");
						draw->option("tire_tracks_b");
						});
					draw->option("tire_tracks_always");
				});
				/*draw->submenu_second("Break Off", "break_off_wheels", [=] {
					draw->button("Test", [] {
						auto damageStruct = (void*)((char*)((rage::fwEntity*)g_utils->cvehicle()) + g_pointers->m_damage_struct);
						breakOffVehicleWheel(damageStruct, 0, 0.0f, 0.0f, 0.0f, false, true); broke tried to skid fivem :skull:
						});
				});*/
				draw->option("wheel_offset");
				draw->option("increase_wheel_crush_damage");
				draw->option("reset_wheels");
				draw->seperator(!m_has_custom_wheels ? "You must have custom wheels for this option." : "Matrix");
				if (g_utils->cvehicle() && m_has_custom_wheels) {
					draw->number("Height", g_utils->cvehicle()->m_draw_data->m_vehicle_stream_render->m_tire_height, { 0, 1000.f, 0.1f, 1 });
					draw->number("Width", g_utils->cvehicle()->m_draw_data->m_vehicle_stream_render->m_tire_width, { 0, 1000.f, 0.1f, 1 });
				}
			});
			draw->submenu_second("Particles", "vehicle:visual:particles", submenus::vehicle::particles);
			draw->submenu_second("Color", "vehicle:visual:color", submenus::vehicle::color);
			draw->option("vehicle_scale");
			draw->option("headlight_multiplier");
			draw->option("shaky_shell");
			draw->option("burned");
			draw->option("taxi_lights");
			draw->option("vehicle_opacity");
		});
		draw->submenu("Audio", "vehicle:audio", [] {
			draw->submenu_second("Engine Sound", "vehicle:audio:engine_sound", submenus::vehicle::engine_sound);
			draw->option("suppress_door_noises");
			draw->option("mute_sirens");
			});
		draw->submenu("Auto Pilot", "", submenus::vehicle::auto_pilot::main);
		draw->submenu("Misc", "vehicle:misc", [] {
			draw->submenu_second("Towtruck", "vehicle:towtruck", submenus::vehicle::towtruck);
			draw->submenu_second("Flags", "vehicle:misc:flags", [] {
				draw->option("flags_brake");
				draw->option("flags_handbrake");
				draw->option("flags_racing");
				draw->option("flags_ceo");
				draw->option("flags_can_wheelie");
				draw->option("flags_can_be_saved_in_garage");
				});
			draw->submenu_second("Trailer", "vehicle:misc:trailer", [] {
				draw->option("trailer_set_raised");
				draw->option("trailer_set_lowered");
				});
			draw->submenu_second("Deluxo", "deluxo_modifiers", [] {
				draw->option("break_deluxo");
				draw->option("deluxo_state");	
				});
			draw->option("open_rear_doors_on_explosion");
			draw->option("strong_axles");
			});
		click_ui::next_col();
		draw->submenu("Los Santos Customs", "lsc", submenus::vehicle::los_santos_customs_on_enter, submenus::vehicle::los_santos_custom);
		draw->submenu("Weapons", "vehicle_weapons", [] {
			draw->option("vehicle_weapons");
			draw->seperator("Settings");
			draw->option("vehicle_weapons_selected");
			draw->submenu_second("Offset", "vehicle_weapons_offset", [] {
				draw->option("vehicle_weapons_offset_x");
				draw->option("vehicle_weapons_offset_y");
				draw->option("vehicle_weapons_offset_z");
				});
			draw->option("vehicle_weapons_trajectory");
			draw->option("vehicle_weapons_speed");
			draw->option("vehicle_weapons_delay");
			draw->seperator("Game");
			draw->option("rapid_fire_vehicle_weapons");
			});
		draw->submenu("Health", "vehicle_health", [] {
			draw->option("auto_repair");
			draw->seperator("Single");
			draw->option("repair");
			});
		draw->submenu("Acrobatics", "vehicle:movement:acrobatics", [] {
			draw->option("select_acrobatic");
			draw->option("start_acrobatic");
			draw->seperator(misc_name);
			draw->option("reverse_acrobatic");
			draw->option("random_acrobatics");
			draw->option("acrobatic_on_horn");
			draw->option("acrobatic_force");
		});
		draw->submenu("Disables", "vehicle:misc:disables", submenus::vehicle::disables);
		draw->submenu("Handling", "Vehicle/Handling", submenus::vehicle::handling);
		draw->submenu("Doors", "vehicle_doors", [] {
			draw->option("open_all_doors");
			draw->option("close_all_doors");
			});
		draw->submenu("Moving Plate", "moving_plate", [] {
			draw->option("moving_plate");
			draw->seperator("Settings");
			draw->option("moving_plate_text");
			draw->option("moving_plate_delay");
			});
		draw->submenu("Ramp", "vehicle_ramp", submenus::vehicle::ramp::init);
		click_ui::end_col();
			
	}
}
