#pragma once
#include "src/Natives/Invoker/Invoker.h"
#include "script_hook.h"
#include <src/rage/script/scrThread.hpp>
#include <src/rage/script/scrProgram.hpp>
#include <unordered_map>

namespace Base {
	class native_hooks final {
		using NativeDetour = std::pair<rage::scrNativeHash, rage::scrNativeHandler>;
		std::unordered_map<rage::joaat_t, std::vector<NativeDetour>> native_registrations;
		std::unordered_map<rage::scrProgram*, std::unique_ptr<ScriptHook>> script_hooks;
	public:
		native_hooks();
		~native_hooks();
	public:
		void add_native_detour(rage::joaat_t ScriptHash, rage::scrNativeHash Hash, rage::scrNativeHandler Detour);
		void hook_program(rage::scrProgram* Program);
		void unhook_program(rage::scrProgram* Program);
	};
	inline std::unique_ptr<native_hooks> g_native_hooks;
}
