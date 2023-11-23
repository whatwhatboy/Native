#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/utility/enum.h"

namespace Base::speedometer {
	namespace settings {
		const char* method[2] = { "Force", "Set" };
		int pos{ 0 };
		float force{ 5 };
	}
	bool enabled{ false };
	void init() {
		if (!enabled) return;
		/*float vehSpeed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
		ui::Drawing::Spriter("Textures", "ZeusSpeedo1", 0.890f, 0.927f, 0.14f, 0.215f, 0, 255, 255, 255, 255);
		ui::Drawing::Spriter("Textures", "ZeusSpeedoNeedo", 0.890f, 0.927f, 0.04f, 0.10f, round(vehSpeed * 4.3f), 255, 255, 255, 255);
		std::ostringstream SpeedoDraw; SpeedoDraw << "~t~" << round(vehSpeed * 3.6f) << " KMH";
		ui::Drawing::Text((char*)SpeedoDraw.str().c_str(), { 255, 255, 255, 255, 4 }, { 0.890f, 0.98f }, { 0.26f, 0.26f }, true);*/
		//will do this later LOL this is from kyros old project
	}
}
