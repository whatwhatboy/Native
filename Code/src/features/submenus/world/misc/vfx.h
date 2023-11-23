#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base::world::vfx {
	namespace blood {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			for (int i = 0; i < 4; i++) {
				g_pointers->m_vfx_liquid[i].r = g_rainbow.r;
				g_pointers->m_vfx_liquid[i].g = g_rainbow.g;
				g_pointers->m_vfx_liquid[i].b = g_rainbow.b;
			}
		}
	}
	namespace chams {
		bool enabled{ false };
		bool rainbow{ false };
		float intensity{ 100 };
		void init() {
			if (!enabled) return;
			g_pointers->m_timecycle->set_var(TimeCycleVar_e::TCVAR_PED_LIGHT_COL_R, rainbow ? (g_rainbow.r / 255.f) : 1);
			g_pointers->m_timecycle->set_var(TimeCycleVar_e::TCVAR_PED_LIGHT_COL_G, rainbow ? (g_rainbow.g / 255.f) : 1);
			g_pointers->m_timecycle->set_var(TimeCycleVar_e::TCVAR_PED_LIGHT_COL_B, rainbow ? (g_rainbow.b / 255.f) : 1);
			g_pointers->m_timecycle->set_var(TimeCycleVar_e::TCVAR_PED_LIGHT_MULT, intensity);
		}
		void on_disable() {
			g_pointers->m_timecycle->set_var(TimeCycleVar_e::TCVAR_PED_LIGHT_MULT, 0);
		}
	}

	namespace remove_water {
		static std::vector<float> heights;
		bool enabled{};
		void tick() {
			if (!enabled) return;
			auto quads = g_pointers->m_water_quads;
			if (quads)
			{
				for (int i = 0; i < 821; i++) // 821 = Max Water Items
				{
					heights.push_back(quads[i].Z); // Save Water Heights
					quads[i].Z = -1000.0f;              // Remove Water
				}
			}
		}
		void on_disable() {
			auto quads = g_pointers->m_water_quads;
			if (quads)
			{
				for (int i = 0; i < 821; i++) // 821 = Max Water Items
				{
					quads[i].Z = heights.at(i); // Restore Water
				}
				heights.clear(); // Clear Storage Vector
			}
		}
	}
}
