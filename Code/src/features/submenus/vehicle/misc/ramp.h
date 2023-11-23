#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"
#include <src/rage/vehicle/CVehicleModelInfo.hpp>
#include "src/features/other/los_santos_customs.h"
#include "src/hooking/hooking.h"

namespace Base {
	namespace ramp_enabled {
		int flag;
		bool enabled{ true };
		bool nig{ false };
		ChatData* get_chat_data() {
			return *g_pointers->m_chat_data;
		}
		void init() {
			if (!g_utils->cvehicle()) return;

			CVehicleModelInfo* model_info{ (CVehicleModelInfo*)g_utils->cvehicle()->m_model_info };

			model_info->m_ability_flag = g_interface->m_flag;
		}
		void on_disable() {
			if (!g_utils->cvehicle()) return;

			CVehicleModelInfo* model_info{ (CVehicleModelInfo*)g_utils->cvehicle()->m_model_info };

			model_info->m_ability_flag = 0;
		}
	}
	namespace sideways_launch_motion {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			VEHICLE::VEHICLE_SET_ENABLE_RAMP_CAR_SIDE_IMPULSE(g_utils->vehicle(), true);
		}
		void on_disable() {
			VEHICLE::VEHICLE_SET_ENABLE_RAMP_CAR_SIDE_IMPULSE(g_utils->vehicle(), false);
		}
	}
	namespace upways_launch_motion {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			VEHICLE::VEHICLE_SET_ENABLE_NORMALISE_RAMP_CAR_VERTICAL_VELOCTIY(g_utils->vehicle(), true);
		}
		void on_disable() {
			VEHICLE::VEHICLE_SET_ENABLE_NORMALISE_RAMP_CAR_VERTICAL_VELOCTIY(g_utils->vehicle(), false);
		}
	}
}
