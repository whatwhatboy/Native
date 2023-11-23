#pragma once 
#include "src/utility/common/common.h"
#include "src/Natives/Natives.h"
#include "src/Memory/Pointers/Pointers.h"

namespace Base {
	class network_options {
	public:
		void add();
	};
	inline network_options g_network_options;
}