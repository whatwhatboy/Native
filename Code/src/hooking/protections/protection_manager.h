#pragma once
#include "src/utility/rate_limiter.h"
#include "src/utility/enum.h"
#include "src/features/utils/host.h"

namespace Base {
	struct protection_toggle {
		bool m_block{ true };
		bool m_notify{ true };
		bool m_log{ true };
		bool m_allow_from_friends;
	};
	struct protection {
		str m_name;
		int m_event_id;
		protection_toggle* m_protection;
	};
	struct protection_single {
		str m_name;
		bool* m_protection;
	};
	struct reaction {
		bool m_kick{};
		bool m_cage{};
		bool m_crash{};
	};
	struct reaction_vec {
		str m_name{};
		reaction* m_reaction;
	};
	class protection_manager {
	public:
		struct reactions {
			reaction m_vote_kick;
		} m_reactions;
		struct crashes {
			bool m_parachute{ true };
			bool m_parachute2{ true };
			bool m_invalid_mods{ true };
			bool m_fragment{ true };
			bool m_invalid_vehicle{ true };
			bool m_invalid_ped{ true };
			bool m_invalid_object{ true };
			bool m_invalid_pickup{ true };
			bool m_invalid_prop{ true };
			bool m_invalid_player{ true };
			bool m_invalid_train{ true };
			bool m_invalid_door{ true };
			bool m_invalid_rope_data{ true };
			bool m_invalid_interior{ true };
			bool m_invalid_mount_flag{ true };
			bool m_invalid_gadget{ true };
			bool m_invalid_control_data{ true };
			bool m_invalid_camera_position{ true };
			bool m_invalid_tasks{ true };
			bool m_invalid_script_information{ true };
			bool m_invalid_train_config{ true };
			bool m_invalid_component{ true };
			bool m_invalid_decal{ true };
			bool m_invalid_weapon_type{ true };
			bool m_invalid_sector_position{ true };
			bool m_infinite_attachment{ true };
			bool m_infinite_recursive_attachment{ true };
			bool m_ped_attachemnt{ true };
			bool m_recursive_ped_attachment{ true };
			bool m_host{ true };
			bool m_tse{ true };
			bool m_temp_action{ true };
			bool m_entity_render{ true };
			bool m_sync_remove{ true };
			bool m_bad_sync{ true };
			bool m_sync_mismatch{ true }; // aka stupid quantum crash

