#include "src/hooking/hooking.h"
#include "src/framework/notifications/notifications.h"
namespace Base {
	void hooks::StatGetInt(rage::scrNativeCallContext* src) {
		Hash ScriptHashThisFrame = SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME();
		if (ScriptHashThisFrame == "main"_joaat || ScriptHashThisFrame == "freemode"_joaat || ScriptHashThisFrame == "main_persistent"_joaat) {
		}
		else {
			return;
		}
		const auto statHash = src->Arg<Hash>(0);
		const auto outValue = src->Arg<int*>(1);
		const auto p2 = src->Arg<int>(2);
		static uint32_t FrameCount = 0;
		if (FrameCount != MISC::GET_FRAME_COUNT()) {
			g_fiber_manager.on_tick();
			FrameCount = MISC::GET_FRAME_COUNT();
		}
		src->SetReturn(STATS::STAT_GET_INT(statHash, outValue, p2));
	}

	void hooks::NETWORK_SESSION_HOST(rage::scrNativeCallContext* src)
	{
		if (m_rid_data.is_queued) {
			g_pointers->m_join_session_by_info(*g_pointers->m_network, &m_rid_data.session_info, 1, 1 | 2 | 4, nullptr, 0);
			LOG(Info, "JBSI called.");
			m_rid_data.is_queued = false;
			src->SetReturn<int>(TRUE);
		}
		else
		{
			src->SetReturn<BOOL>(NETWORK::NETWORK_SESSION_HOST(src->GetArgument<int>(0), src->GetArgument<int>(1), src->GetArgument<BOOL>(2)));
		}
	}
	void hooks::SET_WARNING_MESSAGE_WITH_HEADER(rage::scrNativeCallContext* src)
	{
		if (auto entry_line = src->Arg<const char*>(1); !strcmp(entry_line, "CTALERT_F_2")) {
			*script_global(4536677).as<int*>() = 0;
			g_notifications->send("Error", "Transaction Error Recieved");
			return;
		}
		HUD::SET_WARNING_MESSAGE_WITH_HEADER(src->Arg<const char*>(0), src->Arg<const char*>(1), src->Arg<int>(2), src->Arg<const char*>(3), src->Arg<BOOL>(4), src->Arg<Any>(5), src->Arg<Any*>(6), src->Arg<Any*>(7), src->Arg<BOOL>(8), src->Arg<Any>(9));
	}

