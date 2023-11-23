#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base {
	namespace magnet {
		namespace util {
			bool request_control(Entity ent) {
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent))
					return true;

				for (uint8_t i = 0; !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent) && i < 10; i++)
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);

				if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent))
					return false;

				int netHandle{ NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent) };
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);

				return true;
			}
			float get_velocity(float aimX, float entityX) {
				static float velocity;
				if (aimX > 0 && entityX > 0)
					velocity = aimX - (entityX);
				if (aimX < 0 && entityX < 0)
					velocity = aimX - (entityX);
				if (aimX > 0 && entityX < 0)
					velocity = aimX + (entityX);
				if (aimX < 0 && entityX > 0)
					velocity = aimX + (entityX);

				return velocity;
			}
		}
		namespace settings {
			namespace sphere {
				bool enabled{ true };
				int preview{ 28 };
				float size{ 1.0f };
				Vector3 rotation{ 0, 0, 0 };
			}
			namespace excludes {
				bool vehicles{ false };
				bool peds{ false };
				bool objects{ true };
			}
			std::vector<const char*> forceType = { "Normal", "Blackhole" };
			int forcePos{ 0 };
			float force{ 250.0f };
			float pull_in_force{ 5.0 };
			float zoom{ 50 };
		}
		bool enabled{ false };

		void move(Entity target) {
			auto rot{ CAM::GET_GAMEPLAY_CAM_ROT(0) };
			auto direction{ g_math->rotation_to_direction(&rot) };
			auto zoom{ direction * settings::zoom };
			auto spawn_position{ CAM::GET_GAMEPLAY_CAM_COORD() + zoom };
			if (g_utils->control_pressed(pressed, 25)) {
				if (settings::forcePos == 0) {
					util::request_control(target);
					auto aim_coordsX{ util::get_velocity(spawn_position.x, g_utils->coords(target).x) };
					auto aim_coordsY{ util::get_velocity(spawn_position.y, g_utils->coords(target).y) };
					auto aim_coordsZ{ util::get_velocity(spawn_position.z, g_utils->coords(target).z) };
					if (!g_utils->shooting()) {
						ENTITY::SET_ENTITY_VELOCITY(target, aim_coordsX * settings::pull_in_force, aim_coordsY * settings::pull_in_force, aim_coordsZ * settings::pull_in_force);
						if (settings::sphere::enabled)
							GRAPHICS::DRAW_MARKER(settings::sphere::preview, spawn_position.x, spawn_position.y, spawn_position.z, 0, 0, 0, settings::sphere::rotation.x, settings::sphere::rotation.y, settings::sphere::rotation.z, settings::sphere::size, settings::sphere::size, settings::sphere::size, 255, 0, 0, 150, false, false, 0, false, NULL, NULL, false);
					}


				}
				else if (settings::forcePos == 1) {
					util::request_control(target);
					auto first{ g_utils->coords(target) };
					Vector3 total = { spawn_position.x - first.x, spawn_position.y - first.y, spawn_position.z - first.z };
					first.z += 1.5f;
					if (!g_utils->shooting() && settings::sphere::enabled)
						GRAPHICS::DRAW_MARKER(settings::sphere::preview, spawn_position.x, spawn_position.y, spawn_position.z, 0, 0, 0, settings::sphere::rotation.x, settings::sphere::rotation.y, settings::sphere::rotation.z, settings::sphere::size, settings::sphere::size, settings::sphere::size, 255, 0, 0, 150, false, false, 0, false, NULL, NULL, false);

					if (g_math->distance(spawn_position, first) > 3.f)
						ENTITY::APPLY_FORCE_TO_ENTITY(target, 1, (total.x / 13) * settings::pull_in_force, (total.y / 13) * settings::pull_in_force, total.z / 13, 0.f, 0.f, 0.f, 0, false, true, true, 0, 0);
					else {
						ENTITY::SET_ENTITY_VELOCITY(target, 0.f, 0.f, 0.f);
						ENTITY::APPLY_FORCE_TO_ENTITY(target, 1, 0.f, 0.f, total.z / 15, 0.f, 0.f, 0.f, 0, false, true, true, 0, 0);
					}
				}
			}
		
		}
		void init() {
			if (!enabled) return;

			for (auto e : g_pools->all(settings::excludes::vehicles, settings::excludes::peds, settings::excludes::objects))
				move(e);
			
		}
	}
}
