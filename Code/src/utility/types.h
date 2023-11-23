#pragma once
#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>

using Any = int;
using Hash = std::uint32_t;
using Entity = std::int32_t;
using Player = std::int32_t;
using FireId = std::int32_t;
using Interior = std::int32_t;
using Ped = Entity;
using Vehicle = Entity;
using Cam = std::int32_t;
using Object = Entity;
using Pickup = Object;
using Blip = std::int32_t;
using Camera = Entity;
using ScrHandle = Entity;

#pragma pack(push, 1)
	template <typename T>
	struct color {
		T r{ 255 };
		T g{ 255 };
		T b{ 255 };
		T a{ 255 };
		T pack() {
			return a << 24 | b << 16 | g << 8 | r << 0;
		}
		template <typename t>
		color<t> as() {
			return color<t>(r, g, b, a);
		}

	};
	struct Color {
		uint8_t r{ 255 };
		uint8_t g{ 255 };
		uint8_t b{ 255 };
		uint8_t a{ 255 };
		uint32_t pack() {
			return a << 24 | b << 16 | g << 8 | r << 0;
		}
		bool is_empty() {
			return (r == 0 && g == 0 && b == 0 && a == 0);
		}
		template <typename t>
		color<t> as() {
			return color<t>(r, g, b, a);
		}
	};
	struct ColorFloat {
		float r{ 255 };
		float g{ 255 };
		float b{ 255 };
		float a{ 255 };
	};
	struct ColorInt {
		int r{ 255 };
		int g{ 255 };
		int b{ 255 };
		int a{ 255 };
	};
#pragma pack(pop)