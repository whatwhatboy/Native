#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/rage/script/globals/GlobalPlayerBD.hpp>

#include "src/features/utils/rid_utils.h"
namespace Base::globals {
	namespace off_radar {
		static inline script_global globalplayer_bd(2657704);
		static inline script_global offradar_time(2672524);
		namespace settings {
			bool ghost_org{ false };
		}
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			if (settings::ghost_org)
				MISC::SET_BIT(script_global(2794162).at(4667).as<int*>(), 2);

			globalplayer_bd.as<GlobalPlayerBD*>()->Entries[PLAYER::PLAYER_ID()].OffRadarActive = true;
			*offradar_time.at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 60;
		}
		void on_disable() {
			if (!settings::ghost_org)
				MISC::CLEAR_BIT(script_global(2794162).at(4667).as<int*>(), 2);

			globalplayer_bd.as<GlobalPlayerBD*>()->Entries[PLAYER::PLAYER_ID()].OffRadarActive = false;
		}
	}
	namespace bst {
		std::vector<const char*> type = { "Drop", "Instant" };
		int selected{ 1 };
	}
	namespace join_session {
		std::vector<const char*> session_types {
			"Public",
			"New Public",
			"Closed Crew",
			"Crew",
			"Friends",
			"Find Friend",
			"Solo",
			"Invite Only",
			"Join Crew",
		};
		int selected{ 0 };
		void join() {
			switch (selected) {
			case 0:
				rid_utils::join_type(eSessionType::JOIN_PUBLIC);
				break;
			case 1:
				rid_utils::join_type(eSessionType::NEW_PUBLIC);
				break;
			case 2:
				rid_utils::join_type(eSessionType::CLOSED_CREW);
				break;
			case 3:
				rid_utils::join_type(eSessionType::CREW);
				break;
			case 4:
				rid_utils::join_type(eSessionType::CLOSED_FRIENDS);
				break;
			case 5:
				rid_utils::join_type(eSessionType::FIND_FRIEND);
				break;
			case 6:
				rid_utils::join_type(eSessionType::SOLO);
				break;
			case 7:
				rid_utils::join_type(eSessionType::INVITE_ONLY);
				break;
			case 8:
				rid_utils::join_type(eSessionType::JOIN_CREW);
				break;
			}
		}
	}
}
