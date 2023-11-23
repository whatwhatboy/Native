#pragma once
#include <src/rage/script/scrProgramTable.hpp>
#include <src/rage/script/scrNativeRegistration.hpp>
#include <src/rage/script/scrNativeRegistrationTable.hpp>
#include <src/rage/rage/atArray.hpp>
#include <src/rage/network/CNetGamePlayer.hpp>
#include <src/rage/network/CNetworkPlayerMgr.hpp>
#include <src/rage/draw_handlers/grcTextureStore.hpp>
#include <src/rage/ped/CPedFactory.hpp>
#include <src/rage/script/GtaThread.hpp>
#include "pools.h"
#include <src/rage/network/CMsgJoinResponse.hpp>
#include <src/rage/socialclub/FriendRegistry.hpp>
#include <src/rage/network/ChatData.hpp>
#include <src/rage/camera/CGameCameraAngles.hpp>
#include <src/rage/socialclub/ScInfo.hpp>
#include <src/rage/rage/rlSessionByGamerTaskResult.hpp>
#include <src/rage/rage/rlTaskStatus.hpp>
#include "src/rage/network/Network.hpp"
#include <src/hooking/classes/extra.h>
#include "src/rage/network/netPeerAddress.hpp"
#include "src/rage/network/netConnection.hpp"
#include "src/rage/vehicle/CVehicleModelInfo.hpp"
#include "src/rage/netsync/nodes/player/CPlayerGameStateDataNode.hpp"
#include "src/rage/base/HashTable.hpp"
#include "src/rage/vehicle/CTrainConfig.hpp"
namespace Base {
    namespace func_types {
        using start_get_session_by_gamer_handle = bool (*)(int profile_index, rage::rlGamerHandle* handles, int count, rage::rlSessionByGamerTaskResult* result, int unk, bool* success, rage::rlTaskStatus* state);
        using join_session_by_info = bool (*)(Network* network, rage::rlSessionInfo* info, int unk, int flags, rage::rlGamerHandle* handles, int handlecount);
        using get_net_player = CNetGamePlayer*(uint32_t id);
        using get_player_name = const char* (uint32_t id);
        using write_join_response_data = bool (*)(CMsgJoinResponse* response, void* data, int size, uint32_t* size_used);
        using send_event_ack = void(*)(rage::netEventMgr* eventMgr, CNetGamePlayer* source, CNetGamePlayer* target, int eventIndex, int eventHandledBitset);

        using read_bitbuf_dword = bool (*)(dat_bit_buffer* buffer, PVOID read, int bits);
        using read_bitbuf_string = bool (*)(dat_bit_buffer* buffer, char* read, int bits);
        using read_bitbuf_bool = bool (*)(dat_bit_buffer* buffer, bool* read, int bits);
        using read_bitbuf_array = bool (*)(dat_bit_buffer* buffer, PVOID read, int bits, int unk);
        using write_bitbuf_qword = bool (*)(dat_bit_buffer* buffer, uint64_t val, int bits);
        using write_bitbuf_dword = bool (*)(dat_bit_buffer* buffer, uint32_t val, int bits);
        using write_bitbuf_int64 = bool (*)(dat_bit_buffer* buffer, int64_t val, int bits);
        using write_bitbuf_int32 = bool (*)(dat_bit_buffer* buffer, int32_t val, int bits);
        using write_bitbuf_bool = bool (*)(dat_bit_buffer* buffer, bool val, int bits);
        using write_bitbuf_array = bool (*)(dat_bit_buffer* buffer, void* val, int bits, int unk);

        using handle_chat_message = void (*)(void* chat_data, void*, rage::rlGamerHandle* handle, const char* text, bool is_team);

        using fall_task_constructor_t = std::uint64_t* (std::uint64_t* _this, std::uint32_t flags);
        using fix_vectors_t = void(*)(rage::scrNativeCallContext*);
        using ptr_to_handle = std::int32_t(*)(void*);

        using chat_sender = CNetGamePlayer * (__int64 player);

        using queue_packet = bool (*)(rage::netConnectionManager* mgr, int msg_id, void* data, int size, int flags, void* unk);
        using send_packet = bool (*)(rage::netConnectionManager* mgr, rage::netPeerAddress* adde, int connection_id, void* data, int size, int flags);
        using get_connection_peer = rage::netConnectionPeer* (*)(rage::netConnectionManager* manager, int peer_id);

        using send_chat_message = bool (*)(int64_t* send_chat_ptr, rage::rlGamerInfo* gamer_info, char* message, bool is_team);

        using get_screen_coords_for_world_coords = bool (*)(float* world_coords, float* out_x, float* out_y);
        using trigger_script_event = void(*)(int event_group, int64_t* args, int arg_count, int player_bits);
        using start_matchmaking_find_sessions = bool (*)(int profile_index, int available_slots, NetworkGameFilterMatchmakingComponent* m_filter, unsigned int max_sessions, rage::rlSessionInfo* result_sessions, int* result_session_count, rage::rlTaskStatus* state);

