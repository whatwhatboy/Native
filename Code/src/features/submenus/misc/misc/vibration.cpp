#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base::vibration {
	void disable::tick() {
		if (!m_enabled) return;
		
		PAD::STOP_CONTROL_SHAKE(0);
	}

	void shake::tick() {
		if (!m_enabled) return;

		g_utils->timed_function(m_settings.m_delay, [=] {
			PAD::SET_CONTROL_SHAKE(0, 1000, m_settings.m_intensity);
		});
	}
}
