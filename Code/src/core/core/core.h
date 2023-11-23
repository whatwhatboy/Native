#pragma once
#include "src/utility/common/common.h"
#include "src/Core/Logger/Logger.h"

namespace Base::core {
	namespace main {
		extern void attach();
		extern void detach();
		extern void create_thread_instance();
	}
}