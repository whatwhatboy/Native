#pragma once
#include "src/features/utils/utils.h"
#include "src/core/script/submenus/self/model_changer_table.h"

namespace Base {
	struct bodyguard {
		Ped m_ped{};
		str m_name{};
	};
	class bodyguard_manager {
	public:
		Player m_owner{};
		int m_selected_hash{};
		int m_weapon{};
		std::vector<bodyguard> m_spawned{};
	public:
		float m_accuracy{ 100 };
		bool m_godmode{ false };
	public:
		void spawn();
	};
}
