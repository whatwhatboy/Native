#pragma once
#include "src/Features/utils/find_by_id.h"

namespace Base {
	inline auto operator""_TF(const char* id, size_t) {
		return g_feature_manager.get_command<toggle_option>(id);
	}
	inline auto operator""_TB(const char* id, size_t) {
		return g_feature_manager.get_command<button_option>(id);
	}
	inline auto operator""_TWF(const char* id, size_t) {
		return g_feature_manager.get_command<toggle_with_float_option>(id);
	}
	inline auto operator""_CF(const char* id, size_t) {
		return g_feature_manager.get_command<choose_option>(id);
	}
	inline auto operator""_KF(const char* id, size_t) {
		return g_feature_manager.get_command<keyboard_option>(id);
	}
}