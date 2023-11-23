#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/rage/script/globals/GlobalPlayerBD.hpp>
#include <src/framework/notifications/notifications.h>

namespace Base::notis {
	namespace death {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			
			for (auto plr : get_players()) {
				auto ped = PLAYER::GET_PLAYER_PED(plr->m_player_id);
				if (ped && PED::IS_PED_DEAD_OR_DYING(ped, 0)) {
					auto source{ (CPed*)g_pointers->m_handle_to_ptr(PED::GET_PED_SOURCE_OF_DEATH(ped)) };
					auto weapon{ PED::GET_PED_CAUSE_OF_DEATH(ped) };
					const str name{ (source && source->m_player_info) ? source->m_player_info->m_net_player_data.m_name : "Invalid" };
					const str msg{ (name == plr->get_name()) ? std::format("{} commited suicide", name) : std::format("{} killed {}", name, plr->get_name()) };
                    
					if (name != "Invalid")
						g_notifications->send("Network", msg);
				}
			}

		}
	}
}
