#include "src/hooking/hooking.h"
namespace Base {

	constexpr uint32_t valid_parachute_models[] = {
		rage::joaat("p_parachute_s"),
		rage::joaat("vw_p_para_bag_vine_s"),
		rage::joaat("reh_p_para_bag_reh_s_01a"),
		rage::joaat("xm_prop_x17_scuba_tank"),
		rage::joaat("lts_p_para_bag_pilot2_s"),
		rage::joaat("lts_p_para_bag_lts_s"),
		rage::joaat("p_para_bag_tr_s_01a"),
		rage::joaat("p_para_bag_xmas_s"),
	};

	auto is_valid_parachute_model(rage::joaat_t hash) {
		for (auto& model : valid_parachute_models) {
			if (model == hash) {
				return true;
			}
		}
		return false;
	}

	void hooks::parachute_crash(ClonedTakeOffPedVariationInfo* info, CSyncDataBase* serializer) {
		CALL_DECL(parachute_crash, info, serializer);
		if (!is_valid_parachute_model(info->m_prop_hash) && g_protection_manager.m_crashes.m_parachute) {
			info->m_prop_hash = 0;
		}
	}

	u64 hooks::parachute_crash_2(u64 rcx, int rdx, int r8) {
		if ((rdx == 1 && r8 == 1) && g_protection_manager.m_crashes.m_parachute2) {
			if (auto ptr = *(u64*)(rcx + 16))
				if (auto ptr2 = *(u64*)(ptr + 80))
					if (auto ptr3 = *(u64*)(ptr2 + 64))
						RET_CALL_DECL(parachute_crash_2, rcx, rdx, r8);
			return 0;
		}
		RET_CALL_DECL(parachute_crash_2, rcx, rdx, r8);
	}

	void hooks::invalid_mods_crash(i64  rcx, i64  rdx, int r8, char r9) {
		if (!*(int64_t*)(rcx + 0xD8) && g_protection_manager.m_crashes.m_invalid_mods)
			return;

		RET_CALL_DECL(invalid_mods_crash, rcx, rdx, r8, 49);
	}
}