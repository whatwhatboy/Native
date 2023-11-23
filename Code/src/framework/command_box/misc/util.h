#pragma once
#include "src/utility/common/common.h"
#include <src/memory/pointers/pointers.h>

namespace Base::command_box::util {
	inline auto is_focused_on_gta() {
		return GetForegroundWindow() == g_pointers->m_game_window;
	}
	inline str convert_to_lowercase(const str& input) {
		str lowercase = input;
		std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
		return lowercase;
	}
	inline str remove_underscores_and_spaces(const str& inputString) {
		str result;
		for (char ch : inputString) {
			if (ch != '_' && ch != ' ') {
				result += ch;
			}
		}
		return result;
	}
	inline str join_items(const char* const* items, int count) {
		str result;
		for (int i = 0; i < count; ++i) {
			result += items[i];
			if (i < count - 1) {
				result += ", ";
			}
		}
		return result;
	}
	inline str compare_strings(const str& str1, const str& str2) {
		str str1Lower{ str1 };
		str str2Lower{ str2 };
		if (str1.size() != str2.size()) {
			return str1;
		}

		std::transform(str1Lower.begin(), str1Lower.end(), str1Lower.begin(), ::tolower);

		str2Lower.erase(std::remove_if(str2Lower.begin(), str2Lower.end(), ::isspace), str2Lower.end());
		std::transform(str2Lower.begin(), str2Lower.end(), str2Lower.begin(), ::tolower);

		if (str1Lower == str2Lower) {
			return str2;
		}
		else {
			return std::format("{} - {}", str1, str2);
		}
	}
	inline str get_description(str desc) {
		if (desc != "") {
			return desc;
		}
		else {
			return "No Description Found.";
		}
	}
	inline str get_float_value(const char* input) {
		str strInput(input);
		std::istringstream iss(strInput);
		float value;
		if (iss >> value) {
			return std::to_string(value);
		}
		return "Invalid float value";
	}
	inline bool has_string_attached(const str& first, const str& check) {
		str strLower = first;
		str checkLower = check;
		std::transform(strLower.begin(), strLower.end(), strLower.begin(), [](unsigned char c) {
			return std::tolower(c);
			});
		std::transform(checkLower.begin(), checkLower.end(), checkLower.begin(), [](unsigned char c) {
			return std::tolower(c);
			});

		size_t found{ strLower.find(checkLower) };
		if (found != str::npos) {
			return true;
		}
		else {
			return false;
		}
	}
}
