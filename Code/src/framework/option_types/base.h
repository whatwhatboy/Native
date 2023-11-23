#pragma once
#include "src/utility/common/common.h"
#include "abstract.h"

namespace Base::Framework {
	template <typename T>
	class base_option : public abstract_option {
	public:
		str get_left_text() override {
			return m_left_text;
		}
		str get_right_text() override {
			return m_right_text;
		}
		str get_centered_text() override {
			return m_centered_text;
		}
		str get_description() override {
			return m_description;
		}
		str get_arg() override {
			return m_arg;
		}
		str get_texture() override {
			return m_texture;
		}
		Vector2 get_texture_size() override {
			return m_texture_size;
		}
		void handle_action(option_action action) override {
			if (action == option_action::EnterPress)
				if (m_Action)
					std::invoke(m_Action);
		}
		bool get_flag(option_flag) override {
			return false;
		}
		Color get_color() override {
			return m_color;
		}
		bool* get_bool() override {
			return nullptr;
		}
		std::function<void()> get_button_action() override {
			return [] {};
		}
		std::function<void()> get_toggle_action() override {
			return [] {};
		}
	public:
		T& set_left_text(str text) {
			m_left_text = text;
			return static_cast<T&>(*this);
		}
		T& set_color(Color color) {
			m_color = color;
			return static_cast<T&>(*this);
		}

		T& set_center_text(str text) {
			m_centered_text = text;
			return static_cast<T&>(*this);
		}

		T& set_right_text(str text) {
			m_right_text = text;
			return static_cast<T&>(*this);
		}

		T& set_description(str text) {
			m_description = text;
			return static_cast<T&>(*this);
		}
		T& set_arg(str text) {
			m_arg = text;
			return static_cast<T&>(*this);
		}
		T& set_texture(str id) {
			m_texture = id;
			return static_cast<T&>(*this);
		}
		T& set_texture_size(Vector2 size) {
			if (size)
				m_texture_size = size;
			return static_cast<T&>(*this);
		}
		T& set_action(std::function<void()> action) {
			m_Action = std::move(action);
			return static_cast<T&>(*this);
		}
	protected:
		std::string m_left_text{};
		std::string m_right_text{};
		std::string m_centered_text{};
		std::string m_description{};
		std::string m_arg{};
		std::function<void()> m_Action;
		Color m_color = {};
	protected:
		std::string m_texture{};
		Vector2 m_texture_size{};
	};
}