#include "src/hooking/hooking.h"
#include "src/memory/Pointers/Pointers.h"
#include "src/hooking/dat_bit_buffer/dat_bit_buffer.h"
#include "src/utility/enum.h"
#include "src/features/utils/utils.h"
#include "src/features/utils/operator.h"
#include "src/features/chat_commands/chat_commands.h"
#include <src/rage/network/CMsgTextMessage.hpp>
#include "src/framework/notifications/notifications.h"
namespace Base {
	enum class world_state_data_type {
		car_gen,
		entity_area,
		pop_group_override,
		pop_multiplier_area,
		ptfx,
		road_node,
		rope,
		scenario_blocking_area,
		vehicle_player_locking
	};
	enum class script_entity_change_type {
		blocking_of_non_temporary_events,
		setting_of_ped_relationship_group_hash,
		setting_of_drive_task_cruise_speed,
		setting_of_look_at_entity,
		setting_of_plane_min_height_above_terrain,
		set_ped_ragdoll_block_flag,
		setting_of_task_vehicle_temp_action,
		set_ped_facial_idle_anim_override,
		set_vehicle_lock_state,
		set_vehicle_exclusive_driver
	};
	const char* return_world_state_data_type_name(int position) {
		switch (position)
		{
		case 0:
			return "carGen";
		case 1:
			return "entityArea";
		case 2:
			return "popGroupOverride";
		case 3:
			return "popMultiplierArea";
		case 4:
			return "ptfx";
		case 5:
			return "roadNode";
		case 6:
			return "rope";
		case 7:
			return "scenarioBlockingArea";
		case 8:
			return "vehiclePlayerLocking";
		default:
			return "Unknown";
		}
	}
	static void deserialize_script_id(CGameScriptId& id, dat_bit_buffer& buffer) {
		id.m_hash = buffer.Read<u32>(32);
		id.m_timestamp = buffer.Read<u32>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<u32>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<u32>(8);
	}
	void hooks::handle_network_event(rage::netEventMgr* eventMgr, CNetGamePlayer* source, CNetGamePlayer* target, uint16_t eventId, int eventIndex, int eventHandledBitset, int bufferSize, dat_bit_buffer* buffer) {
		auto send_event_ack = [=]() {
			g_pointers->m_send_event_ack(eventMgr, source, target, eventIndex, eventHandledBitset);
		};
		if (eventId > 91u) {
			send_event_ack();
			return;
		}

		const auto event_name{ *(char**)((DWORD64)eventMgr + 8i64 * eventId + 243376) };
		if (event_name == nullptr || source == nullptr || source->m_player_id < 0 || source->m_player_id >= 32) {
			send_event_ack();
			return;
		}


		switch (static_cast<network_events>(eventId)) {
		case network_events::remove_weapon_event: {
			int netId = buffer->Read<int>(13);
			uint32_t hash = buffer->Read<uint32_t>(32);
			if (g_utils->cped() && g_utils->cped()->m_net_object && g_utils->cped()->m_net_object->m_object_id == netId) {
				if (hash == rage::joaat("WEAPON_UNARMED") && g_protection_manager.m_crashes.m_invalid_weapon_type) {
					g_notifications->send("Protections", std::format("Blocked 'invalid weapon type' crash from {}", source->get_name()));
					send_event_ack();
					return;
				}
				else {
					LOG(Info, "remove_weapon_event | {} removed {} from {}", source->get_name(), std::to_string(hash), target->get_name());
					g_notifications->send("Protections", std::format("{} is trying to remove your weapons.", source->get_name()));
					send_event_ack();
					return;
				}
			}

			buffer->Seek(0);
			break;
		}
		case network_events::network_clear_ped_tasks_event: {
			int netId = buffer->Read<int>(13);
			if (g_utils->cped() && g_utils->cped()->m_net_object && g_utils->cped()->m_net_object->m_object_id == netId) {
				LOG(Info, "network_clear_ped_tasks_event | {} is trying to freeze {}", source->get_name(), target->get_name());
				g_notifications->send("Protections", std::format("{} tried to freeze you.", source->get_name()));
				send_event_ack();
				return;
			}

			buffer->Seek(0);
			break;
		}
		case network_events::network_play_sound_event: {
			auto is_entity{ buffer->Read<bool>(1) };
			std::int16_t net_id;
			u32 ref_hash;

			if (is_entity)
				net_id = buffer->Read<std::int16_t>(13);

			auto ref{ buffer->Read<bool>(1) };
			if (ref)
				ref_hash = buffer->Read<u32>(32);

			auto sound_hash{ buffer->Read<u32>(32) };
			g_notifications->send("Protections", std::format("{} played {}", source->get_name(), std::to_string(sound_hash)));
			LOG(Info, "Sound Played: {}: {}", source->get_name(), std::to_string(sound_hash));

			buffer->Seek(0);
			break;
		}
		case network_events::script_world_state_event: {
			auto type = buffer->Read<world_state_data_type>(4);
			buffer->Read<bool>(1);
			CGameScriptId id;
			deserialize_script_id(id, *buffer);
			if (type == world_state_data_type::rope) {
				buffer->Read<int>(9);
				buffer->Read<float>(19);
				buffer->Read<float>(19);
				buffer->Read<float>(19);
				buffer->Read<float>(19);
				buffer->Read<float>(19);
				buffer->Read<float>(19);
				buffer->Read<float>(16);
				auto type{ buffer->Read<int>(4) };
				auto initial_length{ buffer->Read<float>(16) };
				auto min_length{ buffer->Read<float>(16) };
				LOG(Info, "script_world_state_event | {} created a rope with the aruguments: type | {}, min length | {}, initial Length | {}", source->get_name(), type, min_length, initial_length);

				if (type == 0 || initial_length < min_length) {
					if (g_protection_manager.m_crashes.m_invalid_rope_data) {
						g_notifications->send("Protections", std::format("Blocked 'invalid rope data' crash from {}", source->get_name()));
						send_event_ack();
						return;
					}
				}
			}
			else if (type == world_state_data_type::pop_group_override) {
				auto schedule = buffer->ReadSigned<int>(8);
				auto group = buffer->Read<int>(32);
				auto percentage = buffer->Read<int>(7);
				LOG(Info, "script_world_state_event | {} overrided the pop group with the arguments: schedule | {}, group | {}, percentage | {}", source->get_name(), schedule, group, percentage);
				if (group == 0 && (percentage == 0 || percentage == 103)) {
					if (g_protection_manager.m_crashes.m_pop_group) {
						g_notifications->send("Protections", std::format("Blocked 'pop group' crash from {}", source->get_name()));
						send_event_ack();
						return;
					}
				}
			}
			else if (type > world_state_data_type::vehicle_player_locking || type < world_state_data_type::car_gen) {
				if (g_protection_manager.m_crashes.m_world_state) {
					g_notifications->send("Protections", std::format("Blocked 'world state' crash from {}", source->get_name()));
					send_event_ack();
					return;
				}
			}
			else {
				LOG(Info, "script_world_state_event | {} modified the world state to {}", source->get_name(), return_world_state_data_type_name(int(type)));
				//g_notifications->send("Info", std::format("{} modified the world state to {}", source->get_name(), return_world_state_data_type_name(int(type))));

			}
		}
		case network_events::script_entity_state_change_event: {
			auto entity = buffer->Read<uint16_t>(13);
			auto type = buffer->Read<script_entity_change_type>(4);
			auto unk = buffer->Read<uint32_t>(32);
			if (type == script_entity_change_type::setting_of_task_vehicle_temp_action) {
				auto pedId = buffer->Read<uint16_t>(13);
				auto action = buffer->Read<uint32_t>(8);

				LOG(Info, "setting_of_task_vehicle_temp_action | {} send a temp action to you're vehicle with the arguemnts: action | {}", source->get_name(), action);
				if ((action >= 15 && action <= 18) || action == 33) {
					if (g_protection_manager.m_crashes.m_temp_action) {
						g_notifications->send("Protections", std::format("{} tried to crash you. (temp action)", source->get_name()));
						send_event_ack();
						return;
					}
				}

			}
			buffer->Seek(0);
			break;
		}
		case network_events::alter_wanted_level_event: {
			int netId = buffer->Read<int>(13);
			if (g_utils->cped() && g_utils->cped()->m_net_object && g_utils->cped()->m_net_object->m_object_id == netId)
				LOG(Info, "alter_wanted_level_event | {} changed {}'s wanted level.", source->get_name(), target->get_name());

			buffer->Seek(0);
			break;
		}
		case network_events::kick_votes_event: {
			int netId = buffer->Read<int>(13);
			if (g_utils->cped() && g_utils->cped()->m_net_object && g_utils->cped()->m_net_object->m_object_id == netId) {
				invoke_reaction(g_protection_manager.m_reactions.m_vote_kick, source->m_player_id);
				//LOG(Info, "kick_votes_event | {} voted to kick {}", source->get_name(), target->get_name());
				g_notifications->send("Protections", std::format("{} tried to kick you.", source->get_name()));
				send_event_ack();
				return;
			}

			

			buffer->Seek(0);
			break;
		}
		case network_events::request_control_event: {
			auto net_id = buffer->Read<int>(13);
			if (g_utils->cped() && g_utils->cped()->m_vehicle && g_utils->cped()->m_vehicle->m_net_object && g_utils->cped()->m_vehicle->m_net_object->m_object_id == net_id) {
				Vehicle veh = g_pointers->m_pointer_to_handle(g_utils->cped()->m_vehicle);
				if (!NETWORK::NETWORK_IS_ACTIVITY_SESSION() || DECORATOR::DECOR_GET_INT(veh, "RandomId") == g_utils->cped()->m_net_object->m_object_id) {
					g_notifications->send("Protections", std::format("{} tried to request control of your vehicle.", source->get_name()));
					send_event_ack();
					return;
				}
			}
			buffer->Seek(0);
			break;
		}
		case network_events::give_pickup_rewards: {
			int netId = buffer->Read<int>(13);
			if (g_utils->cped() && g_utils->cped()->m_net_object && g_utils->cped()->m_net_object->m_object_id == netId) {
				g_notifications->send("Protections", std::format("{} is trying to give you pickup rewards.", source->get_name()));
				send_event_ack();
				return;
				
			}

			buffer->Seek(0);
			break;
		}
		case network_events::give_control_event: {
			uint32_t timestamp = buffer->Read<uint32_t>(32);
			int count = buffer->Read<int>(2);
			bool all_objects_migrate_together = buffer->Read<bool>(1);

			if (count > 3)
			{
				count = 3;
			}

			for (int i = 0; i < count; i++)
			{
				int net_id = buffer->Read<int>(13);
				eNetObjType object_type = buffer->Read<eNetObjType>(4);
				int migration_type = buffer->Read<int>(3);

				if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
				{
					if (g_protection_manager.m_crashes.m_out_of_bounds_control_type) {
						g_notifications->send("Protections", std::format("Blocked 'out of bounds control type' crash from {}", source->get_name()));
						send_event_ack();
						return;
					}
				}
			}

			buffer->Seek(0);
			break;
		}
		default: break;
		}

		return static_cast<decltype(&handle_network_event)>(g_hooking->handle_network_event_og)(eventMgr, source, target, eventId, eventIndex, eventHandledBitset, bufferSize, buffer);
	}

