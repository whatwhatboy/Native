#pragma once
#include "src/natives/natives.h"
#include <JSON/json.hpp>
#include "src/framework/notifications/notifications.h"
#include "src/features/utils/curl_wrapper.h"

namespace Base::rid_utils {
	static const script_global transition_state(1574996);
	inline bool join_type(eSessionType session) {
		SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(rage::joaat("pausemenu_multiplayer"));

		while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(rage::joaat("pausemenu_multiplayer")))
			fiber::current()->wait();


		if (session == eSessionType::LEAVE_ONLINE)
			*script_global(1574589).at(2).as<int*>() = -1;
		else {
			*script_global(1574589).at(2).as<int*>() = 0;
			*script_global(1575020).as<int*>() = (int)session;
		}

		*script_global(1574589).as<int*>() = 1;

		if (*g_pointers->m_is_session_started && session != eSessionType::LEAVE_ONLINE) {
			*transition_state.as<eTransitionState*>() = eTransitionState::TRANSITION_STATE_LOOK_TO_JOIN_ANOTHER_SESSION_FM;
		}
		else if (session == eSessionType::LEAVE_ONLINE) {
			*transition_state.as<eTransitionState*>() = eTransitionState::TRANSITION_STATE_RETURN_TO_SINGLEPLAYER;
		}

		*script_global(32284).as<int*>() = 0;
		*script_global(1574934).as<int*>() = 1;
		*script_global(1574995).as<int*>() = 32;

		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("maintransition")) == 0) {
			*script_global(2694534).as<int*>() = 1;
			fiber::current()->wait(200ms);
			*script_global(1574589).as<int*>() = 0;
		}

		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(rage::joaat("pausemenu_multiplayer"));
		return true;
	}
	inline void join(const char* type) {
		if (type == "Public") {
			join_type(eSessionType::JOIN_PUBLIC);
		}
		else if (type == "New Public") {
			join_type(eSessionType::NEW_PUBLIC);
		}
		else if (type == "Closed Crew") {
			join_type(eSessionType::CLOSED_CREW);
		}
		else if (type == "Crew") {
			join_type(eSessionType::CREW);
		}
		else if (type == "Friends") {
			join_type(eSessionType::CLOSED_FRIENDS);
		}
		else if (type == "Find Friend") {
			join_type(eSessionType::FIND_FRIEND);
		}
		else if (type == "Solo") {
			join_type(eSessionType::SOLO);
		}
		else if (type == "Invite Only") {
			join_type(eSessionType::INVITE_ONLY);
		}
		else if (type == "Join Crew") {
			join_type(eSessionType::CREW);
		}
	}
	inline std::string get_ticket() {
		return g_pointers->m_sc_info->m_ticket;
	}

	inline nlohmann::json sendRequest(nlohmann::json body, std::string endpoint) {
		curl_wrapper curl{};
		std::vector<std::string> headers = {
			"X-Requested-With: XMLHttpRequest",
			"Content-Type: application/json; charset=utf-8",
			std::format("Authorization: SCAUTH val=\"{}\"", get_ticket())
		};
		std::string response{ curl.post(endpoint, body.dump(), headers) };
		nlohmann::json j{ nlohmann::json::parse(response) };
		if (j["Status"]) {
			return j;
		}
		return {};
	}

	inline bool is_rid_online(uint64_t rid) {
		if (nlohmann::json json = sendRequest({ { "RockstarId", std::to_string(rid) } }, "https://scui.rockstargames.com/api/friend/getprofile"); !json.is_null()) {
			for (auto& acc : json["Accounts"]) {
				if (auto& r_acc = acc["RockstarAccount"]; !r_acc.is_null()) {
					if (rid == r_acc["RockstarId"].get<uint64_t>()) {
						return r_acc["IsOnline"].get<bool>();
					}
				}
			}
		}
		return false;
	}



	inline void invite_player(uint64_t rockstar_id) {
		net_msg_identifier identifier;
		memset(&identifier, 0, sizeof(identifier));

		identifier.m_rockstar_id = rockstar_id;
		identifier.m_type = 3;

		caller::call<void>(g_pointers->m_invite_player, g_pointers->m_network_base_config, &identifier, 1, "Invite", "Join fr", 0);
	}

	inline void get_session_from_gamer_handle(rage::rlGamerHandle& handle, std::function<void(rage::rlSessionByGamerTaskResult, bool)> callback) {
		bool success = false;
		auto state = NULL;
		rage::rlSessionByGamerTaskResult taskRes;
		if (g_pointers->m_get_session_by_gamer_handle(NULL, &handle, 1, &taskRes, 1, &success, &state)) {
			while (state == 1)
				fiber::current()->wait(5ms);
			callback(taskRes, state == 3 && success ? true : false);
		}
		
	}
	inline void rid_join(uint64_t rid) {
		m_rid_data.gamer_handle = { rid };
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_joaat) != 0 || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
			return;
		}
		bool wasSuccess{};
		get_session_from_gamer_handle(m_rid_data.gamer_handle, [&](rage::rlSessionByGamerTaskResult result, bool success) {
			if (success) {
				m_rid_data.is_queued = true;
				m_rid_data.session_info = result.m_session_info;
				join_type(eSessionType::NEW_PUBLIC);
				fiber::current()->wait(350ms);
				if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_joaat) == 0) {
					m_rid_data.is_queued = false;
				}
				wasSuccess = true;
			}
			});
		if (!wasSuccess)
			return;
			
	}
}
