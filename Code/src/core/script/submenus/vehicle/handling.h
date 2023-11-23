#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/option_types/keyboard.h>
#include <src/framework/option_types/button.h>
namespace Base::submenus::vehicle {
	using namespace Framework;
	void draw_class_2(const char* name) {
		draw->submenu(name, name, [=] {
			for (auto& veh : vehicle_hash_list) {
				if (strcmp(veh.m_class, name) == 0) {
					draw->button(g_feature_manager.get_command<button_option>(std::to_string(veh.hash).c_str())->get_name(), [=] {
							VEHICLE::SET_VEHICLE_HANDLING_OVERRIDE(g_utils->vehicle(), veh.hash);
					});
				}
			}
			});
	}

	void handling() {
		draw->submenu_second("Override", "vehicle/handling override", [] {
			draw->submenu_second("Search", "vehicle:audio:engine_sound:search", [] {
				static std::string search;
				draw->keyboard("Input", search);
				draw->seperator("Results");
				if (search == "") return;

				for (auto& veh : vehicle_hash_list) {
					if (g_utils->has_string_attached(veh.name, search)) {
						draw->button(g_feature_manager.get_command<button_option>(std::to_string(veh.hash).c_str())->get_name(), [=] {
							VEHICLE::SET_VEHICLE_HANDLING_OVERRIDE(g_utils->vehicle(), veh.hash);
						});
					}
				}
			});
			draw->button("Reset To Default", [] {
				VEHICLE::SET_VEHICLE_HANDLING_OVERRIDE(g_utils->vehicle(), ENTITY::GET_ENTITY_MODEL(g_utils->vehicle()));
			});
			draw->seperator("Categories");
			for (auto& i : vehicle_classes)
				draw_class_2(i.c_str());
		});
		draw->seperator("Main");
		if (!g_utils->cvehicle()) return;
		draw->submenu_second("Base", "base_handling", [] {
			auto handling{ g_utils->cvehicle()->m_handling_data };
			if (!handling) return;

			draw->number("Mass", &handling->m_mass, { -1000, 1000, 0.1, 1 });
			draw->number("Initial Drag Coeff", &handling->m_initial_drag_coeff, { -1000, 1000, 0.1, 1 });
			draw->number("Downforce Multiplier", &handling->m_downforce_multiplier, { -1000, 1000, 0.1, 1 });
			draw->number("Popup Light Rotation", &handling->m_popup_light_rotation, { -1000, 1000, 0.1, 1 });
			draw->number("Centre of Mass X", &handling->m_centre_of_mass.x, { -1000, 1000, 0.1, 1 });
			draw->number("Centre of Mass Y", &handling->m_centre_of_mass.y, { -1000, 1000, 0.1, 1 });
			draw->number("Centre of Mass Z", &handling->m_centre_of_mass.z, { -1000, 1000, 0.1, 1 });
			draw->number("Inertia Mult X", &handling->m_inertia_mult.x, { -1000, 1000, 0.1, 1 });
			draw->number("Inertia Mult Y", &handling->m_inertia_mult.y, { -1000, 1000, 0.1, 1 });
			draw->number("Inertia Mult Z", &handling->m_inertia_mult.z, { -1000, 1000, 0.1, 1 });
			draw->number("Buoyancy", &handling->m_buoyancy, { -1000, 1000, 0.1, 1 });
			draw->number("Drive Bias Rear", &handling->m_drive_bias_rear, { -1000, 1000, 0.1, 1 });
			draw->number("Drive Bias Front", &handling->m_drive_bias_front, { -1000, 1000, 0.1, 1 });
			draw->number("Acceleration", &handling->m_acceleration, { -1000, 1000, 0.1, 1 });
			draw->number("Initial Drive Gears", &handling->m_initial_drive_gears, { -1000, 1000, 0.1, 1 });
			draw->number("Drive Inertia", &handling->m_drive_inertia, { -1000, 1000, 0.1, 1 });
			draw->number("Upshift", &handling->m_upshift, { -1000, 1000, 0.1, 1 });
			draw->number("Downshift", &handling->m_downshift, { -1000, 1000, 0.1, 1 });
			draw->number("Initial Drive Force", &handling->m_initial_drive_force, { -1000, 1000, 0.1, 1 });
			draw->number("Drive Max Flat Velocity", &handling->m_drive_max_flat_velocity, { -1000, 1000, 0.1, 1 });
			draw->number("Initial Drive Max Flat Vel", &handling->m_initial_drive_max_flat_vel, { -1000, 1000, 0.1, 1 });
			draw->number("Brake Force", &handling->m_brake_force, { -1000, 1000, 0.1, 1 });
			draw->number("Brake Bias Front", &handling->m_brake_bias_front, { -1000, 1000, 0.1, 1 });
			draw->number("Brake Bias Rear", &handling->m_brake_bias_rear, { -1000, 1000, 0.1, 1 });
			draw->number("Handbrake Force", &handling->m_handbrake_force, { -1000, 1000, 0.1, 1 });
			draw->number("Steering Lock", &handling->m_steering_lock, { -1000, 1000, 0.1, 1 });
			draw->number("Steering Lock Ratio", &handling->m_steering_lock_ratio, { -1000, 1000, 0.1, 1 });
			draw->number("Traction Curve Max", &handling->m_traction_curve_max, { -1000, 1000, 0.1, 1 });
			draw->number("Traction Curve Lateral", &handling->m_traction_curve_lateral, { -1000, 1000, 0.1, 1 });
			draw->number("Traction Curve Min", &handling->m_traction_curve_min, { -1000, 1000, 0.1, 1 });
			draw->number("Traction Curve Ratio", &handling->m_traction_curve_ratio, { -1000, 1000, 0.1, 1 });
			draw->number("Curve Lateral", &handling->m_curve_lateral, { -1000, 1000, 0.1, 1 });
			draw->number("Curve Lateral Ratio", &handling->m_curve_lateral_ratio, { -1000, 1000, 0.1, 1 });
			draw->number("Traction Spring Delta Max", &handling->m_traction_spring_delta_max, { -1000, 1000, 0.1, 1 });
			draw->number("Traction Spring Delta Max Ratio", &handling->m_traction_spring_delta_max_ratio, { -1000, 1000, 0.1, 1 });
			draw->number("Low Speed Traction Loss Mult", &handling->m_low_speed_traction_loss_mult, { -1000, 1000, 0.1, 1 });
			draw->number("Camber Stiffness", &handling->m_camber_stiffness, { -1000, 1000, 0.1, 1 });
			draw->number("Traction Bias Front", &handling->m_traction_bias_front, { -1000, 1000, 0.1, 1 });
			draw->number("Traction Bias Rear", &handling->m_traction_bias_rear, { -1000, 1000, 0.1, 1 });
			draw->number("Traction Loss Mult", &handling->m_traction_loss_mult, { -1000, 1000, 0.1, 1 });
			draw->number("Suspension Force", &handling->m_suspension_force, { -1000, 1000, 0.1, 1 });
			draw->number("Suspension Comp Damp", &handling->m_suspension_comp_damp, { -1000, 1000, 0.1, 1 });
			draw->number("Suspension Rebound Damp", &handling->m_suspension_rebound_damp, { -1000, 1000, 0.1, 1 });
			draw->number("Suspension Upper Limit", &handling->m_suspension_upper_limit, { -1000, 1000, 0.1, 1 });
			draw->number("Suspension Lower Limit", &handling->m_suspension_lower_limit, { -1000, 1000, 0.1, 1 });
			draw->number("Suspension Raise", &handling->m_suspension_raise, { -1000, 1000, 0.1, 1 });
			draw->number("Suspension Bias Front", &handling->m_suspension_bias_front, { -1000, 1000, 0.1, 1 });
			draw->number("Suspension Bias Rear", &handling->m_suspension_bias_rear, { -1000, 1000, 0.1, 1 });
			draw->number("Anti Rollbar Force", &handling->m_anti_rollbar_force, { -1000, 1000, 0.1, 1 });
			draw->number("Anti Rollbar Bias Front", &handling->m_anti_rollbar_bias_front, { -1000, 1000, 0.1, 1 });
			draw->number("Anti Rollbar Bias Rear", &handling->m_anti_rollbar_bias_rear, { -1000, 1000, 0.1, 1 });
			draw->number("Roll Centre Height Front", &handling->m_roll_centre_height_front, { -1000, 1000, 0.1, 1 });
			draw->number("Roll Centre Height Rear", &handling->m_roll_centre_height_rear, { -1000, 1000, 0.1, 1 });
			draw->number("Collision Damage Mult", &handling->m_collision_damage_mult, { -1000, 1000, 0.1, 1 });
			draw->number("Weapon Damage Mult", &handling->m_weapon_damamge_mult, { -1000, 1000, 0.1, 1 });
			draw->number("Deformation Mult", &handling->m_deformation_mult, { -1000, 1000, 0.1, 1 });
			draw->number("Engine Damage Mult", &handling->m_engine_damage_mult, { -1000, 1000, 0.1, 1 });
			draw->number("Petrol Tank Volume", &handling->m_petrol_tank_volume, { -1000, 1000, 0.1, 1 });
			draw->number("Oil Volume", &handling->m_oil_volume, { -1000, 1000, 0.1, 1 });
			draw->number("Seat Offset Dist X", &handling->m_seat_offset_dist.x, { -1000, 1000, 0.1, 1 });
			draw->number("Seat Offset Dist Y", &handling->m_seat_offset_dist.y, { -1000, 1000, 0.1, 1 });
			draw->number("Seat Offset Dist Z", &handling->m_seat_offset_dist.z, { -1000, 1000, 0.1, 1 });

		});
	

	}
}
