#pragma once
#include "src/natives/natives.h"
#include "math.h"
#include "src/fiber/fiber_helper.h"
#include "caller.h"
#include "src/utility/enum.h"
#include <src/rage/script/HudColor.hpp>
#include "src/hooking/hooking.h"
#include "host.h"
#include <src/rage/network/CMsgTextMessage.hpp>
#include <src/hooking/packets/packet.h>
namespace Base {
	namespace particles_data {
		struct particle {
			const char* name;
			const char* dict;
			const char* asset;
		};
		inline std::vector<ccp> names = {
			"Banknotes",
			"Explosion",
			"Clown Explode",
			"Clown Appears",
			"Trailburst",
			"Burst",
			"Spiral Starburst",
			"Trailburst Spawn",
			"Water Splash",
			"Cartoon",
			"Sphere",
			"Eletricle Crackle",
			"Fire"
		};
		inline std::vector<particle> data = {
			{ "Banknotes", "scr_ornate_heist", "scr_heist_ornate_banknotes" },
			{ "Explosion", "core", "exp_grd_grenade" },
			{ "Clown Explode", "scr_rcbarry2", "scr_exp_clown" },
			{ "Clown Appears", "scr_rcbarry2", "scr_clown_appears" },
			{"Trailburst", "scr_indep_fireworks", "scr_indep_firework_trailburst"},
			{"Burst", "proj_xmas_firework", "scr_firework_xmas_burst_rgw"},
			{"Spiral Starburst", "proj_xmas_firework", "scr_firework_xmas_spiral_burst_rgw"},
			{"Trailburst Spawn", "scr_rcpaparazzo1", "scr_mich4_firework_trailburst_spawn"},
			{"Water Splash", "scr_fbi5a", "scr_fbi5_ped_water_splash"},
			{"Cartoon", "scr_rcbarry2", "muz_clown"},
			{"Sphere", "scr_rcpaparazzo1", "scr_mich4_firework_sparkle_spawn"},
			{"Eletricle Crackle", "core", "ent_amb_elec_crackle"},
			{"Fire", "core", "fire_map"},
		};
	}
	template <typename T>
	class random_value {
	public:
		T m_value;
		T m_min;
		T m_max;
		T get() {
			return m_value;
		}
		void reroll() {
			std::random_device rd;
			static std::mt19937 gen(rd());

			if constexpr (std::is_integral_v<T>) {
				std::uniform_int_distribution<T> dis(m_min, m_max);
				m_value = dis(gen);
			}
			else if constexpr (std::is_floating_point_v<T>) {
				std::uniform_real_distribution<T> dis(m_min, m_max);
				m_value = dis(gen);
			}
			else {
				static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Unsupported type for random_value");
			}
		}
	};

