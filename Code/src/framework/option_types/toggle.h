#pragma once
#include "base.h"
#include "src/framework/framework.h"
namespace Base::Framework {
	class toggle : public base_option<toggle> {
	public:
		explicit toggle(str text, str description, bool* toggle, std::function<void()> action = [] {}) :
			m_toggle(toggle), m_action(action) {
			base::set_left_text(text);
			base::set_description(description.empty() ? "Press F12 to set a hotkey." : description + "\nPress F12 to set a hotkey.");
			base::set_action(std::move(action));
		}
		explicit toggle(str text) :
			m_name(text) {
			base::set_left_text(text);
		}
	public:
		toggle& add_toggle(bool& tog) {
			m_toggle = &tog;
			return *this;
		}
		toggle& add_toggle(bool* tog) {
			m_toggle = tog;
			return *this;
		}
	public:
		~toggle() noexcept = default;
		toggle(toggle const&) = default;
		toggle& operator=(toggle const&) = default;
		toggle(toggle&&) = default;
		toggle& operator=(toggle&&) = default;
	public:
		void handle_action(option_action action) override {
			if (action == option_action::EnterPress)
				*m_toggle = !*m_toggle;
			base::handle_action(action);
		}
		bool get_flag(option_flag flag) override {
			switch (flag) {
			case option_flag::Toggle: {
				g_interface->m_toggle = *m_toggle;
				return true;
			} break;
			}
			return base::get_flag(flag);
		}
		bool* get_bool() override {
			return m_toggle;
		}
		std::function<void()> get_toggle_action() override {
			return m_action;
		}
	private:
		bool* m_toggle;
	public:
		std::string m_name{};
		std::function<void()> m_action{};
	private:
		using base = base_option<toggle>;
	};
}