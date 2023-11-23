#include "player_manager.h"
#include <src/features/utils/utils.h>

namespace Base {
	void player_mgr_buttons::ram(player_context context, Hash hash) {
		g_utils->request(request_type::model, hash, [=] {
			auto pos{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(context.m_ped, 0, 20, 0) };
			auto heading{ ENTITY::GET_ENTITY_HEADING(context.m_ped) - 180 };
			auto vehicle{ VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, heading, true, true, 0) };
			g_utils->make_networked(vehicle);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 300);
		});
	}

	void player_mgr_buttons::clone(player_context context) {
		PED::CLONE_PED(context.m_ped, context.m_heading, true, true);
	}

	void player_mgr_buttons::boost(player_context context) {
		g_utils->request_control(context.m_vehicle, [=] {
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(context.m_vehicle, 200);
		});
	}

	void player_mgr_buttons::kill_engine(player_context context) {
		g_utils->request_control(context.m_vehicle, [=] {
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(context.m_vehicle, -4000.f);
		});
	}

	void player_mgr_buttons::upgrade(player_context context) {
		g_utils->request_control(context.m_vehicle, [=] {
			g_utils->max_vehicle(context.m_vehicle);
		});
	}
	void player_mgr_buttons::downgrade(player_context context) {
		g_utils->request_control(context.m_vehicle, [=] {
			g_utils->downgrade_vehicle(context.m_vehicle);
		});
	}
	void player_mgr_buttons::blame(player_context context) {
		for (auto i = 0; i < g_utils->get_network_player_mgr()->m_player_count; i++) {
			if (auto target{ PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) }) {
				auto coords{ g_utils->coords(target) };
				g_utils->blame_explode(context.m_id, coords, eExplosionTag::GRENADE, 9999, true, false, 0);
			}
		}
	}
	void player_mgr_buttons::kick_from_vehicle(player_context context) {
		const size_t arg_count{ 9 };
		int64_t args[arg_count] = {
			(int64_t)-1603050746,
			PLAYER::PLAYER_ID(), 0, 0, 0, 0, 0, 0, 0
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << context.m_id);
	}
	void player_mgr_buttons::cage(player_context context, int type) {
		if (type == 1) {
			g_utils->request(request_type::model, 0x466EB7B8, [=] {
				Vector3 min_dimensions;
				Vector3 max_dimensions;

				MISC::GET_MODEL_DIMENSIONS(0x466EB7B8, &min_dimensions, &max_dimensions);
				auto diameter{ max_dimensions - min_dimensions };

				auto spawn_coords{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(context.m_ped, -1.5f, -1.5f, 0.f) };
				MISC::GET_GROUND_Z_FOR_3D_COORD(spawn_coords.x, spawn_coords.y, spawn_coords.z, &spawn_coords.z, false, 0);

				auto first_object{ OBJECT::CREATE_OBJECT(0x466EB7B8, spawn_coords.x, spawn_coords.y, spawn_coords.z, true, true, false) };
				if (ENTITY::DOES_ENTITY_EXIST(first_object)) {
					float rotation{ context.m_heading };
					ENTITY::SET_ENTITY_ROTATION(first_object, 0.f, 0.f, rotation, 2, false);
					ENTITY::FREEZE_ENTITY_POSITION(first_object, true);

					auto next_object{ first_object };
					for (int i = 0; i < 3; i++) {
						rotation += 90.f;

						auto next{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(next_object, diameter.x, 0.f, 0.f) };
						next_object = OBJECT::CREATE_OBJECT(0x466EB7B8, next.x, next.y, next.z, true, true, false);
						if (ENTITY::DOES_ENTITY_EXIST(next_object)) {
							ENTITY::SET_ENTITY_ROTATION(next_object, 0.f, 0.f, rotation, 2, false);
							ENTITY::FREEZE_ENTITY_POSITION(next_object, true);
						}
					}
				}
			});
		}
		else {
			g_utils->request(request_type::model, 0x7B059043, [=] {
				auto cage{ OBJECT::CREATE_OBJECT(0x7B059043, context.m_coords.x, context.m_coords.y, context.m_coords.z - 1.f, true, true, false) };
				ENTITY::FREEZE_ENTITY_POSITION(cage, true);

				cage = OBJECT::CREATE_OBJECT(0x7B059043, context.m_coords.x, context.m_coords.y, context.m_coords.z + 1.f, true, true, false);
				ENTITY::FREEZE_ENTITY_POSITION(cage, true);
				ENTITY::SET_ENTITY_ROTATION(cage, 0.f, 180.f, 90.f, 0, false);
			});
		}
	}

	//crashes
	void player_mgr_buttons::task_crash(player_context context) {
		g_utils->request_control(context.m_vehicle, [=] {
			TASK::TASK_VEHICLE_TEMP_ACTION(context.m_ped, context.m_vehicle, 18, 100);
			TASK::TASK_VEHICLE_TEMP_ACTION(context.m_ped, context.m_vehicle, 16, 100);
		});
	}
}