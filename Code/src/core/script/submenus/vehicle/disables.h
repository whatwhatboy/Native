#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::vehicle {
	void disables() {
		draw->option("disable_lockon");
		draw->option("disable_brake_lights");
		draw->option("disable_oil_leaking");
		draw->option("disable_petrol_leaking");
		draw->option("disable_vehicle_fire");
		draw->option("disable_wheel_deformation");
		draw->option("disable_pad_effects");
		draw->option("disable_extra_trick_forces");
		draw->option("disable_vehicle_gravity");
		draw->option("disable_deformation");
		draw->option("disable_glass_breaking");
		draw->option("disable_parts_breaking_off");
		draw->option("disable_detachable_bumpers");
		draw->option("disable_weapon_blades");
		draw->option("disable_bike_wheelie");
		draw->option("disable_sirens");
		draw->option("disable_turret_movement");
		draw->option("disable_slipstream");
		draw->option("disable_neon_lights");
	}
}
