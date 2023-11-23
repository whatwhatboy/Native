#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/rage/script/globals/GPBD_FM_3.hpp>
#include "src/features/utils/host.h"
namespace Base {
	static inline script_global gsbd_fm_events(1924276);
	static inline const script_global gpbd_fm_3(1895156);
	inline void set_fm_event_index(int index) {
		int idx = index / 32;
		int bit = index % 32;
		bits::set_bit(gsbd_fm_events.at(11).at(361).at(idx, 1).as<int*>(), bit);
		bits::set_bit(gsbd_fm_events.at(11).at(353).at(idx, 1).as<int*>(), bit);
		bits::set_bit((int*)&gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.ActiveFreemodeEvents[idx], bit);
	}

	inline void clear_fm_event_index(int index) {
		int idx = index / 32;
		int bit = index % 32;
		bits::clear_bit(gsbd_fm_events.at(11).at(361).at(idx, 1).as<int*>(), bit);
		bits::clear_bit(gsbd_fm_events.at(11).at(353).at(idx, 1).as<int*>(), bit);
		bits::clear_bit((int*)&gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.ActiveFreemodeEvents[idx], bit);
	}
	namespace force_thunder {
		bool enabled{ false };
		void init() {
			if (!STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && g_utils->find_script_thread(rage::joaat("freemode")) && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("maintransition")) == 0 && *g_pointers->m_is_session_started) {
				set_fm_event_index(9);
				set_fm_event_index(10);
				set_fm_event_index(11);
			}
		}
		void on_disable() {
			if (!STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && g_utils->find_script_thread(rage::joaat("freemode")) && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("maintransition")) == 0 && *g_pointers->m_is_session_started) {
				clear_fm_event_index(9);
				clear_fm_event_index(10);
				clear_fm_event_index(11);
			}
		}
	}
}
