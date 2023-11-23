#pragma once
#include "src/utility/common/common.h"
#include "base.h"

namespace Base {
    class button_option : public base_option {
    public:
        button_option(std::string mid, std::string mname, std::string mdescription, std::function<void()> maction = {})
            : base_option{ std::move(mid), std::move(mname), std::move(mdescription), std::move(maction), false, eCommandType::button }
        {}
    };

}
