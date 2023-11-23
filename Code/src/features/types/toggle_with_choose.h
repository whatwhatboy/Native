#pragma once
#include "src/utility/common/common.h"
#include "base.h"

namespace Base {
    class toggle_with_choose_option : public base_option {
    public:
        toggle_with_choose_option(std::string mid, std::string mname, std::string mdescription, bool* mtoggle, std::vector<const char*> mitems, int* mcurrent_item, bool mactive_on_horizontal, std::function<void()> minit = [] {}, std::function<void()> mon_disable = {})
            : base_option{ std::move(mid), std::move(mname), std::move(mdescription), std::move(minit), true, eCommandType::toggle_with_choose}, m_toggle(mtoggle), m_items(mitems), m_current_item(mcurrent_item), m_active_on_horizontal(mactive_on_horizontal), m_on_disable(std::move(mon_disable))
        {}
        toggle_with_choose_option(std::string mid, std::string mname, bool* mtoggle, std::vector<const char*> mitems, int* mcurrent_item, bool mactive_on_horizontal = false, std::function<void()> minit = [] {}, std::function<void()> mon_disable = {})
            : base_option{ std::move(mid), std::move(mname), "", std::move(minit), true, eCommandType::toggle_with_choose}, m_toggle(mtoggle), m_items(mitems), m_current_item(mcurrent_item), m_active_on_horizontal(mactive_on_horizontal), m_on_disable(std::move(mon_disable))
        {}
    public:
        bool* m_toggle;
        std::vector<const char*> m_items;
        int* m_current_item;
        bool m_active_on_horizontal{ false };
        std::function<void()> m_on_disable = [] {};
    public:
        bool is_toggled() {
            return *m_toggle;
        }
    };
}
