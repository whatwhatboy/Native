#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base::weather {
	namespace disable_sky {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			g_pointers->m_ui_weather->set_sky(false);
		}
		void on_disable() {
			g_pointers->m_ui_weather->set_sky(true);
		}
	}

	namespace lightning {
		float delay{ 500 };
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			g_utils->timed_function(delay, [] {
				MISC::FORCE_LIGHTNING_FLASH();
			});
		}
	}
}
