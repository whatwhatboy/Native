#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base {
    namespace force {
        namespace settings {
            std::vector<const char*> type = { "Force", "Force 2", "Forward Speed", "Custom" };
            int typePos{ 1 };
            bool backward{ false };
            float force{ 0.5 };

            float customForceX{ 0.0f };
            float customForceY{ 0.0f }; 
            float customForceZ{ 0.0f };
        }
        bool enabled = false;
        void init() {
            if (!enabled) return;
            Entity target;
            if (!g_math->raycast(target) || !g_utils->shooting()) return;
            auto target_coords{ g_utils->coords(target) };
            auto self_coords{ g_utils->coords() };
            auto force{ target_coords - self_coords };
            auto velocity{ force * settings::force };
            switch (settings::typePos) {
            case 0:
                ENTITY::SET_ENTITY_VELOCITY(target, velocity.x, velocity.y, velocity.z);
                break;
            case 1:
                ENTITY::APPLY_FORCE_TO_ENTITY2(target, 3, force, { 0, 0, 0 }, 0, false, true, true, false, true);
                break;
            case 2:
                 VEHICLE::SET_VEHICLE_FORWARD_SPEED(target, settings::backward ? -settings::force : settings::force);
                break;
            case 3:
                ENTITY::APPLY_FORCE_TO_ENTITY(target, 1, settings::customForceX, settings::customForceY, settings::customForceZ, 0.0f, 0.0f, 0.0f, true, false, true, true, true, 0);
                break;
            }
        }

    }
}
