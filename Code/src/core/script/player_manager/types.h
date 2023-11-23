#pragma once

namespace Base {
	struct player_data {
		bool m_taze{};
		bool m_explode{};
		bool m_hostile_vehicles{};
		bool m_rain_rockets{};

		bool m_slipply_tires{};
		bool m_freeze_vehicle{};

		bool m_transaction_error{};

		bool m_spectate{};
	};
	struct player_context {
		Ped m_ped{};
		Vehicle m_vehicle{};
		Vector3 m_coords{};
		float m_heading{};
		Player m_id;
	};
}
