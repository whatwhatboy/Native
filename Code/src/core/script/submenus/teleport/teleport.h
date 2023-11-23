#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/submenu_types/regular_submenu.h"
#include "locations.h"

namespace Base::submenus::teleport::ipls {
	struct ipl {
		const char* name;
		Vector3 coords;
		std::vector<const char*> request;
		std::vector<const char*> remove{};
	};

	std::vector<ipl> list {
		{ 
			"North Yankton", {3360.19f, -4849.67f, 111.8f}, 
			{ "plg_01", "prologue01", "prologue01_lod", "prologue01c", "prologue01c_lod", "prologue01d", "prologue01d_lod", "prologue01e", "prologue01e_lod", "prologue01f", "prologue01f_lod", "prologue01g", "prologue01h", "prologue01h_lod", "prologue01i",
				"prologue01i_lod", "prologue01j", "prologue01j_lod", "prologue01k", "prologue01k_lod", "prologue01z", "prologue01z_lod", "plg_02", "prologue02", "prologue02_lod", "plg_03", "prologue03", "prologue03_lod", "prologue03b", "prologue03b_lod", "prologue03_grv_dug",
				"prologue03_grv_dug_lod", "prologue_grv_torch", "plg_04", "prologue04", "prologue04_lod", "prologue04b", "prologue04b_lod", "prologue04_cover", "des_protree_end", "des_protree_start", "des_protree_start_lod", "plg_05", "prologue05", "prologue05_lod", "prologue05b",
				"prologue05b_lod", "plg_06", "prologue06", "prologue06_lod", "prologue06b", "prologue06b_lod", "prologue06_int", "prologue06_int_lod", "prologue06_pannel", "prologue06_pannel_lod", "prologue_m2_door", "prologue_m2_door_lod", "plg_occl_00", "prologue_occl", "plg_rd",
				"prologuerd", "prologuerdb", "prologuerd_lod"
			} 
		},

		{"Lifeinvader", {-1047.9f, -233.0f, 39.0f}, { "facelobby" }},
		{ "Jewelery Store", {-630.4f, -236.7f, 40.0f}, { "post_hiest_unload" }, { "jewel2fake", "bh1_16_refurb"}}
	};
}
namespace Base::submenus::teleport {
	bool transition{ true };
	int get_ideal_switch(Vector3 from, Vector3 to) {	
		return STREAMING::GET_IDEAL_PLAYER_SWITCH_TYPE(from.x, from.y, from.z, to.x, to.y, to.z);
	}
	void teleport(Vector3 coords) {
		if (transition) {
			g_fiber_pool.queue([=] {
				Hash hash{ rage::joaat(NETWORK::NETWORK_IS_SESSION_STARTED() ? "mp_m_freemode_01" : "player_zero")};
				g_utils->request_model(hash, [=] {
					auto ped{ PED::CREATE_PED(13, hash, coords.x, coords.y, coords.z, 0.f, true, false) };
					if (ENTITY::DOES_ENTITY_EXIST(ped)) {
						STREAMING::START_PLAYER_SWITCH(g_utils->self(), ped, 0, get_ideal_switch(g_utils->coords(), coords));
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, true, true);
						ENTITY::DELETE_ENTITY(&ped);

						if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
							while (STREAMING::GET_PLAYER_SWITCH_STATE() != 8) {
								fiber::current()->wait(100ms);
								if (STREAMING::GET_PLAYER_SWITCH_STATE() == 12) break;
							}

							PED::SET_PED_COORDS_KEEP_VEHICLE(g_utils->self(), coords.x, coords.y, coords.z);
						}
					}
					});
				});
		}
		else
			PED::SET_PED_COORDS_KEEP_VEHICLE(g_utils->self(), coords.x, coords.y, coords.z);
	}
	void draw_teleport_sub(str name, std::vector<locations::location> arr) {
		draw->submenu(name, name, [=] {
			for (auto location : arr) {
				draw->button(location.m_name, [=] {
					teleport({ location.m_x, location.m_y, location.m_z });
				});
			}
		});
	}
	void main() {
		if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::teleport) return;

		draw->submenu("Core", "core_teleports", [] {
			draw->button("Waypoint", [] {
				auto c{ HUD::GET_BLIP_INFO_ID_COORD(HUD::GET_FIRST_BLIP_INFO_ID(8)) };
				teleport(c);
			});
		});
		draw->submenu("Settings", "teleport_settings", [] {
			draw->toggle("Transition", &transition);
		});
		draw->submenu("IPLS", "teleport_ipls", [] {
			for (auto location : ipls::list) {
				draw->button(location.name, [=] {
					for (auto request : location.remove)
						STREAMING::REMOVE_IPL(request);

					for (auto request : location.request)
						STREAMING::REQUEST_IPL(request);

					teleport(location.coords);
					});
			}
		});
		draw_teleport_sub("Landmarks", locations::landmarks);
		draw_teleport_sub("Airstrips", locations::airstrips);
		draw_teleport_sub("Clothing Stores", locations::clothing_stores);
		draw_teleport_sub("Tattoo Shops", locations::tatto_shops);
		draw_teleport_sub("Los Santos Customs", locations::los_santos_customs);
		draw_teleport_sub("Inside", locations::inside);
		draw_teleport_sub("Police Stations", locations::police_stations);
		draw_teleport_sub("Medical Centers", locations::hospitals);
		
	}
}
