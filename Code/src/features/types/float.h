#pragma once
#include "src/utility/common/common.h"
#include "base.h"

namespace Base {
    class float_option : public base_option {
    public:
        float_option(std::string mid, std::string mname = "", std::string mdescription = "", float* mval = nullptr, float mmin = 0, float mmax = 0, float mstep = 0, float mprecision = 0, bool mactive_on_horizontal = false, std::function<void()> maction = {})
            : base_option{ std::move(mid), std::move(mname), std::move(mdescription), std::move(maction), false, eCommandType::number }, m_val(mval), m_min(mmin), m_max(mmax), m_step(mstep), m_precision(mprecision), m_active_on_horizontal(mactive_on_horizontal)
        {}
        float_option(std::string mid, std::string mname = "", float* mval = nullptr, float mmin = 0, float mmax = 0, float mstep = 0, float mprecision = 0, bool mactive_on_horizontal = false, std::function<void()> maction = {})
            : base_option{ std::move(mid), std::move(mname), "", std::move(maction), false, eCommandType::number }, m_val(mval), m_min(mmin), m_max(mmax), m_step(mstep), m_precision(mprecision), m_active_on_horizontal(mactive_on_horizontal)
        {}
    public:
        float* m_val;
        float m_min;
        float m_max;
        float m_step;
        float m_precision;
        bool m_active_on_horizontal{ false };
    };
}
