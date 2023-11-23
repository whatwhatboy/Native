#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::weapon::impacts {
	void main() {
		draw->submenu_second("Force", "weapon:impacts:force", [] {
			draw->option("force");
			draw->option("force_speed");
		});
		draw->submenu_second("Teleport", "weapon:impacts:teleport", submenus::weapon::impacts::teleport);
		draw->submenu_second("Airstrike", "weapon:impacts:airstrike", [] {
			draw->option("airstrike_gun");
			draw->seperator("Settings");
			draw->option("airstrike_height");
			draw->option("airstrike_damage");
			draw->option("airstrike_speed");
		});
		draw->submenu_second("Paint", "weapon:impacts:paint", [] {
			draw->option("paint_gun");
			draw->seperator("Settings");
			draw->submenu_second("Color", "weapon:impacts:paint:color", [] {
				draw->option("paint_gun_rainbow");
				draw->seperator("Main");
				draw->option("paint_gun_r");
				draw->option("paint_gun_g");
				draw->option("paint_gun_b");
			});
			draw->option("paint_gun_scale");
		});
		draw->submenu_second("Explosive Bullets", "explosive_ammo", [] {
			draw->option("explosive_ammo");
			draw->seperator("Settings");
			draw->option("explosion_blame_random_person");
			draw->option("explosion_invisible");
			draw->option("explosion_sound");
			draw->option("explosion_camera_shake");
			draw->option("explosion_damage");
		});
		draw->option("fire_gun");
		draw->option("grapple_hook");
		draw->option("money_gun");
		draw->option("delete_gun");
		draw->option("freeze_gun");
		draw->option("max_gun");
		draw->option("recolor_gun");
		draw->option("shrink_gun");
		draw->option("repair_gun");
		draw->option("hijack_gun");
		draw->option("create_random_ped");
		draw->option("create_random_vehicle");
	}
}