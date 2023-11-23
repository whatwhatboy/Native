#include "script_hook.h"
#include "src/Memory/Pointers/Pointers.h"
#include "src/Core/Logger/Logger.h"
#include <unordered_map>
#include <src/Natives/Invoker/Invoker.h>
#include <src/hooking/vmt/hook.h>

namespace Base {
	std::unordered_map<rage::scrProgram*, ScriptHook*> ScriptHook::s_Map;
	ScriptHook::ScriptHook(rage::joaat_t ScriptHash, std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> Replacements) : m_ScriptHash(ScriptHash), m_NativeReplacementsPointer(std::move(Replacements)) {
		Ensure();
	}
	ScriptHook::ScriptHook(rage::scrProgram* Program, std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> Replacements) : m_NativeReplacementsPointer(std::move(Replacements)) {
		HookInstance(Program);
	}
	ScriptHook::~ScriptHook() {
		if (m_Program) {
			for (auto [Hash, Handler] : m_NativeHandlerPointer) {
				*Handler = g_invoker->m_cache[Hash];
			}
		}
		if (m_VMTHook) {
			m_VMTHook->disable();
			if (m_Program)
				s_Map.erase(m_Program);
		}
	}
	void ScriptHook::Ensure() {
		if (m_VMTHook) {
			return;
		}
		if (auto Program{ g_pointers->m_script_program_table->find_script(m_ScriptHash) }; Program && Program->is_valid()) {
			HookInstance(Program);
		}
	}
	void ScriptHook::HookInstance(rage::scrProgram* Program) {
		m_Program = Program;
		s_Map.emplace(m_Program, this);
		m_VMTHook = std::make_unique<vmt_hook>(vft(m_Program, 9), vft({ vft_function_data(&scrProgramDetour, 6) }));	
		m_VMTHook->enable();
		for (auto [Hash, ReplacementHandler] : m_NativeReplacementsPointer) {
			auto Handler = g_invoker->m_cache[Hash];
			if (!Handler)
				continue;
			auto HandlerPtr = m_Program->get_address_of_native_entrypoint(Handler);
			if (!HandlerPtr)
				continue;
			m_NativeHandlerPointer.emplace(Hash, reinterpret_cast<rage::scrNativeHandler*>(HandlerPtr));
			*HandlerPtr = ReplacementHandler;
		}
	}
	void ScriptHook::scrProgramDetour(rage::scrProgram* this_, bool free_memory) {
		if (auto it = s_Map.find(this_); it != s_Map.end()) {
			auto Hook = it->second;
			Hook->m_Program = nullptr;
			s_Map.erase(it);
			auto OgFunc = Hook->m_VMTHook->get_original<decltype(&scrProgramDetour)>(0);
			Hook->m_VMTHook->disable();
			Hook->m_VMTHook.reset();
			OgFunc(this_, free_memory);
		}
	}
}