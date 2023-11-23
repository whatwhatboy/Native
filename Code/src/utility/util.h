#pragma once
#include "src/Memory/Pointers/Pointers.h"


namespace Base {
	inline bool IsKeyPressed(std::uint16_t key) {
		if (GetAsyncKeyState(key) & 0x8000) {
			return true;
		}
		return false;
	}
	class StringStreamBuf : public std::streambuf {
	public:
		StringStreamBuf(char* Arr, std::size_t ArrSize) {
			std::fill_n(Arr, ArrSize, '\0');
			std::streambuf::setp(Arr, Arr + ArrSize - 1);
		}
		template <std::size_t ArrSize>
		StringStreamBuf(char(&Arr)[ArrSize]) : StringStreamBuf(&Arr[0], ArrSize) {}
	};
	class StringStream : virtual StringStreamBuf, public std::iostream {
	public:
		StringStream(char* Arr, std::size_t ArrSize) : StringStreamBuf(Arr, ArrSize), std::iostream(static_cast<StringStreamBuf*>(this)) {}
		template <std::size_t ArrSize>
		StringStream(char(&Arr)[ArrSize]) : StringStreamBuf(Arr), std::iostream(static_cast<StringStreamBuf*>(this)) {}
	};
	template <std::size_t bufSize>
	class StringStreamWithBuf : public StringStream {
	public:
		StringStreamWithBuf() : StringStream(m_Buffer) {}
	public:
		char m_Buffer[bufSize];
	};
	inline consteval char ToLower(char c) {
		return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
	}
	inline consteval uint32_t Joaat(std::string_view str) {
		uint32_t hash{};
		for (size_t i{}; i != str.size(); ++i) {
			hash += ToLower(str[i]);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash;
	}
	inline consteval uint32_t operator"" _joaat(const char* str, size_t strSize) {
		return Joaat(str);
	}
	class MemoryStreamBuf : public std::streambuf
	{
	public:
		MemoryStreamBuf(char* array, std::size_t size)
		{
			std::fill_n(array, size, '\0');
			std::streambuf::setp(array, array + size - 1);
		}

		template <std::size_t size>
		MemoryStreamBuf(char(&array)[size]) :
			MemoryStreamBuf(&array[0], size)
		{
		}
	};

	/**
	 * \brief An input/output stream that uses a char[] buffer
	 */
	class MemoryStringStream : virtual MemoryStreamBuf, public std::iostream
	{
	public:
		MemoryStringStream(char* array, std::size_t size) :
			MemoryStreamBuf(array, size),
			std::iostream(static_cast<MemoryStreamBuf*>(this))
		{
		}

		template <std::size_t size>
		MemoryStringStream(char(&array)[size]) :
			MemoryStreamBuf(array),
			std::iostream(static_cast<MemoryStreamBuf*>(this))
		{
		}
	};

	/**
	 * \brief A MemoryStringStream with a built in buffer
	 */
	template <std::size_t N>
	class MemoryStringStreamWithBuffer : public MemoryStringStream
	{
	public:
		MemoryStringStreamWithBuffer() :
			MemoryStringStream(m_Buffer)
		{}
	private:
		char m_Buffer[N];
	};
}
