#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/number.h"
std::vector<std::pair<std::string, uint32_t>> explosion_fx_list = {
    {"GRENADE", 0x8CBD7381},
    {"GRENADELAUNCHER", 0x8CBD7381},
    {"STICKYBOMB", 0x6818372E},
    {"MOLOTOV", 0x289C84AB},
    {"ROCKET", 0xC18A7083},
    {"TANKSHELL", 0xC6109DA9},
    {"HI_OCTANE", 0xC18A7083},
    {"CAR", 0x1FDD8CC7},
    {"PLANE", 0x174DDF67},
    {"PETROL_PUMP", 0x5C685140},
    {"BIKE", 0x2E89B6C6},
    {"DIR_STEAM", 0xB096860},
    {"DIR_FLAME", 0x61BEF304},
    {"DIR_WATER_HYDRANT", 0xC9E6266C},
    {"DIR_GAS_CANISTER", 0xDCD1237B},
    {"BOAT", 0x9AE5CE85},
    {"SHIP_DESTROY", 0xC18A7083},
    {"TRUCK", 0x272C2A1C},
    {"BULLET", 0x4A602D1B},
    {"SMOKEGRENADELAUNCHER", 0x1B171B0A},
    {"SMOKEGRENADE", 0xC36F9FF4},
    {"BZGAS", 0xC36F9FF4},
    {"FLARE", 0x4DFE55EF},
    {"GAS_CANISTER", 0x531AE6D7},
    {"EXTINGUISHER", 0x3C212E68},
    {"PROGRAMMABLEAR", 0x4A602D1B},
    {"TRAIN", 0x7DF5D791},
    {"BARREL", 0x26A49BC},
    {"PROPANE", 0x2A8D8114},
    {"BLIMP", 0xBA683EF5},
    {"DIR_FLAME_EXPLODE", 0x61BEF304},
    {"TANKER", 0x6136E279},
    {"PLANE_ROCKET", 0x549AE743},
    {"VEHICLE_BULLET", 0x4A602D1B},
    {"GAS_TANK", 0x2A8D8114},
    {"BIRD_CRAP", 0x8B716982},
    {"RAILGUN", 0x4A602D1B},
    {"BLIMP2", 0x9077376B},
    {"FIREWORK", 0x1499FEF9},
    {"SNOWBALL", 0x4B0245BA},
    {"PROXMINE", 0x6818372E},
    {"VALKYRIE_CANNON", 0x8CBD7381},
    {"AIR_DEFENCE", 0x3C84F30B},
    {"PIPEBOMB", 0x2E3BC2D6},
    {"VEHICLEMINE", 0x8CBD7381},
    {"EXPLOSIVEAMMO", 0x4A602D1B},
    {"APCSHELL", 0xC6109DA9},
    {"BOMB_CLUSTER", 0x7007891E},
    {"BOMB_GAS", 0xAD0A7E5D},
    {"BOMB_INCENDIARY", 0x62F8744D},
    {"BOMB_STANDARD", 0x30A5254A},
    {"TORPEDO", 0xC18A7083},
    {"TORPEDO_UNDERWATER", 0x8D16EE2E},
    {"BOMBUSHKA_CANNON", 0x8CBD7381},
    {"BOMB_CLUSTER_SECONDARY", 0x8CBD7381},
    {"HUNTER_BARRAGE", 0x549AE743},
    {"HUNTER_CANNON", 0x8CBD7381},
    {"ROGUE_CANNON", 0x2E3BC2D6},
    {"MINE_UNDERWATER", 0x4F7CD2DC},
    {"ORBITAL_CANNON", 0x0},
    {"BOMB_STANDARD_WIDE", 0x30A5254A},
    {"EXPLOSIVEAMMO_SHOTGUN", 0x4A602D1B},
    {"OPPRESSOR2_CANNON", 0x3C4CCAAB},
    {"MORTAR_KINETIC", 0x996D8865},
    {"VEHICLEMINE_KINETIC", 0xD0CB2C03},
    {"VEHICLEMINE_EMP", 0xEEC9E329},
    {"VEHICLEMINE_SPIKE", 0xD1C5557C},
    {"VEHICLEMINE_SLICK", 0x98BC33A3},
    {"VEHICLEMINE_TAR", 0x1325B17C},
    {"SCRIPT_DRONE", 0x8CBD7381},
    {"RAYGUN", 0x86AD156C},
    {"BURIEDMINE", 0x25A8CEBF},
    {"SCRIPT_MISSILE", 0xC18A7083},
    {"RCTANK_ROCKET", 0x26CB9D76},
    {"BOMB_WATER", 0xC612E8E3},
    {"BOMB_WATER_SECONDARY", 0xC612E8E3},
    {"EXTINGUISHER", 0x3C212E68},
    {"EXTINGUISHER", 0x3C212E68},
    {"EXTINGUISHER", 0x3C212E68},
    {"EXTINGUISHER", 0x3C212E68},
    {"EXTINGUISHER", 0x3C212E68},
    {"SCRIPT_MISSILE_LARGE", 0xC18A7083},
    {"SUBMARINE_BIG", 0x32775176},
};
namespace Base::submenus::weapon {
	template<typename T, int N>
	constexpr int NUMOF(T(&)[N]) { return N; }
	explosion_data* m_explosion_data_ptr;
	explosion_data m_explosion_data;

	explosion_fx* m_explosion_fx_ptr;
	explosion_fx m_explosion_fx;

    std::vector<const char*> explosion_names{};
	int m_selected_explosion = 0;
    int m_selected_fx = 0;
	explosion_fx* get_explosion_fx(uint32_t hash) {
		for (std::size_t i = 0; i < 53; i++) {
			explosion_fx* fx = &g_pointers->m_explosion_fx[i];
			if (fx->m_name_hash == hash) {
				return fx;
			}
		}

		return nullptr;
	}
	std::size_t get_explosion_fx_entry(uint32_t hash) {
		for (std::size_t i = 0; i < explosion_fx_list.size(); i++) {
			if (explosion_fx_list[i].second == hash) {
				return i;
			}
		}

		return 0;
	}
    bool once{ false };
	void update_editor() {
        
		for (std::size_t i = 0; i < 83; i++) {
			explosion_data* explosion = &g_pointers->m_explosion_data[i];
            explosion_names.push_back(explosion->m_explosion_name);
		}

		m_explosion_data_ptr = &g_pointers->m_explosion_data[m_selected_explosion];
		memcpy(&m_explosion_data, m_explosion_data_ptr, sizeof(explosion_data));

		m_selected_fx = (int)get_explosion_fx_entry(m_explosion_data_ptr->m_vfx_tag_name_hash);

		m_explosion_fx_ptr = get_explosion_fx(m_explosion_data_ptr->m_vfx_tag_name_hash);
		if (m_explosion_fx_ptr) {
			memcpy(&m_explosion_fx, m_explosion_fx_ptr, sizeof(explosion_fx));
		}
        once = true;

	}
	void explosion_data_sub() {
        if (!once) {
            update_editor();
        }
        if (once) {
            add_option<Framework::choose>("Explosion", "", explosion_names, &m_selected_explosion, true, update_editor);
            if (m_explosion_fx_ptr->m_scale) {
                add_option<Framework::number<float>>("Scale", "", &m_explosion_fx_ptr->m_scale, 0, 100, 0.1, 1);
            }

        }
	}
}