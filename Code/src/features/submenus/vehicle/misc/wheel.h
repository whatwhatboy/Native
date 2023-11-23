#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base::wheel {
	enum offsets {
		x_offset = 0x030,
		y_rotation = 0x008,
		radius = 0x110,
	};
	template<typename T>
	static T read_value(rage::fwEntity* ptr, int offset) {
		return (T) * (T*)((char*)ptr + offset);
	}
	float offset{};
	bool enabled{ false };
	void init() {
		if (!g_utils->cvehicle() || !enabled) return;

		if (VEHICLE::IS_THIS_MODEL_A_BOAT(ENTITY::GET_ENTITY_MODEL(g_utils->vehicle()))) return;

		for (int i = 0; i < 4; i++) {
			auto wheel_offset{ read_value<uint64_t>((rage::fwEntity*)g_utils->cvehicle(), g_pointers->m_wheel_offset) };
			auto address{ *reinterpret_cast<uint64_t*>(wheel_offset + 0x008 * i) };

			if (i == 1 || i == 3)
				*reinterpret_cast<float*>(address + offsets::x_offset) = offset;
			else
				*reinterpret_cast<float*>(address + offsets::x_offset) = -offset;
		}
	}
}
