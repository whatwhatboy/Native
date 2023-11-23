#pragma once
#include <JSON/json.hpp>
#include "src/features/utils/utils.h"
#include "src/hooking/hooking.h"

namespace Base::configs::vehicle_gravity {
    void set_vehicle_gravity(uint64_t address, float gravity) {
        caller::call<void>(g_pointers->m_set_vehicle_gravity, address, gravity);
    }
	void save(std::string name) {
        using json = nlohmann::json;

        json data;
        data["value"] = veh_gravity;
        std::string jsonStr = data.dump();

        std::string fileName = name + ".json";
        std::string directoryPath = g_file_utils->get_main_directory() + "\\Configs\\Gravity\\"; // Replace with the actual directory path

        std::string filePath = directoryPath + fileName;

        std::ofstream file(filePath);
        if (file.is_open()) {
            file << jsonStr;
            file.close();
            std::cout << "JSON file created successfully.\n";
        }
        else {
            std::cerr << "Unable to create JSON file.\n";
        }
	}
    void load(std::string name) {
        using json = nlohmann::json;

        std::string fileName = name + ".json";
        std::string directoryPath = g_file_utils->get_main_directory() + "\\Configs\\Gravity\\"; // Replace with the actual directory path

        std::string filePath = directoryPath + fileName;

        std::ifstream file(filePath);
        if (file.is_open()) {
            json data;
            file >> data;
            file.close();

            if (data.contains("value")) {
                float loadedValue = data["value"];
                veh_gravity = loadedValue;
                set_vehicle_gravity(g_utils->get_entity_address(g_utils->vehicle()), loadedValue);
            }
            else {
                std::cerr << "JSON data does not contain expected key 'value'.\n";
            }
        }
        else {
            std::cerr << "Unable to open JSON file.\n";
        }
    }

}