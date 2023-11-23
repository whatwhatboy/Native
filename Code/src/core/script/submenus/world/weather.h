#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "src/framework/option_types/number.h"
#include <src/framework/option_types/button.h>
#include <src/framework/option_types/choose.h>

namespace Base::submenus::world {
    using namespace Framework;
    vector_pair<const char*> weather_types = {
         {"Clear", "CLEAR"},
         {"Extra Sunny", "EXTRASUNNY"},
         {"Clouds", "CLOUDS"},
         {"Overcast", "OVERCAST"},
         {"Rain", "RAIN"},
         {"Clearing", "CLEARING"},
         {"Thunder", "THUNDER"},
         {"Smog", "SMOG"},
         {"Foggy", "FOGGY"},
         {"Christmas", "XMAS"},
         {"Snow", "SNOW"},
         {"Light Snow", "SNOWLIGHT"},
         {"Blizzard", "BLIZZARD"},
         {"Halloween", "HALLOWEEN"},
         {"Neutral", "NEUTRAL"}
    };
    std::vector<const char*> names = {
        "Clear",
        "Extra Sunny",
        "Clouds",
        "Overcast",
        "Rain",
        "Clearing",
        "Thunder",
        "Smog",
        "Foggy",
        "Christmas",
        "Snow",
        "Light Snow",
        "Blizzard",
        "Halloween",
        "Neutral"
    };
    int get_from_hash(Hash hash) {
        for (int i = 0; i < weather_types.size(); ++i)
            if (rage::joaat(weather_types[i].second) == hash)
                return i;
    }
    float time_speed{ 1 };
    void weather() {
        static int selected{};
        static int selected2{};
        static float percentage{};
        draw->submenu_second("Mixing", "weather_mixing", [=] {
            Hash first;
            Hash second;
            float percentage_get{};
            MISC::GET_CURR_WEATHER_STATE(&first, &second, &percentage);
            selected = get_from_hash(first);
            selected2 = get_from_hash(second);
            }, [] {
            draw->choose("First", names, &selected);
            draw->choose("Second", names, &selected2);
            draw->number("Percentage", percentage, { 0, 100, 1, 0 });
            draw->button("Apply", [=] {
                MISC::SET_CURR_WEATHER_STATE(rage::joaat(weather_types[selected].second), rage::joaat(weather_types[selected2].second), percentage);
                });
        });
        draw->option("lightning");
        draw->number("Time", time_speed, { 0, 100, 0.1, 1 });
        draw->seperator("List");
        for (auto type : weather_types) {
            draw->button(type.first, [=] {
                MISC::SET_WEATHER_TYPE_OVERTIME_PERSIST(type.second, time_speed);
            });
        }
    }
}
