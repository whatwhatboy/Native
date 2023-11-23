#include "bodyguard_manager.h"

namespace Base {
	str get_name_from_hash(rage::joaat_t hash) {
		for (auto& model : model_changer_table) {
			if (rage::joaat(model) == hash) return model;
		}

		return "Invalid";
	}
	void bodyguard_manager::spawn() {
		auto hash{ rage::joaat(model_changer_table[m_selected_hash]) };
		auto owner{ PLAYER::GET_PLAYER_PED(m_owner) };
		g_utils->request(request_type::model, hash, [=] {
			Vector3 c{ g_utils->coords(owner) };
			Ped ped{ PED::CREATE_PED(26, hash, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(owner), true, true) };

			NETWORK::NETWORK_FADE_IN_ENTITY(ped, true, false);
			PED::SET_PED_AS_GROUP_LEADER(owner, PLAYER::GET_PLAYER_GROUP(m_owner));
			PED::SET_PED_AS_GROUP_MEMBER(ped, PLAYER::GET_PLAYER_GROUP(m_owner));
			PED::SET_PED_NEVER_LEAVES_GROUP(ped, PLAYER::GET_PLAYER_GROUP(m_owner));
			PED::SET_PED_COMBAT_ABILITY(ped, 100);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, all_weapons_hash[m_weapon], 9998, true);
			PED::SET_PED_CAN_SWITCH_WEAPON(ped, true);
			PED::SET_GROUP_FORMATION(PLAYER::GET_PLAYER_GROUP(m_owner), 3);
			PED::SET_PED_MAX_HEALTH(ped, 5000);
			PED::SET_PED_ACCURACY(ped, m_accuracy);
			ENTITY::SET_ENTITY_INVINCIBLE(ped, m_godmode);
			m_spawned.push_back({ ped, get_name_from_hash(hash) });
		});

	}
}