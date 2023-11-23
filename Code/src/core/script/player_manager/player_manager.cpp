#include "player_manager.h"

namespace Base {
	void player_manager::tick() {
		auto mgr{ g_utils->get_network_player_mgr() };
		if (mgr) {
			for (auto i = 0; i < mgr->m_player_count; i++) {
				if (auto ped{ PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) }) {
					auto coords{ g_utils->coords(ped) };
					auto vehicle{ PED::GET_VEHICLE_PED_IS_IN(ped, false) };

					if (m_players[i].m_spectate) {
						NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, ped);
						HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, ped);

						ENTITY::FREEZE_ENTITY_POSITION(g_utils->self(), true);
						ENTITY::FREEZE_ENTITY_POSITION(g_utils->vehicle(), true);

						STREAMING::SET_FOCUS_ENTITY(ped);

						if (PED::IS_PED_DEAD_OR_DYING(g_utils->self(), 1)) {
							NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, g_utils->self());
						}
					}
					if (m_players[i].m_taze) {
						g_utils->request(request_type::weapon, 0x3656c8c1, [=] {
							MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(g_utils->coords().x, g_utils->coords().y, g_utils->coords().z + 1.f, coords.x, coords.y, coords.z, 10, 0, 0x3656c8c1, g_utils->self(), true, false, 100.f, g_utils->self(), 0);
						});
					}

					if (m_players[i].m_explode) {
						FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, eExplosionTag::GRENADE, 1000, true, false, 0, false);
					}

					if (m_players[i].m_hostile_vehicles) {
						for (auto veh : g_pools->vehicles()) {
							if (!VEHICLE::IS_THIS_MODEL_A_TRAIN(ENTITY::GET_ENTITY_MODEL(veh))) {
								auto ped{ VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1, 1) };
								if (ENTITY::DOES_ENTITY_EXIST(ped)) {
									TASK::TASK_VEHICLE_DRIVE_TO_COORD(ped, veh, coords.x, coords.y, coords.z, 100, 1, ENTITY::GET_ENTITY_MODEL(veh), 16777216, 4, -1);
								}
							}
						}
					}

					if (m_players[i].m_rain_rockets) {
						STREAMING::REQUEST_MODEL(0x13579279);
						auto start_position{ coords };
						start_position.x += MISC::GET_RANDOM_FLOAT_IN_RANGE(-20.f, 20.f);
						start_position.y += MISC::GET_RANDOM_FLOAT_IN_RANGE(-20.f, 20.f);
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(start_position.x, start_position.y, start_position.z + MISC::GET_RANDOM_FLOAT_IN_RANGE(50.f, 150.f), start_position.x, start_position.y, start_position.z, 250, 0, 0x13579279, ped, true, false, 1000.f, ped, 0);
						
					}

					if (m_players[i].m_slipply_tires) {
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);
						VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, true);
					}

					if (m_players[i].m_freeze_vehicle) {
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);
						ENTITY::FREEZE_ENTITY_POSITION(vehicle, true);
					}

					if (m_players[i].m_transaction_error) {
						int64_t event[4] = { (int64_t)eRemoteEvent::TransactionError, PLAYER::PLAYER_ID(), 0, 0 };
						g_pointers->m_trigger_script_event(1, event, 4, 1 << i);
					}
				}
			}
		}
	}
}