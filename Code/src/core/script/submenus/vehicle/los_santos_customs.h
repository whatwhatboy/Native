#include "src/core/script/drawing/drawing.h"
#include "src/features/other/los_santos_customs.h"
#include "src/framework/option_types/button.h"


namespace Base::submenus::vehicle::utils {
	struct mod {
		str m_name{};
		int m_mod_index{};
		int m_mod_variation{};
	};
	int get_mod_size(int mod) {
		return VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), mod);
	}
	str get_mod_name(int index, int var) {
		return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), index, var));
	}
	std::vector<mod> get_mods(int index) {
		std::vector<mod> buf;
		for (int i{ 0 }; i < get_mod_size(index); i++) {
			buf.push_back({ get_mod_name(index, i), index, i });
		}
		return buf;
	}
	void apply_mod(int type, int index) {
		if (index == -1) {
			VEHICLE::REMOVE_VEHICLE_MOD(g_utils->vehicle(), type);
		}
		else {
			VEHICLE::SET_VEHICLE_MOD_KIT(g_utils->vehicle(), 0);
			VEHICLE::SET_VEHICLE_MOD(g_utils->vehicle(), type, index, false);
		}
	}

	void add_mods(std::vector<mod>& mods, int idx) {
		mods.clear();
		for (const auto& m : get_mods(idx)) {
			if (!g_utils->has_string_attached(m.m_name, "HSW")) {
				mods.push_back(m);
			}
		}
	}
	void show_mods(const std::vector<mod>& mods) {
		for (const auto& m : mods) {
			draw->button(m.m_name, [=] {
				apply_mod(m.m_mod_index, m.m_mod_variation);
			});
		}
	}
}
namespace Base::submenus::vehicle {
	struct lsc_mod {
		std::vector<utils::mod> m_mods{};
		bool m_has_mod{};

