#pragma once
#include <string>

namespace Base {
    enum class eCommandType {
        toggle,
        toggle_with_number,
        toggle_with_choose,
        number,
        choose,
        button,
        keyboard
    };
    class base_option {
    public:
        str m_id{};
        str m_name{};
        str m_description{};
        std::function<void()> m_action{};
        bool m_looped{ false };
        eCommandType m_type{};
    public:
        const char* get_id() const {
            return m_id.c_str();
        }
        str get_name() const {
            return m_name.c_str();
        }
        const char* get_description() const {
            return m_description.c_str();
        }
        bool is_type(eCommandType type) const {
            return type == m_type;
        }
    };
}
