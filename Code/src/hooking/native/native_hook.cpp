#include "native_hook.h"
#include "src/hooking/hooking.h"
#include "src/memory/pointers/pointers.h"
#include "src/core/logger/logger.h"

namespace Base {
	native_hooks::native_hooks() {
		add_native_detour("all_scripts"_joaat, 0x767FBC2AC802EF3D, hooks::StatGetInt);
		add_native_detour("all_scripts"_joaat, 0x158C16F5E4CF41F8, hooks::disable_casino_country_restrictions);
		add_native_detour("all_scripts"_joaat, 0xDC38CC1E35B6A5D7, hooks::SET_WARNING_MESSAGE_WITH_HEADER);
		add_native_detour("all_scripts"_joaat, 0x867654CBC7606F2C, hooks::shoot_single_bullet);
		add_native_detour("all_scripts"_joaat, 0x6D0DE6A7B5DA71F8, hooks::get_player_name);

		add_native_detour("all_scripts"_joaat, 0xADF692B254977C0C, hooks::set_current_ped_weapon);
		add_native_detour("all_scripts"_joaat, 0xFE99B66D079CF6BC, hooks::disable_control_action);
		add_native_detour("all_scripts"_joaat, 0xEB354E5376BC81A7, hooks::hud_force_weapon_wheel);

		add_native_detour("maintransition"_joaat, 0x6F3D4ED9BEE4E61D, hooks::NETWORK_SESSION_HOST);
		add_native_detour("freemode"_joaat, 0x95914459A87EBA28, hooks::network_bail);
		add_native_detour("maintransition"_joaat, 0x95914459A87EBA28, hooks::network_bail);

		for (auto& entry : *g_pointers->m_script_program_table)
			if (entry.m_program)
				hook_program(entry.m_program);
	}
	native_hooks::~native_hooks() {
		script_hooks.clear();
	}
	void native_hooks::add_native_detour(rage::joaat_t ScriptHash, rage::scrNativeHash Hash, rage::scrNativeHandler Detour) {
		if (const auto& it = native_registrations.find(ScriptHash); it != native_registrations.end()) {
			it->second.emplace_back(Hash, Detour);
			return;
		}
		native_registrations.emplace(ScriptHash, std::vector<NativeDetour>({ { Hash, Detour } }));
	}
	void native_hooks::hook_program(rage::scrProgram* Program) {
		std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> native_replacements{};
		const auto ScriptHash{ Program->m_name_hash };

		if (const auto& Pair = native_registrations.find("all_scripts"_joaat); Pair != native_registrations.end())
			for (const auto& native_hook_registration : Pair->second)
				native_replacements.insert(native_hook_registration);

		if (const auto& Pair = native_registrations.find(ScriptHash); Pair != native_registrations.end())
			for (const auto& native_hook_registration : Pair->second)
				native_replacements.insert(native_hook_registration);

		if (!native_replacements.empty()) {
			script_hooks.emplace(Program, std::make_unique<ScriptHook>(Program, native_replacements));
		}
	}
	void native_hooks::unhook_program(rage::scrProgram* Program) {
		script_hooks.erase(Program);
		LOG(Info, "Detached from {}'s rage::scrProgram", Program->m_name);
	}
}