#include "vehicle.h"
#include "src/Natives/Natives.h"
#include "src/fiber/script/manager/script_manager.h"
#include "src/memory/pointers/pointers.h"
#include <src/utility/enum.h>
#include "src/features/submenus/vehicle/misc/towtruck.h"
#include "src/features/submenus/vehicle/misc/spawn.h"
#include "src/features/submenus/vehicle/misc/disables.h"
#include "misc/stick_to_ground.h"
#include "misc/flags.h"
#include "misc/auto_repair.h"
#include "misc/misc.h"
#include "misc/modifiers.h"
#include "misc/ramp.h"
#include "misc/water.h"
#include "misc/horn_boost.h"
#include "misc/rocket_boost.h"
#include "misc/godmode.h"
#include "misc/tire_tracks.h"
#include "misc/gravity.h"
#include "misc/weapons.h"
#include "misc/acrobatics.h"
#include "misc/color.h"
#include <src/hooking/hooking.h>
#include "misc/wheel.h"
#include "misc/parachute.h"
#include "src/framework/vehicle_preview/vehicle_preview.h"
#include "misc/classes.h"
#define queue_job g_fiber_pool.queue([=] {
#define end_job });
namespace Base {
	const char* get_name_from_hash(Hash model) {
		const char* name{ VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model) };
		return name != nullptr ? name : "Unknown";
	}
	const char* get_vehicle_class_name(int id) {
		std::stringstream ss; ss << "VEH_CLASS_" << id;
		return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str());
	}
	int veh_count{};
	void update_hash_list() {
		for (std::int32_t j = 0; j < 23; j++)
			vehicle_classes.push_back(get_vehicle_class_name(j));
		if (g_pointers->m_hash_pool != nullptr) {
			for (std::int32_t i = 0; i < g_pointers->m_hash_pool->capacity; i++) {
				std::uint64_t info = g_pointers->m_hash_pool->get(i);
				if (info != NULL && (*(BYTE*)(info + 157) & 0x1F) == 5) {
					std::string make = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION((char*)(info + 0x2A4));
					std::string model = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION((char*)(info + 0x298));
					std::stringstream ss;
					if (!make.empty() && make != "NULL") {
						ss << make;
						if (!model.empty() && model != "NULL")
							ss << " ";
					}
					if (!model.empty() && model != "NULL")
						ss << model;
					if (ss.str().empty())
						ss << "Unknown";
					Hash hash = *(std::uint32_t*)(info + 0x18);
					vehicle_hash_list.push_back({ hash, get_name_from_hash(hash), vehicle_classes[VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(hash)].c_str() });
				}
			}
		}


	}
	void disables_add() {
		g_feature_manager.add<toggle_option>("disable_lockon", "Lockon", "Prevents other players from locking onto your\nvehicle.", &disables::lock_on::enabled, disables::lock_on::init, disables::lock_on::on_disable);
		g_feature_manager.add<toggle_option>("disable_brake_lights", "Brake Lights", "Suppresses the display of brake lights.", &disables::brake_lights::enabled, disables::brake_lights::init, disables::brake_lights::on_disable);
		g_feature_manager.add<toggle_option>("disable_oil_leaking", "Oil Leaking", "", &disables::oil_leaking::enabled, disables::oil_leaking::init, disables::oil_leaking::on_disable);
		g_feature_manager.add<toggle_option>("disable_petrol_leaking", "Petrol Leaking", "", &disables::petrol_leaking::enabled, disables::petrol_leaking::init, disables::petrol_leaking::on_disable);
		g_feature_manager.add<toggle_option>("disable_wheel_deformation", "Wheel Deformation", "", &disables::wheel_deforming::enabled, disables::wheel_deforming::init, disables::wheel_deforming::on_disable);
		g_feature_manager.add<toggle_option>("disable_vehicle_fire", "Fire", "", &disables::fire::enabled, disables::fire::init);
		g_feature_manager.add<toggle_option>("disable_extra_trick_forces", "BMX Extra Trick Forces", "", &disables::bmx_extra_trick_forces::enabled, disables::bmx_extra_trick_forces::init);
		g_feature_manager.add<toggle_option>("disable_vehicle_gravity", "Gravity", "", &disables::gravity::enabled, disables::gravity::init, disables::gravity::on_disable);
		g_feature_manager.add<toggle_option>("disable_pad_effects", "Pad Effects", "", &disables::pad_effects::enabled, disables::pad_effects::init, disables::pad_effects::on_disable);
		g_feature_manager.add<toggle_option>("disable_deformation", "Deformation", "", &disables::deformation::enabled, disables::deformation::init);
		g_feature_manager.add<toggle_option>("disable_glass_breaking", "Glass Breaking", "", &disables::glass_breaking::enabled, disables::glass_breaking::init, disables::glass_breaking::on_disable);
		g_feature_manager.add<toggle_option>("disable_parts_breaking_off", "Parts Breaking Off", "", &disables::parts_breaking_off::enabled, disables::parts_breaking_off::init);
		g_feature_manager.add<toggle_option>("disable_detachable_bumpers", "Special Bumpers", "", &disables::detachable_bumpers::enabled, disables::detachable_bumpers::init, disables::detachable_bumpers::on_disable);
		g_feature_manager.add<toggle_option>("disable_weapon_blades", "Weapon Blades", "", &disables::weapon_blades::enabled, disables::weapon_blades::init, disables::weapon_blades::on_disable);
		g_feature_manager.add<toggle_option>("disable_bike_wheelie", "Bike Wheelie", "", &disables::bike_wheelie::enabled, disables::bike_wheelie::init, disables::bike_wheelie::on_disable);
		g_feature_manager.add<toggle_option>("disable_sirens", "Sirens", "", &disables::sirens::enabled, disables::sirens::init, disables::sirens::on_disable);
		g_feature_manager.add<toggle_option>("disable_turret_movement", "Turret Movement", "", &disables::turret_movement::enabled, disables::turret_movement::init);
		g_feature_manager.add<toggle_option>("disable_slipstream", "Slipstream", "", &disables::slipstream::enabled, disables::slipstream::init, disables::slipstream::on_disable);
		g_feature_manager.add<toggle_option>("disable_neon_lights", "Neon Lights", "", &disables::neon_lights::enabled, disables::neon_lights::init, disables::neon_lights::on_disable);
	}
	void flags_add() {
		g_feature_manager.add<toggle_with_float_option>("flags_higher_jump", "Increase Height", "Raises the jump height of the special ability.", &vehicle_flags::higher_jump::enabled, &vehicle_flags::higher_jump::multiplier, 0, 1000, 0.1, 1, false, vehicle_flags::higher_jump::init, vehicle_flags::higher_jump::on_disable);
		g_feature_manager.add<toggle_option>("flags_brake", "Brake", "", &vehicle_flags::brake::enabled, vehicle_flags::brake::init, vehicle_flags::brake::on_disable);
		g_feature_manager.add<toggle_option>("flags_handbrake", "Handbrake", "", &vehicle_flags::handbrake::enabled, vehicle_flags::handbrake::init, vehicle_flags::handbrake::on_disable);
		g_feature_manager.add<toggle_option>("flags_racing", "Racing", "", &vehicle_flags::racing::enabled, vehicle_flags::racing::init, vehicle_flags::racing::on_disable);
		g_feature_manager.add<toggle_option>("flags_ceo", "CEO", "", &vehicle_flags::ceo::enabled, vehicle_flags::ceo::init, vehicle_flags::ceo::on_disable);
		g_feature_manager.add<toggle_option>("flags_can_wheelie", "Can Wheelie", "Enables all vehicles to perform a wheelie if they\npossess the appropriate level of torque.", &vehicle_flags::can_wheelie::enabled, vehicle_flags::can_wheelie::init, vehicle_flags::can_wheelie::on_disable);
		g_feature_manager.add<toggle_option>("flags_can_be_saved_in_garage", "Can Be Saved In Garage", "", &vehicle_flags::can_save_in_garage::enabled, vehicle_flags::can_save_in_garage::init, vehicle_flags::can_save_in_garage::on_disable);
		g_feature_manager.add<toggle_option>("no_charge", "Disable Charge", "", &vehicle_flags::disable_charge::enabled, vehicle_flags::disable_charge::init);
	}
	void trailer_add() {
		g_feature_manager.add<button_option>("trailer_set_raised", "Set Raised", "", [] {
			VEHICLE::SET_TRAILER_LEGS_RAISED(g_utils->vehicle());
		});
		g_feature_manager.add<button_option>("trailer_set_lowered", "Set Lowered", "", [] {
			VEHICLE::SET_TRAILER_LEGS_LOWERED(g_utils->vehicle());
		});
	}
	void add_ramp() {
		g_feature_manager.add<toggle_option>("ramp_override", "Override", "Allows ramp on any vehicle.", &ramp_enabled::enabled, ramp_enabled::init, ramp_enabled::on_disable);

		g_feature_manager.add<toggle_option>("sideways_launch_motion", "Sideways Launch Motion", "Launches the vehicle sideways.", &sideways_launch_motion::enabled, sideways_launch_motion::init, sideways_launch_motion::on_disable);
		g_feature_manager.add<toggle_option>("upward_launch_motion", "Upward Launch Motion", "Launches the vehicle upward.", &upways_launch_motion::enabled, upways_launch_motion::init, upways_launch_motion::on_disable);
	}
	void add_horn_boost() {
		g_feature_manager.add<toggle_with_choose_option>("horn_boost", "Enabled", &horn_boost::enabled, horn_boost::settings::boostType, &horn_boost::settings::boost_pos, false, horn_boost::init);
		g_feature_manager.add<toggle_with_choose_option>("horn_boost_smooth", "Smooth",&horn_boost::settings::smooth, horn_boost::settings::smooth_type, &horn_boost::settings::smoothPos);
		g_feature_manager.add<toggle_option>("horn_boost_only_on_ground", "Only On Ground", "", &horn_boost::settings::only_on_ground);
		g_feature_manager.add<float_option>("horn_boost_speed", "Speed", "", &horn_boost::settings::speed, 0, 2000, 1, 0);
		g_feature_manager.add<float_option>("horn_boost_power", "Boost Power", "", &horn_boost::settings::boost_power, 0, 300, 0.1, 1);
	}
	void add_rocket_boost() {
		g_feature_manager.add<toggle_option>("infinite_rocket_boost", "Infinite", "Provides you with an unlimited amount of boost.", &rocket_boost::infinite::enabled, rocket_boost::infinite::init);
		g_feature_manager.add<toggle_option>("rocket_boost_always_active", "Always Active", "Always triggers a boost for your vehicle when\navailable.", &rocket_boost::always_active::enabled, rocket_boost::always_active::init);
		g_feature_manager.add<float_option>("rocket_boost_percentage", "Percentage", "", &rocket_boost::percentage, 0, 100, 1.0, 0, true, [] {
			VEHICLE::SET_ROCKET_BOOST_FILL(g_utils->vehicle(), rocket_boost::percentage);
		});
		g_feature_manager.add<float_option>("rocket_boost_refill_time", "Refill Time", "Adjusts the refill time for the boost.", &rocket_boost::refill_time, 0.0f, 1000.f, 1.f, 0, true, [] {
			VEHICLE::SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME(g_utils->vehicle(), rocket_boost::refill_time);
		});
	}
	void add_tire_tracks() {
		g_feature_manager.add<toggle_option>("tire_tracks", "Enabled", "Modifies the color of your vehicle's tire tracks.", &tire_tracks::enabled, tire_tracks::init, tire_tracks::on_disable);
		g_feature_manager.add<toggle_option>("tire_tracks_always", "Persistent", "Ensures that the tire tracks are always \ndisplayed.", &tire_tracks::always);
		g_feature_manager.add<toggle_option>("tire_tracks_rainbow", "Rainbow", "Changes the color of the tire tracks to a rainbow\npattern.", &tire_tracks::rainbow);
		g_feature_manager.add<toggle_option>("tire_tracks_match_car", "Match Car", "Adjusts the color of the tire tracks to match the\ncolor of your car.", &tire_tracks::match_car);
		g_feature_manager.add<float_option>("tire_tracks_r", "R", "", &tire_tracks::red, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("tire_tracks_g", "G", "", &tire_tracks::green, 0, 255, 1, 0);
		g_feature_manager.add<float_option>("tire_tracks_b", "B", "", &tire_tracks::blue, 0, 255, 1, 0);
	}
	void add_weapons() {
		g_feature_manager.add<toggle_option>("vehicle_weapons", "Enabled", "Enables a weapon system for your vehicle.", &vehicle_weapons::enabled, vehicle_weapons::init);
		g_feature_manager.add<toggle_option>("vehicle_weapons_trajectory", "Trajectory", "Displays the trajectory for the weapon.", &vehicle_weapons::settings::trajectory);

		g_feature_manager.add<choose_option>("vehicle_weapons_selected", "Weapon", "Specifies the weapon type that the weapons will\nuse.", all_weapons_name, &vehicle_weapons::settings::selected);
		g_feature_manager.add<float_option>("vehicle_weapons_speed", "Speed", "Adjusts the speed of the weapon.", &vehicle_weapons::settings::speed, 0, 5000, 1, 0);
		g_feature_manager.add<float_option>("vehicle_weapons_delay", "Delay", "Introduces a delay between each bullet.", &vehicle_weapons::settings::delay, 0, 5000, 1, 0);

		g_feature_manager.add<float_option>("vehicle_weapons_offset_x", "X", "", &vehicle_weapons::settings::offset.x, -100, 100, 0.01, 2);
		g_feature_manager.add<float_option>("vehicle_weapons_offset_y", "Y", "", &vehicle_weapons::settings::offset.y, -100, 100, 0.01, 2);
		g_feature_manager.add<float_option>("vehicle_weapons_offset_z", "Z", "", &vehicle_weapons::settings::offset.z, -100, 100, 0.01, 2);
	}
	void add_acrobatics() {
		g_feature_manager.add<choose_option>("select_acrobatic", "Type", "", acrobatics::settings::type, &acrobatics::settings::pos);
		g_feature_manager.add<toggle_option>("reverse_acrobatic", "Reverse", "Reverses the acrobatic.", &acrobatics::settings::reverse);
		g_feature_manager.add<toggle_option>("random_acrobatics", "Random", "Performs a random acrobatic when you are \non the ground.", &acrobatics::settings::randomize, acrobatics::random);
		g_feature_manager.add<toggle_option>("acrobatic_on_horn", "On Horn", "Executes the selected acrobatic maneuver when\nyou press your horn.", &acrobatics::settings::on_horn, acrobatics::on_horn);
		g_feature_manager.add<float_option>("acrobatic_force", "Force", "Modifys the force of the acrobatic.", &acrobatics::settings::force, 0, 200, 1, 0);
		g_feature_manager.add<button_option>("start_acrobatic", "Start", "Executes the acrobatic a single time.", [] {
			g_fiber_pool.queue([=] {
				acrobatics::start();
				});
		});
	}
	void add_color() {
		g_feature_manager.add<toggle_option>("rainbow_primary", "Primary", "", &vehicle_color::primary::rainbow, vehicle_color::primary::init);
	}
	void add_gravity() {
		for (auto& grav : vehicle_gravity::settings::planet_gravity_pairs) {
			vehicle_gravity::settings::just_names.push_back(grav.first);
		}
		g_feature_manager.add<toggle_with_choose_option>("vehicle_gravity_presets", "Preset", "Set your vehicle's gravity to a predefined value.", &vehicle_gravity::enabled, vehicle_gravity::settings::just_names, &vehicle_gravity::settings::selected, false, vehicle_gravity::init, vehicle_gravity::on_disable);
		g_feature_manager.add<float_option>("vehicle_gravity", "Value", "Modify the gravity settings for your vehicle.", &veh_gravity, 0, 1000, 0.1, 1, true, [] {
			set_vehicle_gravity(g_utils->get_entity_address(g_utils->vehicle()), veh_gravity);
		});

		g_feature_manager.add<toggle_option>("vehicle_gravity_global", "Global", "Ensures that all the surrounding vehicles are\nalso affected by the gravitational force.", &vehicle_gravity::settings::global);
	}
	void add_wheel() {
		g_feature_manager.add<toggle_with_float_option>("wheel_offset", "Position", "Adjusts your wheels position.", &wheel::enabled, &wheel::offset, -100, 100, 0.01, 2, true, wheel::init);
	}	
	void add_parachute() {
		g_feature_manager.add<toggle_option>("override_parachute_model", "Enabled", "To modify the parachute model, you need to\nensure that the parachute is activated on your \nvehicle.", &vehicle_parachute::enabled, vehicle_parachute::init, vehicle_parachute::on_disable);
	}
	void add_doors() {
		g_feature_manager.add<button_option>("open_all_doors", "Open All", "", get_func(doors::g_door_mgr.open_all));
		g_feature_manager.add<button_option>("close_all_doors", "Close All", "", get_func(doors::g_door_mgr.close_all));
	}
	void add_moving_plate() {
		g_feature_manager.add<toggle_option>("moving_plate", "Enabled", "", &moving_plate::enabled, &moving_plate::tick);

		g_feature_manager.add<float_option>("moving_plate_delay", "Delay", "", &moving_plate::settings::delay, 0, 5000, 1, 0);
		g_feature_manager.add<keyboard_option>("moving_plate_text", "Text", "", &moving_plate::settings::text);
	}
	float forklift_height{ 1 };
	float helicopter_lag_rate{ 1 };
	float deluxo_state{ 0.5 };
	float veh_opacity{ 255 };
	bool open_rear_doors_on_explosion{};
	bool taxi_lights{};
	bool strong_axles{};
	bool double_click_for_jump{};
	bool suppress_door_noises{};
	bool reset_wheels{};
	bool increase_wheel_crush_damage{};
	void vehicle_options::add() {

		add_parachute();
		add_wheel();
		add_gravity();
		add_color();
		add_acrobatics();
		add_weapons();
		add_tire_tracks();
		add_rocket_boost();
		add_horn_boost();
		add_ramp();
		trailer_add();
		disables_add();
		add_towtruck();
		flags_add();
		add_doors();
		add_moving_plate();

		g_feature_manager.add<toggle_with_choose_option>("vehicle_godmode", "Invincibility", "Prevents your vehicle from being destroyed.", & vehicle_godmode::enabled, vehicle_godmode::settings::type, &vehicle_godmode::settings::position, false, vehicle_godmode::init, vehicle_godmode::on_disable);
		g_feature_manager.add<toggle_option>("acceleration", "Enabled", "Enhances the speed of your vehicle.", &acceleration::enabled, acceleration::init);
		g_feature_manager.add<float_option>("acceleration_speed", "Speed", "Adjusts the rate at which acceleration affects\nthe speed.", & acceleration::speed, 0, 1000, 0.5, 1);
		g_feature_manager.add<toggle_option>("stick_to_ground", "Enabled", "Sticks your vehicle to the ground.", &stick_to_ground::enabled, stick_to_ground::init);
		g_feature_manager.add<float_option>("stick_to_ground_force", "Force", "The force which will the stick to ground hit the ground.", &stick_to_ground::settings::force, 0, 1000, 0.1, 1);
		g_feature_manager.add<toggle_option>("mute_sirens", "Mute Sirens", "", &mute_sirens::enabled, mute_sirens::init, mute_sirens::on_disable);
		g_feature_manager.add<toggle_option>("explode_on_impact", "Explode On Impact", "Causes your vehicle to explode upon impact.", &explode_on_impact::enabled, explode_on_impact::init);
		g_feature_manager.add<toggle_option>("invert_controls", "Invert Controls", "Inverts your control inputs.", &invert_controls::enabled, invert_controls::init, invert_controls::on_disable);
		g_feature_manager.add<toggle_option>("reduce_grip", "Reduce Grip", "Decreases the grip of your vehicle.", &slipply_wheels::enabled, slipply_wheels::init, slipply_wheels::on_disable);

		g_feature_manager.add<toggle_option>("drive_underwater", "Drive Underwater", "Enables underwater driving capability.", &drive_underwater::enabled, drive_underwater::init, drive_underwater::on_disable);
		g_feature_manager.add<toggle_option>("drive_on_water", "Drive On Water", "Grants the ability to drive on water.", &drive_on_water::enabled, drive_on_water::init, drive_on_water::on_disable);

		g_feature_manager.add<toggle_with_float_option>("shaky_shell", "Shell Oscillation", "Shakes your shell.", &shaky_shell::enabled, &shaky_shell::multiplier, 0, 5000, 1, 0, false, shaky_shell::init, shaky_shell::on_disable);
		g_feature_manager.add<toggle_option>("auto_flip", "Auto Flip", "Automatically flips your vehicle when it reaches\na 120 - degree angle.", &auto_flip::enabled, auto_flip::init);

		g_feature_manager.add<toggle_with_float_option>("headlight_multiplier", "Headlight Multiplier", "", &headlight_multiplier::enabled, &headlight_multiplier::value, 0, 1000, 1, 0, false, headlight_multiplier::init, headlight_multiplier::on_disable);
		g_feature_manager.add<toggle_with_float_option>("negitive_torque", "Negitive Torque", "", &negitive_torque::enabled, &negitive_torque::value, 0, 1000, 1, 0, false, negitive_torque::init, negitive_torque::on_disable);

		g_feature_manager.add<toggle_with_choose_option>("auto_repair", "Repair", "Automatically repairs your vehicle.", & auto_repair::enabled, auto_repair::settings::method, &auto_repair::settings::selected, false, auto_repair::init);

		g_feature_manager.add<toggle_option>("drift_tires", "Drift Tires", "Converts your tires to drift tires.", &drift_tires::enabled, drift_tires::init, drift_tires::on_disable);

		g_feature_manager.add<toggle_option>("burned", "Burned", "Burns your shell.", &burned::enabled, burned::init, burned::on_disable);

		g_feature_manager.add<toggle_option>("bypass_max_speed", "Bypass Max Speed", "", &bypass_max_speed::enabled, bypass_max_speed::init, bypass_max_speed::on_disable);
		g_feature_manager.add<toggle_option>("instant_brake", "Instant Brake", "", &instant_brake::enabled, instant_brake::init);

		g_feature_manager.add<toggle_option>("break_deluxo", "Break", "", &break_deluxo::enabled, break_deluxo::init);
		g_feature_manager.add<toggle_option>("always_extend_mk1_wings", "Always Extend MK1 Wings", "Extends the wings on the oppressor mk1.", &always_extend_mk1_wings::enabled, always_extend_mk1_wings::init);
		g_feature_manager.add<toggle_option>("easy_to_land", "Easy To Land", "Ensures that you dont fall off your bike.", &easy_to_land::enabled, easy_to_land::init, easy_to_land::on_disable);

		g_feature_manager.add<toggle_option>("rapid_fire_vehicle_weapons", "Rockets", "", &rapid_fire_vehicle_weapons::enabled, rapid_fire_vehicle_weapons::tick);

		g_feature_manager.add<toggle_with_float_option>("vehicle_scale", "Scale", "", &vehicle_scale::enabled, &vehicle_scale::settings::scale, 0, 5, 0.1, 1, false, vehicle_scale::tick, vehicle_scale::on_disable);

		basic_toggle_function(taxi_lights, "taxi_lights", "Taxi Lights", VEHICLE::SET_TAXI_LIGHTS(g_utils->vehicle(), taxi_lights));
		basic_toggle_function(open_rear_doors_on_explosion, "open_rear_doors_on_explosion", "Open Rear Doors On Explosion", VEHICLE::SET_OPEN_REAR_DOORS_ON_EXPLOSION(g_utils->vehicle(), open_rear_doors_on_explosion));
		basic_toggle_function(strong_axles, "strong_axles", "Strong Axles", VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(g_utils->vehicle(), strong_axles));
		basic_toggle_function(double_click_for_jump, "double_click_for_jump", "Double Click To Activate", VEHICLE::SET_USE_DOUBLE_CLICK_FOR_CAR_JUMP(double_click_for_jump));

		basic_toggle_function(suppress_door_noises, "suppress_door_noises", "Suppress Door Noises", VEHICLE::SET_VEHICLE_IN_CAR_MOD_SHOP(g_utils->vehicle(), suppress_door_noises));
		basic_toggle_function(increase_wheel_crush_damage, "increase_wheel_crush_damage", "Increase Crush Damage", VEHICLE::SET_INCREASE_WHEEL_CRUSH_DAMAGE(g_utils->vehicle(), increase_wheel_crush_damage));
		basic_toggle_function(reset_wheels, "reset_wheels", "Bounce", VEHICLE::RESET_VEHICLE_WHEELS(g_utils->vehicle(), reset_wheels));

		g_feature_manager.add<toggle_option>("spawner_fade", "Fade", "Fades the car in.", &vehicle::spawner::settings::fade);
		g_feature_manager.add<toggle_option>("spawner_delete_last", "Delete Last", "Deletes the last vehicle.", &vehicle::spawner::settings::delete_last);
		g_feature_manager.add<toggle_option>("spawner_set_engine_on", "Set Engine On", "Sets the engine on automaticly.", &vehicle::spawner::settings::set_engine_on);
		g_feature_manager.add<toggle_option>("spawner_spawn_inside", "Teleport Inside", "", &vehicle::spawner::settings::spawn_inside);
		g_feature_manager.add<toggle_option>("spawner_spawn_max", "Max", "", &vehicle::spawner::settings::max);
		g_feature_manager.add<toggle_option>("spawner_spawn_notify", "Notify", "", &vehicle::spawner::settings::notify);
		g_feature_manager.add<toggle_option>("spawner_spawn_keep_velocity", "Keep Velocity", "", &vehicle::spawner::settings::keep_velocity);



		g_feature_manager.add<button_option>("repair", "Repair", "Repairs your vehicle", [] {
			VEHICLE::SET_VEHICLE_FIXED(g_utils->vehicle());
			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(g_utils->vehicle());
		});

		g_feature_manager.add<float_option>("forklift_height", "Forklift Height", "", &forklift_height, 0, 1, 0.1, 1, true, [] {
			queue_job
				VEHICLE::SET_FORKLIFT_FORK_HEIGHT(g_utils->vehicle(), forklift_height);
			end_job
		});

		g_feature_manager.add<float_option>("helicopter_lag_rate", "Helicopter Lag Rate", "", &helicopter_lag_rate, 0, 1000, 1, 0, true, [] {
			queue_job
				VEHICLE::SET_HELI_CONTROL_LAGGING_RATE_SCALAR(g_utils->vehicle(), helicopter_lag_rate);
			end_job
		});

		g_feature_manager.add<float_option>("deluxo_state", "State", "", &deluxo_state, 0, 1000, 1, 0, true, [] {
			queue_job
				VEHICLE::SET_SPECIAL_FLIGHT_MODE_TARGET_RATIO(g_utils->vehicle(), deluxo_state);
			end_job
		});

		g_feature_manager.add<float_option>("vehicle_opacity", "Opacity", "", &veh_opacity, 0, 255, 51, 0, true, [] {
			ENTITY::SET_ENTITY_ALPHA(g_utils->vehicle(), veh_opacity, false);
		});

		update_hash_list();
		for (auto& vehlist : vehicle_hash_list) {
			g_feature_manager.add<button_option>(std::to_string(vehlist.hash), HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(vehlist.name), "", [=] {
				vehicle::spawner::spawn(vehlist.hash);
				});
		}
	}
}