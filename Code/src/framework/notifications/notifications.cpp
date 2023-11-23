#include "notifications.h"
#include "src/framework/Direct_x/renderer.h"
#include "src/framework/framework.h"

namespace Base {
	notifications::notifications() {
		g_notifications = this;
	}

	notifications::~notifications() {
		g_notifications = nullptr;
	}

	void notifications::push(notification n) {
		this->m_notifications.insert({this->m_notifications.size(), n });
	}

	void notifications::send(str title, str message) {
		for (auto& n : this->m_notifications) {
			if (n.second.m_message == message) return;
		}
		this->push({ eNotificationType::INFO, title, message, std::chrono::system_clock::now(), 7000.f, 1.f });
	}


	std::vector<notification> notifications::get() {
		std::vector<notification> to_send;
		std::vector<std::size_t> to_remove;
		for (auto& n : this->m_notifications) {
			std::chrono::time_point<std::chrono::system_clock> CurrentTime = std::chrono::system_clock::now();
			auto time_diff{ std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - n.second.m_creation_date).count() };
			n.second.m_fade_alpha = 1;
			if (n.second.m_destruction_date <= time_diff) {
				n.second.m_fade_alpha = 1.f - ((time_diff - n.second.m_destruction_date) / 600.f);
				n.second.m_fade_alpha = n.second.m_fade_alpha < 0.f ? 0.f : n.second.m_fade_alpha;
			}
			if (n.second.m_alpha_value < 255) n.second.m_alpha_value += 5;
			if (n.second.m_fade_alpha > 0.f) {
				to_send.push_back(n.second);
			}
			else {
				to_remove.push_back(n.first);
			}
		}
		for (auto k : to_remove) {
			this->m_notifications.erase(k);
		}

		return to_send;
	}

	void notifications::Tick() {
		std::vector<notification> notifications{ get() };

		float pos{ 0.f };
		float pos2{ 0 };
		for (auto& n : notifications) {
			float start{ render(pos, ImGui::GetBackgroundDrawList(), n.m_title, n.m_message, m_notification_colors.at(n.m_type), n) };
			pos = start;
		}
	}

	bool g_ShortEnough = false;
	float g_YOffset = 0.012f;
	float notifications::render(float start, ImDrawList* drawlist, std::string title, std::string message, Color color, notification n) {
		uint8_t alpha{ (uint8_t)n.m_alpha_value };
		int j{ 0 };
		int previous_space{ 0 };
		float total_size{ 0.f };
		std::vector<str> split_points;
		for (int i = 0; i <= message.size(); i++) {
			str current_message{ message.substr(j, i - j) };
			auto size{ g_interface->get_text_scale(current_message.c_str()) };

			if (i == message.size()) {
				total_size += size.y;
				split_points.push_back(message.substr(j, i));
			}
			else if (message.substr(i, 1) == " ") {
				previous_space = i;
			}
		}
		float rect_width;

		if (g_interface->get_text_scale(message).x / 2 > g_interface->get_text_scale(title).x / 2)
			rect_width = g_interface->get_text_size(g_interface->m_notifications2_font, g_interface->m_notifications_text_size2, message, 9999999999).x + 0.004;
		else
			rect_width = g_interface->get_text_scale(title).x / 2;

		g_interface->draw_rect(pos_x + rect_width / 2 - 0.1 + 0.004 - m_LineWidth, pos_y + start + (n.m_alpha_value / 5000), rect_width + 0.005, m_Height + (total_size / 2.f), {m_NotificationBackground.r, m_NotificationBackground.g, m_NotificationBackground.b, alpha});

		g_interface->draw_gradiant_rect2(pos_x - (width / 2.f) + (m_LineWidth / 2.f), pos_y + start, m_LineWidth, m_Height + (total_size / 2.f), { g_interface->m_options.m_first_color.r, g_interface->m_options.m_first_color.g, g_interface->m_options.m_first_color.b, alpha }, { g_interface->m_options.m_second_color.r, g_interface->m_options.m_second_color.g, g_interface->m_options.m_second_color.b,alpha });

		g_interface->draw_left_text(title, pos_x - (width / m_Padding) + m_LineWidth, pos_y + start - (g_interface->get_text_scale(title.c_str()).y / 8.f) - (m_Height / 5.f) - (total_size / 4.f) + 0.005, g_interface->m_notifications_text_size, g_interface->m_notifications2_font, { m_NotificationText.r, m_NotificationText.g, m_NotificationText.b, alpha }, true, false);

		g_interface->draw_left_text( message, pos_x - (width / m_Padding) + m_LineWidth, pos_y + start - (g_interface->get_text_scale(message).y / 8.f) + (m_Height / 5.f) + (1 * 0.015f) - g_YOffset, g_interface->m_notifications_text_size2, g_interface->m_notifications2_font, { m_NotificationText.r, m_NotificationText.g, m_NotificationText.b, alpha }, true, false);

		return start + 0.003f + m_Height + total_size - 0.020f;
	}
}