	inline Network* get_network() {
		return *g_pointers->m_network;
	}
	inline bool deserialise_net_message(eNetMessage& msg, dat_bit_buffer& buffer) {
#define RET_DEAD() { \
				msg = eNetMessage::MsgInvalid; \
				return false; \
			}
		if (buffer.m_flagBits & 2)
			RET_DEAD();
		u32 pos{ (buffer.m_flagBits & 1) == 0 ? buffer.m_curBit : buffer.m_maxBit };
		u32 magic{};
		u32 extended{};
		if (buffer.m_bitsRead + 15 > pos)
			RET_DEAD();
		if (!buffer.ReadDword(&magic, 14))
			RET_DEAD();
		if (magic != 0x3246)
			RET_DEAD();
		if (!buffer.ReadDword(&extended, 1))
			RET_DEAD();
		u32 length{ extended ? 16u : 8u };
		pos = (buffer.m_flagBits & 1) == 0 ? buffer.m_curBit : buffer.m_maxBit;
		if (length + buffer.m_bitsRead <= pos) {
			if (buffer.ReadDword((u32*)&msg, length))
				return true;
		}
		return false;
	}
	void gamer_handle_deserialize(rage::rlGamerHandle& hnd, dat_bit_buffer& buf) {
		constexpr int PC_PLATFORM = 3;
		if ((hnd.m_platform = buf.Read<uint8_t>(8)) != PC_PLATFORM)
			return;

		buf.ReadInt64((int64_t*)&hnd.m_rockstar_id, 64);
		hnd.unk_0009 = buf.Read<uint8_t>(8);
	}
	CNetworkPlayerMgr* network_mgr() {
		return *g_pointers->m_network_player_mgr;
	}
	bool is_kick_instruction(dat_bit_buffer& buffer) {
		rage::rlGamerHandle sender, receiver;
		char name[18];
		gamer_handle_deserialize(sender, buffer);
		gamer_handle_deserialize(receiver, buffer);
		buffer.ReadString(name, 17);

		int instruction{ buffer.Read<int>(32) };
		return instruction == 8;
	}
	void protection_notify_kick2(str name, str plr_name) {
		g_notifications->send("Protections", std::format("Blocked '{}' kick from {}", name, plr_name));
	}
	bool is_spam_message(str msg) {
		if (g_utils->has_string_attached(msg, "cashlounge")) {
			return true;
		}
	}
	void invoke_blacklisted_word(CNetGamePlayer* player, blacklist_word word) {
		if (word.m_action.m_notify) {
			g_notifications->send("Word Blacklist", std::format("{} sent a blacklisted word: {}", player->get_name(), word.m_keyword));
		}
		if (word.m_action.m_kick) {
			kick_player(player->m_player_id);
		}
	}
	bool hooks::receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame) {
		if (frame->get_event_type() != rage::netConnection::InFrame::EventType::FrameReceived)
			RET_CALL_DECL(receive_net_message, netConnectionManager, a2, frame);

		if (frame->m_data == nullptr || frame->m_length == 0)
			RET_CALL_DECL(receive_net_message, netConnectionManager, a2, frame);

		dat_bit_buffer buffer(frame->m_data, frame->m_length);
		buffer.m_flagBits = 1;

		eNetMessage msg_type;
		CNetGamePlayer* player{};

		for (u32 i = 0; i < get_network()->m_game_session_ptr->m_player_count; i++) {
			if (get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_peer_id_2 == frame->m_peer_id) {
				player = network_mgr()->m_player_list[i];
				break;
			}
		}

		if (!deserialise_net_message(msg_type, buffer)) {
			RET_CALL_DECL(receive_net_message, netConnectionManager, a2, frame);
		}

		if (player) {
			switch (msg_type) {
				case eNetMessage::MsgTransitionGamerInstruction:
				{
					if (is_kick_instruction(buffer) && g_protection_manager.m_kicks.m_instruction) {
						protection_notify_kick2("instruction", player->get_name());
						return true;
					}
					break;
				}
				case eNetMessage::MsgTextMessage2: {
					char message[256];
					buffer.ReadString(message, 256);
					str str_m{ std::string(message) };
					if (is_spam_message(str_m) && g_protection_manager.m_kick_chat_spammers) {
						kick_player(player->m_player_id);
						g_notifications->send("Network", std::format("Kicked {}. Reason: Text Spamming", player->get_name()));
						return true;
					}
					break;
				}
				case eNetMessage::MsgTextMessage: {
					char message[256];
					buffer.ReadString(message, 256);
					str str_m{ std::string(message) };
					if (g_hooking_features.m_chat.m_log) {
						LOG(Info, "{} | {}", player->get_net_data()->m_name, str_m);
					}
					if (is_spam_message(str_m) && g_protection_manager.m_kick_chat_spammers) {
						kick_player(player->m_player_id);
						g_notifications->send("Network", std::format("Kicked {}. Reason: Chat Spamming", player->get_name()));
						return true;
					}
					if (g_chat_commands.is_command(str_m)) {
						g_chat_commands.execute(player->m_player_id, str_m);
					}

					for (auto word : g_word_blacklist.m_words) {
						if (g_utils->has_string_attached(str_m, word.m_keyword)) {
							invoke_blacklisted_word(player, word);
						}
					}

					if (g_pointers->m_chat_data && player->get_net_data()) {
						rage::rlGamerHandle temp{};
						gamer_handle_deserialize(temp, buffer);
						bool is_team = buffer.Read<bool>(1);
					}
					if (g_hooking_features.m_chat.m_mocking) {
						g_utils->send_chat_msg(g_utils->get_mocking_str(str_m));
					}
					break;
				}
				case eNetMessage::MsgScriptMigrateHost: {
					if (g_host_migration_rate_limit.process()) {
						if (g_host_migration_rate_limit.exceeded_last_process()) {
							if (g_radio_request_rate_limit.exceeded_last_process() && g_protection_manager.m_kicks.m_radio_sync) {
								protection_notify_kick2("radio sync", player->get_name());
							}
						}
						return true;
					}
					break;
				}
				case eNetMessage::MsgRadioStationSyncRequest: { 
					if (g_radio_request_rate_limit.process()) {
						if (g_radio_request_rate_limit.exceeded_last_process() && g_protection_manager.m_kicks.m_radio_sync) {
							protection_notify_kick2("radio sync", player->get_name());
						}
						return true;
					}

					break;
				}
			}
		}


		RET_CALL_DECL(receive_net_message, netConnectionManager, a2, frame);

	}

	bool hooks::receive_pickup(rage::netObject* object, void* unk, CPed* ped) {
		if (g_protection_manager.m_block_pickups) {
			g_notifications->send("Protections", "Blocked pickup.");
			return false;
		}

		RET_CALL_DECL(receive_pickup, object, unk, ped);
	}
	
}