	template <typename t>
	struct num {
		t* value{};
		t min{};
		t max{};
		t step{};
		t per{};
	};
	struct exclude_base {
		bool m_peds{};
		bool m_objects{};
		bool m_vehicles{};
		bool m_pickups{};
	};
	inline int rainbow_speed{ 1 };
	inline std::vector<const char*> all_weapons_name {
		"Antique Cavalry Dagger", "Baseball Bat", "Broken Bottle", "Crowbar", "Unarmed", "Flashlight", "Golf Club", "Hammer", "Hatchet", "Brass Knucles", "Knife", "Machete", "Switchblade", "Nightstick", "Pipe Wrench",
			"Battle Axe", "Pool Cue", "Stone Hatchet", "Pistol", "Pistol Mk II", "Combat Pistol", "AP Pistol", "Stun Gun", "Pistol .50", "SNS Pistol", "SNS Pistol Mk II", "Heavy Pistol", "Vintage Pistol", "Flare Gun", "Marksman Pistol",
			"Heavy Revolver", "Heavy Revolver Mk II", "Double Action Revolver", "Up-n-Atomizer", "Ceramic Pistol", "Navy Revolver", "Perico Pistol", "Stun Gun",
			"Micro SMG", "SMG", "SMG Mk II", "Assault SMG", "Combat PDW", "Machine Pistol", "Mini SMG", "Unholy Hellbringer",
			"Pump Shotgun", "Pump Shotgun Mk II", "Sawed-Off Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "Double Barrel Shotgun", "Sweeper Shotgun", "Combat Shotgun",
			"Assault Rifle", "Assault Rifle Mk II", "Carbine Rifle", "Carbine Rifle Mk II", "Advanced Rifle", "Special Carbine", "Special Carbine Mk II", "Bullpup Rifle", "Bullpup Rifle Mk II", "Compact Rifle", "Military Rifle", "Heavy Rifle", "Service Carbine",
			"MG", "Combat MG", "Combat MG Mk II", "Gusenberg Sweeper",
			"Sniper Rifle", "Heavy Sniper", "Heavy Sniper Mk II", "Marksman Rifle", "Marksman Rifle Mk II", "Precision Rifle",
			"RPG", "Grenade Launcher", "Grenade Launcher Smoke", "Minigun", "Firework Launcher", "Railgun", "Homing Launcher", "Compact Grenade Launcher", "Widowmaker", "Compact EMP Launcher", "Grenade", "BZ Gas", "Molotov Cocktail", "Sticky Bomb", "Proximity Mines",
			"Snowballs", "Pipe Bombs", "Baseball", "Tear Gas", "Flare", "Jerry Can", "Parachute", "Fire Extinguisher", "Hazardous Jerry Can", "Fertilizer Can", "Candy Cane", "Acid Package" };
	inline Hash all_weapons_hash[106] {
		0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,
		0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x57A4368C,
		0x45CD9CF3, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0x5A96BA4,
		0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D1F17E6, 0xC78D71B4, 0xD1D5F52B, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x05FC3C11, 0x0C472FE2,
		0xA914799, 0xC734385A, 0x6A6C02E0, 0x6E7DDDEC, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, 0xDB26713A, 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0xAB564B93,
		0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, 0x34A67B97, 0xFBAB5776, 0xFBAB5776, 0xBA536372, 0x184140A1, 0x6589186A, 0xF7F1E25E
	};
	enum pressed_type {
		pressed,
		released,
		just_pressed,
		just_released,
		disable_pressed,
		disable_released,
		disable_just_pressed,
		disable_just_released,
	};
	enum class request_type {
		model,
		weapon,
		particle
	};
	struct cam_struct {
		Vector3 coords;
		Vector3 rotation;
		Vector3 direction;
	};
	class cam_utils {
	public:
		auto coords() {
			return CAM::GET_GAMEPLAY_CAM_COORD();
		}
		auto rotation() {
			return CAM::GET_GAMEPLAY_CAM_ROT(0);
		}
		auto direction() {
			auto rot{ rotation() };
			return g_math->rotation_to_direction(&rot);
		}
		cam_struct get() {
			return { coords(), rotation(), direction() };
		}
	};
	class utils {
	public:
		cam_utils cam;
		bool key_press(std::uint16_t keycode, bool only_once = false);
		cam_struct get_cam();
		Ped self();
		Player self_id();
		bool aiming();
		Entity weapon();
		bool in_vehicle();
		bool is_model(std::vector<std::string> models, Ped ped = 0);
		Vector3 coords(Entity entity = 0);
		Vehicle vehicle(bool includeLast = false);
		Vehicle vehicle(Player player);
		Entity hybrid();
		Hash get_hash(Entity model);
		BOOL control_pressed(pressed_type flag, eControllerInputs action);
		BOOL control_pressed(pressed_type flag, int action);
		void teleport(Vector3 coords, Entity entity = 0, bool keep_vehicle = true);
	public:
		u64 get_entity_address(Entity entity);
	public:
		GtaThread* find_script_thread(rage::joaat_t hash);
		void sync_money_rewards(std::function<void()> function);
	public:
		bool shooting();
		bool is_enemy(Ped ped);
	public:
		Vector3 weapon_bone_coords(const char* bone);
		Vector3 vehicle_bone_coords(const char* bone);
		Vector3 get_ped_bone_coords(int bone);
		std::pair<Vector3, Vector3> get_tracer_coords();
		std::pair<Vector3, Vector3> get_tracer_coords2();
		void particle_on_entity_bone(Entity entity, int bone, const char* dict, const char* particle, float scale, bool color = false, int r = 255, int g = 255, int b = 255);
		void particle_on_coord(const char* dict, const char* particle, Vector3 coords, float scale, bool color = false, float r = 1.f, float g = 1.f, float b = 1.f);
		void particle_on_self(const char* dict, const char* particle, int bone, float scale, bool color = false, float r = 1.f, float g = 1.f, float b = 1.f);
		void delete_entity(Entity entity);
		void shoot_single_bullet(Hash weapon, Vector3 start, Vector3 end, float damage = 250, float speed = -1.0, Ped owner = 0);
		void shoot_single_bullet_out_of_muzzle(Hash hash, float speed, float damage = 250);
		void fake_shoot();
	public:
		CPed* cped();
		CVehicle* cvehicle();
		CWeaponInfo* cweapon();
	public:
		void timed_function(int delay, std::function<void()> action = [] {});
	public:
		bool has_string_attached(const str& first, const str& check);

