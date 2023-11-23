#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>
#include <src/rage/weapon/CAmmoProjectileInfo.hpp>
#include <src/rage/weapon/CAmmoRocketInfo.hpp>

namespace Base::weapon::modifiers {
	namespace instant_lockon {
		bool enabled = false;
		void init() {
			if (g_utils->cweapon() && g_utils->cped()->m_weapon_manager->m_selected_weapon_hash == 0x63AB0442 && enabled) {
				auto const e = reinterpret_cast<CAmmoProjectileInfo*>(g_utils->cped()->m_weapon_manager->m_weapon_info->m_ammo_info);
				auto const e2 = reinterpret_cast<CAmmoRocketInfo*>(e);
				e2->m_time_before_homing = 0;
			}
		}
		void on_disable() {
			if (g_utils->cweapon() && g_utils->cped()->m_weapon_manager->m_selected_weapon_hash == 0x63AB0442) {
				auto const e = reinterpret_cast<CAmmoProjectileInfo*>(g_utils->cped()->m_weapon_manager->m_weapon_info->m_ammo_info);
				auto const e2 = reinterpret_cast<CAmmoRocketInfo*>(e);
				e2->m_time_before_homing = 2.0f;
			}
		}
	}
	namespace instant_kill {
		bool enabled = false;
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_player_info->m_weapon_damage_mult = 9999;
			g_utils->cped()->m_player_info->m_melee_weapon_damage_mult = 9999;
		}
		void on_disable() {
			g_utils->cped()->m_player_info->m_weapon_damage_mult = 1.0;
			g_utils->cped()->m_player_info->m_melee_weapon_damage_mult = 1.0;
		}
	}
	namespace no_damage {
		bool enabled = false;
		void init() {
			if (!enabled) return;
			g_utils->cped()->m_player_info->m_weapon_damage_mult = 0;
		}
		void on_disable() {
			g_utils->cped()->m_player_info->m_weapon_damage_mult = 1.0;
		}
	}

	namespace shotgun {
		bool enabled = false;
		void init() {
			if (!enabled) return;
			g_utils->cweapon()->m_batch_spread = 0.5f;
			g_utils->cweapon()->m_bullets_in_batch = 30;
			g_utils->cweapon()->m_force = 200.0f;
			g_utils->cweapon()->m_speed = 5000.0f;
			
		}
		void on_disable() {
			g_utils->cweapon()->m_batch_spread = 0.1f;
			g_utils->cweapon()->m_bullets_in_batch = 1;
			g_utils->cweapon()->m_force = 200.0f;
			g_utils->cweapon()->m_speed = 5000.0f;
		}
	}
	namespace weapon_scale {
		template<typename T>
		struct vector4 {
			T x;
			T y;
			T z;
			T w;
		};

		template<typename T>
		struct matrix {
			union {
				struct {
					vector4<T> m_left;
					vector4<T> m_up;
					vector4<T> m_forward;
					vector4<T> m_translation;
				};

				T m_elements[4][4];
			};

			matrix() {}

			T& operator () (int Row, int Col) {
				return m_elements[Row][Col];
			}
		};
		struct base_model_info {
			char _0x0000[24];
			uint32_t m_model;
		};
		struct object {
			char _0x0000[0x20];
			base_model_info* m_model_info;
			char _0x0028[0x20];
			void* m_object_draw_handler;
			char _0x0050[0x10];
			matrix<float> m_matrix;
		};
		bool enabled{ false };
		float scale{ 5 };
		void init() {
			if (!enabled) return;
			Entity weapon{ WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(g_utils->self(), 0) };
			object* objectt{ (object*)g_utils->get_entity_address(weapon) };
			if (objectt) {
				objectt->m_matrix.m_forward.x = scale;
				objectt->m_matrix.m_up.x = scale;
			}
		}
		void on_disable() {

		}
	}

	namespace revolver_spam {
		bool enabled{ false };
		CWeaponInfo* modified_weapon = nullptr;
		float og_value = 0.0f;

		void tick() {
			if (g_utils->cweapon() && enabled) {
				if (modified_weapon != g_utils->cweapon()) {
					if (modified_weapon)
						modified_weapon->m_time_between_shots = og_value;

					modified_weapon = g_utils->cweapon();

					if (g_utils->cweapon()) {
						og_value = g_utils->cweapon()->m_time_between_shots;
						g_utils->cweapon()->m_time_between_shots = 0;
					}
				}
			}
		}
		void on_disable() {
			if (modified_weapon) {
				modified_weapon->m_time_between_shots = og_value;
				modified_weapon = nullptr;
			}
		}
	}
	

}
