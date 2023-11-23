#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base::config_flags {
	class disable_arrests {
	public:
		bool m_enabled{ false };
		void init();
		void on_disable();
	} inline g_disable_arrests;

	class swimming {
	public:
		bool m_enabled{ false };
		void init();
		void on_disable();
	} inline g_swimming;

	class is_climbing_ladder {
	public:
		bool m_enabled{ false };
		void init();
		void on_disable();
	} inline g_is_climbing_ladder;

	class dont_take_off_helmet {
	public:
		bool m_enabled{ false };
		void init();
		void on_disable();
	} inline g_dont_take_off_helmet;

	class disable_wanted_level_sharing {
	public:
		bool m_enabled{ false };
		void init();
		void on_disable();
	} inline g_disable_wanted_level_sharing;

	class electrocution_ragdoll {
	public:
		bool m_enabled{ false };
		void init();
		void on_disable();
	} inline g_electrocution_ragdoll;

	class always_aiming {
	public:
		bool m_enabled{ false };
		void init();
		void on_disable();
	} inline g_always_aiming;
}
