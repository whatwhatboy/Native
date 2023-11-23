#pragma once
#include "src/utility/common/common.h"
#include "base.h"

namespace Base {
    class toggle_option : public base_option {
    public:
        toggle_option(std::string mid, std::string mname = "", std::string mdescription = "", bool* mtoggle = nullptr, std::function<void()> minit = [] {}, std::function<void()> mon_disable = [] {})
            : base_option{ std::move(mid), std::move(mname), std::move(mdescription), std::move(minit), true, eCommandType::toggle }, m_toggle(mtoggle), m_on_disable(std::move(mon_disable))
        {}

    public:
        bool* m_toggle;
        std::function<void()> m_init = [] {};
        std::function<void()> m_on_disable = [] {};
    public:
        bool is_toggled() {
            return *m_toggle;
        }
    };
}