	void hooks::disable_casino_country_restrictions(rage::scrNativeCallContext* src) {
		const auto og{ src->GetReturn<BOOL>() };
		if (g_hooking_features.disable_casino_country_restrictions)
			src->SetReturn<BOOL>(TRUE);
		else
			src->SetReturn(og);
	}
	void hooks::shoot_single_bullet(rage::scrNativeCallContext* src) {
		LOG(Info, "Bullet Shot");
		MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(src->Arg<float>(0), src->Arg<float>(1), src->Arg<float>(2), src->Arg<float>(3), src->Arg<float>(4), src->Arg<float>(5), src->Arg<int>(6), src->Arg<BOOL>(7), src->Arg<Hash>(8), src->Arg<Ped>(9), src->Arg<BOOL>(10), src->Arg<BOOL>(11), src->Arg<float>(12));
	}
	void hooks::set_current_ped_weapon(rage::scrNativeCallContext* context) {
		const auto ped = context->Arg<Ped>(0);
		const auto hash = context->Arg<rage::joaat_t>(1);
		if (g_hooking_features.m_weapons_in_interiors && ped == PLAYER::PLAYER_PED_ID() && hash == rage::joaat("WEAPON_UNARMED"))
			return;

		WEAPON::SET_CURRENT_PED_WEAPON(ped, hash, context->Arg<int>(2));

	}
	void hooks::hud_force_weapon_wheel(rage::scrNativeCallContext* src) {
		if (g_hooking_features.m_weapons_in_interiors && src->Arg<BOOL>(0) == false)
			return;

		HUD::HUD_FORCE_WEAPON_WHEEL(src->Arg<BOOL>(0));
	}
	void hooks::disable_control_action(rage::scrNativeCallContext* context) {
		const auto action{ context->Arg<eControllerInputs>(1) };

		if (g_hooking_features.m_weapons_in_interiors)
		{
			switch (action)
			{
			case eControllerInputs::INPUT_ATTACK:
			case eControllerInputs::INPUT_AIM:
			case eControllerInputs::INPUT_DUCK:
			case eControllerInputs::INPUT_SELECT_WEAPON:
			case eControllerInputs::INPUT_COVER:
			case eControllerInputs::INPUT_TALK:
			case eControllerInputs::INPUT_DETONATE:
			case eControllerInputs::INPUT_WEAPON_SPECIAL:
			case eControllerInputs::INPUT_WEAPON_SPECIAL_TWO:
			case eControllerInputs::INPUT_VEH_AIM:
			case eControllerInputs::INPUT_VEH_ATTACK:
			case eControllerInputs::INPUT_VEH_ATTACK2:
			case eControllerInputs::INPUT_VEH_HEADLIGHT:
			case eControllerInputs::INPUT_VEH_NEXT_RADIO:
			case eControllerInputs::INPUT_VEH_PREV_RADIO:
			case eControllerInputs::INPUT_VEH_NEXT_RADIO_TRACK:
			case eControllerInputs::INPUT_VEH_PREV_RADIO_TRACK:
			case eControllerInputs::INPUT_VEH_RADIO_WHEEL:
			case eControllerInputs::INPUT_VEH_PASSENGER_AIM:
			case eControllerInputs::INPUT_VEH_PASSENGER_ATTACK:
			case eControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON:
			case eControllerInputs::INPUT_VEH_SELECT_PREV_WEAPON:
			case eControllerInputs::INPUT_VEH_ROOF:
			case eControllerInputs::INPUT_VEH_JUMP:
			case eControllerInputs::INPUT_VEH_FLY_ATTACK:
			case eControllerInputs::INPUT_MELEE_ATTACK_LIGHT:
			case eControllerInputs::INPUT_MELEE_ATTACK_HEAVY:
			case eControllerInputs::INPUT_MELEE_ATTACK_ALTERNATE:
			case eControllerInputs::INPUT_MELEE_BLOCK:
			case eControllerInputs::INPUT_SELECT_WEAPON_UNARMED:
			case eControllerInputs::INPUT_SELECT_WEAPON_MELEE:
			case eControllerInputs::INPUT_SELECT_WEAPON_HANDGUN:
			case eControllerInputs::INPUT_SELECT_WEAPON_SHOTGUN:
			case eControllerInputs::INPUT_SELECT_WEAPON_SMG:
			case eControllerInputs::INPUT_SELECT_WEAPON_AUTO_RIFLE:
			case eControllerInputs::INPUT_SELECT_WEAPON_SNIPER:
			case eControllerInputs::INPUT_SELECT_WEAPON_HEAVY:
			case eControllerInputs::INPUT_SELECT_WEAPON_SPECIAL:
			case eControllerInputs::INPUT_ATTACK2:
			case eControllerInputs::INPUT_MELEE_ATTACK1:
			case eControllerInputs::INPUT_MELEE_ATTACK2:
			case eControllerInputs::INPUT_VEH_GUN_LEFT:
			case eControllerInputs::INPUT_VEH_GUN_RIGHT:
			case eControllerInputs::INPUT_VEH_GUN_UP:
			case eControllerInputs::INPUT_VEH_GUN_DOWN:
			case eControllerInputs::INPUT_VEH_HYDRAULICS_CONTROL_TOGGLE:
			case eControllerInputs::INPUT_VEH_MELEE_HOLD:
			case eControllerInputs::INPUT_VEH_MELEE_LEFT:
			case eControllerInputs::INPUT_VEH_MELEE_RIGHT:
			case eControllerInputs::INPUT_VEH_CAR_JUMP:
			case eControllerInputs::INPUT_VEH_ROCKET_BOOST:
			case eControllerInputs::INPUT_VEH_FLY_BOOST:
			case eControllerInputs::INPUT_VEH_PARACHUTE:
			case eControllerInputs::INPUT_VEH_BIKE_WINGS:
			case eControllerInputs::INPUT_VEH_TRANSFORM: return;
			}
		}

		PAD::DISABLE_CONTROL_ACTION(context->Arg<int>(0), (int)action, context->Arg<int>(2));
	}

	void hooks::get_player_name(rage::scrNativeCallContext* src) {
		const auto player_id{ src->Arg<int>(0) };
		if (g_hooking_features.m_streamer_mode.m_enabled) {
			src->SetReturn(std::format("{} {}", g_hooking_features.m_streamer_mode.m_prefix, player_id).c_str());
		}
		else {
			src->SetReturn(PLAYER::GET_PLAYER_NAME(player_id));
		}
	}

	void hooks::network_bail(rage::scrNativeCallContext* src) {
		g_notifications->send("Network", std::format("Bail prevented. Args: {}, {}, {}", src->Arg<int>(0), src->Arg<int>(1), src->Arg<int>(2)));
	}
}