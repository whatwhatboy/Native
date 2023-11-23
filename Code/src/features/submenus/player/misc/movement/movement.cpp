#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "movement.hpp"

namespace Base::movement {
	void freeze::init() {
		if (!m_enabled) return;

		ENTITY::FREEZE_ENTITY_POSITION(g_utils->self(), true);
	}
	void freeze::on_disable() {
		ENTITY::FREEZE_ENTITY_POSITION(g_utils->self(), false);
	}
}
