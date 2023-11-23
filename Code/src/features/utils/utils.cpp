#include "utils.h"

namespace Base {
	Ped utils::self() {
		return PLAYER::PLAYER_PED_ID();
	}
	Player utils::self_id() {
		return PLAYER::PLAYER_ID();
	}
	bool utils::aiming() {
		return PLAYER::IS_PLAYER_FREE_AIMING(self_id());
	}
	Entity utils::weapon() {
		return WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(self(), 0);
	}
	CPed* utils::cped() {
		return (*g_pointers->m_ped_factory)->m_local_ped;
	}
	CVehicle* utils::cvehicle() {
		return (*g_pointers->m_ped_factory)->m_local_ped->m_vehicle;
	}
	CWeaponInfo* utils::cweapon() {
		return (*g_pointers->m_ped_factory)->m_local_ped->m_weapon_manager->m_weapon_info;
	}
	bool utils::in_vehicle() {
		if (PED::IS_PED_IN_ANY_VEHICLE(self(), 0))
			return true;
		return false;
	}
	bool utils::is_model(std::vector<std::string> models, Ped ped) {
		auto entity{ ped == 0 ? self() : ped };
		for (auto model : models) {
			if (ENTITY::GET_ENTITY_MODEL(self()) == rage::joaat(model)) return true;
		}
	}
	Vector3 utils::coords(Entity entity) {
		return ENTITY::GET_ENTITY_COORDS(entity == 0 ? self() : entity, 0);
	}
	Vehicle utils::vehicle(bool include_last) {
		auto vehicle{ PED::GET_VEHICLE_PED_IS_IN(self(), include_last) };
		if (include_last) {
			return vehicle;
		}
		else {
			if (PED::IS_PED_IN_ANY_VEHICLE(self(), 0)) {
				return vehicle;
			}
			else {
				return -1;
			}
		}
	}
	u64 utils::get_entity_address(Entity entity) {
		if (entity <= 0) return 0;
		return caller::call<u64>(g_pointers->m_get_entity_address, entity);
	}

