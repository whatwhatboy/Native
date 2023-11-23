#pragma once
#include "src/Natives/Invoker/Invoker.h"
#include "src/hooking/vmt/hook.h"
#include <src/rage/network/netObject.hpp>
#include <src/rage/script/scrThreadContext.hpp>
#define DEFINE_SCRIPT_HASH_THIS_FRAME() Hash ScriptHashThisFrame = SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME();
#define IS_VIABLE_SCRIPT(hash) hash == "main"_joaat || hash == "freemode"_joaat || hash == "main_persistent"_joaat
#define ENSURE_VIABLE_SCRIPT_THIS_FRAME() DEFINE_SCRIPT_HASH_THIS_FRAME() \
	if (IS_VIABLE_SCRIPT(ScriptHashThisFrame)) { \
	} \
	else { \
		return; \
	}
#define FRAME_COUNT(value) static u32 FrameCount = value;
#define BEGIN_MATCHING_FRAME_ENSURE() if (FrameCount != MISC::GET_FRAME_COUNT()) {
#define END_MATCHING_FRAME_ENSURE() FrameCount = MISC::GET_FRAME_COUNT(); \
	}
#include <src/rage/network/snSession.hpp>
#include <src/rage/network/Network.hpp>
#include <src/rage/network/CJoinRequestContext.hpp>
#include <src/rage/network/CMsgJoinResponse.hpp>
#include <src/rage/rage/rlTaskStatus.hpp>
#include <src/rage/rage/rlSessionInfo.hpp>
#include "detour/detour.h"
#include <src/rage/network/netConnection.hpp>
#include "src/utility/enum.h"
#define CALL_DECL(hk, ...) g_hooking->m_##hk##.get_original<decltype(&##hk)>()(__VA_ARGS__)
#define RET_CALL_DECL(hk, ...) return CALL_DECL(hk, __VA_ARGS__);
#include "protections/protection_manager.h"
#include <src/rage/netsync/nodes/task/ClonedTakeOffPedVariationInfo.hpp>
#include <src/rage/stats/CPlayerCardStats.hpp>
#include <src/rage/stats/CStatsSerializationContext.hpp>
#include <src/rage/netsync/nodes/player/CPlayerAppearanceDataNode.hpp>
#include <src/rage/netsync/nodes/player/CPlayerCreationDataNode.hpp>
#include <src/rage/netsync/nodes/player/CPlayerGameStateDataNode.hpp>
#include <src/rage/netsync/nodes/player/CPlayerGamerDataNode.hpp>
#include "vmt/hook.h"
#include "src/rage/netsync/netSyncTree.hpp"
#include "src/rage/network/CNetworkEvent.hpp"
#include "../hooking/classes/extra.h"
namespace Base {
	struct hooks {
		static void StatGetInt(rage::scrNativeCallContext* src);
		static void disable_casino_country_restrictions(rage::scrNativeCallContext* src);
		static void SET_WARNING_MESSAGE_WITH_HEADER(rage::scrNativeCallContext* src);
		static void shoot_single_bullet(rage::scrNativeCallContext* src);
		static void get_player_name(rage::scrNativeCallContext* src);
		static void network_bail(rage::scrNativeCallContext* src);
		static void begin_text_command_thefeed_post(rage::scrNativeCallContext* src);
		static void set_current_ped_weapon(rage::scrNativeCallContext* context);
		static void disable_control_action(rage::scrNativeCallContext* context);
		static void hud_force_weapon_wheel(rage::scrNativeCallContext* src);

