#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"
#include <csignal>

namespace Base::misc::random {
	void instant_alt_f4::tick() {
		if (!m_enabled) return;

		if (GetAsyncKeyState(0xA4) && GetAsyncKeyState(VK_F4)) {
			raise(SIGSEGV);
		}
	}
}