	bool utils::shooting() {
		return PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID());
	}
	bool utils::is_enemy(Ped ped) {
		int relation{ PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped, self()) };
		if (relation == 4 || relation == 5) {
			return true;
		}
		return false;
	}

	void utils::invoke_transaction(rage::joaat_t category, rage::joaat_t item_hash, rage::joaat_t action_type_hash, int value, int flag) {
		execute_as_script(rage::joaat("shop_controller"), [=] {
			if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE()) {
				NETSHOPPING::NET_GAMESERVER_BASKET_END();
			}
			int transaction_id{ -1 };

			if (NETSHOPPING::NET_GAMESERVER_BEGIN_SERVICE(&transaction_id, category, item_hash, action_type_hash, value, flag)) {
				NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(transaction_id);
			}
		});
	}
	rage::joaat_t utils::get_action_for_transaction(str item) {
		if (has_string_attached(item, "SERVICE_SPEND")) {
			return 537254313;
		}
		else if (has_string_attached(item, "SERVICE_EARN")) {
			return 1445302971;
		}
	}
	void utils::add_transaction(str category, str item, int flag) {
		auto price{ NETSHOPPING::NET_GAMESERVER_GET_PRICE(rage::joaat(item), rage::joaat(category), true) };
		invoke_transaction(rage::joaat(category), rage::joaat(item), get_action_for_transaction(item), price, flag);
	}

	Vector3 utils::weapon_bone_coords(const char* bone) {
		auto weapon_entity{ WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(self(), 0) };
		return ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(weapon_entity, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(weapon_entity, bone));
	}
	Vector3 utils::vehicle_bone_coords(const char* bone) {
		auto c{ ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle(), bone)) };
		return c;
	}
	Vector3 utils::get_ped_bone_coords(int bone) {
		return PED::GET_PED_BONE_COORDS(self(), bone, 0, 0, 0);
	}
	std::pair<Vector3, Vector3> utils::get_tracer_coords() {
		Vector3 cast{};
		auto raycast{ g_math->raycast(cast) };
		auto cam_rotation{ cam.rotation() };
		auto cam_coords{ cam.coords() };
		auto startDistance{ g_math->distance(cam_coords, coords()) + 0.25 };
		auto endDistance{ g_math->distance(cam_coords, coords()) + 1000.0 };
		auto pos{ weapon_bone_coords("gun_muzzle") };
		auto direction{ g_math->rotation_to_direction(&cam_rotation) };
		auto multiply{ direction * endDistance };
		return std::make_pair(pos, raycast ? cast : cam_coords + multiply);
	}
	std::pair<Vector3, Vector3> utils::get_tracer_coords2() {
		Vector3 cast{};
		auto raycast{ g_math->raycast(cast) };
		auto cam_rotation{ cam.rotation() };
		auto cam_coords{ cam.coords() };
		auto startDistance{ g_math->distance(cam_coords, coords()) + 0.25 };
		auto endDistance{ g_math->distance(cam_coords, coords()) + 1000.0 };
		auto pos{ weapon_bone_coords("gun_muzzle") };
		auto direction{ g_math->rotation_to_direction(&cam_rotation) };
		auto multiply{ direction * endDistance };
		return std::make_pair(pos, raycast ? cast : cam_coords + multiply);
	}
	void utils::particle_on_entity_bone(Entity entity, int bone, const char* dict, const char* particle, float scale, bool color, int r, int g, int b) {
		STREAMING::REQUEST_NAMED_PTFX_ASSET(dict);
		GRAPHICS::USE_PARTICLE_FX_ASSET(dict);
		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE(particle, entity, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.0f, bone, scale, true, true, true);
		if (color) {
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(r / 255.f, g / 255.f, b / 255.f);
		}
		STREAMING::REMOVE_PTFX_ASSET();
	}
	void utils::particle_on_coord(const char* dict, const char* particle, Vector3 coords, float scale, bool color, float r, float g, float b) {
		STREAMING::REQUEST_NAMED_PTFX_ASSET(dict);
		GRAPHICS::USE_PARTICLE_FX_ASSET(dict);
		GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle, coords.x, coords.y, coords.z, 0, 0, 0, scale, false, false, false, true);
		if (color) {
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(r, g, b);
		}
		STREAMING::REMOVE_PTFX_ASSET();
	}
	void utils::particle_on_self(const char* dict, const char* particle, int bone, float scale, bool color, float r, float g, float b) {
		STREAMING::REQUEST_NAMED_PTFX_ASSET(dict);
		GRAPHICS::USE_PARTICLE_FX_ASSET(dict);
		GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(particle, self(), 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.0f, bone, scale, TRUE, TRUE, TRUE);
		if (color) {
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(r, g, b);
		}
		STREAMING::REMOVE_PTFX_ASSET();
	}
	void utils::delete_entity(Entity entity) {
		if (ENTITY::DOES_ENTITY_EXIST(entity)) {
			ENTITY::DETACH_ENTITY(entity, true, true);
			ENTITY::SET_ENTITY_VISIBLE(entity, false, false);
			NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(entity, true);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, 0.f, 0.f, 0.f, false, false, false);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(entity, true, true);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&entity);
			ENTITY::DELETE_ENTITY(&entity);
			OBJECT::DELETE_OBJECT(&entity);
		}
	}
	void utils::shoot_single_bullet(Hash weapon, Vector3 start, Vector3 end, float damage, float speed, Ped owner) {
		g_fiber_pool.queue([=] {
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weapon)) {
				WEAPON::REQUEST_WEAPON_ASSET(weapon, 31, 0);
				fiber::current()->wait();
			}
		});
		MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(start.x, start.y, start.z, end.x, end.y, end.z, damage, 0, weapon, owner, true, false, speed);
	}
	void utils::shoot_single_bullet_out_of_muzzle(Hash hash, float speed, float damage) {
		auto cam_rotation{ CAM::GET_GAMEPLAY_CAM_ROT(0) };
		if (!weapon_bone_coords("gun_muzzle").empty()) {
			shoot_single_bullet(hash, get_tracer_coords().first, get_tracer_coords().second, damage, speed, self());
		}
		else {
			auto cam_direction{ g_math->rotation_to_direction(cam_rotation) };
			auto start_multiply{ cam_direction * 1.0f };
			auto end_multiply{ cam_direction * 500.0f };
			auto start{ CAM::GET_GAMEPLAY_CAM_COORD() + start_multiply };
			auto end{ start + end_multiply };
			shoot_single_bullet(hash, start, end, damage, speed, self());
		}
	}

	int utils::get_open_seat(Vehicle vehicle) {
		for (int i{ -1 }; i < VEHICLE::GET_NUMBER_OF_VEHICLE_DOORS(vehicle); i++) {
			if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, i, i)) {
				return i;
			}
		}
	}
	Vector3 utils::get_vector3(auto offset) {
		return Vector3(*reinterpret_cast<float*>(offset), *reinterpret_cast<float*>(offset + 0x4),
			*reinterpret_cast<float*>(offset + 0x8));
	}

	void utils::set_vector3(auto offset, Vector3 vec) {
		*reinterpret_cast<float*>(offset) = vec.x;
		*reinterpret_cast<float*>(offset + 0x4) = vec.y;
		*reinterpret_cast<float*>(offset + 0x8) = vec.z;
	}
	void utils::set_vehicle_scale(Vehicle veh, float val) {
		auto baseAddr{ get_entity_address(veh) };
		if (!baseAddr) {
			return;
		}

		auto passengerMatrixAddress = baseAddr + 0x60;
		Vector3 passengerForwardVec = get_vector3(passengerMatrixAddress + 0x00);
		Vector3 passengerRightVec = get_vector3(passengerMatrixAddress + 0x10);
		Vector3 passengerUpVec = get_vector3(passengerMatrixAddress + 0x20);

		auto vehicleMatrixAddress = *reinterpret_cast<uintptr_t*>(baseAddr + 0x30) + 0x20;
		Vector3 vehicleForwardVec = get_vector3(vehicleMatrixAddress + 0x00);
		Vector3 vehicleRightVec = get_vector3(vehicleMatrixAddress + 0x10);
		Vector3 vehicleUpVec = get_vector3(vehicleMatrixAddress + 0x20);

		set_vector3(passengerMatrixAddress + 0x00, passengerForwardVec * val);
		set_vector3(passengerMatrixAddress + 0x10, passengerRightVec * val);
		set_vector3(passengerMatrixAddress + 0x20, passengerUpVec * val);

		set_vector3(vehicleMatrixAddress + 0x00, vehicleForwardVec * val);
		set_vector3(vehicleMatrixAddress + 0x10, vehicleRightVec * val);
		set_vector3(vehicleMatrixAddress + 0x20, vehicleUpVec * val);
	}
	bool utils::change_network_object_owner(i32 script_index, CNetGamePlayer* owner) {
		if (*g_pointers->m_is_session_started && !ENTITY::IS_ENTITY_A_PED(script_index)) {
			u64 network_object_mgr_interface{ *(u64*)(g_pointers->m_network_object_mgr) };
			if (network_object_mgr_interface == NULL)
				return false;

			if (!ENTITY::DOES_ENTITY_EXIST(script_index)) {
				return false;
			}

			u64 entity{ g_pointers->m_get_entity_from_script(script_index) };
			if (entity == NULL) {
				return false;
			}

			u64 net_object{ *(u64*)(entity + 0xD0) };
			if (net_object == NULL) {
				return false;
			}

			if (*(u16*)(net_object + 0x8) == 11) {
				return false;
			}

			int network_handle{ NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(script_index) };
			g_pointers->m_change_network_object_owner(network_object_mgr_interface, net_object, owner, 0ui64);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(network_handle, true);

			return true;
		}
	}

	void utils::blame_explode(int plr, Vector3 pos, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake) {
		*(unsigned short*)g_pointers->m_owned_explosion = 0xE990;

		FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plr), pos.x, pos.y, pos.z, (int)explosion_type, damage, is_audible, is_invisible, camera_shake);

		*(unsigned short*)g_pointers->m_owned_explosion = 0x850F;
	}
	void utils::blame_explode(int plr, Vector3 pos, int explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake) {
		*(unsigned short*)g_pointers->m_owned_explosion = 0xE990;

		FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plr), pos.x, pos.y, pos.z, explosion_type, damage, is_audible, is_invisible, camera_shake);

		*(unsigned short*)g_pointers->m_owned_explosion = 0x850F;
	}

	void utils::make_networked(Vehicle vehicle) {
		DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
		auto id{ NETWORK::VEH_TO_NET(vehicle) };
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle)) {
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(id, true);
		}
		VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, false);
	}
	void utils::max_vehicle(Vehicle vehicle, bool set_colours) {
		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
		for (int i{ 0 }; i < 50; i++) {
			VEHICLE::SET_VEHICLE_MOD(vehicle, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1), false);
		}
		if (set_colours) {
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 2));
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
		}
	}
	void utils::downgrade_vehicle(Vehicle vehicle) {
		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
		for (int i{ 0 }; i < 50; i++) {
			VEHICLE::SET_VEHICLE_MOD(vehicle, i, -1, false);
		}
	}

	bool utils::has_string_attached(const str& first, const str& check) {
		str lower{ first };
		str check_lower{ check };
		std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
			return std::tolower(c);
		});
		std::transform(check_lower.begin(), check_lower.end(), check_lower.begin(), [](unsigned char c) {
			return std::tolower(c);
		});

		size_t found{ lower.find(check_lower) };
		if (found != std::string::npos) {
			return true;
		}
		else {
			return false;
		}
	}
	

	Vehicle utils::vehicle(Player player) {
		return PED::GET_VEHICLE_PED_IS_IN(self(), PLAYER::GET_PLAYER_PED(player));
	}
	Entity utils::hybrid() {
		return in_vehicle() ? vehicle() : self();
	}
	Hash utils::get_hash(Entity model) {
		return ENTITY::GET_ENTITY_MODEL(model);
	}
	BOOL utils::control_pressed(pressed_type flag, eControllerInputs action) {
		switch (flag) {
		case pressed:
			return PAD::IS_CONTROL_PRESSED(0, (int)action);
			break;
		case released:
			return PAD::IS_CONTROL_RELEASED(0, (int)action);
			break;
		case just_pressed:
			return PAD::IS_CONTROL_JUST_PRESSED(0, (int)action);
			break;
		case just_released:
			return PAD::IS_CONTROL_JUST_RELEASED(0, (int)action);
			break;
		case disable_pressed:
			return PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)action);
			break;
		case disable_released:
			return PAD::IS_DISABLED_CONTROL_RELEASED(0, (int)action);
			break;
		case disable_just_pressed:
			return PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)action);
			break;
		case disable_just_released:
			return PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)action);
			break;
		}
		return FALSE;
	}
	BOOL utils::control_pressed(pressed_type flag, int action) {
		switch (flag) {
		case pressed:
			return PAD::IS_CONTROL_PRESSED(0, action);
			break;
		case released:
			return PAD::IS_CONTROL_RELEASED(0, action);
			break;
		case just_pressed:
			return PAD::IS_CONTROL_JUST_PRESSED(0, action);
			break;
		case just_released:
			return PAD::IS_CONTROL_JUST_RELEASED(0, action);
			break;
		case disable_pressed:
			return PAD::IS_DISABLED_CONTROL_PRESSED(0, action);
			break;
		case disable_released:
			return PAD::IS_DISABLED_CONTROL_RELEASED(0, action);
			break;
		case disable_just_pressed:
			return PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, action);
			break;
		case disable_just_released:
			return PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, action);
			break;
		}
		return FALSE;
	}

	void utils::teleport(Vector3 coords, Entity entity, bool keep_vehicle) {
		if (!coords.empty()) {
			auto is_vehicle{ ENTITY::IS_ENTITY_A_VEHICLE(entity) };
			if (entity == 0) {
				keep_vehicle ? PED::SET_PED_COORDS_KEEP_VEHICLE(self(), coords.x, coords.y, coords.z) : ENTITY::SET_ENTITY_COORDS_NO_OFFSET(self(), coords.x, coords.y, coords.z, true, true, true);
			}
			else {
				is_vehicle ? ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, coords.z, true, true, true) : keep_vehicle ? PED::SET_PED_COORDS_KEEP_VEHICLE(entity, coords.x, coords.y, coords.z) : ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, coords.z, true, true, true);
			}
		}
	}
	void utils::fake_shoot() {
		PED::SET_PED_SHOOTS_AT_COORD(self(), 0, 0, 0, true);
	}

	void utils::request_model(Hash hash, std::function<void()> function) {
		while (!STREAMING::HAS_MODEL_LOADED(hash)) {
			STREAMING::REQUEST_MODEL(hash);
			fiber::current()->wait();
		}
		function();
	}
	void utils::request(request_type type, Hash hash, std::function<void()> function) {
		*script_global(4540731).as<bool*>() = true;
		g_fiber_pool.queue([=] {
			switch (type) {
			case request_type::model:
				while (!STREAMING::HAS_MODEL_LOADED(hash)) {
					STREAMING::REQUEST_MODEL(hash);
					fiber::current()->wait();
				}
				function();
				break;
			case request_type::weapon:
				while (!WEAPON::HAS_WEAPON_ASSET_LOADED(hash)) {
					WEAPON::REQUEST_WEAPON_ASSET(hash, 31, 0);
					fiber::current()->wait();
				}
				function();
				break;
			}
		});
	}
	void utils::request(request_type type, str name, std::function<void()> function) {
		g_fiber_pool.queue([=] {
			switch (type) {
			case request_type::particle:
				while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(name.c_str())) {
					STREAMING::REQUEST_NAMED_PTFX_ASSET(name.c_str());
					fiber::current()->wait();
				}
				function();
				break;
			}
		});
	}
	void utils::request_control(Entity entity, std::function<void()> function) {
		g_fiber_pool.queue([=] {
			while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity)) {
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
				fiber::current()->wait();
			}
			function();
		});
	}
	void utils::fade_screen(int time, std::function<void()> function) {
		CAM::DO_SCREEN_FADE_OUT(time);
		function();
		CAM::DO_SCREEN_FADE_IN(time);
	}
	str utils::get_mocking_str(const str& input) {
		str result{};
		bool capitalize{ true };

		for (char c : input) {
			if (isalpha(c)) {
				if (capitalize) {
					result += std::toupper(c);
				}
				else {
					result += std::tolower(c);
				}
				capitalize = !capitalize;
			}
			else {
				result += c;
			}
		}

		return result;
	}
	void utils::draw_chat_msg(char* msg, const char* player_name, bool is_team) {
		auto scaleform{ GRAPHICS::REQUEST_SCALEFORM_MOVIE("MULTIPLAYER_CHAT") };

		while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(scaleform)) {
			fiber::current()->wait();
		}

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "ADD_MESSAGE");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(msg);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(is_team ? "MP_CHAT_TEAM" : "MP_CHAT_ALL"));
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(false);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)HudColor::HUD_COLOUR_PURE_WHITE);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SET_FOCUS");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)HudColor::HUD_COLOUR_PURE_WHITE);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(scaleform, 255, 255, 255, 255, 0);

		if (auto chat_data{ *g_pointers->m_chat_data }; chat_data && (chat_data->m_chat_open || chat_data->m_timer_two)) {
			HUD::CLOSE_MP_TEXT_CHAT();
		}
	}
	Network* utils::network() {
		return *g_pointers->m_network;
	}
	rage::snPlayer* utils::get_player_by_peer_address(uint64_t addr) {
		network()->m_game_session_ptr->get_peer_by_rockstar_id(addr);
		return nullptr;
	}
	void utils::send_chat_msg(const str& message, bool show) {
		char* char_ptr{ const_cast<char*>(message.c_str()) };
		g_fiber_pool.queue([=] {
			if (const auto net_game_player = get_network_player_mgr()->m_local_net_player; net_game_player) {
				if (g_hooking->m_send_chat_message.get_original<decltype(&hooks::send_chat_message)>()(*g_pointers->m_send_chat_ptr, net_game_player->get_net_data(), char_ptr, false)) {
					if (show) {
						draw_chat_msg(char_ptr, net_game_player->get_name(), false);
					}
					if (g_hooking_features.m_chat.m_log)
						LOG(Info, "{} | {}", net_game_player->get_name(), message);
				}
			}
		});
	}
	str utils::get_character_prefix() {
		int last;
		STATS::STAT_GET_INT(rage::joaat("MPPLY_LAST_MP_CHAR"), &last, 1);
		return "MP" + std::to_string(last) + "_";
	}

	bool utils::get_blip_location(Vector3& location, int sprite, int color) {
		Blip blip;
		for (blip = HUD::GET_FIRST_BLIP_INFO_ID(sprite); HUD::DOES_BLIP_EXIST(blip) && color != -1 && HUD::GET_BLIP_COLOUR(blip) != color; blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite));

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != -1 && HUD::GET_BLIP_COLOUR(blip) != color)) return false;

		location = HUD::GET_BLIP_COORDS(blip);

		return true;
	}
	Vector3 utils::get_blip_icon() {
		static Vector3 zero;
		Vector3 coords;

		bool found{ false };
		int blip_id{ HUD::GET_WAYPOINT_BLIP_ENUM_ID() };
		for (auto i{ HUD::GET_FIRST_BLIP_INFO_ID(blip_id) }; HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(blip_id)) {
			if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4) {
				coords = HUD::GET_BLIP_INFO_ID_COORD(i);
				found = true;
				break;
			}
		}
		if (found) {
			return coords;
		}

		return zero;
	}
	bool utils::get_objective_location(Vector3& location) {
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission)) return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission2)) return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Mission)) return true;
		if (get_blip_location(location, (int)BlipIcons::RaceFinish, (int)BlipColors::None)) return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Green)) return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Blue)) return true;
		if (get_blip_location(location, (int)BlipIcons::CrateDrop)) return true;

		static const int blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };
		for (const auto& blip : blips) {
			if (get_blip_location(location, blip, 5)) return true;
		}

		return false;
	}

	GtaThread* utils::find_script_thread(rage::joaat_t hash) {
		for (auto thread : *g_pointers->m_script_threads)
			if (thread && thread->m_context.m_thread_id && thread->m_handler && thread->m_script_hash == hash)
				return thread;
		return nullptr;
	}
	void utils::sync_money_rewards(std::function<void()> function) {
		*g_pointers->m_sync_money_rewards = true;
		function();
		*g_pointers->m_sync_money_rewards = false;
	}

	void utils::timed_function(int delay, std::function<void()> action) {
		static int timer;
		if (timer == 0 || (int)(GetTickCount64() - timer) > delay) {
			action();
			timer = GetTickCount64();
		}
	}

	std::vector<u32> utils::get_hash_list_from_hash_table(u32 count, u64 table) {
		std::vector<u32> hashes;

		if (count && table) {
			u64* ptr{ (u64*)table };

			for (u32 i{ 0 }; i < count; i++) {
				if (ptr[i]) {
					u32 hash = *(u32*)(ptr[i] + 0x10);

					if (hash) {
						hashes.push_back(hash);
					}
				}
			}
		}

		return hashes;
	}

	void utils::add_rainbow(Color* rainbow) {
		if ((rainbow->r == 255 && rainbow->g == 255 && rainbow->b == 255) ||
			(rainbow->r == 0 && rainbow->g == 0 && rainbow->b == 0)) {
			rainbow->r = 255;
			rainbow->g = 0;
			rainbow->b = 0;
		}
		else if (rainbow->r > 0 && rainbow->b == 0) {
			rainbow->r = std::max(0, rainbow->r - rainbow_speed);
			rainbow->g = std::min(255, rainbow->g + rainbow_speed);
		}
		else if (rainbow->g > 0 && rainbow->r == 0) {
			rainbow->g = std::max(0, rainbow->g - rainbow_speed);
			rainbow->b = std::min(255, rainbow->b + rainbow_speed);
		}
		else if (rainbow->b > 0 && rainbow->g == 0) {
			rainbow->r = std::min(255, rainbow->r + rainbow_speed);
			rainbow->b = std::max(0, rainbow->b - rainbow_speed);
		}
	}
	CNetworkPlayerMgr* utils::get_network_player_mgr() {
		if (auto mgr{ *g_pointers->m_network_player_mgr })
			return mgr;
		return nullptr;
	}

	bool utils::key_press(std::uint16_t keycode, bool only_once) {
		if (keycode == VK_SHIFT || keycode == VK_ESCAPE || keycode == 0x5C)
			return false;
		if (GetForegroundWindow() == g_pointers->m_game_window) {
			if (only_once) {
				if (GetAsyncKeyState(keycode) & 1)
					return true;
			}
			else {
				if (GetAsyncKeyState(keycode) & 0x8000)
					return true;
			}
		}

		return false;
	}
	cam_struct utils::get_cam() {
		return cam.get();
	}
}