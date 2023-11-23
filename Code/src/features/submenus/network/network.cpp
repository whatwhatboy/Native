#include "network.h"
#include "src/Natives/Natives.h"
#include "src/fiber/script/manager/script_manager.h"
#include "src/memory/pointers/pointers.h"
#include <src/utility/enum.h>
#include "src/features/feature_manager.h"
#include <src/hooking/hooking.h>
#include "misc/force_thunder.h"
#include "misc/globals.h"
#include "misc/responses.h"
#include "src/features/chat_commands/chat_commands.h"
#include "misc/classes.h"
#include "misc/notifications.h"
namespace Base {
	namespace am_hunt_the_beast
	{
		constexpr static auto broadcast_idx = 600;
		constexpr static auto player_broadcast_idx = 2584;
	}

	namespace am_criminal_damage
	{
		constexpr static auto broadcast_idx = 111;
		constexpr static auto score_idx = 106;
	}

	namespace am_cp_collection
	{
		constexpr static auto broadcast_idx = 816;
		constexpr static auto player_broadcast_idx = 3457;
	}

	namespace am_king_of_the_castle
	{
		constexpr static auto broadcast_idx = 94;
	}
	void invoke_request(int offset) {
		*script_global(2794162).at(offset).as<bool*>() = true;
	}
	bool extra_slot{};
	void add_session_scripts() {
		g_feature_manager.add<button_option>("criminal_damage", "Criminal Damage", "", [] {
			start_launcher_script(launcher_scripts::criminal_damage);
		});
		g_feature_manager.add<button_option>("business_battle", "Business Battle", "", [] {
			start_launcher_script(launcher_scripts::business_battles);
		});
		g_feature_manager.add<button_option>("king_of_the_castle", "King Of The Castle", "", [] {
			start_launcher_script(launcher_scripts::king_of_the_castle);
		});
		g_feature_manager.add<button_option>("hunt_the_beast", "Hunt The Beast", "", [] {
			start_launcher_script(launcher_scripts::hunt_the_beast);
		});
		g_feature_manager.add<button_option>("penned_in", "Penned In", "", [] {
			start_launcher_script(41);
		});
		g_feature_manager.add<button_option>("hot_property", "Hot Property", "", [] {
			start_launcher_script(launcher_scripts::hot_property);
		});
		g_feature_manager.add<button_option>("hot_target", "Hot Target", "", [] {
			start_launcher_script(36);
		});
		g_feature_manager.add<button_option>("checkpoints", "Checkpoints", "", [] {
			start_launcher_script(launcher_scripts::checkpoints);
		});
		g_feature_manager.add<button_option>("kill_list", "Kill List", "", [] {
			start_launcher_script(36);
		 });
		g_feature_manager.add<button_option>("challenges", "Challenges List", "", [] {
			start_launcher_script(40);
		});

		//activites
		g_feature_manager.add<button_option>("golf", "Golf", "", [] {
			start_launcher_script(launcher_scripts::golf);
		});
		g_feature_manager.add<button_option>("flight_school", "Flight School", "", [] {
			start_launcher_script(launcher_scripts::flight_school);
		});
		g_feature_manager.add<button_option>("one_on_one_deathmatch", "One-On-One Deathmatch", "", [] {
			start_launcher_script(launcher_scripts::one_on_one_deathmatch);
		});
		g_feature_manager.add<button_option>("impromptu_race", "Impromptu Race", "", [] {
			start_launcher_script(launcher_scripts::impromptu_race);
		});
		g_feature_manager.add<button_option>("tutorial", "Tutorial", "", [] {
			start_launcher_script(launcher_scripts::tutorial);
		});
		g_feature_manager.add<button_option>("ghost_hunt", "Ghost Hunt", "", [] {
			start_launcher_script(launcher_scripts::ghost_hunt);
		});

		//arcade
		g_feature_manager.add<button_option>("space_monkey", "Space Monkey", "", [] {
			start_launcher_script(launcher_scripts::space_monkey);
		});
		g_feature_manager.add<button_option>("wizard", "Wizard", "", [] {
			start_launcher_script(launcher_scripts::wizard);
		});
		g_feature_manager.add<button_option>("gunslinger", "Gun Slinger", "", [] {
			start_launcher_script(launcher_scripts::gunslinger);
		});
	}
	void add_ongoing_scripts() {
		//criminal damage
		g_feature_manager.add<button_option>("start_criminal_damage", "Start", "", [] {
			if (force_host(rage::joaat("am_criminal_damage")))
				if (auto script{ find_script_thread(rage::joaat("am_criminal_damage")) })
					*script_local(script->m_stack, am_criminal_damage::broadcast_idx).at(43).as<int*>() = 0;
		});
		g_feature_manager.add<button_option>("end_criminal_damage", "End", "", [] {
			if (force_host(rage::joaat("am_criminal_damage")))
				if (auto script{ find_script_thread(rage::joaat("am_criminal_damage")) })
					*script_local(script->m_stack, am_criminal_damage::broadcast_idx).at(39).as<int*>() = 0;
		});
		g_feature_manager.add<button_option>("win_criminal_damage", "Win", "", [] {
			g_fiber_pool.queue([] {
				if (force_host(rage::joaat("am_criminal_damage"))) {
					if (auto script{ find_script_thread(rage::joaat("am_criminal_damage")) }) {
						*script_local(script->m_stack, am_criminal_damage::broadcast_idx).at(43).as<int*>() = 0;
						*script_local(script->m_stack, am_criminal_damage::score_idx).as<int*>() = 999'999'999;
						fiber::current()->wait(1s);
						*script_local(script->m_stack, am_criminal_damage::broadcast_idx).at(39).as<int*>() = 0;
					}
				}
			});
		});

	}
	void add_globals() {
		g_feature_manager.add<toggle_option>("off_radar", "Enabled", "", &globals::off_radar::enabled, globals::off_radar::init, globals::off_radar::on_disable);
		g_feature_manager.add<toggle_option>("ghost_org", "Ghost Orginization", "", &globals::off_radar::settings::ghost_org);
		g_feature_manager.add<choose_option>("bst", "BST", "", globals::bst::type, &globals::bst::selected, false, [] {
			switch (globals::bst::selected) {
			case 0:
				*script_global(2794162).at(899).as<bool*>() = true;
				break;
			case 1:
				*script_global(2672524).at(3690).as<int*>() = 1;
				break;
			}
		});

		g_feature_manager.add<button_option>("airstrike", "Airstrike", "", [] {
			invoke_request(4492);
		});
		g_feature_manager.add<button_option>("ammo_crate", "Ammo Crate", "", [] {
			invoke_request(891);
		});
		g_feature_manager.add<button_option>("backup_helicopter", "Backup Helicopter", "", [] {
			invoke_request(4491);
		});
		g_feature_manager.add<button_option>("ballistic_armor", "Ballistic Armor", "", [] {
			invoke_request(896);
		});
		g_feature_manager.add<button_option>("boat_pickup", "Boat Pickup", "", [] {
			invoke_request(892);
		});

		g_feature_manager.add<button_option>("taxi", "Taxi", "", [] {
			invoke_request(853);
		});

		g_feature_manager.add<button_option>("dinghy", "Dinghy", "", [] {
			invoke_request(972);
		});
		g_feature_manager.add<button_option>("avenger", "Avenger", "", [] {
			invoke_request(938);
		});
		g_feature_manager.add<button_option>("kosatka", "Kosatka", "", [] {
			invoke_request(960);
		});
		g_feature_manager.add<button_option>("moc", "Mobile Operations Center", "", [] {
			invoke_request(930);
		});
		g_feature_manager.add<button_option>("terrobyte", "Terrobyte", "", [] {
			invoke_request(943);
		});
		g_feature_manager.add<button_option>("acid_lab", "Acid Lab", "", [] {
			invoke_request(944);
		});
	}
	void add_host() {
		g_feature_manager.add<button_option>("force_script_host", "Force Script", "", [] {
			force_host(rage::joaat("freemode"));
			if (auto script = find_script_thread(rage::joaat("freemode")); script && script->m_net_component)
				((CGameScriptHandlerNetComponent*)script->m_net_component)->block_host_migration(true);

			force_host(rage::joaat("fmmc_launcher"));
			if (auto script = find_script_thread(rage::joaat("fmmc_launcher")); script && script->m_net_component)
				((CGameScriptHandlerNetComponent*)script->m_net_component)->block_host_migration(true);
		});
	}
	void add_heist_editor() {
		g_feature_manager.add<button_option>("instant_finish_cayo", "Instant Finish Cayo", "", [] {
			g_fiber_pool.queue([] {
				if (force_host(rage::joaat("fm_mission_controller"))) {
					if (auto script{ find_script_thread(rage::joaat("fm_mission_controller")) }) {
						*script_local(script->m_stack, 31656).as<int*>() = 0;
						*script_local(script->m_stack, 19710).as<int*>() = 12;
					}
				}
				});
			});
	}
	float max_players = 0;
	float max_spectators = 0;
	void trigger_transaction2(str name) {
		g_utils->add_transaction("CATEGORY_SERVICE_WITH_THRESHOLD", name);
	}
	bool loop[7] = { false, false, false, false, false, false };

