#pragma once
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>
#include "classes.hpp"
namespace Base {
    void entity_shooter::tick() {
        if (!m_enabled) return;
		
		auto selected_hash{ rage::joaat(m_selected_vehicle_name) };
		auto vehicle_name{ HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(selected_hash)) };
		if (m_settings.pos == 0) {
			if (g_utils->shooting()) {
				auto camera_coords{ CAM::GET_GAMEPLAY_CAM_COORD() };
				auto camera_direction{ g_math->rotation_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)) };
				auto self_coords{ g_utils->coords() };
				auto start_multiply{ camera_direction * (std::distance(&camera_coords, &self_coords) + 15.25f) };
				auto start{ camera_coords + start_multiply };
				auto rot{ CAM::GET_GAMEPLAY_CAM_ROT(2) };
				float pitch{ (float)g_math->degree_to_radian(rot.x) };
				float yaw{ (float)g_math->degree_to_radian(rot.z + 90) };

				STREAMING::REQUEST_MODEL(selected_hash);
				m_vehicle = VEHICLE::CREATE_VEHICLE(selected_hash, start.x, start.y, start.z, ENTITY::GET_ENTITY_HEADING(g_utils->self()), true, false, false);
				m_entity_shooter_shot.push_back({ vehicle_name, m_vehicle });
				g_utils->make_networked(m_vehicle);

				Vector3 velocity;

				velocity.x = g_utils->coords().x + (1000.0f * cos(pitch) * cos(yaw)) - self_coords.x;
				velocity.y = g_utils->coords().y + (1000.0f * sin(yaw) * cos(pitch)) - self_coords.y;
				velocity.z = g_utils->coords().z + (1000.0f * sin(pitch)) - self_coords.z;
				ENTITY::SET_ENTITY_ROTATION(m_vehicle, rot.x, rot.y, rot.z, 2, false);
				ENTITY::SET_ENTITY_VELOCITY(m_vehicle, velocity.x * 3.0f, velocity.y * 3.0f, velocity.z * 3.0f);

			}
		}
		if (m_settings.pos == 1) {
			static Vehicle vehicle;
			auto position{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_utils->self(), 0.4f, 3.0f, 0.8f) };
			auto cam_rotation{ CAM::GET_GAMEPLAY_CAM_ROT(2) };
			auto player_rotation{ ENTITY::GET_ENTITY_ROTATION(g_utils->self(), 2) };
			auto direction{ g_math->rotation_to_direction(cam_rotation) };

			if (g_utils->aiming()) {
				STREAMING::REQUEST_MODEL(selected_hash);
				if (!ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					vehicle = VEHICLE::CREATE_VEHICLE(selected_hash, g_utils->coords().x + 6.0f, g_utils->coords().y + 6.0f, g_utils->coords().z + 7.0f, ENTITY::GET_ENTITY_HEADING(g_utils->self()), true, false, false);

					g_utils->make_networked(m_vehicle);
				}
				else {
					auto vehicle_coords{ g_utils->coords(vehicle) };
					Vector3 force = {
						((position.x + (direction.x * 5.0f)) - vehicle_coords.x) * 4,
						((position.y + (direction.y * 5.0f)) - vehicle_coords.y) * 4,
						((position.z + (direction.z * 5.0f)) - vehicle_coords.z) * 4
					};
					ENTITY::SET_ENTITY_VELOCITY(vehicle, force.x, force.y, force.z);
					ENTITY::SET_ENTITY_ROTATION(vehicle, player_rotation.x, player_rotation.y, cam_rotation.z, 2, true);

					if (g_utils->shooting()) {
						Vector3 velocity;
						float pitch{ (float)g_math->degree_to_radian(cam_rotation.x) };
						float yaw{ (float)g_math->degree_to_radian(cam_rotation.z + 90) };
						velocity.x = g_utils->coords().x + (1000.0f * cos(pitch) * cos(yaw)) - vehicle_coords.x;
						velocity.y = g_utils->coords().y + (1000.0f * sin(yaw) * cos(pitch)) - vehicle_coords.y;
						velocity.z = g_utils->coords().z + (1000.0f * sin(pitch)) - vehicle_coords.z;
						ENTITY::SET_ENTITY_VELOCITY(vehicle, velocity.x * (float)3.0, velocity.y * (float)3.0, velocity.z * (float)3.0);
						m_entity_shooter_shot.push_back({ vehicle_name, vehicle });
						vehicle = NULL;
					}
				}
				
			}
			else {
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					if (ENTITY::GET_ENTITY_ALPHA(vehicle) < 21) {
						g_utils->delete_entity(vehicle);
						vehicle = 0;
					}
					else {
						ENTITY::SET_ENTITY_ALPHA(vehicle, ENTITY::GET_ENTITY_ALPHA(vehicle) - 20, true);
					}
				}
			}
		}
    }

}
