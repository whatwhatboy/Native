#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"
#include "src/framework/notifications/notifications.h"
namespace Base::vehicle::spawner {
    namespace settings {
        namespace color {
            bool enabled{ false };
            bool secondaryEnabled{ false };
            ImColor primary;
            ImColor secondary;
        }
        bool max{ false };
        bool spawn_inside{ true };
        bool delete_last{ false };
        bool set_engine_on{ true };
        bool fade{ true };

        bool notify{ false };
        bool keep_velocity{ true };
    }
    void spawn(Hash hash) {
        g_utils->request(request_type::model, hash, [=] {
            auto og_velo{ ENTITY::GET_ENTITY_VELOCITY(g_utils->vehicle()) };
            if (spawner::settings::delete_last) {
                auto last{ PLAYER::GET_PLAYERS_LAST_VEHICLE() };
                VEHICLE::DELETE_VEHICLE(&last);
            }
            auto heading{ ENTITY::GET_ENTITY_HEADING(g_utils->self()) };
            auto pos{ g_utils->coords() };
            auto rotation{ ENTITY::GET_ENTITY_ROTATION(g_utils->vehicle(), 0) };
            auto vehicle{ VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, heading, true, true, 0) };
            if (!rotation.empty())
                ENTITY::SET_ENTITY_ROTATION(g_utils->vehicle(), rotation.x, rotation.y, rotation.z, 0, 0);
            g_utils->make_networked(vehicle);
            if (settings::max) {
                g_utils->max_vehicle(vehicle);
            }
            if (settings::set_engine_on) {
                VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, true, true, true);
            }
            if (settings::spawn_inside) {
                PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
            }
            if (settings::fade) {
                NETWORK::NETWORK_FADE_IN_ENTITY(vehicle, 1, 1);
            }
            if (settings::keep_velocity) {
                if (!og_velo.empty()) {
                    ENTITY::SET_ENTITY_VELOCITY(vehicle, og_velo.x, og_velo.y, og_velo.z);
                }
            }
            if (settings::notify) {
                g_notifications->send("Spawner", std::format("You spawned a {} for yourself.", HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hash))));
            }
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
        });
        
    }
   
   
}
