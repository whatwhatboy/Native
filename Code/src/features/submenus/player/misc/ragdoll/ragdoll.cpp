#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "ragdoll.hpp"

namespace Base::ragdoll {
	void on_q::init() {
		if (g_utils->key_press(0x51) & 1 && m_enabled) {
			auto forward_vector{ ENTITY::GET_ENTITY_FORWARD_VECTOR(g_utils->self()) };
			PED::SET_PED_TO_RAGDOLL_WITH_FALL(g_utils->self(), 1500, 2000, 1, -forward_vector.x, -forward_vector.y, -forward_vector.z, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
		}
	}

	void no_ragdoll::init() {
		if (!m_enabled) return;

		PED::SET_PED_RAGDOLL_ON_COLLISION(g_utils->self(), false);
		PED::SET_PED_CAN_RAGDOLL(g_utils->self(), false);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(g_utils->self(), false);
	}
	void no_ragdoll::on_disable() {
		PED::SET_PED_CAN_RAGDOLL(g_utils->self(), true);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(g_utils->self(), true);
	}

	void bound_ankles::init() {
		if (!m_enabled) return;

		PED::SET_ENABLE_BOUND_ANKLES(g_utils->self(), true);
	}
	void bound_ankles::on_disable() {
		PED::SET_ENABLE_BOUND_ANKLES(g_utils->self(), false);
	}

	void fly::init() {
		if (!m_enabled) return;

		auto forward_vector{ ENTITY::GET_ENTITY_FORWARD_VECTOR(g_utils->self()) };
		PED::SET_PED_TO_RAGDOLL_WITH_FALL(g_utils->self(), 1500, 2000, 1, -forward_vector.x, -forward_vector.y, -forward_vector.z, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);

		/*auto direction{ CAM::GET_GAMEPLAY_CAM_COORD() };
		ENTITY::SET_ENTITY_VELOCITY(g_utils->self(), direction.x, direction.y, direction.z);*/
	}

	void die::tick() {
		if (!m_enabled) return;

		if (PED::IS_PED_RAGDOLL(g_utils->self())) {
			g_utils->cped()->m_health = 0;
		}
	}
}
