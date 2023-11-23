#pragma once
#include "src/framework/option_types/base.h"
#include "src/framework/framework.h"
namespace Base::Framework {
	class seperator : public base_option<seperator> {
	public:
		explicit seperator() = default;
		explicit seperator(str text) {
			set_center_text(text);
		}
	public:
		bool get_flag(option_flag flag) override {
			if (flag == option_flag::Break)
				return true;
			return base_option::get_flag(flag);
		}
	public:
		~seperator() noexcept = default;
		seperator(seperator const&) = default;
		seperator& operator=(seperator const&) = default;
		seperator(seperator&&) = default;
		seperator& operator=(seperator&&) = default;
	};
}