#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"

namespace Base::ped_matrix {
	namespace width {
		bool enabled{ false };
		float value{ 1 };
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_transformation_matrix.data[0][1] * value;
		}
	}
	namespace height {
		bool enabled{ false };
		float value{ 1 };
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_transformation_matrix.data[2][2] * value;
		}
	}
	namespace lean {
		bool enabled{ false };
		float value{ 1 };
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_transformation_matrix.data[1][1] * value;
		}
	}
}
