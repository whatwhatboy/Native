#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/keyboard.h"
#include "src/framework/option_types/button.h"
#include "src/framework/option_types/toggle.h"
#include "src/framework/option_types/number.h"

namespace Base::submenus::vehicle::auto_pilot {
	class autopilot_c {
	public:
		std::string avoid_roads_name = "Slot 3";
		bool wreckless = true;
		bool avoid_roads = false;
		int avoid_roads_flag = 20972036;
		std::string avoid_roads_buffer;
		int wreckless_flag = 786972;
		std::string wreckless_buffer;
		int nonwreckless_flag = 387;
		std::string nonwreckless_flag_buffer;
		float speed = 100.f;
		float stop_range = 50.f;
		std::vector<const char*> destination = { "Waypoint", "Objective", "Wander" };
		int destination_i = 0;
	};
	inline autopilot_c autopilot;
	class flag_creator_c {
	public:
		std::vector<const char*> direction = { "Reckless", "Non-Reckless", autopilot.avoid_roads_name.c_str() };
		int data = 0;
		bool auto_save = false;
		bool stop_before_vehicles = false;
		bool stop_before_peds = false;
		bool avoid_vehicles = false;
		bool avoid_empty_vehicles = false;
		bool avoid_peds = false;
		bool avoid_objects = false;
		bool stop_at_traffic_lights = false;
		bool use_blinkers = false;
		bool allow_going_wrong_way = false;
		bool drive_in_reverse = false;
		bool take_shortest_path = false;
		bool wreckless = false;
		bool ignore_roads = false;
		bool ignore_all_pathing = false;
		bool avoid_highways = false;
		int current = 0;
		void init() {
			if (auto_save) {
				switch (data) {
				case 0:
					autopilot.wreckless_flag = current;
					break;
				case 1:
					autopilot.nonwreckless_flag = current;
					break;
				case 2:
					autopilot.avoid_roads_flag = current;
					break;
				}
			}
		}

	};
	inline flag_creator_c flag_creator;
	void main() {
		draw->submenu_second("Flag Creator", "vehicle/autopilot/flag creator", [] {
			draw->submenu_second("Flags", "vehicle/autopilot/flag creator/flags", [] {
				add_option<Framework::toggle>(("Stop Before Vehicles"), "", &flag_creator.stop_before_vehicles, [] {
					if (flag_creator.stop_before_vehicles) {
						flag_creator.current += 1;
					}
					if (!flag_creator.stop_before_vehicles) {
						flag_creator.current -= 1;
					}
					});
				add_option<Framework::toggle>(("Stop Before Peds"), "", &flag_creator.stop_before_peds, [] {
					if (flag_creator.stop_before_peds) {
						flag_creator.current += 2;
					}
					if (!flag_creator.stop_before_peds) {
						flag_creator.current -= 2;
					}
					});
				add_option<Framework::toggle>(("Avoid Vehicles"), "", &flag_creator.avoid_vehicles, [] {
					bool buffer = flag_creator.avoid_vehicles;
					if (buffer) {
						flag_creator.current += 4;
					}
					if (!buffer) {
						flag_creator.current -= 4;
					}
					});
				add_option<Framework::toggle>(("Avoid Empty Vehicles"), "", &flag_creator.avoid_empty_vehicles, [] {
					bool buffer = flag_creator.avoid_empty_vehicles;
					if (buffer) {
						flag_creator.current += 8;
					}
					if (!buffer) {
						flag_creator.current -= 8;
					}

					});
				add_option<Framework::toggle>(("Avoid Peds"), "", &flag_creator.avoid_peds, [] {
					bool buffer = flag_creator.avoid_peds;
					if (buffer) {
						flag_creator.current += 16;
					}
					if (!buffer) {
						flag_creator.current -= 16;
					}

					});
				add_option<Framework::toggle>(("Avoid Objects"), "", &flag_creator.avoid_objects, [] {
					bool buffer = flag_creator.avoid_objects;
					if (buffer) {
						flag_creator.current += 16 * 2;
					}
					if (!buffer) {
						flag_creator.current -= 16 * 2;
					}

					});
				add_option<Framework::toggle>(("Stop At Traffic Lights"), "", &flag_creator.stop_at_traffic_lights, [] {
					bool buffer = flag_creator.stop_at_traffic_lights;
					if (buffer) {
						flag_creator.current += 128;
					}
					if (!buffer) {
						flag_creator.current -= 128;
					}

					});
				add_option<Framework::toggle>(("Use Blinkers"), "", &flag_creator.use_blinkers, [] {
					bool buffer = flag_creator.use_blinkers;
					if (buffer) {
						flag_creator.current += 256;
					}
					if (!buffer) {
						flag_creator.current -= 256;
					}

					});
				add_option<Framework::toggle>(("Allow Going Wrong Way"), "", &flag_creator.allow_going_wrong_way, [] {
					bool buffer = flag_creator.allow_going_wrong_way;
					if (buffer) {
						flag_creator.current += 512;
					}
					if (!buffer) {
						flag_creator.current -= 512;
					}

					});
				add_option<Framework::toggle>(("Drive In Reverse"), "", &flag_creator.drive_in_reverse, [] {
					bool buffer = flag_creator.drive_in_reverse;
					if (buffer) {
						flag_creator.current += 1024;
					}
					if (!buffer) {
						flag_creator.current -= 1024;
					}

					});
				add_option<Framework::toggle>(("Take Shortest Path"), "", &flag_creator.take_shortest_path, [] {
					bool buffer = flag_creator.take_shortest_path;
					if (buffer) {
						flag_creator.current += 262144;
					}
					if (!buffer) {
						flag_creator.current -= 262144;
					}

					});
				add_option<Framework::toggle>(("Reckless"), "", &flag_creator.wreckless, [] {
					bool buffer = flag_creator.wreckless;
					if (buffer) {
						flag_creator.current += 524288;
					}
					if (!buffer) {
						flag_creator.current -= 524288;
					}

					});
				add_option<Framework::toggle>(("Ignore Roads"), "", &flag_creator.ignore_roads, [] {
					bool buffer = flag_creator.ignore_roads;
					if (buffer) {
						flag_creator.current += 4194304;
					}
					if (!buffer) {
						flag_creator.current -= 4194304;
					}

					});
				add_option<Framework::toggle>(("Ignore All Pathing"), "", &flag_creator.ignore_all_pathing, [] {
					bool buffer = flag_creator.ignore_all_pathing;
					if (buffer) {
						flag_creator.current += 16777216;
					}
					if (!buffer) {
						flag_creator.current -= 16777216;
					}

					});
				add_option<Framework::toggle>(("Avoid Highways"), "", &flag_creator.avoid_highways, [] {
					bool buffer = flag_creator.avoid_highways;
					if (buffer) {
						flag_creator.current += 536870912;
					}
					if (!buffer) {
						flag_creator.current -= 536870912;
					}

					});
				});
			add_option<Framework::toggle>(("Automaticly Save"), "", &flag_creator.auto_save);
			add_option<Framework::choose>("Save", flag_creator.direction, &flag_creator.data, false, [] {
					switch (flag_creator.data) {
						case 0:
							autopilot.wreckless_flag = flag_creator.current;
							break;
						case 1:
							autopilot.nonwreckless_flag = flag_creator.current;
							break;
						case 2:
							autopilot.avoid_roads_flag = flag_creator.current;
							break;
						}
				});
			draw->seperator(("Current"));
			char current[64];
			sprintf(current, "%i", flag_creator.current);
			add_option<Framework::button>((current), "");
			draw->seperator(("Names"));
			add_option<Framework::keyboard>(("Slot 3"), "", &autopilot.avoid_roads_name);
		});
		add_option<Framework::toggle>(("Reckless"), "", &autopilot.wreckless);
		if (autopilot.wreckless)
			add_option<Framework::toggle>((autopilot.avoid_roads_name.c_str()), "", &autopilot.avoid_roads);
		add_option<Framework::choose>("Destination", "", autopilot.destination, &autopilot.destination_i);
		add_option<Framework::number<float>>("Speed", "", &autopilot.speed, 1.0f, 200.f, 1.0f, 0, true, "", "mph");
		add_option<Framework::number<float>>("Stop Range", "", &autopilot.stop_range, 0.f, 1000.f, 0.50f, 1);
		add_option<Framework::button>(("Start"), "", [] {
			g_fiber_pool.queue([] {
				int waypoint_handle{ HUD::GET_FIRST_BLIP_INFO_ID(8) };
				if (!HUD::DOES_BLIP_EXIST(waypoint_handle) && autopilot.destination_i == 0)
					return;
				Vector3 destination{ HUD::GET_BLIP_INFO_ID_COORD(HUD::GET_FIRST_BLIP_INFO_ID(8)) };
				auto veh{ g_utils->vehicle() };
				if (autopilot.destination_i == 0) {
					PED::SET_DRIVER_ABILITY(g_utils->self(), 100.f);
					TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(g_utils->self(), veh, destination.x, destination.y, destination.z, autopilot.speed * 2.236936, autopilot.wreckless ? autopilot.wreckless_flag : autopilot.nonwreckless_flag, autopilot.stop_range);
				}
				if (autopilot.destination_i == 1) {
					Vector3 location;
					g_utils->get_objective_location(location);
					if (autopilot.wreckless) {
						PED::SET_DRIVER_ABILITY(g_utils->self(), 100.f);
						TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(g_utils->self(), veh, location.x, location.y, location.z, autopilot.speed * 2.236936, autopilot.avoid_roads ? autopilot.avoid_roads_flag : autopilot.wreckless_flag, autopilot.stop_range);
					}
					else
						TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(g_utils->self(), veh, location.x, location.y, location.z, autopilot.speed * 2.236936, autopilot.nonwreckless_flag, autopilot.stop_range);
				}
				if (autopilot.destination_i == 2) {
					if (autopilot.wreckless) {
						PED::SET_DRIVER_ABILITY(g_utils->self(), 100.f);
						TASK::TASK_VEHICLE_DRIVE_WANDER(g_utils->self(), veh, autopilot.speed * 2.236936, autopilot.avoid_roads ? autopilot.avoid_roads_flag : autopilot.wreckless_flag);

					}
					else
						TASK::TASK_VEHICLE_DRIVE_WANDER(g_utils->self(), veh, autopilot.speed * 2.236936, autopilot.nonwreckless_flag);
				}
				});
			});
		add_option<Framework::button>(("Stop"), "", [] {
			auto oldveh{ g_utils->vehicle() };
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(g_utils->self());
			PED::SET_PED_INTO_VEHICLE(g_utils->self(), oldveh, -1);

		});
	}
}
