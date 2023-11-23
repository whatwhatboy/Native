#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base::graphics {
	void reduce_ped_budget::tick() {
		if (!m_enabled) return;

		STREAMING::SET_REDUCE_PED_MODEL_BUDGET(true);
	}
	void reduce_ped_budget::on_disable() {
		STREAMING::SET_REDUCE_PED_MODEL_BUDGET(false);
	}

	void reduce_vehicle_budget::tick() {
		if (!m_enabled) return;

		STREAMING::SET_REDUCE_VEHICLE_MODEL_BUDGET(true);
	}
	void reduce_vehicle_budget::on_disable() {
		STREAMING::SET_REDUCE_VEHICLE_MODEL_BUDGET(false);
	}

	void render_hd_only::tick() {
		if (!m_enabled) return;

		STREAMING::SET_RENDER_HD_ONLY(true);
	}
	void render_hd_only::on_disable() {
		STREAMING::SET_RENDER_HD_ONLY(false);
	}
}
