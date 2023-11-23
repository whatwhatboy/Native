#pragma once 
#include "src/hooking/vmt/hook.h"
#include "src/Natives/Invoker/Invoker.h"
#include <src/rage/script/scrProgram.hpp>
#include <src/rage/rage/joaat.hpp>

namespace Base {
	class ScriptHook {
	public:
		ScriptHook(rage::joaat_t script_hash, std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> replacements);
		ScriptHook(rage::scrProgram* program, std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> replacements);
		~ScriptHook();
		void Ensure();
	private:
		void HookInstance(rage::scrProgram* program);
		static void scrProgramDetour(rage::scrProgram* this_, bool free_memory);
		static std::unordered_map<rage::scrProgram*, ScriptHook*> s_Map;
		rage::joaat_t m_ScriptHash;
		rage::scrProgram* m_Program;
		std::unique_ptr<vmt_hook> m_VMTHook;
		std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> m_NativeReplacementsPointer;
		std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler*> m_NativeHandlerPointer;
	};
}