#pragma once
#include "src/utility/common/common.h"
#include "base.h"

namespace Base {
    class toggle_with_float_option : public base_option {
    public:
        toggle_with_float_option(std::string mid, std::string mname = "", std::string mdescription = "", bool* mtoggle = nullptr, float* mval = nullptr, float mmin = 0, float mmax = 0, float mstep = 0, float mprecision = 0, bool mactive_on_horizontal = false, std::function<void()> maction = [] {}, std::function<void()> mon_disable = [] {})
            : base_option{ std::move(mid), std::move(mname), std::move(mdescription), std::move(maction), true, eCommandType::toggle_with_number }, m_toggle(mtoggle), m_val(mval), m_min(mmin), m_max(mmax), m_step(mstep), m_precision(mprecision), m_active_on_horizontal(mactive_on_horizontal), m_on_disable(std::move(mon_disable))
        {}
        toggle_with_float_option(std::string mid, std::string mname = "", bool* mtoggle = nullptr, float* mval = nullptr, float mmin = 0, float mmax = 0, float mstep = 0, float mprecision = 0, bool mactive_on_horizontal = false, std::function<void()> maction = [] {}, std::function<void()> mon_disable = [] {})
            : base_option{ std::move(mid), std::move(mname), "", std::move(maction), true, eCommandType::toggle_with_number }, m_toggle(mtoggle), m_val(mval), m_min(mmin), m_max(mmax), m_step(mstep), m_precision(mprecision), m_active_on_horizontal(mactive_on_horizontal), m_on_disable(std::move(mon_disable))
        {}

        toggle_with_float_option(std::string mid, std::string mname = "", bool* mtoggle = nullptr, num<float> num = {}, bool mactive_on_horizontal = false, std::function<void()> maction = [] {}, std::function<void()> mon_disable = [] {})
            :
            base_option{ std::move(mid), std::move(mname), "", std::move(maction), true, eCommandType::toggle_with_number },
            m_toggle(mtoggle), m_val(num.value), m_min(num.min), m_max(num.max), m_step(num.step), m_precision(num.per), m_active_on_horizontal(mactive_on_horizontal), m_on_disable(std::move(mon_disable))
        {}
        toggle_with_float_option(std::string mid, std::string mname = "", std::string mdescription = "", bool* mtoggle = nullptr, num<float> num = {}, bool mactive_on_horizontal = false, std::function<void()> maction = [] {}, std::function<void()> mon_disable = [] {})
            :
            base_option{ std::move(mid), std::move(mname), std::move(mdescription), std::move(maction), true, eCommandType::toggle_with_number },
            m_toggle(mtoggle), m_val(num.value), m_min(num.min), m_max(num.max), m_step(num.step), m_precision(num.per), m_active_on_horizontal(mactive_on_horizontal), m_on_disable(std::move(mon_disable))
        {}
    public:
        bool* m_toggle;
        float* m_val;
        float m_min;
        float m_max;
        float m_step;
        float m_precision;
        bool m_active_on_horizontal{ false };
        std::function<void()> m_on_disable = [] {};
    public:
        bool is_toggled() {
            return *m_toggle;
        }
    };
}