        using handle_to_ptr = rage::CDynamicEntity* (*)(Entity);

        using write_player_game_state_data_node = bool (*)(rage::netObject* plr, CPlayerGameStateDataNode* node);

        using reset_network_complaints = void (*)(CNetComplaintMgr* mgr);


        using get_session_by_gamer_handle = bool(*)(int metric_mgr, rage::rlGamerHandle* handles, int count, rage::rlSessionByGamerTaskResult* result, int unk, bool* success, int* state);
        using send_invite_accepted_presence_event = void(*)(void* presenceStruct, rage::rlPresenceEventInviteAccepted* invite, int flags);
        using construct_basket = bool(CNetworkShoppingMgr* netshop_mgr, std::int32_t* id, std::uint32_t category, std::uint32_t action, std::uint32_t flags);
        using begin_service = bool(CNetworkShoppingMgr* netshop_mgr, std::int32_t* id, std::uint32_t service_type, std::uint32_t category, std::uint32_t item, std::uint32_t action, std::int32_t value, std::uint32_t flags);

        using add_item_to_basket = bool(CNetworkShoppingMgr* netshop_mgr, std::int32_t* items);

        using get_net_object = rage::netObject* (*)(CNetworkObjectMgr* mgr, int16_t id, bool can_delete_be_pending);

        using get_sync_tree_for_type = rage::netSyncTree* (*)(CNetworkObjectMgr* mgr, uint16_t sync_type);
        using change_network_object_owner = std::uint64_t(std::uint64_t obj_mgr, std::uint64_t net_obj, CNetGamePlayer* player, std::uint64_t unk);
        using get_entity_from_script = std::uint64_t(std::int32_t script_index);
    }
    class pointers {
    public:
        pointers();
        ~pointers() = default;
    public:
        //natives
        rage::scrNativeRegistrationTable* m_script_native_registration_table{};
        void* m_native_return_address{};
    public:
        //hooks
        PVOID m_fall_task_constructor{};
        func_types::send_chat_message m_send_chat_message{};
        PVOID m_new_index{};
        PVOID m_timecycle_override{};
        PVOID* m_draw_handler_mgr{};
        PVOID m_render_ped{};
        PVOID m_render_entity{};
        PVOID m_render_big_ped{};
        PVOID m_send_http_request{};
        PVOID m_handle_join_request{};
        PVOID m_weapon_group_info{};
        PVOID m_handle_network_event{};
        PVOID m_process_game_event{};
        PVOID m_init_native_tables{};
        PVOID m_task_jump_constructor{};
        PVOID m_receive_net_message{};
        PVOID m_chat_profanity{};
        PVOID m_send_metric{};
        PVOID m_get_event_data{};
        PVOID m_parachute_crash{};
        PVOID m_receive_pickup{};
        PVOID m_queue_dependency{};
        PVOID m_can_apply_data{};
        PVOID m_get_network_event_data{};
        PVOID m_set_game_pitch{};
        //spoofing
        func_types::write_player_game_state_data_node m_write_player_game_state_data_node;
        PVOID m_send_player_card_stats{};
        PVOID m_serialize_stats{};
        PVOID m_write_player_creation_data_node{};
        PVOID m_write_player_appearance_data_node{};
        PVOID m_write_player_gamer_data_node{};
        PVOID m_send_session_matchmaking_attributes{};

