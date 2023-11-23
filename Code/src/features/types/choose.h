#pragma once
#include "src/utility/common/common.h"

namespace Base {
    class choose_option : public base_option {
    public:
        choose_option(std::string mid, std::string mname = "", std::string mdescription = "", std::vector<const char*> vec = {}, int* mcurrent_item = nullptr, bool mactive_on_horizontal = true, std::function<void()> minit = {})
            : base_option{ std::move(mid), std::move(mname), std::move(mdescription), std::move(minit), false, eCommandType::choose }, m_items(vec), m_current_item(mcurrent_item), m_active_on_horizontal(mactive_on_horizontal)
        {}
        choose_option(std::string mid, std::string mname = "", std::vector<const char*> vec = {}, int* mcurrent_item = nullptr, bool mactive_on_horizontal = true, std::function<void()> minit = {})
            : base_option{ std::move(mid), std::move(mname), "", std::move(minit), false, eCommandType::choose }, m_items(vec), m_current_item(mcurrent_item), m_active_on_horizontal(mactive_on_horizontal)
        {}
    public:
        std::vector<const char*> m_items;
        int* m_current_item;
        bool m_active_on_horizontal{ false };
    };
}