		static constexpr auto ResizeBuffersIndex = 13;
		static HRESULT Present(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
		static constexpr auto PresentIndex = 8;
		static HRESULT ResizeBuffers(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
		static void* convert_thread_to_fiber(void* param);

		static u64 process_game_event(u64 _this);

		static void NETWORK_SESSION_HOST(rage::scrNativeCallContext* src);

		static u64* fall_task_constructor(u64* _this, u32 flags);
		static u64 jump_task_constructor(u64 _this, u32 flags);
		static bool send_http_request(CHttpRequest* request);

		static void* render_ped(__int64 renderer, CPed* ped, __int64 a3, __int64 a4);
		static void render_entity(__int64 renderer, rage::fwEntity* entity, int unk, bool a4);
		static __int64 render_big_ped(__int64 renderer, CPed* ped, __int64 a3, __int64 a4);

		static bool handle_join_request(Network* network, rage::snSession* session, rage::rlGamerInfo* player_info, CJoinRequestContext* ctx, BOOL is_transition_session);

		static void handle_network_event(rage::netEventMgr* eventMgr, CNetGamePlayer* source, CNetGamePlayer* target, uint16_t eventId, int eventIndex, int eventHandledBitset, int bufferSize, dat_bit_buffer* buffer);
		static bool weapon_group_info(u64 unk, int group);
		static bool init_native_tables(rage::scrProgram* program);

		static void* assign_new_physical_index_handler(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, u8 new_index);

		static void update_timecycle_keyframe_data(i64 timecycleManager, TimecycleKeyframeData* timecycleKeyframeData);

		static bool receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame);
		static bool send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, char* message, bool is_team);
		static int check_chat_profanity(u64 rcx, u64 input, u64 output);

		static bool send_cheat_metric(rage::rlMetric* metric, bool unk);

		static bool get_event_data(int32_t event_group, int32_t event_index, i64* args, u32 arg_count);

		static void parachute_crash(ClonedTakeOffPedVariationInfo* info, CSyncDataBase* serializer);
		static bool receive_pickup(rage::netObject* object, void* unk, CPed* ped);

