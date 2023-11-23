#pragma once
#include "src/core/script/drawing/drawing.h"
#include "noclip.h"
#include "super_jump.h"
#include "ragdoll.h"

namespace Base::submenus::self {
	void movement() {
		draw->submenu_second("No Clip", "self:movement:noclip", submenus::movement::noclip);
		draw->submenu_second("Super Jump", "self:movement:super_jump", submenus::movement::super_jump);
		draw->submenu_second("Editor", "self:editor", [] {
			draw->submenu_second("Jump", "self:editor:jump", [] {
				draw->option("beast_jump");
				draw->option("dive_jump");
				draw->option("shake_camera_jump");
				draw->option("land_jump");
				draw->option("super_jump_editor");
			});
			draw->submenu_second("Fall", "self:editor:fall", [] {
				draw->option("beast_landing");
				draw->option("dive_landing");
				draw->option("shake_camera_landing");
				draw->option("land");
				draw->option("super_landing");
			});
		});
		draw->submenu_second("Ragdoll", "self_ragdoll", submenus::self::ragdoll);
		draw->submenu_second("Superman", "superman", [] {
			draw->option("superman");
			draw->seperator("Settings");
			draw->option("rise_on_collision");
			draw->option("forward_force");
			draw->option("upward_force");
		});
		draw->option("slide_run");
		draw->option("freeze_self");
		inline_item
		draw->option("forced_jump");
		inline_item
		draw->option("swimming");
		draw->option("walk_underwater");
		draw->option("walk_on_air");
		inline_item
		draw->option("walk_on_water");
		draw->option("backward_walking");
		draw->option("tennis_mode");
		draw->option("run_speed");
		draw->option("swim_speed");
	}
}