        PVOID m_receive_clone_sync{};
        PVOID m_receive_clone_create{};
        PVOID m_receive_clone_remove{};
        PVOID m_receive_clone_create_ack{};
        PVOID m_receive_clone_sync_ack{};
        PVOID m_add_item_to_basket{};
    public:
        //dat bit buffer
        func_types::read_bitbuf_dword m_read_bitbuf_dword{};
        func_types::read_bitbuf_string m_read_bitbuf_string{};
        func_types::read_bitbuf_bool m_read_bitbuf_bool{};
        func_types::read_bitbuf_array m_read_bitbuf_array{};
        func_types::write_bitbuf_qword m_write_bitbuf_qword{};
        func_types::write_bitbuf_dword m_write_bitbuf_dword{};
        func_types::write_bitbuf_int64 m_write_bitbuf_int64{};
        func_types::write_bitbuf_int32 m_write_bitbuf_int32{};
        func_types::write_bitbuf_bool m_write_bitbuf_bool{};
        func_types::write_bitbuf_array m_write_bitbuf_array{};
    public:
        //functions
        func_types::start_get_session_by_gamer_handle m_start_get_session_by_gamer_handle{};
        func_types::join_session_by_info m_join_session_by_info{};
        func_types::get_player_name* m_get_player_name{};
        func_types::get_net_player* m_get_net_player{};
        func_types::ptr_to_handle m_pointer_to_handle{};
        func_types::fix_vectors_t m_fix_vectors{};
        func_types::write_join_response_data m_write_join_response_data{};
        func_types::send_event_ack m_send_event_ack{};
        func_types::handle_chat_message m_handle_chat_message{};
        func_types::chat_sender* m_get_chat_sender{};
        func_types::queue_packet m_queue_packet{};
        func_types::send_packet m_send_packet{};
        func_types::get_connection_peer m_get_connection_peer{};
        func_types::get_screen_coords_for_world_coords m_get_screen_coords_for_world_coords;
        func_types::trigger_script_event m_trigger_script_event{};
        func_types::handle_to_ptr m_handle_to_ptr{};
        func_types::reset_network_complaints m_reset_network_complaints{};
        func_types::get_session_by_gamer_handle m_get_session_by_gamer_handle{};
        func_types::send_invite_accepted_presence_event m_send_invite_accepted_presence_event{};
        func_types::get_net_object m_get_net_object{};
        func_types::get_sync_tree_for_type m_get_sync_tree_for_type{};
        func_types::change_network_object_owner* m_change_network_object_owner;
        func_types::get_entity_from_script* m_get_entity_from_script;
        PVOID m_model_spawn_bypass{};
        PVOID m_owned_explosion{};
        uint64_t m_invite_player{};
        uint64_t m_get_entity_address{};
        uint64_t m_set_vehicle_gravity{};
        uint64_t m_get_model_info{};
        int64_t** m_send_chat_ptr;
        timecycle* m_timecycle;
        timecycle* m_timecycle_og;
    public:
        //crashes
        PVOID m_parachute_crash2{};
        PVOID m_invalid_mods_crash{};
    public:
        //non public :wink:
        uint64_t m_construct_basket;
        uint64_t m_begin_service;
        bool* m_has_game_been_altered{};
    public:
        //bypass stuff ig
        void* m_report_dependency{};
    public:
        //variables
        rage::grcTextureStore* m_texture_store{};
        network_base_config* m_network_base_config{};
        CNetworkPlayerMgr** m_network_player_mgr{};
        CNetworkObjectMgr** m_network_object_mgr{};
        HashTable<CBaseModelInfo*>* m_model_table;
        rage::atArray<CTrainConfig>* m_train_config_array;
        CPedFactory** m_ped_factory{};
        Network** m_network{};
        uint64_t m_dispatch_table{};
        uint32_t m_wheel_offset{};
        CGameVisuals* m_game_visuals{};
        ScInfo* m_sc_info{};
        uint64_t m_max_sticky_bombs{};
        std::uint32_t* m_region_code{};
        waypoint_data* m_waypoint_data{};
        rage::atArray<GtaThread*>* m_script_threads{};
        CNetworkShoppingMgr** m_netshopping_mgr{};
        ChatData** m_chat_data{};
        hash_list2 m_weapon_info{};
        hash_list2 m_weapon_components{};
        hash_list* m_hash_pool{};
        eGameState* m_game_state{};
        uint64_t** m_global_base{};
        PVOID m_break_off_wheels;
        uint32_t m_damage_struct{};
        HWND m_game_window{};
        bool* m_sync_money_rewards{};
        bool* m_is_session_started{};
        void* m_presence_struct{};
    public:
        //vfx
        uint64_t m_drop_shaders{};
        uint64_t m_drop_shader_count{};
        ui_visual_settings* m_ui_visual_settings{};
        explosion_data* m_explosion_data{};
        explosion_fx* m_explosion_fx{};
        ui_weather* m_ui_weather{};
        std::pair<vfx_wheel*, uint8_t> m_vfx_wheel{};
        ocean_quads m_ocean_quads{};
        CWaterQuad* m_water_quads{};
        vfx_liquid* m_vfx_liquid{};
        vfx_liquid* m_vfx_liquid_backup{};
    public:
        //misc
        FriendRegistry* m_friend_registry{};
        uint64_t m_world{};
        FARPROC m_convert_thread_to_fiber{};
        rage::scrProgramTable* m_script_program_table{};
        IDXGISwapChain** m_swapchain{};
    public:
       //ped preview
        uintptr_t m_ui_3d_draw_manager{};
        uintptr_t m_add_element_to_scene{};
        uintptr_t m_push_scene_preset_manager{};
        uintptr_t m_set_scene_element_lighting{};
        uintptr_t m_get_scene_preset{};
    public:
        //pools
        v_pool*** m_vehicle_pool{};
        entity_pool** m_ped_pool{};
        entity_pool** m_object_pool{};
        entity_pool** m_pickup_pool{};
        entity_pool** m_interior_proxy_pool{};

    };
	inline std::unique_ptr<pointers> g_pointers{};
 
}
