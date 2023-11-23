#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/features/utils/rid_utils.h"
#include "src/framework/option_types/keyboard.h"
#include "src/framework/option_types/button.h"

namespace Base::submenus::network::rid_toolkit {
	std::string get_rid_from_user;
	uint64_t rid;
	void main() {
		add_option(Framework::keyboard("Username", "", &get_rid_from_user));
		add_option(Framework::button("Check")
			.set_action([=] {
				g_fiber_pool.queue([=] {
					//rid_utils::get_rid_from_username(get_rid_from_user, rid);
				});
			}));
	}
}
