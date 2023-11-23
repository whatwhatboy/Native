#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "src/framework/option_types/number.h"

namespace Base::submenus::world {
	namespace dispatch_toggles {
		bool m_police_automobile;
		bool m_police_helicopter;
		bool m_police_riders;
		bool m_police_vehicle_request;
		bool m_police_roadblock;
		bool m_police_boat;
		bool m_swat_automobile;
		bool m_swat_helicopter;
		bool m_fire_department;
		bool m_ambulance_department;
		bool m_gangs;
		bool m_army_vehicle;
		bool m_bikers;
		bool m_assassin;
		bool m_wait_pulled_over;
		bool m_wait_cruising;
	}
	bool is_toggled(eDispatchType service) {
		if (g_pointers->m_dispatch_table) {
			auto table{ *(uint64_t*)(g_pointers->m_dispatch_table + (service * 8)) };
			if (table) {
				return *(bool*)(table + 0x20);
			}
		}

		return false;
	}

	void set_toggle(eDispatchType service, bool toggle) {
		if (g_pointers->m_dispatch_table) {
			auto table{ *(uint64_t*)(g_pointers->m_dispatch_table + (service * 8)) };
			if (table) {
				*(bool*)(table + 0x20) = toggle;
			}
		}
	}
	using namespace Framework;
	void dispatch_init() {
		draw->toggle("Police Automobile", &dispatch_toggles::m_police_automobile, [] { set_toggle(PoliceAutomobile, dispatch_toggles::m_police_automobile); });
		draw->toggle("Police Helicopter", &dispatch_toggles::m_police_helicopter, [] { set_toggle(PoliceHelicopter, dispatch_toggles::m_police_helicopter); });
		draw->toggle("Fire Department", &dispatch_toggles::m_fire_department, [] { set_toggle(FireDepartment, dispatch_toggles::m_fire_department); });
		draw->toggle("Swat Automobile", &dispatch_toggles::m_swat_automobile, [] { set_toggle(SwatAutomobile, dispatch_toggles::m_swat_automobile); });
		draw->toggle("Ambulance Department", &dispatch_toggles::m_ambulance_department, [] { set_toggle(AmbulanceDepartment, dispatch_toggles::m_ambulance_department); });
		draw->toggle("Police Riders", &dispatch_toggles::m_police_riders, [] { set_toggle(PoliceRiders, dispatch_toggles::m_police_riders); });
		draw->toggle("Police Vehicle Request", &dispatch_toggles::m_police_vehicle_request, [] { set_toggle(PoliceVehicleRequest, dispatch_toggles::m_police_vehicle_request); });
		draw->toggle("Police Road Block", &dispatch_toggles::m_police_roadblock, [] { set_toggle(PoliceRoadBlock, dispatch_toggles::m_police_roadblock); });
		draw->toggle("Police Wait Pulled Over", &dispatch_toggles::m_wait_pulled_over, [] { set_toggle(PoliceAutomobileWaitPulledOver, dispatch_toggles::m_wait_pulled_over); });
		draw->toggle("Police Wait Cruising", &dispatch_toggles::m_wait_cruising, [] { set_toggle(PoliceAutomobileWaitCruising, dispatch_toggles::m_wait_cruising); });
		draw->toggle("Gangs", &dispatch_toggles::m_gangs, [] { set_toggle(Gangs, dispatch_toggles::m_gangs); });
		draw->toggle("Swat Helicopter", &dispatch_toggles::m_swat_helicopter, [] { set_toggle(SwatHelicopter, dispatch_toggles::m_swat_helicopter); });
		draw->toggle("Police Boat", &dispatch_toggles::m_police_boat, [] { set_toggle(PoliceBoat, dispatch_toggles::m_police_boat); });
		draw->toggle("Army Vehicle", &dispatch_toggles::m_army_vehicle, [] { set_toggle(ArmyVehicle, dispatch_toggles::m_army_vehicle); });
		draw->toggle("Biker Backup", &dispatch_toggles::m_bikers, [] { set_toggle(BikerBackup, dispatch_toggles::m_bikers); });
		draw->toggle("Assassin", &dispatch_toggles::m_assassin, [] { set_toggle(Assassin, dispatch_toggles::m_assassin); });
	}

	void dispatch_on_click() {
		dispatch_toggles::m_police_automobile = is_toggled(PoliceAutomobile);
		dispatch_toggles::m_police_helicopter = is_toggled(PoliceHelicopter);
		dispatch_toggles::m_police_riders = is_toggled(PoliceRiders);
		dispatch_toggles::m_police_vehicle_request = is_toggled(PoliceVehicleRequest);
		dispatch_toggles::m_police_roadblock = is_toggled(PoliceRoadBlock);
		dispatch_toggles::m_police_boat = is_toggled(PoliceBoat);
		dispatch_toggles::m_swat_automobile = is_toggled(SwatAutomobile);
		dispatch_toggles::m_swat_helicopter = is_toggled(SwatHelicopter);
		dispatch_toggles::m_fire_department = is_toggled(FireDepartment);
		dispatch_toggles::m_ambulance_department = is_toggled(AmbulanceDepartment);
		dispatch_toggles::m_gangs = is_toggled(Gangs);
		dispatch_toggles::m_army_vehicle = is_toggled(ArmyVehicle);
		dispatch_toggles::m_bikers = is_toggled(BikerBackup);
		dispatch_toggles::m_assassin = is_toggled(Assassin);
		dispatch_toggles::m_wait_cruising = is_toggled(PoliceAutomobileWaitCruising);
		dispatch_toggles::m_wait_pulled_over = is_toggled(PoliceAutomobileWaitPulledOver);
	}
}