	void add_loops() {
		g_feature_manager.add<toggle_option>("one_million_loop", "Juggalo Mission (1M)", "", &loop[0], [] {
			if (!loop[0]) return;
			trigger_transaction2("SERVICE_EARN_JUGGALO_STORY_MISSION");
		});
		g_feature_manager.add<toggle_option>("battle_loop", "Business Battle (50K)", "", &loop[1], [] {
			if (!loop[1]) return;
			trigger_transaction2("SERVICE_EARN_FROM_BUSINESS_BATTLE");
		});
		g_feature_manager.add<toggle_option>("item_loop", "Collectable Item (100K)", "", &loop[2], [] {
			if (!loop[2]) return;
			trigger_transaction2("SERVICE_EARN_COLLECTABLE_ITEM");
		});
		g_feature_manager.add<toggle_option>("jobs_loop", "Jobs (180K)", "", &loop[3], [] {
			if (!loop[3]) return;
			trigger_transaction2("SERVICE_EARN_JOBS");
		});
		g_feature_manager.add<toggle_option>("betting_loop", "Betting (-600K)", "", &loop[4], [] {
			if (!loop[4]) return;
			trigger_transaction2("SERVICE_SPEND_BETTING");
		});
		g_feature_manager.add<toggle_option>("casino_remove_loop", "Casino (-900K)", "", &loop[5], [] {
			if (!loop[5]) return;
			trigger_transaction2("SERVICE_SPEND_CASINO_HEIST_VAULT_DOOR");
		});
		g_feature_manager.add<toggle_option>("weapon_stash_loop", "Weapon Stash (-10K)", "", &loop[6], [] {
			if (!loop[6]) return;
			trigger_transaction2("SERVICE_SPEND_ISLAND_HEIST_SUPPORT_WEAPON_STASH");
		});
	}
	void add_protections() {
		g_feature_manager.add<choose_option>("vote_kick_response", "Vote Kick", responses::response_struct, &responses::vote_kick);
	}
	void add_chat() {
		g_feature_manager.add<toggle_option>("chat_commands_enabled", "Enabled", "", &m_chat_command_toggles.m_enabled);

		g_feature_manager.add<toggle_option>("chat_mocking", "Mocking", "", &g_hooking_features.m_chat.m_mocking);
		g_feature_manager.add<toggle_option>("chat_log", "Log", "", &g_hooking_features.m_chat.m_log);
		g_feature_manager.add<toggle_option>("chat_profanity", "Bypass Profanity", "", &g_hooking_features.m_chat.m_profanity);


		g_feature_manager.add<toggle_with_float_option>("chat_spammer", "Enabled", &g_spammer.m_enabled, &g_spammer.m_settings.m_delay, 0, 5000, 1, 0, false, get_func(g_spammer.tick));
		g_feature_manager.add<toggle_option>("chat_spammer_show", "Visible Locally", "", &g_spammer.m_settings.m_visible_locally);
	}
	void add_notis() {
		g_feature_manager.add<toggle_option>("kill_feed", "Kill Feed", "", &notis::death::enabled, notis::death::init);

		g_feature_manager.add<toggle_option>("joining_players", "Joining Players", "", &g_hooking_features.m_notifications.m_joining);
		g_feature_manager.add<toggle_option>("leaving_players", "Leaving Players", "", &g_hooking_features.m_notifications.m_leaving);
	}
	void add_modder_detection() {
		g_feature_manager.add<toggle_option>("modder_detection", "Enabled", "", &g_modder_detection.m_enabled, get_func(g_modder_detection.tick));

		g_feature_manager.add<toggle_option>("modder_detection_invalid_model", "Invalid Model", "", &g_modder_detection.m_detections.m_model);
		g_feature_manager.add<toggle_option>("modder_detection_speed", "Speed", "", &g_modder_detection.m_detections.m_speed);
	}
	bool dummy{ true };
	void network_options::add() {
		add_chat_commands();
		add_loops();
		add_heist_editor();
		add_host();
		add_globals();
		add_session_scripts();
		add_ongoing_scripts();
		add_protections();
		add_chat();
		add_notis();
		add_modder_detection();

		g_feature_manager.add<toggle_option>("disable_casino_region_lock", "Disable Region Lock", "", &g_hooking_features.disable_casino_country_restrictions);
		g_feature_manager.add<toggle_option>("block_joins", "Enabled", "", &g_hooking_features.block_join);
		g_feature_manager.add<toggle_option>("force_thunder", "Force Thunder", "", &force_thunder::enabled, force_thunder::init, force_thunder::on_disable);
		g_feature_manager.add<toggle_option>("open_extra_slot", "Open Extra Slot", "", &extra_slot, [] {
			NETWORK::NETWORK_SESSION_SET_MATCHMAKING_GROUP(extra_slot ? 4 : 0);
		});
		g_feature_manager.add<button_option>("bail", "Bail", "", [] {
			NETWORK::NETWORK_BAIL(0, 0, 16);
			NETWORK::NETWORK_BAIL_TRANSITION(0, 0, 16);
		});

		g_feature_manager.add<float_option>("max_players", "Max Players", "", & max_players, 0, 32, 1, 0, true, [] {
			NETWORK::NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX(0, max_players);
		});
		g_feature_manager.add<float_option>("max_spectators", "Max Spectators", "", & max_spectators, 0, 32, 1, 0, true, [] {
			NETWORK::NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX(4, max_spectators);
		});

		g_feature_manager.add<toggle_option>("null_spof", "null", "", &dummy, get_func(g_spoofing_tick.tick));
		g_feature_manager.add<toggle_option>("null_spofdd", "nulldd", "", &dummy, get_func(g_streamer_mode.tick));

		g_feature_manager.add<choose_option>("join_session", "Join Type", globals::join_session::session_types, &globals::join_session::selected, false, globals::join_session::join);
	}
}