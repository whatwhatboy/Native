#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
    void magnet::init() {
        if (!m_enabled) return;

        for (auto entity : g_pools->all(m_settings.m_excludes.m_vehicles, m_settings.m_excludes.m_peds, m_settings.m_excludes.m_objects)) {
            auto velocity{ (g_utils->coords(entity) - g_utils->coords())};
            ENTITY::SET_ENTITY_VELOCITY(entity, velocity.x, velocity.y, velocity.z);
        }
    }
}
