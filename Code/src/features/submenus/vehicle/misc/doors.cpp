#include "../../../utils/utils.h"
#include "classes.h"

namespace Base::doors {
	std::vector<int> get_doors() {
		std::vector<int> doors;
		for (int i{ 0 }; i < VEHICLE::GET_NUMBER_OF_VEHICLE_DOORS(g_utils->vehicle()); i++) {
			doors.push_back(i);
		}
		return doors;
	}

	void door_mgr::open_all() {
		for (auto door : get_doors()) {
			VEHICLE::SET_VEHICLE_DOOR_OPEN(g_utils->vehicle(), door, false, false);
		}
	}
	void door_mgr::close_all() {
		for (auto door : get_doors()) {
			VEHICLE::SET_VEHICLE_DOOR_SHUT(g_utils->vehicle(), door, false);
		}
	}
}