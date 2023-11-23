#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "classes.h"

namespace Base {
	void tron_loop::init() {
		if (!m_enabled) return;
		g_utils->timed_function(1000, [=] {
			if (m_selected > 6)
				m_selected = 0;

			if (g_utils->get_hash(g_utils->self()) == rage::joaat("mp_m_freemode_01"))
				set_tron_index(m_selected, 0);

			if (g_utils->get_hash(g_utils->self()) == rage::joaat("mp_f_freemode_01")) {
				m_selected += 1;
				set_tron_index(m_selected, 1);
			}

			m_selected++;
		});
	}
}
