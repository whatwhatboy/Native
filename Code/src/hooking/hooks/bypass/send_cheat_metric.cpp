#include "src/hooking/hooking.h"

namespace Base {
	constexpr std::array<std::string_view, 28> blocked_metrics = {
		"DIG",
		"XP_LOSS",
		"AWARD_XP",
		"CF",
		"CC",
		"CNR",
		"SCRIPT",
		"CHEAT",
		"AUX_DEUX",
		"WEATHER",
		"HARDWARE_OS",
		"HARDWARE_GPU",
		"HARDWARE_MOBO",
		"HARDWARE_MEM",
		"HARDWARE_CPU",
		"PCSETTINGS",
		"CASH_CREATED",
		"DR_PS",
		"UVC",
		"W_L",
		"ESVCS",
		"IDLEKICK",
		"GSCB",
		"GSINV",
		"GSCW",
		"GSINT",
		"EARN",
		"GARAGE_TAMPER"
	};

	bool hooks::send_cheat_metric(rage::rlMetric* metric, bool unk) {
		char buffer[256]{};
		rage::json_serializer serializer(buffer, sizeof(buffer));

		metric->serialize(&serializer);
		if (metric->using_c()) {
			if (metric->crc_flag()) {
				LOG(Fatal, "Metric found: {}, data: {}", metric->get_name(), serializer.get_string());
				return false;
			}
		}

		for (i8 i{}; i != blocked_metrics.size(); i++) {
			if (metric->get_name_hash() == rage::joaat(blocked_metrics[i])) {
				LOG(Fatal, "Metric found: {}, data: {}", metric->get_name(), serializer.get_string());
				return false;
			}
		}

		RET_CALL_DECL(send_cheat_metric, metric, unk);
	}
}