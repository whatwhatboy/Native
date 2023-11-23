#pragma once
#include "src/utility/common/common.h"
#include "base.h"

namespace Base {
    class keyboard_option : public base_option {
    public:
        keyboard_option(str mid, str mname = "", str mdescription = "", str* mstr = nullptr, std::function<void()> minit = [] {})
            : base_option{ std::move(mid), std::move(mname), std::move(mdescription), std::move(minit), true, eCommandType::keyboard }, m_str(mstr)
        {}
    public:
        str* m_str;
    public:
        const char* get_data() {
            return m_str->c_str();
        }
    };
}
