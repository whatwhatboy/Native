#pragma once
#include "src/framework/ImGui/imgui.h"
#include "src/Utility/Types.h"
#include <string>
#include <chrono>
#include <unordered_map>
#include <map>

namespace Base
{
	enum class eNotificationType {
		INFO,
		SUCCESS,
		DANGER,
	};

	struct notification {
		eNotificationType m_type;
		const std::string m_title;
		const std::string m_message;
		const std::chrono::time_point<std::chrono::system_clock> m_creation_date;
		const float m_destruction_date;
		float m_fade_alpha;
		int m_alpha_value{ 0 };
	};

	class notifications final {
		std::unordered_map<std::size_t, notification> m_notifications;
	public:
		notifications();
		virtual ~notifications();

		void push(notification);
		void send(str title, str message);
		std::vector<notification> get();
		void Tick();

		std::map<eNotificationType, Color> m_notification_colors = {
			{ eNotificationType::INFO, Color(255, 255, 255, 255) },
			{ eNotificationType::DANGER, Color(255, 255, 255, 255) },
			{ eNotificationType::SUCCESS, Color(255, 255, 255, 255) }
		};

		float pos_x = 0.105f;
		float pos_y = 0.05f;
		float width = 0.2f;
		float m_Height = 0.020f;
		float m_LineWidth = 0.001f;
		float m_Padding = 2.092f;
		Color m_NotificationBackground{ 31, 31, 31, 255 };
		Color m_NotificationText{ 255, 255, 255, 255 };
	private:
		float render(float start, ImDrawList* drawlist, std::string title, std::string message, Color color, notification n);
	};

	inline notifications* g_notifications{};
}