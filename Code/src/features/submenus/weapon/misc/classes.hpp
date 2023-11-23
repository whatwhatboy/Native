#pragma once
#include "src/natives/natives.h"

namespace Base {
	class display_weapon_on_back {
	private:
        uint32_t m_hash;
        uint32_t m_unko, m_backup;
        int m_weapon_entity;
        bool m_backcompat;

        int create_object(const char* object_name, UINT32 object_hash, bool visible, bool position) {
            auto coords{ ENTITY::GET_ENTITY_COORDS(g_utils->self(), 1) };

            STREAMING::REQUEST_MODEL(object_hash);
            if (STREAMING::HAS_MODEL_LOADED(object_hash)) {
                int get_memory{ OBJECT::CREATE_OBJECT(object_hash, coords.x + 0, coords.y + 0, coords.z + (m_backcompat ? 3.0f : 0.0f), 1, 1, 1) };
                if (ENTITY::DOES_ENTITY_EXIST(get_memory)) {
                    ENTITY::FREEZE_ENTITY_POSITION(get_memory, position);
                    ENTITY::SET_ENTITY_VISIBLE(get_memory, visible, 1);
                    ENTITY::SET_ENTITY_COORDS(get_memory, coords.x + 3, coords.y + 3, coords.z + 3, false, false, false, false);
                    return get_memory;
                }
            }
            return 0;
        }
        struct vector6 {
            float lx, ly, lz, rx, ry, rz;
        };
        const vector6 m_selected = { 0.075f, -0.15f, -0.02f, 0.0f, 165.0f, 0.0f };
	public:
		bool m_enabled{ false };
		void init();
        void on_disable();
	} inline g_display_weapon_on_back;

    class particles {
    public:
        struct setttings {
            std::vector<ccp> m_type {
                "Muzzle",
                "Bullet Impact"
            };
            int m_type_selected{ 1 };
            struct colorr {
                bool m_enabled{ false };
                color<float> m_value{ 255, 0, 0, 255 };
                bool rainbow{ false };
            } m_color;
            
            float m_scale{ 1 };
            int m_selected_particle{ 0 };
            bool m_always{ false };
        } m_settings;
    public:
        void init();
        bool m_enabled{ false };
    } inline g_particles;

    class missle_launcher {
    public:
        struct settings {
            std::vector<const char*> explosion_type = { "Grenade", "Grenade (Launcher)", "Sticky Bomb", "Molotov", "Rocket", "Tank Shell", "HI Octane", "Car", "Plane", "Gas Pump", "Bike", "Steam", "Flame", "Water", "Gas", "Boat", "Ship Destroy", "Truck", "Bullet", "Smoke", "Smoke 2", "BZ Gas", "Flare",
                "Dust", "Extinguisher", "Unknown", "Train", "Barrel", "Propane", "Blimp", "Flame 2", "Tanker", "Plane Rocket", "Vehicle Bullet", "Gas Tank", "Bird Crap", "Railgun", "Blimp 2", "Firework", "Snowball", "Proximity Mine", "Valkyrie Cannon", "Air Defense", "Pipe Bomb",
                "Vehicle Mine", "Unknown 2", "APC Shell", "Cluster Bomb", "Gas Bomb", "Incendiary Bomb", "Bomb", "Torpedo", "Torpedo (Underwater)", "Bombushka Cannon", "Cluster Bomb 2", "Hunter Barrage", "Hunter Cannon", "Rouge Cannon", "Underwater Mine", "Orbital Cannon",
                "Bomb (Wide)", "Shotgun", "Oppressor MK II", "Kinetic Mortar", "Kinetic Vehicle Mine", "EMP Vehicle Mine", "Spike Vehicle Mine", "Slick Vehicle Mine", "Tar Vehicle Mine", "Script Drone", "Up-n-Atomizer", "Burried Mine", "Script Missle", "RC Tank Rocket",
                "Bomb (Water)", "Bomb (Water 2)", "Steam 2", "Steam 3", "Flash Grenade", "Stun Grenade", "Stun Grenade 2", "Script Missle (Large)", "Submarine (Big)", "EMP Launcher"
            };
            std::int32_t rocket, cam;
            std::uint8_t y_position;
            float meter_val{};
            bool initialized{};
            bool hud{};
            bool vision{};
            bool meter{ true };
            int pos{ 82 };
            bool only_explode_on_impact{};
            bool noclip{ false };
            Vector3 offset;
        } m_settings;
    public:
        void tick();
        void on_disable();
        bool m_enabled{ false };
    } inline g_missle_launcher;

  
    class entity_shooter {
    public:
        struct settings {
            std::vector<ccp> type = { "Normal", "Smooth" };
            int pos{ 1 };
        } m_settings;
        str m_selected_vehicle_name{ "nero2" };
        Vehicle m_vehicle;
    public:
        void tick();
        bool m_enabled{};
    } inline g_entity_shooter;

    class gravity_gun {
    public:
        struct settings {
            float m_zoom{ 25 };
            float m_force{ 5.0 };

            bool m_save_on_unaim{ false };
        } m_settings;
        struct data {
            bool m_has_entity{};
            Entity m_entity{};
        } m_data;
    public:
        void tick();
        bool m_enabled{};
    } inline g_gravity_gun;

}