		//spoofing
		static void write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node);
		static void write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node);

		static netGameEvent* send_player_card_stats(netGameEvent* a1, CPlayerCardStats* stats);
		static void serialize_stats(CStatsSerializationContext* context, rage::joaat_t* stats, u32 stat_count);

		static void write_player_creation_data_node(rage::netObject* player, CPlayerCreationDataNode* node);
		static void write_player_appearance_data_node(rage::netObject* player, CPlayerAppearanceDataNode* node);
		static bool send_session_matchmaking_attributes(void* a1, rage::rlSessionInfo* info, u64 session_id, bool use_session_id, MatchmakingAttributes* attributes);

		static u64 parachute_crash_2(u64 rcx, int rdx, int r8);

		//syncing
		static eAckCode receive_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, u16 object_id, rage::datBitBuffer* buffer, u16 unk, u32 timestamp);
		static bool receive_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, i32 object_id, i32 object_flag, rage::datBitBuffer* buffer, i32 timestamp);
		static bool receive_clone_remove(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, i32 object_id, i32 timestamp);
		static void receive_clone_create_ack(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, u16 object_id, i32 ack_code);
		static void receive_clone_sync_ack(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, rage::datBitBuffer* buffer, u16 object_id, i32 ack_code);

		static void invalid_mods_crash(i64  rcx, i64  rdx, int r8, char r9);

		static bool can_apply_data(rage::netSyncTree* tree, rage::netObject* object);

		static bool add_item_to_basket(CNetworkShoppingMgr* netshop_mgr, i32* items);

		static i64 set_game_pitch(i64 _this, int pitch);
	};
	class Hooking {
		friend struct Hooks;
	public:
		Hooking();
		~Hooking();
	public:
		void Hook();
		void Unhook();
	public:
		vmt_hook m_dx_vmt;
		MinHook m_minhook;
		void* m_OriginalGetFontId{};

		void* original_draw1{};
		void* original_draw2{};
		void* original_draw3{};

		void* handle_join_request{};

		void* handle_network_event_og{};

		void* og_weapon_group_info{};

		void* process_game_event{};
		detour m_handle_join_request;
		detour m_add_item_to_basket;
		detour m_weapon_group_info;
		detour m_update_timecycle_keyframe_data;
		detour m_assign_new_physical_index_handler;
		detour m_fall_task_constructor;
		detour m_jump_task_constructor;
		detour m_send_http_request;

		detour m_receive_net_message;

		detour m_send_chat_message;
		detour m_check_chat_profanity;
		detour m_send_cheat_metric;
		detour m_get_event_data;
		detour m_convert_thread_to_fiber;

		//crashes
		detour m_parachute_crash;
		detour m_parachute_crash_2;
		detour m_invalid_mods_crash;

		//other protections
		detour m_receive_pickup;

		//spoofing
		detour m_write_player_gamer_data_node;
		detour m_write_player_game_state_data_node;

		detour m_send_player_card_stats;
		detour m_serialize_stats;

		detour m_write_player_creation_data_node;
		detour m_write_player_appearance_data_node;
		detour m_send_session_matchmaking_attributes;

		//syncing
		detour m_receive_clone_sync;
		detour m_receive_clone_create;
		detour m_receive_clone_remove;
		detour m_receive_clone_create_ack;
		detour m_receive_clone_sync_ack;

		detour m_can_apply_data;
		detour m_set_game_pitch;
	};
	inline std::unique_ptr<Hooking> g_hooking;

	class hooking_features {
	public:
		struct jump {
			bool super{};
			bool beast{};
			bool dive{};
			bool shake_camera{};
			bool land{};

		};
		struct fall {
			bool super{};
			bool beast{};
			bool dive{};
			bool shake_camera{};
			bool land{};
		};
		jump jump;
		fall fall;

		bool weapons_in_interior{ true };

		const char* reasons[22] = {
			"None",
			"Been Voted Out",
			"Incompatible Assets",
			"Session Full",
			"Slot Full",
			"No Title Update",
			"Invites Disabled",
			"Different Targeting Mode",
			"Cheater",
			"Incompatible DLC",
			"Crew Only",
			"Session No Longer Exists",
			"Invite Only",
			"Friends Only",
			"Different Build Type",
			"Different Content",
			"Bad Sport",
			"Bad Sports Only",
			"Cheaters Only",
			"Bad Reputation",
			"May Not Exist",
			"Premium Race"
		};
		int reasons_selected{ 0 };
		bool block_join{ false };

		bool disable_casino_country_restrictions{ false };

		bool super_jump{ false };
		bool beast_jump{ false };

		bool any_weapon_in_vehicle{};

		struct notificationss {
			bool m_joining{ true };
			bool m_leaving{ true };
			bool m_player_spawns{ true };
		};
		notificationss m_notifications;

		struct colors {
			bool m_enabled{ false };
			bool m_rainbow_sky{ false };
			bool m_rainbow_clouds{ false };
			bool m_rainbow_moon{ false };

			bool m_star_intensity_toggle{ false };
			float m_star_intensity{ 1.0 };
		} m_colors;

		struct chat {
			bool m_log{ true };
			bool m_mocking{ false };
			bool m_profanity{ false };
			str m_spammer_message{};
		} m_chat;

		struct streamer_mode {
			bool m_enabled{ false };
			str m_prefix{ "Player" };
		} m_streamer_mode;

		bool m_weapons_in_interiors;

		bool m_change_game_pitch{};
		float m_game_pitch{-500};
	};
	inline hooking_features g_hooking_features;

	inline std::vector<u32> ped_pool;
	inline bool cached{ false };
	inline bool just_entered_model_changer{ false };
	inline float veh_gravity{ 9.807f };

	inline Hash selected_parachute{ rage::joaat("prop_beach_parasol_03") };

	inline bool is_doing_selected_scenario{};
	inline const char* selected_scenario{};

	inline CNetGamePlayer* g_syncing_player;
	inline eNetObjType g_syncing_object_type = (eNetObjType)-1;

	struct entity_shooter_struct {
		str m_name;
		Vehicle m_id;
	};
	inline std::vector<entity_shooter_struct> m_entity_shooter_shot;

	inline std::vector<CNetShopTransactionBasket*> g_transactions;

	
}