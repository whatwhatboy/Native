#pragma once
#include <src/utility/types.h>
namespace Base::cutscene {
	class disable {
	public:
		void tick();
		bool m_enabled{};
	} inline g_disable;

	class buttons {
	public:
		void stop();
		void set_skippable();
	} inline g_buttons;

}

namespace Base::graphics {
	class reduce_ped_budget {
	public:
		void tick();
		void on_disable();
		bool m_enabled;
	} inline g_reduce_ped_budget;

	class reduce_vehicle_budget {
	public:
		void tick();
		void on_disable();
		bool m_enabled;
	} inline g_reduce_vehicle_budget;

	class render_hd_only {
	public:
		void tick();
		void on_disable();
		bool m_enabled{};
	} inline g_render_hd_only;

}

namespace Base::vibration {
	class disable {
	public:
		void tick();
		bool m_enabled{};
	} inline g_disable;

	class shake {
	public:
		struct settings {
			float m_intensity{ 100 };
			float m_delay{ 500 };
		} m_settings;
	public:
		void tick();
		bool m_enabled{};
	} inline g_shake;

}

namespace Base::camera {
	class gta_1 {
	private:
		Cam m_cam;
	public:
		struct settings {
			float m_distance{ 10 };
		} m_settings;
		bool m_enabled{ false };
		void tick();
		void on_disable();
	} inline g_gta_1;
}

namespace Base::misc::random {
	class instant_alt_f4 {
	public:
		void tick();
		bool m_enabled{};
	} inline g_instant_alt_f4;

}