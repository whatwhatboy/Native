#pragma once
#include "joaat.hpp"

namespace rage
{
	class json_serializer
	{
		uint32_t unk0;  // 0x00
		uint32_t unk1;  // 0x00
		char* buffer;   // 0x08
		uint32_t curlen;// 0x10
		uint32_t maxlen;// 0x14
		uint32_t unk4;  // 0x18
		uint8_t flags;  // 0x1C

	public:
		json_serializer(char* _buffer, uint32_t _length) :
			buffer(_buffer),
			maxlen(_length)
		{
			unk0
				= 0;
			unk1 = 0;
			curlen = 0;
			unk4 = 1;
			flags = 0;
		}

		inline char* get_string() const
		{
			return buffer;
		}
	};
	static_assert(sizeof(json_serializer) == 0x20);
	class JSONSerialiser {
	public:
		JSONSerialiser(uint32_t length) : m_buffer(new char[length]), m_max_length(length), m_read(TRUE) {}
		~JSONSerialiser() { delete[] m_buffer; }
	public:
		uint32_t unk_0000{}; //0x0000
		uint32_t unk_0004{}; //0x0004
		char* m_buffer{}; //0x0008
		uint32_t m_current_length{}; //0x0010
		uint32_t m_max_length{}; //0x0014
		uint32_t m_read{}; //0x0018
		uint8_t m_flags{}; //0x001C

		std::string str() {
			return m_buffer;
		}
		void clear() {
			memset(m_buffer, NULL, m_max_length);
		}
	}; //Size: 0x0020
	class rlMetric {
	public:
		virtual ~rlMetric() = default; //Deconstructor
		virtual int metric_b() { return 0; }; //Returns a constant integer like 4, 5, 6
		virtual int metric_a() { return 0; }; //Returns a constant integer like 0
		virtual int unk_0018() { return 0; };
		virtual char const* get_name() { return ""; }; //Short name of the metric
		virtual bool serialize(void* serializer) { return false; };
		virtual int get_size() { return 0; }; //Size in bytes of derived object (for copying)
		virtual uint32_t get_name_hash() { return 0; }; //Joaat of short name
	public:
		bool using_a() {
			return metric_a() == 6;
		}
		bool using_b() {
			return metric_b() == 5;
		}
		bool using_c() {
			return !using_a() && !using_b();
		}
		bool crc_flag() {
			return !(*(std::int8_t*)(*(std::uint64_t*)__readgsqword(0x58) + 0xB4) & 1);
		}
	};
};