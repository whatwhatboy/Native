#pragma once
#include "src/framework/notifications/notifications.h"
#include "src/features/utils/utils.h"
#include "src/natives/natives.h"
#include "classes.h"

namespace Base {
	constexpr auto valid_player_models = {
		rage::joaat("mp_m_freemode_01"),
		rage::joaat("mp_f_freemode_01"),
		rage::joaat("u_m_m_filmdirector"),
		rage::joaat("player_zero"),
		rage::joaat("player_one"),
		rage::joaat("player_two"),
		rage::joaat("A_C_Boar"),
		rage::joaat("A_C_Cat_01"),
		rage::joaat("A_C_Cow"),
		rage::joaat("A_C_Coyote"),
		rage::joaat("A_C_Deer"),
		rage::joaat("A_C_Husky"),
		rage::joaat("A_C_MtLion"),
		rage::joaat("A_C_Pig"),
		rage::joaat("A_C_Poodle"),
		rage::joaat("A_C_Pug"),
		rage::joaat("A_C_Rabbit_01"),
		rage::joaat("A_C_Retriever"),
		rage::joaat("A_C_Rottweiler"),
		rage::joaat("A_C_shepherd"),
		rage::joaat("A_C_Westy"),
		rage::joaat("A_C_Chickenhawk"),
		rage::joaat("A_C_Cormorant"),
		rage::joaat("A_C_Crow"),
		rage::joaat("A_C_Hen"),
		rage::joaat("A_C_Pigeon"),
		rage::joaat("A_C_Seagull"),
		rage::joaat("A_C_Dolphin"),
		rage::joaat("A_C_Fish"),
		rage::joaat("A_C_KillerWhale"),
		rage::joaat("A_C_SharkHammer"),
		rage::joaat("A_C_SharkTiger"),
		rage::joaat("A_C_Stingray"),
		rage::joaat("IG_Orleans"),
		rage::joaat("A_C_Chop"),
		rage::joaat("A_C_HumpBack"),
	};
	bool is_valid_player_model(Hash model) {
		for (auto model : valid_player_models)
			if (model == model) return true;

		return false;
	}
	bool is_modding(str name) {
		for (auto modder : g_modder_detection.m_modders) {
			if (modder == name) return true;
		}

		return false;
	}
	void mark_as_modder(str name, str reason) {
		if (!is_modding(name)) {
			g_notifications->send("Modder Detection", std::format("Flagged {} as a modder. Reason: {}", name, reason));
		}
	}
	void modder_detection::tick() {
		if (!m_enabled) return;

		for (int i{ 0 }; i < g_utils->get_network_player_mgr()->m_player_count; i++) {
			if (auto ped{ PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) }) {
				auto model{ ENTITY::GET_ENTITY_MODEL(ped) };
				auto name{ g_pointers->m_get_player_name(i) };
				auto vehicle{ PED::GET_VEHICLE_PED_IS_IN(ped, false) };

				if (!is_valid_player_model(model) && m_detections.m_model) {
					mark_as_modder(name, "Invalid Model");
				}

				//vehicle speed
				if (m_detections.m_speed && PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
					if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1, 1) == ped) {
						if (VEHICLE::GET_HAS_ROCKET_BOOST(vehicle)) {
							Hash scramjet = rage::joaat("scramjet");
							Hash oppressor = rage::joaat("oppressor2");
							if (ENTITY::GET_ENTITY_MODEL(vehicle) == oppressor) {
								if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 67) {
									if (!PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped)) {
										if (!VEHICLE::IS_ROCKET_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(ped, false))) {
											if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
												mark_as_modder(name, "Vehicle Speed");
											}
										}
									}
								}
							}
							else {
								if (ENTITY::GET_ENTITY_MODEL(vehicle) == scramjet) {
									if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 74) {
										if (!PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped)) {
											if (!VEHICLE::IS_ROCKET_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(ped, false))) {
												mark_as_modder(name, "Vehicle Speed");
											}
										}
									}
								}
								else {
									if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 67 && !PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped) && !VEHICLE::IS_ROCKET_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(ped, false))) {
										mark_as_modder(name, "Vehicle Speed");
									}
								}
							}
						}
						else {
							if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 67) {
								if (!PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped)) {
									if (!VEHICLE::IS_ROCKET_BOOST_ACTIVE(PED::GET_VEHICLE_PED_IS_IN(ped, false))) {
										mark_as_modder(name, "Vehicle Speed");
									}

								}
							}
						}
					}
					if (PED::IS_PED_IN_ANY_PLANE(ped) && PED::IS_PED_IN_ANY_HELI(ped)) {
						if (ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, false)) > 161) {
							if (!PED::IS_PED_IN_ANY_PLANE(ped) && !PED::IS_PED_IN_ANY_HELI(ped)) {
								mark_as_modder(name, "Vehicle Speed");
							}
						}
					}
				}
			}
		}
	}
}
