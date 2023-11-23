#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "src/framework/option_types/number.h"
#include "src/framework/option_types/toggle.h"
namespace Base::submenus::world {
	enum eOceanTasks {
		OCEAN_DISABLE,
		OCEAN_CLEAR,
		OCEAN_FIERCE
	};

	enum eOceanTypes {
		OCEAN_TYPE_OCEAN,
		OCEAN_TYPE_WAVE,
		OCEAN_TYPE_CALMING
	};
	bool disable_ocean{};
	bool fierce_ocean{};
	bool clear_ocean{};
	void ocean_loop(eOceanTypes type, std::function<void(uint64_t)> callback) {
		uint64_t quad_pool = 0;
		short quad_count = 0;

		switch (type) {
		case OCEAN_TYPE_OCEAN:
			quad_pool = g_pointers->m_ocean_quads.m_ocean->m_quad_pool;
			quad_count = g_pointers->m_ocean_quads.m_ocean->m_quad_count;
			break;

		case OCEAN_TYPE_WAVE:
			quad_pool = g_pointers->m_ocean_quads.m_wave->m_quad_pool;
			quad_count = g_pointers->m_ocean_quads.m_wave->m_quad_count;
			break;

		case OCEAN_TYPE_CALMING:
			quad_pool = g_pointers->m_ocean_quads.m_calming->m_quad_pool;
			quad_count = g_pointers->m_ocean_quads.m_calming->m_quad_count;
			break;
		}

		for (short i = 0; i < quad_count; i++) {
			switch (type) {
			case OCEAN_TYPE_OCEAN:
				callback((quad_pool + (i * sizeof(ocean_quad))));
				break;

			case OCEAN_TYPE_WAVE:
				callback((quad_pool + (i * sizeof(ocean_wave_quad))));
				break;

			case OCEAN_TYPE_CALMING:
				callback((quad_pool + (i * sizeof(ocean_calming_quad))));
				break;
			}
		}
	}

	void ocean_task(eOceanTypes type, eOceanTasks task) {
		ocean_loop(type, [=](uint64_t pool) {
			switch (task) {
			case OCEAN_DISABLE: {
				ocean_quad* quad = (ocean_quad*)(pool);

				if (disable_ocean && quad->m_height == 0.0f) {
					quad->m_height = -10000.0f;
				}
				else if (!disable_ocean && quad->m_height == -10000.0f) {
					quad->m_height = 0.0f;
				}

				break;
			}

			case OCEAN_CLEAR: {
				ocean_quad* quad = (ocean_quad*)(pool);
				quad->m_alpha = clear_ocean ? 0x01010101 : 0x1A1A1A1A;
				break;
			}

			case OCEAN_FIERCE: {
				ocean_wave_quad* quad = (ocean_wave_quad*)(pool);
				quad->m_amplitude = fierce_ocean ? quad->m_amplitude + 2000 : quad->m_amplitude - 2000;
				break;
			}
			}
			});
	}

	void ocean() {
		//outdated
		draw->option("drain_ocean");
		return;
		add_option<Framework::toggle>("Disable", "", &disable_ocean, [] {
			g_fiber_pool.queue([] {
				ocean_task(OCEAN_TYPE_OCEAN, OCEAN_DISABLE);
			});
			
		});
	}
}
