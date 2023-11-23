#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>

namespace Base {
	namespace clown_vfx {
		bool enabled{ false };
		void init() {
			if (!enabled) return;
			GRAPHICS::ENABLE_CLOWN_BLOOD_VFX(true);
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
		}
		void on_disable() {
			GRAPHICS::ENABLE_CLOWN_BLOOD_VFX(false);
		}
	}

	namespace invisible_weapon {
		bool enabled{ false };
		void tick() {
			if (!enabled) return;

			ENTITY::SET_ENTITY_VISIBLE(g_utils->weapon(), false, 0);
		}
		void on_disable() {
			ENTITY::SET_ENTITY_VISIBLE(g_utils->weapon(), true, 0);
		}
	}

	namespace mk2_ammo {
		namespace settings {
			std::vector<ccp> type = { "Armor Piercing", "Explosive", "FMJ", "Hollow Point", "Incendiary", "Tracer" };
			int selected{ 0 };
		}
		bool enabled{ false };
		void tick() {
			if (!enabled) return;

			if (g_utils->cweapon() && g_utils->cweapon()->m_ammo_info) {
				switch (settings::selected) {
				case 0:
					g_utils->cweapon()->m_ammo_info->m_ammo_special_type = eAmmoSpecialType::ArmorPiercing;
					break;
				case 1:
					g_utils->cweapon()->m_ammo_info->m_ammo_special_type = eAmmoSpecialType::Explosive;
					break;
				case 2:
					g_utils->cweapon()->m_ammo_info->m_ammo_special_type = eAmmoSpecialType::FMJ;
					break;
				case 3:
					g_utils->cweapon()->m_ammo_info->m_ammo_special_type = eAmmoSpecialType::HollowPoint;
					break;
				case 4:
					g_utils->cped()->m_player_info->m_frame_flags = 1 << 12;
					break;
				case 5:
					g_utils->cweapon()->m_ammo_info->m_ammo_special_type = eAmmoSpecialType::Tracer;
					break;
				}
			}
		}
		void on_disable() {
			g_utils->cweapon()->m_ammo_info->m_ammo_special_type = eAmmoSpecialType::None;
		}
	}

	namespace aim_tracer {
		namespace settings {
			color<float> col{ 255, 0, 0, 255 };
			bool rainbow{ false };
		}
		bool enabled{ false };
		void tick() {
			if (!enabled) return;

			if (settings::rainbow) {
				settings::col = g_rainbow.as<float>();
			}
			if (g_utils->aiming()) {
				GRAPHICS::DRAW_LINE2(g_utils->get_tracer_coords().first, g_utils->get_tracer_coords().second, settings::col.r, settings::col.g, settings::col.b, settings::col.a);
			}
		}
	}
}
