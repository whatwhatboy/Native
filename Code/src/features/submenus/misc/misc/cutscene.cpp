#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base::cutscene {
	void disable::tick() {
		if (!m_enabled) return;

		CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
	}

	void buttons::stop() {
		CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
	}
	void buttons::set_skippable() {
		CUTSCENE::SET_CUTSCENE_CAN_BE_SKIPPED(0);
	}
}
