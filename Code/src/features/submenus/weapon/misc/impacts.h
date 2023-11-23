#pragma once
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>
#include <src/fiber/fiber_helper.h>

namespace Base::impacts {
	namespace teleport {
		namespace settings {
			std::vector<const char*> type = { "Smooth", "Rough", "Glide" };
			int typePos{ 0 };
			Vector3 offset{ 0, 0, 0 };
			float delay{ 0 };
		}
		bool enabled{ false };
		float zoom{ 0 };
		Vector3 get_coords;
		void init() {
			if (!enabled) return;
			if (!get_coords.empty() && settings::typePos == 2) {
				auto distance{ SYSTEM::VDIST(get_coords.x, get_coords.y, get_coords.z, g_utils->coords().x, g_utils->coords().y, g_utils->coords().z) };
				if (distance < 3.0f)
					get_coords = { 0, 0, 0 };
				else {
					auto velocity{ (get_coords - g_utils->coords()) * 2 };
					ENTITY::SET_ENTITY_VELOCITY(g_utils->hybrid(), velocity.x, velocity.y, velocity.z);
				}
			}
			g_fiber_pool.queue([&] {
				Vector3 c;
				if (g_math->raycast(c)) {
					auto is_glide{ settings::typePos == 2 };
					if (is_glide) {
						if (g_utils->shooting())
							get_coords = c;
					}
					else {
						if (g_utils->shooting()) {
							std::chrono::milliseconds delayDuration((int)settings::delay * 1000);
							fiber::current()->wait(delayDuration);
							bool is_relative{ settings::typePos == 0 };
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_utils->hybrid(), c.x + settings::offset.x, c.y + settings::offset.y, c.z + settings::offset.z, is_relative, is_relative, is_relative);
						}
					}
				}
			});
		}
	}
	bool create_random_ped_toggle{ false };
	namespace create_random_vehicle {
		bool enabled{ false };
		void init() {
			if (g_utils->shooting() && enabled) {
				Vector3 c;
				if (g_math->raycast(c)) {
					int random{ MISC::GET_RANDOM_INT_IN_RANGE(0, vehicle_hash_list.size()) };
					auto hash{ vehicle_hash_list[random].hash };
					g_fiber_pool.queue([=] {
						*script_global(4540731).as<bool*>() = true;
						while (!STREAMING::HAS_MODEL_LOADED(hash)) {
							STREAMING::REQUEST_MODEL(hash);
							fiber::current()->wait();
						}
						auto heading{ ENTITY::GET_ENTITY_HEADING(g_utils->self()) };
						auto pos{ c };
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
						auto vehicle{ VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, heading, true, true, 0) };
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

						g_utils->make_networked(vehicle);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						
						if (create_random_ped_toggle) {
							auto ped{ PED::CREATE_RANDOM_PED(c.x, c.y, c.z) };
							PED::SET_PED_INTO_VEHICLE(ped, vehicle, -1);
						}
					});
				}

			}
		}
	}
	namespace create_random_ped {
		void init() {
			if (g_utils->shooting() && create_random_ped_toggle) {
				Vector3 c;
				if (g_math->raycast(c)) {
					if (create_random_vehicle::enabled) return;
					PED::CREATE_RANDOM_PED(c.x, c.y, c.z);
				}
			}
		}
	}
	namespace fire {
		namespace settings {
			std::vector<const char*> type = { "Flame", "Molotov" };
			int type_pos{ 0 };
		}
		bool enabled{ false };
		void init() {
			if (g_utils->shooting() && enabled) {
				Vector3 c;
				if (g_math->raycast(c)) {
					switch (settings::type_pos) {
					case 0:
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, eExplosionTag::DIR_FLAME, 1, true, false, 0, 0);
						break;
					case 1:
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, eExplosionTag::MOLOTOV, 1, true, false, 0, 0);
						break;
					}
				}
			}
		}
	}
	namespace airstrike {
		namespace settings {
			float height{ 100 };
			float damage{ 1000 };
			float speed{ -1.00 };
		}
		bool enabled{ false };
		void init() {
			if (g_utils->shooting() && enabled) {
				Vector3 c;
				if (g_math->raycast(c)) {
					auto hash{ rage::joaat("WEAPON_AIRSTRIKE_ROCKET") };
					if (!WEAPON::HAS_WEAPON_ASSET_LOADED(hash))
						WEAPON::REQUEST_WEAPON_ASSET(hash, 31, 0);

					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(c.x, c.y, settings::height, c.x, c.y, 0, settings::damage, 1, hash, g_utils->self(), 1, 0, settings::speed);
				}
			}
		}
	}
	namespace grapple_hook {
		namespace util {
			bool activated{ false };
			Vector3 coords;
		}
		float speed{ 3.0 };
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			if (g_utils->shooting()) {
				Vector3 c;
				if (g_math->raycast(c)) {
					util::coords = { c.x, c.y, c.z };
					util::activated = true;
				}
			}
			if (util::activated) {
				auto distance{ g_math->distance(util::coords, g_utils->coords()) };
				if (distance < 3.0f) {
					if (!g_utils->in_vehicle()) {
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(g_utils->self());
						TASK::CLEAR_PED_SECONDARY_TASK(g_utils->self());
					}
					util::activated = false;
				}
				else {
					auto velocity{ (util::coords - g_utils->coords()) * speed };
					if (!g_utils->in_vehicle())
						TASK::TASK_SKY_DIVE(g_utils->self(), 0);
					ENTITY::SET_ENTITY_VELOCITY(g_utils->hybrid(), velocity.x, velocity.y, velocity.z);
				}
			}
		}
	}
	namespace delete_gun {
		bool enabled{ false };
		void init() {
			if (g_utils->shooting() && enabled) {
				Entity e;
				if (g_math->raycast(e)) {
					ENTITY::SET_ENTITY_COORDS(e, 9999.f, 9999.f, 0, false, false, false, false);
				}
			}
		}
	}
	namespace steal_gun {
		bool enabled{};
		void tick() {
			if (!enabled) return;

			if (g_utils->shooting()) {
				Entity e;
				if (g_math->raycast(e)) {
					if (ENTITY::IS_ENTITY_A_VEHICLE(e))	{
						if (g_utils->change_network_object_owner(e, g_pointers->m_get_net_player(g_utils->self_id()))) {
							if (!VEHICLE::IS_VEHICLE_SEAT_FREE(e, -1, FALSE)) {
								auto ped{ VEHICLE::GET_PED_IN_VEHICLE_SEAT(e, -1, FALSE) };
								TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
							}

							PED::SET_PED_INTO_VEHICLE(g_utils->self(), e, -1);
						}
					}

				}
			}
		}
	}
	namespace freeze {
		std::vector<std::pair<Vehicle, bool>> frozen;
		bool enabled{ false };

		void init() {
			if (g_utils->shooting() && enabled) {
				Entity e;
				if (g_math->raycast(e)) {
					for (auto& f : frozen) {
						if (f.first == e) {
							if (f.second) {
								ENTITY::FREEZE_ENTITY_POSITION(e, false);
								f.second = false;
							}
							else {
								ENTITY::FREEZE_ENTITY_POSITION(e, true);
								f.second = true;
							}
							return;
						}
					}
					frozen.push_back({ e, true });
					ENTITY::FREEZE_ENTITY_POSITION(e, true);
				}
			}
		}
	}
	namespace shrink {
		bool enabled{ false };
		void init() {
			if (g_utils->shooting() && enabled) {
				Entity e;
				if (g_math->raycast(e) && ENTITY::IS_ENTITY_A_PED(e)) {
					PED::SET_PED_CONFIG_FLAG(e, 223, !PED::GET_PED_CONFIG_FLAG(e, 223, 0));
				}
			}
		}
	}
	namespace max {
		bool enabled{ false };
		void init() {
			if (g_utils->shooting() && enabled) {
				Entity e;
				if (g_math->raycast(e)) {
					if (!ENTITY::IS_ENTITY_A_VEHICLE(e)) return;
					VEHICLE::SET_VEHICLE_MOD_KIT(e, 0);
					for (int i = 0; i < 50; i++)
						VEHICLE::SET_VEHICLE_MOD(e, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(e, i) - 1), false);
				}
			}
		}
	}
	namespace repair_gun {
		bool enabled{ false };
		void tick() {
			if (g_utils->shooting() && enabled) {
				Entity e;
				if (g_math->raycast(e)) {
					if (!ENTITY::IS_ENTITY_A_VEHICLE(e)) return;
					VEHICLE::SET_VEHICLE_FIXED(e);
					VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(e);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(e, false);
				}
			}
		}
	}
	namespace recolor {
		bool enabled{ false };
		void init() {
			if (g_utils->shooting() && enabled) {
				Entity e;
				if (g_math->raycast(e)) {
					if (!ENTITY::IS_ENTITY_A_VEHICLE(e)) return;
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(e, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(e, MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
				}
			}
		}
	}
	namespace explosive_ammo {
		namespace settings {
			std::vector<const char*> explosion_type = { "Grenade", "Grenade (Launcher)", "Sticky Bomb", "Molotov", "Rocket", "Tank Shell", "HI Octane", "Car", "Plane", "Gas Pump", "Bike", "Steam", "Flame", "Water", "Gas", "Boat", "Ship Destroy", "Truck", "Bullet", "Smoke", "Smoke 2", "BZ Gas", "Flare",
				"Dust", "Extinguisher", "Unknown", "Train", "Barrel", "Propane", "Blimp", "Flame 2", "Tanker", "Plane Rocket", "Vehicle Bullet", "Gas Tank", "Bird Crap", "Railgun", "Blimp 2", "Firework", "Snowball", "Proximity Mine", "Valkyrie Cannon", "Air Defense", "Pipe Bomb",
				"Vehicle Mine", "Unknown 2", "APC Shell", "Cluster Bomb", "Gas Bomb", "Incendiary Bomb", "Bomb", "Torpedo", "Torpedo (Underwater)", "Bombushka Cannon", "Cluster Bomb 2", "Hunter Barrage", "Hunter Cannon", "Rouge Cannon", "Underwater Mine", "Orbital Cannon",
				"Bomb (Wide)", "Shotgun", "Oppressor MK II", "Kinetic Mortar", "Kinetic Vehicle Mine", "EMP Vehicle Mine", "Spike Vehicle Mine", "Slick Vehicle Mine", "Tar Vehicle Mine", "Script Drone", "Up-n-Atomizer", "Burried Mine", "Script Missle", "RC Tank Rocket",
				"Bomb (Water)", "Bomb (Water 2)", "Steam 2", "Steam 3", "Flash Grenade", "Stun Grenade", "Stun Grenade 2", "Script Missle (Large)", "Submarine (Big)", "EMP Launcher"
			};
			bool invisible{ false };
			bool sound{ true };
			float damage{ 1.0f };
			float camera_shake{ 0.0 };
			bool blame_random_person{ false };
			int explosion{ 0 };
		}
		bool enabled{ false };
		void init() {
			if (g_utils->shooting() && enabled) {
				Vector3 c;
				if (g_math->raycast(c)) {
					if (settings::blame_random_person) {
						g_utils->blame_explode(g_utils->get_random_value_in_range<int>(0, g_utils->get_network_player_mgr()->m_player_count), c, settings::explosion, settings::damage, settings::sound, settings::invisible, settings::camera_shake);
					}
					else {
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, settings::explosion, settings::damage, settings::sound, settings::invisible, settings::camera_shake, false);
					}
				}
			}
		}
	}
	namespace money {
		bool enabled{ false };
		void init() {
			if (g_utils->shooting() && enabled) {
				Vector3 c;
				if (g_math->raycast(c)) {
					g_utils->sync_money_rewards([=] {
						if (!STREAMING::HAS_MODEL_LOADED(289396019))
							STREAMING::REQUEST_MODEL(289396019);

						OBJECT::CREATE_AMBIENT_PICKUP(1704231442, c.x, c.y, c.z, 1, 2500, 289396019, false, true);
					});
					
				}
			}
		}
	}
}
