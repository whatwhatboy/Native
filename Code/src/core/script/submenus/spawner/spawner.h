#pragma once
#include "src/core/script/drawing/drawing.h"
#include "src/framework/submenu_types/regular_submenu.h"
#include "src/framework/option_types/keyboard.h"
namespace Base::submenus::spawner {
	void save(std::string name) {
		std::string MenuFolderPath = "C:\\Native\\Vehicles\\";

		nlohmann::json jsonData;

		int r, g, b;
		VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(g_utils->vehicle(), &r, &g, &b);
		int r2, g2, b2;
		VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(g_utils->vehicle(), &r2, &g2, &b2);
		int hash = ENTITY::GET_ENTITY_MODEL(g_utils->vehicle());
		int primaryColor, secondaryColor;
		VEHICLE::GET_VEHICLE_COLOURS(g_utils->vehicle(), &primaryColor, &secondaryColor);
		int pearl;
		int wheel;
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(g_utils->vehicle(), &pearl, &wheel);

		jsonData["Info"]["Name"] = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(g_utils->vehicle()));
		jsonData["Color"]["R"] = r;
		jsonData["Color"]["G"] = g;
		jsonData["Color"]["B"] = b;
		jsonData["Color"]["R2"] = r2;
		jsonData["Color"]["G2"] = g2;
		jsonData["Color"]["B2"] = b2;
		jsonData["wheel"]["type"] = VEHICLE::GET_VEHICLE_WHEEL_TYPE(g_utils->vehicle());
		jsonData["plate"]["index"] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(g_utils->vehicle());
		jsonData["plate"]["text"] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(g_utils->vehicle());
		jsonData["upgrades"]["livery"] = VEHICLE::GET_VEHICLE_MOD(g_utils->vehicle(), 48);
		jsonData["upgrades"]["spoiler"] = VEHICLE::GET_VEHICLE_MOD(g_utils->vehicle(), 0);
		jsonData["Color1"]["index"] = primaryColor;
		jsonData["Color2"]["index"] = secondaryColor;
		jsonData["Wheel"]["index"] = wheel;
		jsonData["Pearl"]["index"] = pearl;

		for (int i = 0; i < 50; i++) {
			char input2[64];
			sprintf(input2, "index_%i", i);
			jsonData["upgrades"][input2] = VEHICLE::GET_VEHICLE_MOD(g_utils->vehicle(), i);
		}

		std::ofstream outputFile(MenuFolderPath + name + ".json");
		outputFile << jsonData.dump(4);
		outputFile.close();
	}
	void load(std::string name) {
		int modifiedItems{ 0 };
		try {
			std::string MenuFolderPath = "C:\\Native\\Vehicles\\";
			std::ifstream inputFile(MenuFolderPath + name + ".json");
			if (inputFile.is_open()) {
				nlohmann::json jsonData;
				inputFile >> jsonData;
				inputFile.close();


				*script_global(4540731).as<bool*>() = true;
				Hash hash = MISC::GET_HASH_KEY(jsonData["Info"]["Name"].get<std::string>().c_str());
				while (!STREAMING::HAS_MODEL_LOADED(hash))
				{
					STREAMING::REQUEST_MODEL(hash);
					fiber::current()->wait();
				}
				auto heading = ENTITY::GET_ENTITY_HEADING(g_utils->self());
				auto pos = g_utils->coords();
				*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
				auto vehicle = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, heading, true, true, 0);
				*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				auto networkId = NETWORK::VEH_TO_NET(vehicle);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
				Vector3 c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(g_utils->self(), { 0.f, 0.f, 1.0f });
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, jsonData["Color"]["R"], jsonData["Color"]["G"], jsonData["Color"]["B"]);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, jsonData["Color"]["R2"], jsonData["Color"]["G2"], jsonData["Color"]["B2"]);
				VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, jsonData["wheel"]["type"]);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, jsonData["plate"]["index"]);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, jsonData["plate"]["text"].get<std::string>().c_str());
				VEHICLE::SET_VEHICLE_MOD(vehicle, 48, jsonData["upgrades"]["livery"], false);
				VEHICLE::SET_VEHICLE_MOD(vehicle, 0, jsonData["upgrades"]["spoiler"], false);
				VEHICLE::SET_VEHICLE_COLOURS(vehicle, jsonData["Color1"]["index"], jsonData["Color2"]["index"]);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, jsonData["Pearl"]["index"], jsonData["Wheel"]["index"]);
				for (int i = 0; i < 50; i++) {
					char input2[64];
					sprintf(input2, "index_%i", i);
					if (jsonData["upgrades"][input2] != -1) {
						modifiedItems++;
					}
					VEHICLE::SET_VEHICLE_MOD(vehicle, i, jsonData["upgrades"][input2], false);
				}

			}
		}
		catch (const std::exception& e) {
			// logger->Info(e.what());
		}
	}
	void draw_class(const char* name) {
		draw->submenu_second(name, name, [=] {
			for (auto& veh : vehicle_hash_list) {
				if (strcmp(veh.m_class, name) == 0) {
					draw->vehicle_button(std::to_string(veh.hash), veh.name);
				}
			}
		});
	}
	bool has_string_attached(const std::string& str, const std::string& check) {
		std::string strLower = str;
		std::string checkLower = check;
		std::transform(strLower.begin(), strLower.end(), strLower.begin(), [](unsigned char c) {
			return std::tolower(c);
			});
		std::transform(checkLower.begin(), checkLower.end(), checkLower.begin(), [](unsigned char c) {
			return std::tolower(c);
			});

		size_t found = strLower.find(checkLower);
		if (found != std::string::npos) {
			return true;
		}
		else {
			return false;
		}
	}
	void main() {
		if (g_interface->m_click_ui && g_interface->m_selected_tab != Framework::tab::spawner) return;

		draw->submenu("Vehicle", "spawner:vehicle", [] {
			draw->submenu_second("Search", "spawner:vehicle:search", [] {
				static std::string search;
				draw->keyboard("Input", search);
				draw->seperator("Results");
				if (search == "") return;
				for (auto& veh : vehicle_hash_list) {
					if (has_string_attached(g_feature_manager.get_command<button_option>(std::to_string(veh.hash).c_str())->get_name(), search)) {
						draw->option(std::to_string(veh.hash));
					}
				}
			});
			draw->submenu_second("Saved", "spawner:vehicle:saved", [] {
				static std::string save_veh;
				draw->keyboard("Save", save_veh, [] {
					if (GetAsyncKeyState(VK_RETURN) && !Framework::keyboard_open)
						save(save_veh);
				});
				draw->seperator("List");
				for (auto file : g_file_utils->get_all_files_from_dict("C:\\Native\\Vehicles\\")) {
					draw->button(file.name_without_extension, [=] {
						load(file.name_without_extension);
					});
				}
				});
			draw->submenu_second("Settings", "spawner_settings", [] {
				draw->option("spawner_spawn_notify");
				draw->option("spawner_spawn_max");
				draw->option("spawner_spawn_keep_velocity");
				draw->option("spawner_fade");
				draw->option("spawner_delete_last");
				draw->option("spawner_set_engine_on");
				draw->option("spawner_spawn_inside");
			});
			draw->button("Random", [] {
				const auto random{ g_utils->get_random_value_in_range<int>(0, vehicle_hash_list.size()) };
				const auto hash{ vehicle_hash_list[random].hash };
				g_feature_manager.get_command<button_option>(std::to_string(hash).c_str())->m_action();
			});
			draw->seperator("Categories");
			for (auto& i : vehicle_classes) {
				draw_class(i.c_str());
			}

		});

	}
}
