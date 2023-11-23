#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base::world::time {
	namespace timelapse {
		bool enabled{ false };
		void init() {
			if (!enabled) return;

			CLOCK::ADD_TO_CLOCK_TIME(0, 0, 1);
		}
	}
	namespace pause {
		bool enabled{};
		void tick() {
			CLOCK::PAUSE_CLOCK(enabled);
		}
	}
}
