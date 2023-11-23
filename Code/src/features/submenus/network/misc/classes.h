#pragma once

namespace Base {
	class spammer {
	public:
		struct settings {
			float m_delay{ 500 };
			bool m_visible_locally{ true };
		} m_settings;
	public:
		bool m_enabled{ false };
		void tick();
	} inline g_spammer;

	class spoofingt {
	public:
		void tick();
	} inline g_spoofing_tick;

	class streamer_mode {
	public:
		void tick();
	} inline g_streamer_mode;

	class modder_detection {
	public:
		struct detections {
			bool m_model{ true };
			bool m_speed{ true };
		} m_detections;
	public:
		void tick();
		bool m_enabled{ false };
		std::vector<std::string> m_modders;
	} inline g_modder_detection;
}