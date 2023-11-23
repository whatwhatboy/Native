#include "script_manager.h"
#include "src/Natives/Invoker/Invoker.h"

namespace Base {
	void script_manager::Init(std::unique_ptr<Script> script) {
		std::lock_guard lock(Mutex);
		Scripts.push_back(std::move(script));
	}

	void script_manager::Destroy()
	{
		std::lock_guard lock(Mutex);
		Scripts.clear();
	}

	void script_manager::Tick()
	{
		static bool Convert = (ConvertThreadToFiber(nullptr), true);
		static bool EnsureNativeHandlers = (g_invoker->cache_handlers(), true);

		std::lock_guard lock(Mutex);
		for (auto const& script : Scripts)
		{
			script->Tick();
		}
	}
}