		template <typename T>
		T get_random_value_in_range(T min, T max) {
			std::random_device rd;
			std::mt19937 gen(rd());

			if constexpr (std::is_integral_v<T>) {
				std::uniform_int_distribution<T> dis(min, max);
				return dis(gen);
			}
			else if constexpr (std::is_floating_point_v<T>) {
				std::uniform_real_distribution<T> dis(min, max);
				return dis(gen);
			}
			else {
				static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Unsupported type for get_random_value_in_range");
			}
		}
	public:
		std::vector<u32> get_hash_list_from_hash_table(u32 count, u64 table);
	public:
		void add_rainbow(Color* rainbow);
		CNetworkPlayerMgr* get_network_player_mgr();
	public:
		bool get_blip_location(Vector3& location, int sprite, int color = -1);
		Vector3 get_blip_icon();
		bool get_objective_location(Vector3& location);
	public:
		void request_model(Hash hash, std::function<void()> function);
		void request(request_type type, Hash hash, std::function<void()> function);
		void request(request_type type, str name, std::function<void()> function);
		void request_control(Entity entity, std::function<void()> function);
		void fade_screen(int time, std::function<void()> function);
		str get_mocking_str(const str& input);
		void draw_chat_msg(char* msg, const char* player_name, bool is_team);
		Network* network();
		rage::snPlayer* get_player_by_peer_address(uint64_t addr);
		void send_chat_msg(const str& message, bool show = true);
		str get_character_prefix();
	public:
		void make_networked(Vehicle vehicle);
		void max_vehicle(Vehicle vehicle, bool set_colours = true);
		void downgrade_vehicle(Vehicle vehicle);
	public:
		void invoke_transaction(rage::joaat_t category, rage::joaat_t item_hash, rage::joaat_t action_type_hash, int value, int flag);
		rage::joaat_t get_action_for_transaction(str item);
		void add_transaction(str category, str item, int flag = 4);
		void blame_explode(int plr, Vector3 pos, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake);
		void blame_explode(int plr, Vector3 pos, int explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake);
	public:
		int get_open_seat(Vehicle vehicle);
		Vector3 get_vector3(auto offset);

		void set_vector3(auto offset, Vector3 vec);
		void set_vehicle_scale(Vehicle veh, float val);
		bool change_network_object_owner(i32 script_index, CNetGamePlayer* owner);
	};
	inline utils* g_utils;

	inline std::vector<CNetGamePlayer*> get_players() {
		std::vector<CNetGamePlayer*> temp;
		auto mgr{ g_utils->get_network_player_mgr() };
		if (mgr) {
			for (auto& player : mgr->m_player_list) {
				if (player && player->is_valid()) {
					temp.push_back(player);
				}
			}
		}
		return temp;
	}

