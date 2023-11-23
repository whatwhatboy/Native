#pragma once
#include <JSON/json.hpp>
#include "src/features/feature_manager.h"
#include <fstream>
#include "src/core/logger/logger.h"

namespace Base::config {
    using json = nlohmann::json;
    void save_options_to_file(const std::string& filePath) {
        json j;
        for (const auto& option : g_feature_manager.m_commands) {
            json optionJson;
            auto feature{ g_feature_manager.get_command<toggle_option>(option.first) };
            if (feature != nullptr) {
                optionJson["id"] = feature->m_id;
                optionJson["toggle"] = *feature->m_toggle;
                j.push_back(optionJson);
            }
        }
        for (const auto& option : g_feature_manager.m_commands) {
            json optionJson;
            auto feature{ g_feature_manager.get_command<toggle_with_choose_option>(option.first) };
            if (feature != nullptr) {
                optionJson["id"] = feature->m_id;
                optionJson["toggle"] = *feature->m_toggle;
                optionJson["current_item"] = *feature->m_current_item;
                j.push_back(optionJson);
            }
        }
        for (const auto& option : g_feature_manager.m_commands) {
            auto feature{ g_feature_manager.get_command<toggle_with_float_option>(option.first) };
            if (feature != nullptr) {
                json optionJson;
                optionJson["id"] = feature->m_id;
                optionJson["toggle"] = *feature->m_toggle;
                optionJson["value"] = *feature->m_val;
                j.push_back(optionJson);
            }
        }
        std::ofstream file(filePath);
        if (file.is_open()) {
            file << j.dump(4);
            file.close();
        }
    }
    void load_options_from_json(const std::string& filePath) {
        try {
            std::ifstream file(filePath);
            if (file.is_open()) {
                json j = json::parse(file);
                for (auto& tog : g_feature_manager.m_commands) {
                    for (auto& option : j) {
                        std::string id = option["id"].get<std::string>();
                        auto feature{ g_feature_manager.get_command<toggle_option>(id.c_str()) };
                        if (feature != nullptr) {
                            bool toggle = false;
                            try {
                                toggle = option["toggle"].get<bool>();
                            }
                            catch (const json::exception&) {

                            }
                            if (feature->m_id == id)
                                *feature->m_toggle = toggle;
                        }
                    }
                }
                for (auto& tog : g_feature_manager.m_commands) {
                    for (auto& option : j) {
                        std::string id = option["id"].get<std::string>();
                        auto feature{ g_feature_manager.get_command<toggle_with_choose_option>(id.c_str()) };
                        if (feature != nullptr) {
                            bool toggle = false;
                            int value = 0;
                            if (!option["current_item"].is_null()) {
                                value = option["current_item"].get<int>();
                            }
                            try {
                                toggle = option["toggle"].get<bool>();
                            }
                            catch (const json::exception&) {
                            }
                            if (feature->m_id == id) {
                                *feature->m_toggle = toggle;
                                *feature->m_current_item = value;
                            }
                        }
                    }
                }
                for (auto& tog : g_feature_manager.m_commands) {
                    for (auto& option : j) {
                        std::string id = option["id"].get<std::string>();
                        auto feature{ g_feature_manager.get_command<toggle_with_float_option>(id.c_str()) };
                        if (feature != nullptr) {
                            bool toggle = false;
                            float value = 0;
                            if (!option["value"].is_null()) {
                                value = option["value"].get<float>();
                            }
                            try {
                                toggle = option["toggle"].get<bool>();
                                *feature->m_val = value;
                            }
                            catch (const json::exception&) {
                            }
                            if (feature->m_id == id) {
                                *feature->m_toggle = toggle;
                            }
                        }
                    }
                }
                file.close();
            }
        }
        catch (const json::exception& e) {
        }
        catch (const std::ifstream::failure& e) {
        }
    }
}
