#include "src/hooking/hooking.h"
#include "src/memory/Pointers/Pointers.h"
namespace Base {
	void hooks::render_entity(__int64 renderer, rage::fwEntity* entity, int unk, bool a4) {
		if (*(int*)(((__int64)(*g_pointers->m_draw_handler_mgr) + 0x14730)) >= 512 && g_protection_manager.m_crashes.m_entity_render) {
			*(int*)(renderer + 4) &= ~0x80000000;
			*(int*)(renderer + 4) &= ~0x40000000;
			*(int*)(renderer + 4) |= (a4 & 1) << 30;
			*(int*)renderer = -2;
		}
		else {
			return static_cast<decltype(&render_entity)>(g_hooking->original_draw1)(renderer, entity, unk, a4);
		}
	}
	void* hooks::render_ped(__int64 renderer, CPed* ped, __int64 a3, __int64 a4) {
		if (*(int*)(((__int64)(*g_pointers->m_draw_handler_mgr) + 0x14730)) >= 499 && g_protection_manager.m_crashes.m_entity_render) {
			return nullptr;
		}
		else {
			return static_cast<decltype(&render_ped)>(g_hooking->original_draw2)(renderer, ped, a3, a4);
		}
	}
	__int64 hooks::render_big_ped(__int64 renderer, CPed* ped, __int64 a3, __int64 a4) {
		if (*(int*)(((__int64)(*g_pointers->m_draw_handler_mgr) + 0x14730)) >= 512 && g_protection_manager.m_crashes.m_entity_render) {
			*(int*)(a4 + 4) = -2;
			return a4 + 0x14;
		}
		else {
			return static_cast<decltype(&render_big_ped)>(g_hooking->original_draw3)(renderer, ped, a3, a4);
		}
	}
}