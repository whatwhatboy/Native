#pragma once
#include "src/utility/common/common.h"
namespace Base {
	class text_box {
	public:
		const char* get_text() {
			return buffer.c_str();
		}
		void add(const char* text) {
			buffer += text;
		}
		void remove_last_char() {
			pop_back_utf8(buffer);
		}
	private:
		void pop_back_utf8(std::string& utf8) {
			if (utf8.empty())
				return;
			auto cp{ utf8.data() + utf8.size() };
			while (--cp >= utf8.data() && ((*cp & 0b10000000) && !(*cp & 0b01000000))) {}
			if (cp >= utf8.data())
				utf8.resize(cp - utf8.data());
		}
	private:
		std::string buffer;
	};
}