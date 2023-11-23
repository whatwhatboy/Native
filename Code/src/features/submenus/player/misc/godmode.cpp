#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	void godmode::init() {
        if (!m_enabled) return;
        u32 last_bits{ 0 };
        u32 proof_mask{ 1 << 8 };
        auto bits{ proof_mask };
        auto changed_bits{ bits ^ last_bits };
        auto changed_or_enabled_bits{ bits | changed_bits };
        auto ped{ g_utils->cped() };

        switch (m_settings.m_position) {
        case 0:
            if (changed_or_enabled_bits) {
                uint32_t unchanged_bits{ ped->m_damage_bits & ~changed_or_enabled_bits };
                ped->m_damage_bits = unchanged_bits | bits;
                last_bits = bits;
            }
            break;

        case 1:
            reset();
            ped->m_health = ped->m_maxhealth;
            break;

        case 2:
            reset();
            ENTITY::SET_ENTITY_INVINCIBLE(g_utils->self(), true);
            break;

        case 3:
            reset();
            if (ped->m_health < 10) {
                ped->m_health = 10;
            }
            break;
        }
	}
	void godmode::on_disable() {
        reset();
		ENTITY::SET_ENTITY_INVINCIBLE(g_utils->self(), false);
	}
}
