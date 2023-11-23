#pragma once
#include "src/utility/util.h"
namespace Base {
	class timer {
	public:
		explicit timer(std::chrono::milliseconds del) :
			current(std::chrono::high_resolution_clock::now()),
			delay(std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(del))
		{}
	public:
		bool update() {
			auto now = std::chrono::high_resolution_clock::now();
			if ((now.time_since_epoch() - current.time_since_epoch()).count() >= delay.count()) {
				current = now;
				return true;
			}
			return false;
		}
		void set_delay(std::chrono::milliseconds del) {
			delay = del;
		}
		void set_delay(int del) {
			delay = (std::chrono::milliseconds)del;
		}
	private:
		std::chrono::high_resolution_clock::time_point current;
		std::chrono::high_resolution_clock::duration delay;
	};
}