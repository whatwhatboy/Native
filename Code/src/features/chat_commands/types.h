#pragma once
#include "src/utility/common/common.h"
#include <vector>

namespace Base {
	struct command {
		Player m_plr;
		std::vector<str> m_args;
	};
    struct command_toggle {
        bool m_enabled{ true };
        bool m_notify;
        bool m_log;
    };
	struct chat_command {
		str m_name{};
		str m_description{};
		str m_command{};
        command_toggle* m_toggle;
	};
	struct color_with_name {
		str m_name{};
		color<int> m_color{};
	};
    inline std::vector<color_with_name> g_colors_with_names {
        { "red", { 255, 0, 0, 255 } },
        { "blue", { 0, 0, 255, 255 } },
        { "green", { 0, 255, 0, 255 } },
        { "yellow", { 255, 255, 0, 255 } },
        { "orange", { 255, 165, 0, 255 } },
        { "purple", { 128, 0, 128, 255 } },
        { "pink", { 255, 192, 203, 255 } },
        { "brown", { 139, 69, 19, 255 } },
        { "gray", { 128, 128, 128, 255 } },
        { "cyan", { 0, 255, 255, 255 } },
        { "lime", { 0, 255, 0, 255 } },
        { "magenta", { 255, 0, 255, 255 } },
        { "teal", { 0, 128, 128, 255 } },
        { "olive", { 128, 128, 0, 255 } },
        { "maroon", { 128, 0, 0, 255 } },
        { "black", { 0, 0, 0, 255 } },
        { "white", { 255, 255, 255, 255 } }
    };
}
