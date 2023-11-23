#pragma once
#include "src/fiber/script/fiber_script.h"

namespace Base::script_manager {
	extern void Init(std::unique_ptr<Script> script);
	extern void Destroy();

	extern void Tick();

	inline std::recursive_mutex Mutex;
	inline std::vector<std::unique_ptr<Script>> Scripts;
}