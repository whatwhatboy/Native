#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::weapon {
	void gun_locker() {
		draw->option("give_all_weapons");
		draw->option("give_all_attachments");
	}
}