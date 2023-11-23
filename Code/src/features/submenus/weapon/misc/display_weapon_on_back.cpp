#pragma once
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>
#include "classes.hpp"
namespace Base {
    void display_weapon_on_back::init() {
        if (!m_enabled) return;
        if (WEAPON::GET_CURRENT_PED_WEAPON(g_utils->self(), &m_hash, true)) {
            m_unko = ENTITY::GET_ENTITY_MODEL(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(g_utils->self(), 0));
            m_backcompat = true;
        }
        else {
            m_backcompat = false;
        }

        if (m_backcompat) {
            if (!ENTITY::DOES_ENTITY_EXIST(m_weapon_entity)) {
                m_backup = m_unko;
                m_weapon_entity = create_object("", m_unko, true, true);
            }
            else {
                ENTITY::ATTACH_ENTITY_TO_ENTITY(m_weapon_entity, g_utils->self(), PED::GET_PED_BONE_INDEX(g_utils->self(), 24818), m_selected.lx, m_selected.ly, m_selected.lz, m_selected.rx, m_selected.ry, m_selected.rz, 1, 1, 0, 1, 2, 1, 0);
            }

            if (ENTITY::IS_ENTITY_ATTACHED(m_weapon_entity) && m_backup != m_unko) {
                NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(m_weapon_entity);
                ENTITY::SET_ENTITY_AS_MISSION_ENTITY(m_weapon_entity, true, true);
                ENTITY::DELETE_ENTITY(&m_weapon_entity);
            }
        }
        else {
            if (ENTITY::DOES_ENTITY_EXIST(m_weapon_entity)) {
                NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(m_weapon_entity);
                ENTITY::SET_ENTITY_AS_MISSION_ENTITY(m_weapon_entity, true, true);
                ENTITY::DELETE_ENTITY(&m_weapon_entity);
            }
        }
    }
    void display_weapon_on_back::on_disable() {
        if (ENTITY::DOES_ENTITY_EXIST(m_weapon_entity)) {
            NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(m_weapon_entity);
            ENTITY::SET_ENTITY_AS_MISSION_ENTITY(m_weapon_entity, 1, 1);
            ENTITY::DELETE_ENTITY(&m_weapon_entity);
        }
    }
}
