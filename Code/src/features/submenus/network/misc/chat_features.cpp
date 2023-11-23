#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/rage/script/globals/GlobalPlayerBD.hpp"

#include "classes.h"

namespace Base {
	void spammer::tick() {
		if (!m_enabled) return;

		g_utils->timed_function(m_settings.m_delay, [=] {
			g_utils->send_chat_msg(g_hooking_features.m_chat.m_spammer_message, m_settings.m_visible_locally);
		});
	}
}
