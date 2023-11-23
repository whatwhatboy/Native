#pragma once
#include "types.h"
#include "src/features/utils/utils.h"
namespace Base {
	class player_mgr_buttons {
	public:
		void ram(player_context context, Hash hash);
		void clone(player_context context);
		void kick_from_vehicle(player_context context);

		//vehicles
		void boost(player_context context);
		void kill_engine(player_context context);
		void cage(player_context context, int type);
		void upgrade(player_context context);
		void downgrade(player_context context);
		void blame(player_context context);

		//crashes
		void task_crash(player_context context);

	};

	class player_manager {
	public:
		player_data m_players[32];
	public:
		void tick();
	public:
		player_mgr_buttons m_buttons;
	} inline g_player_mgr;

	inline player_context get_context(int plr) {
		auto ped{ PLAYER::GET_PLAYER_PED(plr) };

		player_context cxt;
		cxt.m_ped = ped;
		cxt.m_coords = g_utils->coords(ped);
		cxt.m_heading = ENTITY::GET_ENTITY_HEADING(ped);
		cxt.m_id = plr;
		cxt.m_vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);
		return cxt;
	}
}
