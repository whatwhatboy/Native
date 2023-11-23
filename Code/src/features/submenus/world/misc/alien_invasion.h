#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base {
	namespace alien_invasion {
		namespace data {
			std::vector<Ped> spawned{};
			int money{ 0 };
		}
		namespace settings {
			const char* difficulty_names[3] = { "Easy", "Medium", "Hard" };
			int difficulty{ 2 };
		}
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			int found_peds{};
			for (auto spawned_ped : data::spawned)
				TASK::TASK_COMBAT_PED(spawned_ped, g_utils->self(), 0, 16);
			auto alien_hash{ rage::joaat("s_m_m_movalien_01") };
			for (auto ped : g_pools->peds()) {
				found_peds++;
				if (found_peds > 100) return;
				if (ENTITY::GET_ENTITY_MODEL(ped) != alien_hash) {
					STREAMING::REQUEST_MODEL(alien_hash);
					if (STREAMING::HAS_MODEL_LOADED(alien_hash)) {
						auto coords{ g_utils->coords(ped) };
						auto heading{ ENTITY::GET_ENTITY_HEADING(ped)};
						PED::DELETE_PED(&ped);
						auto spawned_alien{ PED::CREATE_PED(ePedType::PED_TYPE_MISSION, alien_hash, coords.x, coords.y, coords.z, heading, true, false) };
						data::spawned.push_back(spawned_alien);
						TASK::TASK_COMBAT_PED(spawned_alien, g_utils->self(), 0, 16);
						PED::SET_PED_COMBAT_ATTRIBUTES(spawned_alien, 5, true);
						PED::SET_PED_COMBAT_ATTRIBUTES(spawned_alien, 13, true);
						int random{ g_utils->get_random_value_in_range<int>(0, 10) };
						if (random == 6) { 
							if (settings::difficulty == 2) {
								WEAPON::GIVE_DELAYED_WEAPON_TO_PED(spawned_alien, rage::joaat("WEAPON_RAYPISTOL"), 9999, true);
								PED::SET_PED_SUFFERS_CRITICAL_HITS(spawned_alien, false);
								PED::SET_PED_MAX_HEALTH(spawned_alien, 500);
							}
						}
						else
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(spawned_alien, rage::joaat("WEAPON_KNIFE"), 9999, true);
						
						
					}
				}

			}
		}
	}
}
