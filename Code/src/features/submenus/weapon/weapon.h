#pragma once 
#include "src/utility/common/common.h"
#include "src/Natives/Natives.h"
#include "src/Memory/Pointers/Pointers.h"

namespace Base {
	class weapon_options {
	public:
		void add();
	};
	inline weapon_options g_weapon_options;
}