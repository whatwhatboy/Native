#include "src/hooking/hooking.h"
#include "src/memory/Pointers/Pointers.h"
#include "src/features/utils/operator.h"
#include "src/framework/notifications/notifications.h"
namespace Base {
	inline std::vector<std::pair<int, const char*>> block_join_reasons = {
		{1, "None"},
		{5, "Been Voted Out"},           // You have already been voted out of this game session.
		{7, "Incompatible Assets"},      // Failed to join session due to incompatible assets.
		{8, "Session Full"},             // The session you're trying to join is currently full.
		{9, "Slot Full"},                // The session you're trying to join is currently full of players.
		{10, "No Title Update"},         // Please make sure all players have the latest Title Update.
		{12, "Invites Disabled"},        // Invites are currently disabled in the session.
		{13, "Different Targeting Mode"},// The session you are trying to join is using a different targeting preference. You can change your preference in the Settings tab of the Pause Menu in Grand Theft Auto V. Joining a new GTA Online Session.
		{14, "Cheater"},// You are classed as a cheat and can only play with other cheats until you are forgiven.
		{16, "Incompatible DLC"},// Incompatible downloadable content. All players must have the latest compatibility pack.
		{17, "Crew Only"},       // You are trying to enter a Crew Members only session.
		{21, "Session No Longer Exists"},// The session you are trying to join no longer exists.
		{22, "Invite Only"},// The session you are trying to join is private. You will need to be invited to join this session.
		{26, "Friends Only"},        // The session you are trying to join is friends only.
		{23, "Different Build Type"},// The session you are trying to join is a different build type.
		{25, "Different Content"},   // The session you are trying to join is not using the same content.
		{18, "Bad Sport"},// The session you are trying to join is for people who are not Bad Sports or cheaters - you are a Bad Sport.
		{19, "Bad Sports Only"},// The session you are trying to join is for Bad Sports only.
		{20, "Cheaters Only"},  // The session you are trying to join is for cheaters only.
		{27, "Bad Reputation"}, // Unable to join this session, your account has a bad reputation.
		{28, "May Not Exist"},  // Unable to connect to session. The session may no longer exist.
		{29, "Premium Race"},// Unable to Join. The session you are trying to join is a Premium Race. Joining and accepting invites is disabled for this mode.
	};
	bool hooks::handle_join_request(Network* network, rage::snSession* session, rage::rlGamerInfo* player_info, CJoinRequestContext* ctx, BOOL is_transition_session) {
		if ("block_joins"_TF->is_toggled()) {
			CMsgJoinResponse response{};
			response.m_status_code = block_join_reasons[g_hooking_features.reasons_selected].first;
			g_pointers->m_write_join_response_data(&response, ctx->m_join_response_data, 512, &ctx->m_join_response_size);
			g_notifications->send("Block Joins", std::format("Blocked {} from joining.", player_info->m_name));
			return false;
		}
		else {
			RET_CALL_DECL(handle_join_request, network, session, player_info, ctx, is_transition_session);
		}
	}


	bool hooks::weapon_group_info(u64 unk, int group) {
		if (g_hooking_features.any_weapon_in_vehicle) {
			if (group == rage::joaat("GROUP_THROWN"))
				RET_CALL_DECL(weapon_group_info, unk, group);
			return true;
		}
		RET_CALL_DECL(weapon_group_info, unk, group);
	}
	template<typename T, typename P1>
	static T call(u64 address, P1 p1) { return ((T(*)(P1))address)(p1); }
	struct event_player_spawn {
		char _0x0000[0x18];
		char m_name[0x20];
	};
	u64 hooks::process_game_event(u64 _this) {
		u64 vtable = *(u64*)_this;
		u32 id = call<u32>(*(u64*)(vtable + 0x18), _this);

		switch (id) {
		case 164: {
			event_player_spawn* _event = (event_player_spawn*)_this;

			LOG(Info, "{} just respawned", _event->m_name);

			break;
		}
		}

		return static_cast<decltype(&process_game_event)>(g_hooking->process_game_event)(_this);
	}
	void* hooks::assign_new_physical_index_handler(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, u8 new_index) {
		const auto* net_player_data = player->get_net_data();

		if (net_player_data) {
			if (new_index == 0xFF) {
				if (g_hooking_features.m_notifications.m_leaving)
					g_notifications->send("Network", std::format("{} Left", player->get_name()));
			}
			else {
				if (g_hooking_features.m_notifications.m_leaving)
					g_notifications->send("Network", std::format("{} joined", player->get_name()));
			}
		}

		RET_CALL_DECL(assign_new_physical_index_handler, netPlayerMgr, player, new_index);
	}
	void hooks::update_timecycle_keyframe_data(i64 timecycleManager, TimecycleKeyframeData* timecycleKeyframeData) {
		g_hooking->m_update_timecycle_keyframe_data.get_original<decltype(&hooks::update_timecycle_keyframe_data)>()(timecycleManager, timecycleKeyframeData);

		if (g_hooking_features.m_colors.m_rainbow_sky) {
			timecycleKeyframeData->m_azimuth_east.x = g_rainbow.r / 255.f;
			timecycleKeyframeData->m_azimuth_east.y = g_rainbow.g / 255.f;
			timecycleKeyframeData->m_azimuth_east.z = g_rainbow.b / 255.f;

			timecycleKeyframeData->m_azimuth_west.x = g_rainbow.r / 255.f;
			timecycleKeyframeData->m_azimuth_west.y = g_rainbow.g / 255.f;
			timecycleKeyframeData->m_azimuth_west.z = g_rainbow.b / 255.f;

			timecycleKeyframeData->m_azimuth_transition.x = g_rainbow.r / 255.f;
			timecycleKeyframeData->m_azimuth_transition.y = g_rainbow.g / 255.f;
			timecycleKeyframeData->m_azimuth_transition.z = g_rainbow.b / 255.f;

			timecycleKeyframeData->m_zenith.x = g_rainbow.r / 255.f;
			timecycleKeyframeData->m_zenith.y = g_rainbow.g / 255.f;
			timecycleKeyframeData->m_zenith.z = g_rainbow.b / 255.f;
		}
		if (g_hooking_features.m_colors.m_rainbow_moon) {
			timecycleKeyframeData->m_moon.x = g_rainbow.r / 255.f;
			timecycleKeyframeData->m_moon.y = g_rainbow.g / 255.f;
			timecycleKeyframeData->m_moon.z = g_rainbow.b / 255.f;
		}
		if (g_hooking_features.m_colors.m_rainbow_clouds) {
			timecycleKeyframeData->m_cloud_base.x = g_rainbow.r / 255.f;
			timecycleKeyframeData->m_cloud_base.y = g_rainbow.g / 255.f;
			timecycleKeyframeData->m_cloud_base.z = g_rainbow.b / 255.f;

			timecycleKeyframeData->m_cloud_mid.x = g_rainbow.r / 255.f;
			timecycleKeyframeData->m_cloud_mid.y = g_rainbow.g / 255.f;
			timecycleKeyframeData->m_cloud_mid.z = g_rainbow.b / 255.f;

			timecycleKeyframeData->m_cloud_1.x = g_rainbow.r / 255.f;
			timecycleKeyframeData->m_cloud_1.y = g_rainbow.g / 255.f;
			timecycleKeyframeData->m_cloud_1.z = g_rainbow.b / 255.f;
		}

		if (g_hooking_features.m_colors.m_star_intensity_toggle)
			timecycleKeyframeData->m_stars_iten = g_hooking_features.m_colors.m_star_intensity;
	}
}