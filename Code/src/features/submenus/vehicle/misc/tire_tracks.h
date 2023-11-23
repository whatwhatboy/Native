#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"
#include <src/rage/vehicle/CVehicleModelInfo.hpp>

namespace Base {
	namespace tire_tracks {
		bool enabled{ false };
		bool nig{ false };
		float red = 255, green = 0, blue = 0;
		bool rainbow{ false };
		bool match_car{ false };
		bool always{ true };
		void persistent(bool reset = false) {
			vfx_wheel* vfx_wheel_fx{ g_pointers->m_vfx_wheel.first };
			vfx_wheel* vfx_wheel_cache{ m_wheel_cache };

			for (uint32_t i = 0; i < (uint32_t)(g_pointers->m_vfx_wheel.second * 4); i++) {
				if (!reset) {
					vfx_wheel_fx[i].m_type1 = 53;
					vfx_wheel_fx[i].m_type2 = 53;
					vfx_wheel_fx[i].m_type3 = 64;
					vfx_wheel_fx[i].m_type4 = 255;
					vfx_wheel_fx[i].m_unk1 = TRUE;
					vfx_wheel_fx[i].m_unk2 = TRUE;
					vfx_wheel_fx[i].m_unk3 = TRUE;
					vfx_wheel_fx[i].m_unk4 = TRUE;
					vfx_wheel_fx[i].m_pressure_min = always ? (-1.f) : 0.0f;
					vfx_wheel_fx[i].m_pressure_max = 0.0f;
				}
				else {
					vfx_wheel_fx[i].m_type1 = vfx_wheel_cache[i].m_type1;
					vfx_wheel_fx[i].m_type2 = vfx_wheel_cache[i].m_type2;
					vfx_wheel_fx[i].m_type3 = vfx_wheel_cache[i].m_type3;
					vfx_wheel_fx[i].m_type4 = vfx_wheel_cache[i].m_type4;
					vfx_wheel_fx[i].m_unk1 = vfx_wheel_cache[i].m_unk1;
					vfx_wheel_fx[i].m_unk2 = vfx_wheel_cache[i].m_unk2;
					vfx_wheel_fx[i].m_unk3 = vfx_wheel_cache[i].m_unk3;
					vfx_wheel_fx[i].m_unk4 = vfx_wheel_cache[i].m_unk4;
					vfx_wheel_fx[i].m_pressure_min = vfx_wheel_cache[i].m_pressure_min;
					vfx_wheel_fx[i].m_pressure_max = vfx_wheel_cache[i].m_pressure_max;
				}
			}
		}

		void set_color(bool reset, Color color) {
			vfx_wheel* vfx_wheel_fx{ g_pointers->m_vfx_wheel.first };
			vfx_wheel* vfx_wheel_cache{ m_wheel_cache };

			for (uint32_t i = 0; i < (uint32_t)(g_pointers->m_vfx_wheel.second * 4); i++) {
				if (!reset) {
					vfx_wheel_fx[i].m_r = color.r;
					vfx_wheel_fx[i].m_g = color.g;
					vfx_wheel_fx[i].m_b = color.b;
				}
				else {
					vfx_wheel_fx[i].m_r = vfx_wheel_cache[i].m_r;
					vfx_wheel_fx[i].m_g = vfx_wheel_cache[i].m_g;
					vfx_wheel_fx[i].m_b = vfx_wheel_cache[i].m_b;
				}
			}

		}
		void init() {
			if (!enabled) return;

			int custom_r{};
			int custom_g{};
			int custom_b{};
			if (rainbow) {
				if (match_car) return;
				red = g_rainbow.r;
				green = g_rainbow.g;
				blue = g_rainbow.b;
			}
			if (match_car) {
				VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(g_utils->vehicle(), &custom_r, &custom_g, &custom_b);
				red = custom_r;
				green = custom_g;
				blue = custom_b;
			}
			persistent();
			set_color(false, { (uint8_t)red, (uint8_t)green, (uint8_t)blue, 255 });
		}
		void on_disable() {
			set_color(true, {0, 0, 0, 0});
			persistent(true);
		}
	}
}
