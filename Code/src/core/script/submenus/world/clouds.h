#pragma once
#pragma once
#include "src/core/script/drawing/drawing.h"
#include <src/framework/submenu_types/regular_submenu.h>
#include "src/framework/option_types/number.h"
#include <src/framework/option_types/button.h>

namespace Base::submenus::world {
    using namespace Framework;
    vector_pair<const char*> clouds_list = {
        {"Altostratus", "altostratus"},
        {"Cirrus", "Cirrus"},
        {"Cirrocumulus", "cirrocumulus"},
        {"Clear 01", "Clear 01"},
        {"Cloudy 01", "Cloudy 01"},
        {"Contrails", "Contrails"},
        {"Horizon", "Horizon"},
        {"Horizonband1", "horizonband1"},
        {"Horizonband2", "horizonband2"},
        {"Horizonband3", "horizonband3"},
        {"Horsey", "horsey"},
        {"Nimbus", "Nimbus"},
        {"Puffs", "Puffs"},
        {"RAIN", "RAIN"},
        {"Snowy 01", "Snowy 01"},
        {"Stormy 01", "Stormy 01"},
        {"Stratoscumulus", "stratoscumulus"},
        {"Stripey", "Stripey"},
        {"Shower", "shower"},
        {"Wispy", "Wispy"}
    };
    float transaition_time{ 1 };
    void clouds() {
        draw->number("Transition Time", transaition_time, { 0, 50, 0.1, 1 });
        draw->seperator("List");
        for (auto cloud : clouds_list) {
            draw->button(cloud.first, [=] {
                MISC::LOAD_CLOUD_HAT(cloud.second, transaition_time);
            });
        }
    }
}