	class entity_pools {
	private:
		//note need to use replay interface
		auto& get_vehicle_pool() {
			return ***g_pointers->m_vehicle_pool;
		}
		auto& get_object_pool() {
			return **g_pointers->m_object_pool;
		}
		auto& get_ped_pool() {
			return **g_pointers->m_ped_pool;
		}
		auto& get_pickup_pool() {
			return **g_pointers->m_pickup_pool;
		}
	public:
		std::vector<Vehicle> vehicles() {
			std::vector<Vehicle> get;
			for (auto vehicles : get_vehicle_pool()) {
				auto veh = g_pointers->m_pointer_to_handle(vehicles);
				get.push_back(veh);
			}
			return get;
		};
		std::vector<Ped> peds() {
			std::vector<Ped> get;
			for (auto peds : get_ped_pool()) {
				auto ped = g_pointers->m_pointer_to_handle(peds);
				if (ped != PLAYER::PLAYER_PED_ID()) {
					get.push_back(ped);
				}
			}
			return get;
		};
		std::vector<Object> objects() {
			std::vector<Object> get;
			for (auto objects : get_object_pool()) {
				auto object = g_pointers->m_pointer_to_handle(objects);
				get.push_back(object);
			}
			return get;
		};
		std::vector<Pickup> pickups() {
			std::vector<Pickup> get;
			for (auto pickups : get_pickup_pool()) {
				auto pickup{ g_pointers->m_pointer_to_handle(pickups) };
				get.push_back(pickup);
			}
			return get;
		};
		std::vector<Entity> all(bool exclude_vehicles = false, bool exclude_peds = false, bool exclude_objects = false) {
			std::vector<Entity> get;
			if (!exclude_objects) {
				for (auto objects : get_object_pool()) {
					auto object = g_pointers->m_pointer_to_handle(objects);
					get.push_back(object);
				}
			}
			if (!exclude_peds) {
				for (auto peds : get_ped_pool()) {
					auto ped = g_pointers->m_pointer_to_handle(peds);
					if (ped != g_utils->self())
						get.push_back(ped);
				}
			}
			if (!exclude_vehicles) {
				for (auto vehicles : get_vehicle_pool()) {
					auto veh = g_pointers->m_pointer_to_handle(vehicles);
					if (veh != g_utils->vehicle())
						get.push_back(veh);
				}
			}
			return get;
		};
	};
	inline entity_pools* g_pools;

	class LSC {
	public:
		void max(Vehicle vehicle) {
			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
			for (int i = 0; i < 50; i++)
				VEHICLE::SET_VEHICLE_MOD(vehicle, i, MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1), false);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 2));
		}
		void downgrade(Vehicle vehicle) {
			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
			for (int i = 0; i < 50; i++)
				VEHICLE::SET_VEHICLE_MOD(vehicle, i, -1, false);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, MISC::GET_RANDOM_INT_IN_RANGE(0, 2));
		}
	};
	inline LSC g_lsc;

	inline CPed* og_cped;
	inline Color g_rainbow{ 255, 0, 0, 255 };

	class file_utils {
	public:
		struct file {
			std::string full_name;
			std::string name_without_extension;
		};
		std::vector<file> get_all_files_from_dict(std::string dict) {
			std::vector<file> files;

			auto path{ fs::path(dict) };
			if (fs::exists(path) && fs::is_directory(path)) {
				fs::directory_iterator dirIt{ path };
				for (auto&& dirEntry : dirIt) {
					if (dirEntry.is_regular_file() && dirEntry.path().has_filename()) {
						file f;
						f.full_name = dirEntry.path().filename().string();
						f.name_without_extension = dirEntry.path().stem().string();
						files.push_back(f);
					}
				}
			}

			return files;
		}
		std::string get_main_directory() {
			return std::format("C:\\{}", BRANDING);
		}
		bool does_file_exist(const std::string& filename) {
			std::ifstream file(filename);
			return file.good();
		}

	};
	inline file_utils* g_file_utils;

	class game_utils {
	public:
		CPed* m_self_cped;
		Ped m_self;
		Vehicle m_vehicle;
	public:
		void on_tick() {
			
			
		}
	} inline g_game_utils;

	inline game_utils g_game;

	namespace game {
		inline game_utils get_self() {
			return g_game_utils;
		}
	}
}
