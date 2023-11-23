#include "src/framework/Framework.h"
#include "vehicle_preview.h"
namespace Base::Framework {
	std::vector<str> not_found;
	void add_non_found(str s) {
		for (auto f : not_found) {
			if (f == s) return;
		}

		not_found.push_back(s);
	}
	bool is_hash_in_preview(Hash hash) {
		for (auto entry : g_vehicle_previews) {
			if (rage::joaat(entry.first) == hash) return true;
		}

		return false;
	}
	auto get_preview(Hash hash) {
		for (auto entry : g_vehicle_previews) {
			if (rage::joaat(entry.first) == hash) return entry.second;
		}
	}
	float size{ 0.005 };
	void Interface::draw_vehicle_info(str name) {
		auto hash{ rage::joaat(name) };

		float height{ 0.1 };
		bool has_preview{ is_hash_in_preview(hash) };
		if (has_preview)
			height = height + 0.1;
		if (has_preview) {
			float offset{ 0.16 };
			draw_rect(m_lerped_pos_x + offset, m_lerped_pos_y + (height / 2), m_width - 0.07, height, m_option_unselected_background_color, ImGui::GetForegroundDrawList(), 8.f, ImDrawFlags_RoundCornersAll);
			draw_sprite(get_preview(hash).m_dict, get_preview(hash).m_asset, m_lerped_pos_x + offset, m_lerped_pos_y + (height / 2), m_width - 0.08, height - 0.02, m_footer_sprite_color, 0, ImGui::GetForegroundDrawList(), 8.f, ImDrawFlags_RoundCornersAll);

			draw_gradiant_rect(m_lerped_pos_x + offset, m_lerped_pos_y + (0.0035f / 2.f) - (0.0035f / 2.f) + 0.0015, m_width - 0.07, 0.0035f, { m_options.m_first_color.r, m_options.m_first_color.g, m_options.m_first_color.b, m_header_text_color.a }, { m_options.m_second_color.r, m_options.m_second_color.g, m_options.m_second_color.b, m_header_text_color.a }, ImGui::GetForegroundDrawList());
		}
	}
}