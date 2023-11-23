#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base::los_santos_customs {
	inline std::vector<std::pair<const char*, int>> wheel_sport;
	inline std::vector<std::pair<const char*, int>> wheel_muscle;
	inline std::vector<std::pair<const char*, int>> wheel_lowrider;
	inline std::vector<std::pair<const char*, int>> wheel_suv;
	inline std::vector<std::pair<const char*, int>> wheel_offroad;
	inline std::vector<std::pair<const char*, int>> wheel_tuner;
	inline std::vector<std::pair<const char*, int>> wheel_bike;
	inline std::vector<std::pair<const char*, int>> wheel_high_end;
	inline std::vector<std::pair<const char*, int>> wheel_bennys;
	inline std::vector<std::pair<const char*, int>> wheel_bespoke;
	inline std::vector<std::pair<const char*, int>> wheel_open;
	inline std::vector<std::pair<const char*, int>> wheel_street;
	inline std::vector<std::pair<const char*, int>> wheel_track;

	inline void update() {
		if (wheel_sport.empty() && g_utils->in_vehicle()) {
			int cached{ VEHICLE::GET_VEHICLE_WHEEL_TYPE(g_utils->vehicle()) };

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 0);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_sport.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 1);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_muscle.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 2);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_lowrider.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 3);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_suv.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 4);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_offroad.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 5);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_tuner.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 6);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_bike.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 7);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_high_end.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 8);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_bennys.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 9);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_bespoke.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 10);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_open.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 11);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_street.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), 12);
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(g_utils->vehicle(), MOD_FRONTWHEELS); i++) {
				wheel_track.push_back({ VEHICLE::GET_MOD_TEXT_LABEL(g_utils->vehicle(), MOD_FRONTWHEELS, i), i });
			}

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(g_utils->vehicle(), cached);
		}
	}
}