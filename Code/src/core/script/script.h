#pragma once

namespace Base {
	class menu {
	public:
		void initialize();
		void destroy();
		static void tick();
		static void dx_tick();
	};
	inline std::shared_ptr<menu> g_menu{};
}