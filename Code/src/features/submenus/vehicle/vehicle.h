#pragma once 
#include "src/Utility/Common/Common.h"
#include "src/Natives/Natives.h"
#include "src/Memory/Pointers/Pointers.h"

namespace Base {
	inline std::vector<std::string> vehicle_classes = {

	};
	struct veh {
		Hash hash;
		ccp name;
		ccp m_class;
	};
	inline std::vector<veh> vehicle_hash_list = {

	};
	class vehicle_options {
	public:
		void add();
	};
	inline vehicle_options g_vehicle_options;

	inline vfx_wheel* m_wheel_cache;
}