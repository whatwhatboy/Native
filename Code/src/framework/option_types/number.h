#pragma once
#include "base.h"
#include "src/framework/framework.h"
#include "src/fiber/fiber_helper.h"

namespace Base::Framework {
	template <typename T>
	struct number_struct {
		T min;
		T max;
		T step;
		T precision;
	};
	inline bool number_type_open{ false };
	inline inline char text_buffer[256] = "";
	template <typename num_type>
	class number : public base_option<number<num_type>> {
	public:
		number() = default;
		number(str text, str description, num_type* number, num_type min, num_type max, num_type step = 1, std::size_t precision = 3, bool action_on_horizontal = true, str prefix = "", str suffix = "", std::function<void()> action = [] {}) :
			m_action_on_horizontal(action_on_horizontal), m_number(number), m_min(min), m_max(max), m_step(step), m_precision(precision) {
			Base::set_left_text(text);
			Base::set_description(description.empty() ? "Press enter to set a value." : description + "\nPress enter to set a value.");
			Base::set_action(std::move(action));
			m_prefix = prefix;
			m_suffix = suffix;
		}
		number(str text, num_type* number, num_type min, num_type max, num_type step = 1, std::size_t precision = 3, bool action_on_horizontal = true, str prefix = "", str suffix = "", std::function<void()> action = [] {}) :
			m_action_on_horizontal(action_on_horizontal), m_number(number), m_min(min), m_max(max), m_step(step), m_precision(precision) {
			Base::set_left_text(text);
			Base::set_action(std::move(action));
			m_prefix = prefix;
			m_suffix = suffix;
		}
		number(str text, bool action_on_horizontal, str prefix = "", str suffix = "", std::function<void()> action = [] {}) :
			m_name(text), m_action_on_horizontal(action_on_horizontal) {
			Base::set_left_text(text);
			Base::set_action(std::move(action));
			m_prefix = prefix;
			m_suffix = suffix;
		}

		number& add_number(num_type* num, number_struct<num_type> num_struct) {
			m_number = num;
			m_min = num_struct.min;
			m_max = num_struct.max;
			m_step = num_struct.step;
			m_precision = num_struct.precision;
			return *this;
		}
		number& add_number(num_type& num, number_struct<num_type> num_struct) {
			m_number = &num;
			m_min = num_struct.min;
			m_max = num_struct.max;
			m_step = num_struct.step;
			m_precision = num_struct.precision;
			return *this;
		}

		number& add_action(std::function<void()> action) {
			std::function<void()> action2 = [=] {
				g_fiber_pool.queue([=] {
					action();
				});
			};
			Base::set_action(std::move(action2));
			return *this;
		}

		str get_right_text() override {
			char buf[128]{};
			StringStream stream(buf);
			stream << std::setprecision(m_precision) << std::fixed << m_prefix << static_cast<display_type>(*m_number) << m_suffix;
			Base::m_right_text = buf;
			return Base::get_right_text();
		}
		bool get_flag(option_flag flag) override {
			if (flag == option_flag::Horizontal)
				return true;
			return Base::get_flag(flag);
		}
		void handle_action(option_action action) override {
			switch (action) {
				case option_action::LeftPress:
					*m_number = (*m_number - m_step < m_min) ? m_max : (*m_number - m_step);
					if (m_action_on_horizontal && Base::m_Action)
						std::invoke(Base::m_Action);
					break;

				case option_action::RightPress:
					*m_number = (*m_number + m_step > m_max) ? m_min : (*m_number + m_step);
					if (m_action_on_horizontal && Base::m_Action)
						std::invoke(Base::m_Action);
					break;

				case option_action::EnterPress:
					if (strlen(text_buffer) > 0 && number_type_open) {
						const char* test = text_buffer;
						*m_number = std::stof(test);
						if (!m_action_on_horizontal && Base::m_Action)
							std::invoke(Base::m_Action);
						number_type_open = false;
						g_interface->m_disable_input = false;
					}
					else {
						std::snprintf(text_buffer, sizeof(text_buffer), "%f", *m_number);
						g_interface->m_disable_input = true;
						number_type_open = true;
					}
					break;

				default:
					break;
			}

			Base::handle_action(action);
		}
	private:
		str m_prefix{};
		str m_suffix{};
		bool m_action_on_horizontal{};
		num_type* m_number{};
		num_type m_min{};
		num_type m_max{};
		num_type m_step{};
		std::size_t m_precision{};
	public:
		std::string m_name{};
	private:
		using Base = base_option<number<num_type>>;
		using display_type = std::conditional_t<sizeof(num_type) == 1, std::uint32_t, num_type>;
	};
}