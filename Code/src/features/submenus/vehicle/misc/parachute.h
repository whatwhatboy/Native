#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/hooking/hooking.h"
namespace Base {
    namespace vehicle_parachute {
        bool enabled{ false };
        void init() {
            if (!enabled) return;
            STREAMING::REQUEST_MODEL(selected_parachute);
            VEHICLE::VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE(g_utils->vehicle(), selected_parachute);
        }
        void on_disable() {
            STREAMING::REQUEST_MODEL(rage::joaat("imp_prop_impexp_para_s"));
            VEHICLE::VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE(g_utils->vehicle(), rage::joaat("imp_prop_impexp_para_s"));
        }
    }
}
