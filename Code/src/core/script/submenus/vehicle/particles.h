#include "src/core/script/drawing/drawing.h"
#include "src/features/submenus/vehicle/misc/particles.h"
#include "src/framework/option_types/toggle.h"
#include "src/framework/option_types/icon_button.h"
namespace Base::submenus::vehicle {
	const char* names[5] = { "Front Left Wheel", "Front Right Wheel", "Back Left Wheel", "Back Right Wheel", "Exhaust" };
	bool first_enter{ true };
	void particles() {
		if (first_enter) {
			g_feature_manager.add<toggle_option>("vehicle_particles", "Enabled", "", &vehicle_particles::enabled, vehicle_particles::init);
			first_enter = false;
		}
		draw->option("vehicle_particles");
		draw->seperator("Parts");
		for (int i = 0; i < 5; i++) {
			draw->submenu_second(names[i], names[i], [=] {
				add_option<Framework::toggle>("Enabled", "", &vehicle_particles::settings::selected_enabled[i]);
				draw->number("Scale", vehicle_particles::settings::scale[i], { 0, 100, 0.01, 2 });
				draw->submenu_second("Color", "vehicle_particles:color", [i] {
					add_option<Framework::toggle>("Enabled", "", &vehicle_particles::settings::color_enabled[i]);
					draw->seperator("Main");
					add_option<Framework::toggle>("Rainbow", "", &vehicle_particles::settings::rainbow[i]);
					add_option<Framework::number<int>>("R", "", &vehicle_particles::settings::color[i].r, 0, 255, 1, 0);
					add_option<Framework::number<int>>("G", "", &vehicle_particles::settings::color[i].g, 0, 255, 1, 0);
					add_option<Framework::number<int>>("B", "", &vehicle_particles::settings::color[i].b, 0, 255, 1, 0);
				});
				draw->seperator("Settings");
				for (int j = 0; j < particles_data::data.size(); j++) {
					if (particles_data::data[j].name == particles_data::names[vehicle_particles::settings::selected[i]]) {
						add_option<Framework::icon_button>(particles_data::data[j].name, "", "On", [=] {
							vehicle_particles::settings::selected[i] = j;
						});
					}
					else {
						add_option<Framework::button>(particles_data::data[j].name, "", [=] {
							vehicle_particles::settings::selected[i] = j;
						});
					}
				}
			});
		}
	}
}