		str m_menu_name;
		str m_name;
	};
	std::vector<lsc_mod> lsc_mods;
	void add_mod(str name1, str name2, int index) {
		std::vector<utils::mod> mods;
		bool has_mod{ (utils::get_mod_size(index) > 0) };
		utils::add_mods(mods, index);

		lsc_mods.push_back({ mods, has_mod, name1, name2 });
	}
	void show_mods() {
		for (auto& m : lsc_mods) {
			if (m.m_has_mod) {
				draw->submenu_second(m.m_menu_name, m.m_name, [=] {
					utils::show_mods(m.m_mods);
				});
			}
		}
	}
	void los_santos_customs_on_enter() {
		if (g_utils->cvehicle()) {
			VEHICLE::SET_VEHICLE_MOD_KIT(g_utils->vehicle(), 0);

			lsc_mods.clear();
			add_mod("Front Bumper", "lsc_front_bumper", MOD_FRONTBUMPER);
			add_mod("Rear Bumper", "lsc_rear_bumper", MOD_REARBUMPER);
			add_mod("Spoiler", "lsc_spoiler", MOD_SPOILER);
			add_mod("Side Skirt", "lsc_side_skirt", MOD_SIDESKIRT);
			add_mod("Exhaust", "lsc_exhaust", MOD_EXHAUST);
			add_mod("Chassis", "lsc_chassis", MOD_CHASSIS);
			add_mod("Grille", "lsc_grille", MOD_GRILLE);
			add_mod("Hood", "lsc_hood", MOD_HOOD);
			add_mod("Fender", "lsc_fender", MOD_FENDER);
			add_mod("Right Fender", "lsc_right_fender", MOD_RIGHTFENDER);
			add_mod("Roof", "lsc_roof", MOD_ROOF);
			add_mod("Engine", "lsc_engine", MOD_ENGINE);
			add_mod("Brakes", "lsc_brakes", MOD_BRAKES);
			add_mod("Transmission", "lsc_transmission", MOD_TRANSMISSION);
			add_mod("Horns", "lsc_horns", MOD_HORNS);
			add_mod("Suspension", "lsc_suspension", MOD_SUSPENSION);
			add_mod("Armor", "lsc_armor", MOD_ARMOR);
			add_mod("Unknown 17", "lsc_unknown_17", MOD_UNK17);
			add_mod("Turbo", "lsc_turbo", MOD_TURBO);
			add_mod("Unknown 19", "lsc_unknown_19", MOD_UNK19);
			add_mod("Tire Smoke", "lsc_tire_smoke", MOD_TIRESMOKE);
			add_mod("Unknown 21", "lsc_unknown_21", MOD_UNK21);
			add_mod("Xenon Lights", "lsc_xenon_lights", MOD_XENONLIGHTS);
			add_mod("Front Wheels", "lsc_front_wheels", MOD_FRONTWHEELS);
			add_mod("Back Wheels", "lsc_back_wheels", MOD_BACKWHEELS);
			add_mod("Plate Holder", "lsc_plate_holder", MOD_PLATEHOLDER);
			add_mod("Vanity Plates", "lsc_vanity_plates", MOD_VANITY_PLATES);
			add_mod("Trim Design", "lsc_trim_design", MOD_TRIM_DESIGN);
			add_mod("Ornaments", "lsc_ornaments", MOD_ORNAMENTS);
			add_mod("Dashboard", "lsc_dashboard", MOD_DASHBOARD);
			add_mod("Dial", "lsc_dial", MOD_DIAL);
			add_mod("Door Speaker", "lsc_door_speaker", MOD_DOOR_SPEAKER);
			add_mod("Seats", "lsc_seats", MOD_SEATS);
			add_mod("Steering Wheel", "lsc_steering_wheel", MOD_STEERINGWHEEL);
			add_mod("Shifter Leavers", "lsc_shifter_leavers", MOD_SHIFTER_LEAVERS);
			add_mod("Plaques", "lsc_plaques", MOD_PLAQUES);
			add_mod("Speakers", "lsc_speakers", MOD_SPEAKERS);
			add_mod("Trunk", "lsc_trunk", MOD_TRUNK);
			add_mod("Hydraulics", "lsc_hydraulics", MOD_HYDRULICS);
			add_mod("Engine Block", "lsc_engine_block", MOD_ENGINE_BLOCK);
			add_mod("Air Filter", "lsc_air_filter", MOD_AIR_FILTER);
			add_mod("Struts", "lsc_struts", MOD_STRUTS);
			add_mod("Arch Cover", "lsc_arch_cover", MOD_ARCH_COVER);
			add_mod("Aerials", "lsc_aerials", MOD_AERIALS);
			add_mod("Trim", "lsc_trim", MOD_TRIM);
			add_mod("Tank", "lsc_tank", MOD_TANK);
			add_mod("Windows", "lsc_windows", MOD_WINDOWS);
			add_mod("Unknown 47", "lsc_unknown_47", MOD_UNK47);
			add_mod("Livery", "lsc_livery", MOD_LIVERY);
			add_mod("Special Front Rims", "lsc_special_front_rims", MOD_SPECIAL_FRONT_RIMS);
			add_mod("Special Rear Rims", "lsc_special_rear_rims", MOD_SPECIAL_REAR_RIMS);
			add_mod("Neon", "lsc_neon", MOD_NEON);
			add_mod("Standard Horn", "lsc_standard_horn", MOD_HORN_STANDARD);
			add_mod("Musical Horn", "lsc_musical_horn", MOD_HORN_MUSICAL);
			add_mod("Loop Horn", "lsc_loop_horn", MOD_HORN_LOOP);
			add_mod("Custom Windows", "lsc_custom_windows", MOD_WINDOWS_CUSTOM);
			add_mod("Plates", "lsc_plates", MOD_PLATES);

		}
	}
	void los_santos_custom() {
		if (g_utils->cvehicle()) {
			if (lsc_mods.empty()) {
				los_santos_customs_on_enter();
			}
			draw->button("Upgrade", [] {
				g_utils->max_vehicle(g_utils->vehicle());
			});
			draw->button("Downgrade", [] {
				g_utils->downgrade_vehicle(g_utils->vehicle());
			});
			draw->seperator("Mods");
			show_mods();
		}
		else {
			draw->text("You must be in a vehicle.");
		}
	}
}
