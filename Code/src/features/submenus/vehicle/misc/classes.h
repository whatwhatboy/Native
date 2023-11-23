#pragma once
#include "src/utility/common/common.h"

namespace Base::doors {
	class door_mgr {
	public:
		void open_all();
		void close_all();
	} inline g_door_mgr;
}
