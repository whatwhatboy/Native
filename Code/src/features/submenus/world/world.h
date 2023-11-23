#pragma once 
#include "src/utility/common/common.h"
#include "src/Natives/Natives.h"
#include "src/Memory/Pointers/Pointers.h"

namespace Base {
	class world_options {
	public:
		void add();
	};
	inline world_options g_world_options;
}