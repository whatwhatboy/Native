#pragma once

#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/hooking/hooking.h"
#include "classes.h"
namespace Base {
    Vector3 calculate_jump_force(const Vector3& forward_vector, float jump_forward_force, float jump_upward_force) {
        return { forward_vector.x * jump_forward_force + 0.0f, forward_vector.y * jump_forward_force + 0.0f, forward_vector.z * jump_forward_force + jump_upward_force };
    }
    void super_jump::init() {
        if (!m_enabled) return;
        if (PED::IS_PED_JUMPING(g_utils->self()) && !PED::IS_PED_RAGDOLL(g_utils->self()) && m_settings.m_add_force)
            ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->self(), 1, 0.f, m_settings.m_force, 0.0f, 0.0f, 0.0f, 0.0f, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE);

        if (m_settings.m_type_pos == 0 || m_settings.m_infinite_jump || m_settings.m_rolling.m_use_super_jump)
            g_hooking_features.super_jump = true;

        if (m_settings.m_type_pos != 0 && !m_settings.m_infinite_jump && !m_settings.m_rolling.m_use_super_jump)
            g_hooking_features.super_jump = false;

        if (m_settings.m_type_pos != 1)
            g_hooking_features.beast_jump = false;

        switch (m_settings.m_type_pos) {
        case 1:
            g_hooking_features.beast_jump = true;
            break;
        case 2:
            if (PED::IS_PED_JUMPING(g_utils->self())) {
                if (ENTITY::IS_ENTITY_IN_AIR(g_utils->self())) {
                    static int flip;
                    if (m_settings.m_rolling.m_flip_pos == 0)
                        flip -= m_settings.m_rolling.m_speed;
                    if (m_settings.m_rolling.m_flip_pos == 1)
                        flip += m_settings.m_rolling.m_speed;

                    ENTITY::SET_ENTITY_ROTATION(g_utils->self(), flip, 0, ENTITY::GET_ENTITY_HEADING(g_utils->self()), 0, 0);
                }
            }
            break;
        case 3:
            if (m_settings.m_instant_jump)
                PAD::DISABLE_CONTROL_ACTION(0, 22, true);

            if (m_settings.m_max_jump_distance > 0.0f) {
                float jump_distance{ ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(g_utils->self()) };
                if (jump_distance > m_settings.m_max_jump_distance) {
                    Vector3 push_force = { 0.0f, 0.0f, -m_settings.m_push_down_force };
                    ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->self(), 1, push_force.x, push_force.y, push_force.z, 0.0f, 0.0f, 0.0f, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE);
                }
            }

            if (m_settings.m_jump_forward_force > 0.0f || m_settings.m_jump_upward_force > 0.0f) {
                if (PAD::IS_CONTROL_JUST_PRESSED(0, 22) && !PED::IS_PED_IN_ANY_VEHICLE(g_utils->self(), false) && !ENTITY::IS_ENTITY_IN_AIR(g_utils->self()) && !PED::IS_PED_DOING_A_BEAST_JUMP(g_utils->self())) {
                    auto forward_vector{ ENTITY::GET_ENTITY_FORWARD_VECTOR(g_utils->self()) };
                    auto jump_force{ calculate_jump_force(forward_vector, m_settings.m_jump_forward_force, m_settings.m_jump_upward_force) };
                    ENTITY::APPLY_FORCE_TO_ENTITY(g_utils->self(), 1, jump_force.x, jump_force.y, jump_force.z, 0.0f, 0.0f, 0.0f, FALSE, TRUE, TRUE, TRUE, FALSE, TRUE);
                }
            }
            break;
        }
    }
    void super_jump::on_disable() {
        g_hooking_features.super_jump = false;
        g_hooking_features.beast_jump = false;
    }
}
