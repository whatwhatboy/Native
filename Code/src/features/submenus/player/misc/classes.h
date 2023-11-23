#pragma once
#include "src/features/utils/utils.h"
namespace Base {
    class super_jump {
    public:
        struct settings {
            struct rolling {
                float m_speed = 25;
                std::vector<const char*> m_flip_type = { "Front", "Back" };
                int m_flip_pos{ 0 };
                bool m_use_super_jump{ true };
            } m_rolling;
            bool m_add_force{ false };
            float m_force{ 1.5 };
            std::vector<const char*> m_type = { "Normal", "Beast", "Roll", "Custom" };
            int m_type_pos{ 0 };
            bool m_infinite_jump{ true };
            bool m_instant_jump{ false };
            float m_max_jump_distance{ 0.0f };
            float m_jump_forward_force{ 0.0f };
            float m_jump_upward_force{ 0.0f };
            float m_push_down_force{ 5.0 };
        } m_settings;

        bool m_enabled{ false };
        void init();
        void on_disable();
    } inline g_superjump;

    class noclip {
    public:
        struct settings {
            float m_speed{ 2.5f };
            num<float> m_speed_num{ &m_speed, 0, 25, 0.1, 1 };
            float m_interior_speed{ 2.5 }; bool m_change_speed;
            std::vector<const char*> m_types = { "Normal", "Walking" };
            int m_type_pos{ 1 };
            bool m_transparent{ false };
            float m_transparent_value{ 190 };
            bool m_spin{ false };
            float m_spin_speed{ 10.0f };
            bool m_set_rotation{ false };
        } m_settings;
        bool m_enabled{ false };
        void init();
    } inline g_noclip;

    class spinbot {
    public:
        struct settings {
            float m_speed{ 10.0f };

            bool m_first_rotation{ true };
            std::vector<ccp> m_direction = { "Left", "Right" };
            int m_direction_pos{ 0 };

            bool m_second_rotation{ false };
            std::vector<ccp> m_direction_2 = { "Front", "Back" };
            int m_direction_pos2{ 0 };
        } m_settings;
        bool m_enabled{ false };
        void init();
    } inline g_spinbot;

    class forcefield {
    public:
        struct settings {
            float m_radius{ 8 };
            bool m_exclude_vehicles, m_exclude_peds, m_exclude_objects;
            float m_force_multiplier{ 0.5 };

            bool m_show_radius{};

            std::vector<ccp> m_type{ "Push", "Pull" };
            int m_type_pos{ 0 };
        } m_settings;
        bool m_enabled{ false };
        void move(Entity vehicle, bool pull);
        void init();
    } inline g_forcefield;

    class fov {
    public:
        struct settings {
            float m_value{ 50.f };
            num<float> m_value_num{ &m_value, 0, 130, 0.1, 1 };
        } m_settings;
        bool m_enabled{ false };
        void init();
        void on_disable();
    } inline g_fov;

    class regeneration {
    public:
        struct settings {
            bool m_health{ false };
            bool m_armor{ false };
            float m_amount{ 10 };
            float m_delay{ 550 };
            bool m_in_cover{ false };
        } m_settings;
        bool m_enabled{ false };
        void init();
    } inline g_regeneration;

    class godmode {
    private:
        void reset() {
            if (g_utils->cped()->m_damage_bits != 0)
                g_utils->cped()->m_damage_bits = 0;
        }
    public:
        struct settings {
            std::vector<const char*> m_type = { "Normal", "Set", "Native", "Semi-Legit" };
            int m_position{ 0 };
        } m_settings;

        bool m_enabled{};
        void init();
        void on_disable();
    } inline g_self_godmode;

    class fast_respawn {
    public:
        bool m_enabled{};
        void init();
    } inline g_fast_respawn;

    class tron_loop {
    private:
        void set_tron_index(int index, int gender) {
            if (gender == 0) {
                PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), 8, 15, 0, 0);
                PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), 11, 178, index, 0);
                PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), 6, 55, index, 0);
                PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), 4, 77, index, 0);
                PED::SET_PED_PROP_INDEX(g_utils->self(), 0, 91, index, 0);
            }
            if (gender == 1) {
                PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), 8, 6, 0, 0);
                PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), 11, 180, index, 0);
                PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), 6, 58, index, 0);
                PED::SET_PED_COMPONENT_VARIATION(g_utils->self(), 4, 79, index, 0);
                PED::SET_PED_PROP_INDEX(g_utils->self(), 0, 90, index, 0);
            }
        }
        int m_selected{ 0 };
    public:
        bool m_enabled{ false };
        void init();
    } inline g_tron_loop;

    class magnet {
    public:
        struct settings {
            float m_main_velocity{ 0.3 };

            exclude_base m_excludes;

            Vector3 m_offset;
            Vector3 m_velocity_offset;
        } m_settings;
    public:
        bool m_enabled{};
        void init();
    } inline g_magnet;

    class handtrails {
    public:
        struct settings {
            std::vector<ccp> m_type = { "Normal", "Sphere", "Sphere (Less Fuzzy)" };
            int m_selected{ 0 };

            color<float> m_color{ 255, 0, 0, 255 };
            bool m_rainbow{};

            float m_scale{ 0.2f };
        } m_settings;
    public:
        void tick();
        bool m_enabled{};
    } inline g_handtrails;

    class iron_man {
    public:
        void tick();
        void on_disable();
        bool m_enabled{};
    } inline g_ironman;
}
