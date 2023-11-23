#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/button.h"
#include "src/framework/option_types/number.h"
#include <JSON/json.hpp>

namespace Base::submenus::network {
	using namespace Framework;
	void set_int(str name, int value) {
		STATS::STAT_SET_INT(rage::joaat(g_utils->get_character_prefix() + name), value, true);
	}
	void set_bool(str name, bool value) {
		STATS::STAT_SET_BOOL(rage::joaat(g_utils->get_character_prefix() + name), value, true);
	}
	void unlock_clothing() {
		set_int("CHAR_FM_CLOTHES_1_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_2_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_3_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_4_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_5_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_6_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_7_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_8_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_9_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_10_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_11_UNLCK", -1);
		set_int("CHAR_FM_CLOTHES_1_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_2_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_3_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_4_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_5_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_6_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_7_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_8_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_9_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_10_OWNED", -1);
		set_int("CHAR_FM_CLOTHES_11_OWNED", -1);

		for (int i{ 0 }; i < 250; i++) {
			set_int("DLC_APPAREL_ACQUIRED_" + std::to_string(i), -1);
		}
		for (int i{ 0 }; i < 250; i++) {
			set_int("DLC_APPAREL_USED_" + std::to_string(i), -1);
		}

		for (int i{ 0 }; i < 40; i++) {
			set_int("ADMIN_CLOTHES_GV_BS_" + std::to_string(i), -1);
			set_int("ADMIN_CLOTHES_RM_BS_" + std::to_string(i), -1);
		}

		for (int i{ 1 }; i < 6; i++) {
			for (int k{ 1 }; k < 10; k++) {
				for (int j{ 1 }; j < 7; j++) {
					set_int("CLTHS_ACQUIRED_BERD", -1);
					set_int("CLTHS_ACQUIRED_DECL", -1);
					set_int("CLTHS_ACQUIRED_FEET", -1);
					set_int("CLTHS_ACQUIRED_JBIB", -1);
					set_int("CLTHS_ACQUIRED_LEGS", -1);
					set_int("CLTHS_ACQUIRED_OUTFIT", -1);
					set_int("CLTHS_ACQUIRED_PROPS", -1);
					set_int("CLTHS_ACQUIRED_SPECIAL", -1);
					set_int("CLTHS_ACQUIRED_SPECIAL2", -1);
					set_int("CLTHS_ACQUIRED_SPECIAL2_1", -1);
					set_int("CLTHS_ACQUIRED_TORSO", -1);
					set_int("CLTHS_ACQUIRED_TEETH", -1);
					set_int("CLTHS_ACQUIRED_TEETH_1", -1);
					set_int("CLTHS_ACQUIRED_TEETH_2", -1);
					set_int("CLTHS_ACQUIRED_BERD_" + std::to_string(i), -1);
					set_int("CLTHS_ACQUIRED_FEET_" + std::to_string(j), -1);
					set_int("CLTHS_ACQUIRED_JBIB_" + std::to_string(j), -1);
					set_int("CLTHS_ACQUIRED_LEGS_" + std::to_string(j), -1);
					set_int("CLTHS_ACQUIRED_SPECIAL_" + std::to_string(j), -1);
					set_int("CLTHS_ACQUIRED_PROPS_" + std::to_string(k), -1);
					set_int("CLTHS_AVAILABLE_DECL", -1);
					set_int("CLTHS_AVAILABLE_FEET", -1);
					set_int("CLTHS_AVAILABLE_HAIR", -1);
					set_int("CLTHS_AVAILABLE_JBIB", -1);
					set_int("CLTHS_AVAILABLE_LEGS", -1);
					set_int("CLTHS_AVAILABLE_BERD", -1);
					set_int("CLTHS_AVAILABLE_OUTFIT", -1);
					set_int("CLTHS_AVAILABLE_PROPS", -1);
					set_int("CLTHS_AVAILABLE_SPECIAL", -1);
					set_int("CLTHS_AVAILABLE_SPECIAL2", -1);
					set_int("CLTHS_AVAILABLE_SPECIAL2_1", -1);
					set_int("CLTHS_AVAILABLE_TEETH", -1);
					set_int("CLTHS_AVAILABLE_TEETH_1", -1);
					set_int("CLTHS_AVAILABLE_TEETH_2", -1);
					set_int("CLTHS_AVAILABLE_TORSO", -1);
					set_int("CLTHS_AVAILABLE_BERD_" + std::to_string(j), -1);
					set_int("CLTHS_AVAILABLE_FEET_" + std::to_string(j), -1);
					set_int("CLTHS_AVAILABLE_HAIR_" + std::to_string(j), -1);
					set_int("CLTHS_AVAILABLE_JBIB_" + std::to_string(j), -1);
					set_int("CLTHS_AVAILABLE_LEGS_" + std::to_string(j), -1);
					set_int("CLTHS_AVAILABLE_SPECIAL_" + std::to_string(j), -1);
					set_int("CLTHS_AVAILABLE_PROPS_" + std::to_string(k), -1);
					set_int("CLTHS_USED_HAIR", -1);
					set_int("CLTHS_USED_HAIR_" + std::to_string(j), -1);
					set_int("CLTHS_USED_JBIB", -1);
					set_int("CLTHS_USED_JBIB_" + std::to_string(j), -1);
					set_int("CLTHS_USED_LEGS", -1);
					set_int("CLTHS_USED_LEGS_" + std::to_string(j), -1);
					set_int("CLTHS_USED_FEET", -1);
					set_int("CLTHS_USED_FEET_" + std::to_string(j), -1);
					set_int("CLTHS_USED_BERD", -1);
					set_int("CLTHS_USED_BERD_" + std::to_string(j), -1);
					set_int("CLTHS_USED_PROPS", -1);
					set_int("CLTHS_USED_PROPS_" + std::to_string(k), -1);
					set_int("CLTHS_USED_OUTFIT", -1);
					set_int("CLTHS_USED_TORSO", -1);
					set_int("CLTHS_USED_SPECIAL", -1);
					set_int("CLTHS_USED_SPECIAL_" + std::to_string(j), -1);
					set_int("CLTHS_USED_SPECIAL2", -1);
					set_int("CLTHS_USED_SPECIAL2_1", -1);
					set_int("CLTHS_USED_DECL", -1);
					set_int("CLTHS_USED_TEETH", -1);
					set_int("CLTHS_USED_TEETH_1", -1);
					set_int("CLTHS_USED_TEETH_2", -1);

				}
			}
		}
	}
	void recovery_unlocks() {
		draw->button("Clothes", unlock_clothing);
		inline_item
		draw->button("Camo & Parachutes", [] {
			set_int("CHAR_KIT_1_FM_UNLCK", -1);
			set_int("CHAR_KIT_2_FM_UNLCK", -1);
			set_int("CHAR_KIT_3_FM_UNLCK", -1);
			set_int("CHAR_KIT_4_FM_UNLCK", -1);
			set_int("CHAR_KIT_5_FM_UNLCK", -1);
			set_int("CHAR_KIT_6_FM_UNLCK", -1);
			set_int("CHAR_KIT_7_FM_UNLCK", -1);
			set_int("CHAR_KIT_8_FM_UNLCK", -1);
			set_int("CHAR_KIT_9_FM_UNLCK", -1);
			set_int("CHAR_KIT_10_FM_UNLCK", -1);
			set_int("CHAR_KIT_11_FM_UNLCK", -1);
			set_int("CHAR_KIT_12_FM_UNLCK", -1);
			set_int("CHAR_KIT_13_FM_UNLCK", -1);
			set_int("CHAR_KIT_14_FM_UNLCK", -1);
			set_int("CHAR_KIT_15_FM_UNLCK", -1);
			set_int("CHAR_KIT_16_FM_UNLCK", -1);
			set_int("CHAR_KIT_17_FM_UNLCK", -1);
			set_int("CHAR_KIT_18_FM_UNLCK", -1);
			set_int("CHAR_KIT_19_FM_UNLCK", -1);
			set_int("CHAR_KIT_20_FM_UNLCK", -1);
			set_int("CHAR_KIT_21_FM_UNLCK", -1);
			set_int("CHAR_KIT_22_FM_UNLCK", -1);
			set_int("CHAR_KIT_23_FM_UNLCK", -1);
			set_int("CHAR_KIT_24_FM_UNLCK", -1);
			set_int("CHAR_KIT_25_FM_UNLCK", -1);
			set_int("CHAR_KIT_26_FM_UNLCK", -1);
			set_int("CHAR_KIT_27_FM_UNLCK", -1);
			set_int("CHAR_KIT_28_FM_UNLCK", -1);
			set_int("CHAR_KIT_29_FM_UNLCK", -1);
			set_int("CHAR_KIT_30_FM_UNLCK", -1);
			set_int("CHAR_KIT_31_FM_UNLCK", -1);
			set_int("CHAR_KIT_32_FM_UNLCK", -1);
			set_int("CHAR_KIT_33_FM_UNLCK", -1);
			set_int("CHAR_KIT_34_FM_UNLCK", -1);
			set_int("CHAR_KIT_35_FM_UNLCK", -1);
			set_int("CHAR_KIT_36_FM_UNLCK", -1);
			set_int("CHAR_KIT_37_FM_UNLCK", -1);
			set_int("CHAR_KIT_38_FM_UNLCK", -1);
			set_int("CHAR_KIT_39_FM_UNLCK", -1);
			set_int("CHAR_KIT_40_FM_UNLCK", -1);
		});
		draw->button("Tattoos", [] {
			set_int("tattoo_fm_unlocks_1", -1);
			set_int("tattoo_fm_unlocks_2", -1);
			set_int("tattoo_fm_unlocks_3", -1);
			set_int("tattoo_fm_unlocks_4", -1);
			set_int("tattoo_fm_unlocks_5", -1);
			set_int("tattoo_fm_unlocks_6", -1);
			set_int("tattoo_fm_unlocks_7", -1);
			set_int("tattoo_fm_unlocks_8", -1);
			set_int("tattoo_fm_unlocks_9", -1);
			set_int("tattoo_fm_unlocks_10", -1);
			set_int("tattoo_fm_unlocks_11", -1);
			set_int("tattoo_fm_unlocks_12", -1);
		});
		draw->seperator("Misc");
		draw->button("Fast Run", [] {
			set_int("CHAR_ABILITY_1_UNLCK", -1);
			set_int("CHAR_ABILITY_2_UNLCK", -1);
			set_int("CHAR_ABILITY_3_UNLCK", -1);
			set_int("CHAR_FM_ABILITY_1_UNLCK", -1);
			set_int("CHAR_FM_ABILITY_2_UNLCK", -1);
			set_int("CHAR_FM_ABILITY_3_UNLCK", -1);
		});
		inline_item
		draw->button("Alien Tattoo", [] {
			set_int("TATTOO_FM_CURRENT_32", true);
		});
		inline_item
		draw->button("Heist Vehicles", [] {
			set_int("CHAR_FM_VEHICLE_1_UNLCK", -1);
			set_int("CHAR_FM_VEHICLE_2_UNLCK", -1);
		});
	}
}
