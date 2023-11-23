#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/hooking/hooking.h"
namespace Base {
	void set_vehicle_gravity(uint64_t address, float gravity) {
        if (address) {
            veh_gravity = gravity;
            caller::call<void>(g_pointers->m_set_vehicle_gravity, address, gravity);
        }
	}
	namespace vehicle_gravity {
		namespace settings {
            std::vector<std::pair<const char*, float>> planet_gravity_pairs = {
             { "Earth", 9.807f },
             { "Moon", 1.62f },
             { "Mercury", 3.7f },
             { "Jupiter", 24.79f },
             { "Mars", 3.711f },
             { "Saturn", 10.44f },
             { "Uranus/Venus", 8.87f },
             { "Neptune", 11.15f },
             { "Sun", 274.0f },
             { "Pluto", 0.62f },
             { "Ceres", 0.28f },
             { "Europa", 1.314f },
             { "Ganymede", 1.428f },
             { "Callisto", 1.235f },
             { "Titan", 1.352f },
             { "Enceladus", 0.113f },
             { "Io", 1.796f },
             { "Triton", 0.779f },
             { "Haumea (Dwarf planet)", 0.44f },
             { "Eris (Dwarf planet)", 0.82f },
             { "Makemake (Dwarf planet)", 0.38f },
             { "Charon (Pluto's moon)", 0.291f },
             { "Oberon (Uranus's moon)", 0.33f },
             { "Tethys (Saturn's moon)", 0.146f },
             { "Eros (Asteroid)", 0.0053f },
             { "Vesta (Asteroid)", 0.025f },
             { "Pallas (Asteroid)", 0.025f },
             { "Phobos (Mars's moon)", 0.0057f },
             { "Deimos (Mars's moon)", 0.003f },
             { "Hygiea (Asteroid)", 0.02f },
             { "Sedna (Dwarf planet)", 0.5f },
             { "Miranda (Uranus's moon)", 0.079f },
             { "Proteus (Neptune's moon)", 0.075f },
             { "Amalthea (Jupiter's moon)", 0.0206f },
             { "Hydra (Pluto's moon)", 0.005f },
             { "Rhea (Saturn's moon)", 0.26f },
             { "Dione (Saturn's moon)", 0.232f },
             { "Iapetus (Saturn's moon)", 0.223f },
             { "Phoebe (Saturn's moon)", 0.00067f },
             { "Hyperion (Saturn's moon)", 0.005f },
             { "Janus (Saturn's moon)", 0.00014f },
             { "Atlas (Saturn's moon)", 0.0015f },
             { "Amphitrite (Asteroid)", 0.006f },
             { "Pandora (Saturn's moon)", 0.0013f },
             { "Prometheus (Saturn's moon)", 0.0006f },
             { "Juno (Asteroid)", 0.0008f },
             { "Iris (Asteroid)", 0.0044f },
             { "Flora (Asteroid)", 0.001f },
             { "Hidalgo (Asteroid)", 0.00001f },
             { "Camilla (Asteroid)", 0.00004f },
             { "Kalliope (Asteroid)", 0.00003f },
             { "Themis (Asteroid)", 0.0007f },
            };
            std::vector<const char*> just_names;
            int selected{ 0 };
            bool global{ false };
		}
		bool enabled{ false };
		void init() {
            if (!enabled) return;
            if (settings::global)
                for (auto vehicles : g_pools->vehicles())
                    set_vehicle_gravity(g_utils->get_entity_address(vehicles), settings::planet_gravity_pairs[settings::selected].second);
            set_vehicle_gravity(g_utils->get_entity_address(g_utils->vehicle()), settings::planet_gravity_pairs[settings::selected].second);
		}
		void on_disable() {
            for (auto vehicles : g_pools->vehicles())
                set_vehicle_gravity(g_utils->get_entity_address(vehicles), 9.807f);
            set_vehicle_gravity(g_utils->get_entity_address(g_utils->vehicle()), 9.807f);
		}
	}
}
