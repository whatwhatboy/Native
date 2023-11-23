#pragma once
namespace Base::movement {
	class freeze {
	public:
		bool m_enabled{ false };
		void init();
		void on_disable();
	} inline g_freeze;

}
