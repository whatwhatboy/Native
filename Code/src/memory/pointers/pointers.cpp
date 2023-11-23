#include "pointers.h"
#include "src/natives/invoker/invoker.h"
#include "src/Memory/Memory.h"
#include "src/memory/hex_memory.h"
#include "src/hooking/hooking.h"
#include "scanning.h"
#include "src/hooking/xor.h"
#include "src/memory/patching/byte.h"
uintptr_t base{ (uintptr_t)GetModuleHandle(NULL) };
#define SCAN(p, n, ...) p = scan(n)__VA_ARGS__.as<decltype(p)>()
#define SCAN_FROM_ADDRESS(p, a, ...) 	p = *(decltype(p)*)(get_address(GETSTRING(a)) __VA_ARGS__)
#define SCAN_FROM_ADDRESS2(p, a, ...) 	p = *(decltype(p)*)(get_address(a) __VA_ARGS__)
#define MATCH(a, b) a = b;
namespace Base {
	u64 get_address(str ptr) {
		return (u64)Memory::pattern(ptr).get(0).get<char>(0);
	}
	str get_milisecond_results(int mil) {
		if (mil < 1000) return "Really good!";
		else if (mil > 1000 && mil < 1500) return "Good";
		else if (mil > 1500 && mil < 2500) return "Average";
		else if (mil > 2500 && mil < 4000) return "Decent";
		else if (mil > 4000) return "Bad";
	}
	void patch_address(u8* address) {
		byte_patch::make(address, std::to_array({ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }))->apply();
	}
	pointers::pointers() {
#ifndef DEV
		VIRTUALIZER_TIGER_WHITE_START
#endif
		LOG(Info, "Starting...");
		set_base();
		auto start_time{ std::chrono::high_resolution_clock::now() };
		SCAN(m_script_native_registration_table, "SNRT", .add(0xC).mov());
		SCAN(m_swapchain, "SWC", .mov());
		SCAN(m_game_state, "GS", .lea());
		SCAN(m_has_game_been_altered, "HGBA");
		SCAN(m_texture_store, "TS", .mov());
		SCAN(m_script_program_table, "SPT", .mov());
		SCAN(m_native_return_address, "NRA");
		SCAN(m_global_base, "GB", .sub(12).rip());
		SCAN(m_network_player_mgr, "NPM", .mov());
		SCAN(m_get_player_name, "GPN", .add(28));
		SCAN(m_pointer_to_handle, "PTH", .sub(0x15));
		SCAN(m_ped_factory, "PF", .mov());
		SCAN(m_fall_task_constructor, "FTC", .call());
		SCAN(m_task_jump_constructor, "TJC");
		SCAN(m_vehicle_pool, "VP", .mov());
		SCAN(m_ped_pool, "PP", .mov());
		SCAN(m_object_pool, "OP", .mov());
		SCAN(m_pickup_pool, "PUP", .mov());
		SCAN(m_interior_proxy_pool, "IPP", .mov());
		SCAN(m_hash_pool, "HP", .mov());
		SCAN(m_model_spawn_bypass, "MSB", .add(8));
		SCAN(m_get_net_player, "GNP");
		SCAN(m_fix_vectors, "FV");
		SCAN(m_is_session_started, "ISS");
		SCAN(m_render_entity, "MRE");
		SCAN(m_render_ped, "RP1");
		SCAN(m_draw_handler_mgr, "DHM", .mov());
		SCAN(m_write_join_response_data, "WJRD", .call());
		SCAN(m_handle_join_request, "HJR");
		SCAN(m_send_http_request, "SHR");
		SCAN(m_script_threads, "ST", .add(5).mov());
		SCAN(m_region_code, "RC", .add(16).rip().add(1));
		SCAN(m_handle_network_event, "HNE");
		SCAN(m_send_event_ack, "SEA", .call());
		SCAN(m_init_native_tables, "INT", .sub(37));
		SCAN(m_friend_registry, "FR", .sub(0xB).lea());
		SCAN(m_sync_money_rewards, "SMR", .mov());
		SCAN(m_weapon_group_info, "WGI", .sub(23));
		SCAN(m_timecycle_override, "TO");
		SCAN(m_process_game_event, "PGE");
		SCAN(m_new_index, "NI");
		SCAN(m_chat_data, "CD", .mov());
		SCAN(m_start_get_session_by_gamer_handle, "SGSBGH", .call());
		SCAN(m_join_session_by_info, "JBSI", .call());
		SCAN(m_network, "N", .mov());
		SCAN(m_get_entity_address, "GEA", .call());
		SCAN(m_set_vehicle_gravity, "SVG");
		SCAN(m_waypoint_data, "WD", .mov());
		SCAN(m_explosion_data, "ED", .mov());
		SCAN(m_explosion_fx, "ED", .mov().add(0x10));
		SCAN(m_ui_visual_settings, "IVS", .mov());
		SCAN(m_get_model_info, "GMI", .call());
		SCAN(m_network_base_config, "GNB", .mov());
		SCAN(m_vfx_liquid, "VL", .mov());
		SCAN(m_invite_player, "IP", .mov());
		SCAN(m_ui_weather, "UW", .mov().add(0x60));
		SCAN(m_receive_net_message, "RNM", .sub(0x19));
		SCAN(m_read_bitbuf_dword, "RBWD", .sub(5));
		SCAN(m_read_bitbuf_array, "RBA");
		SCAN(m_read_bitbuf_string, "RBS");
		SCAN(m_read_bitbuf_bool, "RBB", .call());
		SCAN(m_write_bitbuf_dword, "WBD");
		SCAN(m_write_bitbuf_qword, "WBQ");
		SCAN(m_write_bitbuf_int64, "WBI64", .call());
		SCAN(m_write_bitbuf_int32, "WBI32", .call());
		SCAN(m_write_bitbuf_bool, "WBB", .call());
		SCAN(m_write_bitbuf_array, "WBA", .call());
		SCAN(m_get_connection_peer, "GCP");
		SCAN(m_queue_packet, "QP", .call());
		SCAN(m_send_packet, "SP");
		SCAN(m_send_chat_message, "SCM", .sub(21));
		SCAN(m_send_chat_ptr, "SCP", .add(7).rip());
		SCAN(m_chat_profanity, "CP", .call());
		SCAN(m_game_visuals, "GV", .mov());
		SCAN(m_send_metric, "SM", .call());
		SCAN(m_get_event_data, "GED", .sub(28));
		SCAN(m_parachute_crash, "PC");
		SCAN(m_receive_pickup, "RP");
		SCAN(m_get_screen_coords_for_world_coords, "GSCFWC", .call());
		SCAN(m_owned_explosion, "CBO");
		SCAN(m_trigger_script_event, "TSE", .sub(28));
		SCAN(m_handle_to_ptr, "HTP");
		SCAN(m_write_player_game_state_data_node, "WPGSDN");
		SCAN(m_send_player_card_stats, "SPCS");
		SCAN(m_serialize_stats, "SS");
		SCAN(m_write_player_creation_data_node, "WPCDN");
		SCAN(m_write_player_appearance_data_node, "WPADN");
		SCAN(m_send_session_matchmaking_attributes, "SSMA");
		SCAN(m_write_player_gamer_data_node, "WPGDN");
		SCAN(m_reset_network_complaints, "RNC", .call());
		SCAN(m_report_dependency, "RD", .mov());
		SCAN(m_queue_dependency, "QD");
		SCAN(m_get_session_by_gamer_handle, "GSBGH", .call());
		SCAN(m_send_invite_accepted_presence_event, "SIAPE");
		SCAN(m_presence_struct, "PS", .sub(5).call());
		SCAN(m_get_net_object, "GNO", .add(0x109).call());
		SCAN(m_model_table, "MT", .mov());
		SCAN(m_train_config_array, "TCA", .mov());
		SCAN(m_water_quads, "WQ", .add(6).rip());
		SCAN(m_can_apply_data, "CAD", .call());
		SCAN(m_add_item_to_basket, "AITB");
		SCAN(m_receive_clone_create, "RCC");
		SCAN(m_receive_clone_remove, "RCR");
		SCAN(m_receive_clone_create_ack, "RCCA");
		SCAN(m_receive_clone_sync, "RCS");
		SCAN(m_receive_clone_sync_ack, "RCSA");
		SCAN(m_get_sync_tree_for_type, "GSTFT", .add(0x2F).call());
		SCAN(m_network_object_mgr, "NOM", .mov());
		SCAN(m_change_network_object_owner, "CNOO");
		SCAN(m_get_entity_from_script, "GEFS", .call());
		SCAN(m_parachute_crash2, "PC2", .sub(6));
		SCAN(m_invalid_mods_crash, "IMC", .call());
		SCAN(m_world, "W", .mov());
		SCAN(m_vfx_wheel.first, "VW", .mov());
		SCAN(m_weapon_components.m_count, "WC", .lea());
		SCAN(m_weapon_components.m_list, "WC", .mov().add(0x14));
		SCAN(m_ocean_quads.m_ocean, "OQ", .mov());
		SCAN(m_ocean_quads.m_calming, "OQ", .mov().add(0xC));
		SCAN(m_ocean_quads.m_wave, "OQ", .mov().add(0x25));
		SCAN(m_set_game_pitch, "SGP", .call());

		SCAN_FROM_ADDRESS(m_vfx_wheel.second, "VW", +0xA);
		SCAN_FROM_ADDRESS(m_wheel_offset, "WO", +15);
		SCAN_FROM_ADDRESS2(m_break_off_wheels, "F3 44 0F 11 4C 24 ? E8 ? ? ? ? EB 7A", +7);
		SCAN_FROM_ADDRESS2(m_damage_struct, "F3 44 0F 11 4C 24 ? E8 ? ? ? ? EB 7A", -11);
		MATCH(m_game_window, FindWindowA("grcWindow", nullptr));
		MATCH(m_convert_thread_to_fiber, GetProcAddress(g_Kernel32, "ConvertThreadToFiber"));

		for (auto& handle : get_all_results(GETSTRING("INTEG"))) {
			patch_address(handle.add(8).as<u8*>());
		}

		//unused
		/*m_ui_3d_draw_manager = scan("UI3DM", "4C 8B 15 ? ? ? ? F3 0F 11 45 ? F3 0F 10 05 ? ? ? ? BF ? ? ? ? BB ? ? ? ? 41 BE ? ? ? ? F3 0F 11").mov().as<decltype(m_ui_3d_draw_manager)>();
		m_push_scene_preset_manager = scan("PSPM", "40 53 48 83 EC 20 8B 02 48 8D 54 24 38 48 8B D9 89 44 24 38 E8 ? ? ? ? 48 8B C8").as<decltype(m_push_scene_preset_manager)>();
		m_add_element_to_scene = scan("AETS", "4C 8B DC 48 83 EC 58 8B").as<decltype(m_add_element_to_scene)>();
		m_set_scene_element_lighting = scan("SSEL", "48 8B C4 48 89 58 10 48 89 70 18 57 48 83 EC 30 48 83 B9").as<decltype(m_set_scene_element_lighting)>();
		m_get_scene_preset = scan("GSP", "0F B7 81 10 08 00 00").as<decltype(m_get_scene_preset)>();*/

		//outdated
		//m_drop_shaders, "DS", "4C 8D 35 B6 6F 8E 01 0F 2F C6 0F 97 C0").mov().as<decltype(m_drop_shader_count)>();
		//m_drop_shader_count, "DSC", "4C 8D 35 B6 6F 8E 01 0F 2F C6 0F 97 C0").add(0x15).lea().as<decltype(m_drop_shader_count)>();
		//m_dispatch_table, "DT", "48 8D 3D FC 95 F6 01 80 3B 00 76").mov().as<decltype(m_dispatch_table)>();
		//SCAN_FROM_ADDRESS(m_timecycle, 0x284FD80);
		m_timecycle = (timecycle*)read_instruction(get_address("bleeding through the afterlifeeeeee"), 8, 12);

		auto end_time{ std::chrono::high_resolution_clock::now() }; 
		auto elapsed_time{ std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() };
		LOG(Success, "Scanning done! | Time taken: {}ms ({}), Found {}/{}", elapsed_time, get_milisecond_results(elapsed_time), g_found_sig_count, g_total_sig_count);
#ifndef DEV
		VIRTUALIZER_TIGER_WHITE_END
#endif
	}	
}