			bool m_out_of_bounds_gadget{ true };
			bool m_pop_group{ true };
			bool m_world_state{ true };
			bool m_out_of_bounds_control_type{ true };
		} m_crashes;
		struct kicks {
			bool m_bail{ true };
			bool m_interior{ true };
			bool m_instruction{ true };
			bool m_radio_sync{ true };
		} m_kicks;
		protection_toggle m_bountys;
		protection_toggle m_clear_wanted;
		protection_toggle m_bail;
		protection_toggle m_vehicle_kick;
		protection_toggle m_ceo_money;
		protection_toggle m_crash;
		protection_toggle m_soap_crash;
		bool m_block_pickups{};
		bool m_desync_kicks{ true };
		bool m_kick_chat_spammers{ true };
	public:
		std::vector<protection> m_protections {
			{ "Bounty", (int)eScriptEvents::ScriptEventSetBountyOnPlayer, &m_bountys },
			{ "Clear Wanted", (int)eScriptEvents::GeneralEventTypeClearWantedLevel, &m_clear_wanted },
			{ "Bail", (int)eScriptEvents::ScriptEventBailMeForSctv, &m_bail },
			{ "Vehicle Kick", -503325966, &m_vehicle_kick },
			{ "Ceo Money", (int)eScriptEvents::ScriptEventBeenPaidGoonCash, &m_ceo_money },
			{ "Crash", -11, &m_crash },
			{ "Soap Crash", (int)eRemoteEvent::Crash, &m_soap_crash }
		};
		std::vector<protection_single> m_crashes_vector {
			{ "Parachute", & m_crashes.m_parachute },
			{ "Parachute 2", &m_crashes.m_parachute2 },
			{ "Fragment", &m_crashes.m_fragment },
			{ "Invalid Mods", &m_crashes.m_invalid_mods },
			{ "Invalid Vehicle", &m_crashes.m_invalid_vehicle },
			{ "Invalid Ped", &m_crashes.m_invalid_ped },
			{ "Invalid Object", &m_crashes.m_invalid_object },
			{ "Invalid Pickup", &m_crashes.m_invalid_pickup },
			{ "Invalid Prop", &m_crashes.m_invalid_prop },
			{ "Invalid Player", &m_crashes.m_invalid_player },
			{ "Invalid Train", &m_crashes.m_invalid_train },
			{ "Invalid Door", &m_crashes.m_invalid_door },
			{ "Invalid Rope Data", &m_crashes.m_invalid_rope_data },
			{ "Invalid Interior", &m_crashes.m_invalid_interior },
			{ "Invalid Mount Flag", &m_crashes.m_invalid_mount_flag },
			{ "Invalid Gadget", &m_crashes.m_invalid_gadget },
			{ "Invalid Control Data", &m_crashes.m_invalid_control_data },
			{ "Invalid Camera Position", &m_crashes.m_invalid_camera_position },
			{ "Invalid Tasks", &m_crashes.m_invalid_tasks },
			{ "Invalid Script Information", &m_crashes.m_invalid_script_information },
			{ "Invalid Train Config", &m_crashes.m_invalid_train_config },
			{ "Invalid Component", &m_crashes.m_invalid_component },
			{ "Invalid Decal", &m_crashes.m_invalid_decal },
			{ "Invalid Weapon Type", &m_crashes.m_invalid_weapon_type },
			{ "Invalid Sector Position", &m_crashes.m_invalid_sector_position },
			{ "Infinite Attachment", &m_crashes.m_infinite_attachment },
			{ "Infinite Recursive Attachment", &m_crashes.m_infinite_recursive_attachment },
			{ "Ped Attachment", &m_crashes.m_ped_attachemnt },
			{ "Recursive Ped Attachment", &m_crashes.m_recursive_ped_attachment },
			{ "Host", &m_crashes.m_host },
			{ "TSE", &m_crashes.m_tse },
			{ "Temp Action", &m_crashes.m_temp_action },
			{ "Entity Render", &m_crashes.m_entity_render },
			{ "Sync Remove", &m_crashes.m_sync_remove },
			{ "Bad Sync", &m_crashes.m_bad_sync },
			{ "Sync Mismatch", &m_crashes.m_sync_mismatch },
			{ "Out of Bounds Gadget", &m_crashes.m_out_of_bounds_gadget },
			{ "Pop Group", &m_crashes.m_pop_group },
			{ "World State", &m_crashes.m_world_state },
			{ "Out Of Bounds Control Type", &m_crashes.m_out_of_bounds_control_type },
		};
		std::vector< protection_single> m_kicks_vector {
			{ "Bail", & m_kicks.m_bail },
			{ "Interior", &m_kicks.m_interior },
			{ "Instruction", &m_kicks.m_instruction },
			{ "Radio Sync", &m_kicks.m_radio_sync }
		};
		std::vector<reaction_vec> m_reaction {
			{ "Vote Kick", &m_reactions.m_vote_kick }
		};
	} inline g_protection_manager;

	inline rate_limiter g_radio_request_rate_limit{ 5s, 2 };
	inline rate_limiter g_host_migration_rate_limit{ 2s, 15 };
	inline rate_limiter g_mc_teleport{ 1s, 5 };

	inline void kick_player(int plr) {
		g_fiber_pool.queue([=] {
			if (force_host(rage::joaat("freemode"))) {
				*script_global(1885447).at(plr, 1).as<bool*>() = true;
			}
		});
	}

	inline void invoke_reaction(reaction react, int plr) {
		if (react.m_kick) {
			kick_player(plr);
		}
	}
	struct blacklist_action {
		bool m_notify{};
		bool m_kick{};
		bool m_crash{};
	};
	struct blacklist_word {
		str m_keyword{};
		blacklist_action m_action;
	};
	class word_blacklist {
	public:
		std::vector<blacklist_word> m_words;
		void add(blacklist_word w) {
			for (auto word : m_words) {
				if (word.m_keyword == w.m_keyword) return;
			}
			m_words.push_back(w);
		}
		void remove(const str& keyword) {
			for (auto it{ m_words.begin() }; it != m_words.end(); ++it) {
				if (it->m_keyword == keyword) {
					m_words.erase(it);
					return;
				}
			}
		}
	} inline g_word_blacklist;
}
