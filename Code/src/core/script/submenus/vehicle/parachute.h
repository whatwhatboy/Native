#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/toggle.h"
#include "src/framework/option_types/icon_button.h"
#include "src/framework/option_types/button.h"

namespace Base::submenus::vehicle {
	namespace objects {
		std::vector<std::pair<std::string, std::string>> models {
			{ "Umbrella", "prop_beach_parasol_03"},
			{ "Rainbow", "sr_prop_specraces_para_s_01" },
			{ "SecuroServ", "imp_prop_impexp_para_s" },
			{ "Orange", "xm_prop_x17_para_sp_s" },
			{ "Colorful", "p_parachute1_s" },
			{ "White", "p_parachute1_mp_dec" },
			{ "Yellow", "prop_v_parachute" },
			{ "Sprunk Umbrella", "prop_parasol_04d" },
			{ "Crashed Jet", "apa_mp_apa_crashed_usaf_01a"},
		};
	}
	bool parachute_override{};
	void parachute() {
		add_option<Framework::toggle>("Override", "", &parachute_override, [] {
			if (parachute_override)
				g_interface->m_flag += 256;
			else
				g_interface->m_flag -= 256;
		});
		draw->seperator("Modifiers");
		draw->submenu_second("Override Model", "override_parachute_model", [] {
			draw->option("override_parachute_model");
			draw->seperator("Models");
			for (int i = 0; i < objects::models.size(); i++) {
				if (rage::joaat(objects::models[i].second) == selected_parachute) {
					add_option<Framework::icon_button>(objects::models[i].first.c_str(), "", "On", [=] {
						selected_parachute = rage::joaat(objects::models[i].second);
					});
				}
				else {
					add_option<Framework::button>(objects::models[i].first.c_str(), "", [=] {
						selected_parachute = rage::joaat(objects::models[i].second);
					});
				}
			}
		});
	}
}
