#pragma once
#include "src/features/utils/utils.h"
#include <src/utility/enum.h>
#include "classes.hpp"
namespace Base {
    void missle_launcher::tick() {
		if (!m_enabled) return;
		
		if (g_utils->shooting()) {
			if (!m_settings.initialized)
				m_settings.initialized = true;
		}

		if (m_settings.initialized) {
			if (ENTITY::DOES_ENTITY_EXIST(m_settings.rocket)) {
				auto rotation{ CAM::GET_GAMEPLAY_CAM_ROT(0) };
				CAM::SET_CAM_ROT(m_settings.cam, rotation.x, rotation.y, rotation.z, 0);
				ENTITY::SET_ENTITY_ROTATION(m_settings.rocket, rotation.x, rotation.y, rotation.z, 0, TRUE);
				auto rocket_pos{ ENTITY::GET_ENTITY_COORDS(m_settings.rocket, FALSE) };
				auto coords{ rocket_pos + (g_math->rotation_to_direction(rotation) * .8f) };
				auto cam_doord{ CAM::GET_CAM_COORD(m_settings.cam) };
				auto ped{ g_utils->self() };
				auto start_dist{ std::distance(&cam_doord, &rocket_pos) };
				auto cam_rot{ CAM::GET_CAM_ROT(m_settings.cam, 0) };
				auto cam_direction{ g_math->rotation_to_direction(cam_rot) };
				auto cam_direction_offset{ cam_direction * 2.50 };



				if (m_settings.noclip) {
					if (g_utils->key_press(0x57) || g_utils->control_pressed(pressed, 32)) {
						auto pos{ rocket_pos + cam_direction_offset };
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(m_settings.rocket, pos.x, pos.y, pos.z, false, false, false);
					}
				}
				else {
					ENTITY::SET_ENTITY_COORDS(m_settings.rocket, coords.x, coords.y, coords.z, FALSE, FALSE, FALSE, FALSE);
				}

				HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
				PLAYER::DISABLE_PLAYER_FIRING(g_utils->self(), TRUE);
				ENTITY::FREEZE_ENTITY_POSITION(g_utils->self(), TRUE);
				HUD::HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME();

				if (m_settings.hud) {
					GRAPHICS::DRAW_RECT(0.5f, 0.5f - 0.025f, 0.050f, 0.002f, 255, 255, 255, 255, FALSE);
					GRAPHICS::DRAW_RECT(0.5f, 0.5f + 0.025f, 0.050f, 0.002f, 255, 255, 255, 255, FALSE);
					GRAPHICS::DRAW_RECT(0.5f - 0.025f, 0.5f, 0.002f, 0.050f, 255, 255, 255, 255, FALSE);
					GRAPHICS::DRAW_RECT(0.5f + 0.025f, 0.5f, 0.002f, 0.050f, 255, 255, 255, 255, FALSE);
					GRAPHICS::DRAW_RECT(0.5f + 0.05f, 0.5f, 0.050f, 0.002f, 255, 255, 255, 255, FALSE);
					GRAPHICS::DRAW_RECT(0.5f - 0.05f, 0.5f, 0.050f, 0.002f, 255, 255, 255, 255, FALSE);
					GRAPHICS::DRAW_RECT(0.5f, 0.5f + 0.05f, 0.002f, 0.050f, 255, 255, 255, 255, FALSE);
					GRAPHICS::DRAW_RECT(0.5f, 0.5f - 0.05f, 0.002f, 0.050f, 255, 255, 255, 255, FALSE);
				}
				if (m_settings.vision) {
					GRAPHICS::SET_TIMECYCLE_MODIFIER("CAMERA_secuirity");
				}
				if (m_settings.meter) {
					GRAPHICS::DRAW_RECT(0.25f, 0.5f, 0.03f, 0.5f, 255, 255, 255, 255, FALSE);
				}
				static auto tick_count{ GetTickCount() };
				if (GetTickCount() - tick_count >= 250) {
					m_settings.meter_val -= .01f; m_settings.y_position -= 4;
					tick_count = GetTickCount();
				}
				if (m_settings.meter) {
					GRAPHICS::DRAW_RECT(0.25f, 0.75f - (m_settings.meter_val / 2.f), 0.03f, m_settings.meter_val, 255, m_settings.y_position, 0, 255, FALSE);
				}

				float groundz;
				MISC::GET_GROUND_Z_FOR_3D_COORD(rocket_pos.x, rocket_pos.y, rocket_pos.z, &groundz, FALSE, FALSE);
				if (m_settings.only_explode_on_impact) {
					if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(m_settings.rocket) || (std::abs(rocket_pos.z - groundz) < .5f)) {
						FIRE::ADD_EXPLOSION(rocket_pos.x, rocket_pos.y, rocket_pos.z, m_settings.pos, 1000.f, TRUE, FALSE, .4f, FALSE);
						g_utils->delete_entity(m_settings.rocket);
						m_settings.rocket = 0;
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 0);
						CAM::RENDER_SCRIPT_CAMS(FALSE, TRUE, 700, TRUE, TRUE, NULL);
						CAM::DESTROY_CAM(m_settings.cam, TRUE);
						GRAPHICS::SET_TIMECYCLE_MODIFIER("DEFAULT");
						ENTITY::FREEZE_ENTITY_POSITION(g_utils->self(), FALSE);
						m_settings.initialized = false;

					}
				}
				else {
					if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(m_settings.rocket) || (std::abs(rocket_pos.z - groundz) < .5f) || m_settings.meter_val <= 0.01) {
						FIRE::ADD_EXPLOSION(rocket_pos.x, rocket_pos.y, rocket_pos.z, m_settings.pos, 1000.f, TRUE, FALSE, .4f, FALSE);
						g_utils->delete_entity(m_settings.rocket);
						m_settings.rocket = 0;
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 0);
						CAM::RENDER_SCRIPT_CAMS(FALSE, TRUE, 700, TRUE, TRUE, NULL);
						CAM::DESTROY_CAM(m_settings.cam, TRUE);
						GRAPHICS::SET_TIMECYCLE_MODIFIER("DEFAULT");
						ENTITY::FREEZE_ENTITY_POSITION(g_utils->self(), FALSE);
						m_settings.initialized = false;

					}
				}
			}
			else {
				auto coords{ ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_utils->weapon(), 0.f, 1.f, 0.f)};
				m_settings.rocket = OBJECT::CREATE_OBJECT(rage::joaat("w_lr_rpg_rocket"), coords.x, coords.y, coords.z, TRUE, TRUE, FALSE);
				CAM::DESTROY_ALL_CAMS(TRUE);
				m_settings.cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", TRUE);
				CAM::ATTACH_CAM_TO_ENTITY(m_settings.cam, m_settings.rocket, m_settings.offset.x, m_settings.offset.y, m_settings.offset.z, TRUE);
				CAM::RENDER_SCRIPT_CAMS(TRUE, TRUE, 700, TRUE, TRUE, NULL);
				CAM::SET_CAM_ACTIVE(m_settings.cam, TRUE);
				ENTITY::SET_ENTITY_VISIBLE(m_settings.cam, FALSE, FALSE);
				m_settings.y_position = 255; m_settings.meter_val = .5f;
			}
		}
    }
    void missle_launcher::on_disable() {
		CAM::DESTROY_CAM(m_settings.cam, TRUE);
		PLAYER::DISABLE_PLAYER_FIRING(g_utils->self(), FALSE);
		m_settings.rocket = 0;
		m_settings.y_position = 255;
		m_settings.meter_val = .5f;
		ENTITY::FREEZE_ENTITY_POSITION(g_utils->self(), FALSE);
    }
}
