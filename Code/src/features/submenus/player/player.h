#pragma once 
#include "src/utility/common/common.h"
#include "src/Natives/Natives.h"
#include "src/Memory/Pointers/Pointers.h"

namespace Base {
	class player_options {
	public:
		void add();
	public:
		bool never_wanted_t{};
	public:
		void add_feature_subs();
		std::vector<std::pair<std::string, std::function<void()>>> m_feature_subs;
	};
	inline player_options g_player_options;
}