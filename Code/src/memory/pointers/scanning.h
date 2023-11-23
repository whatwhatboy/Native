#pragma once
#include "src/core/logger/logger.h"

#include <VLIZER/VirtualizerSDK.h>
#include <ETAUTH/variablepool.hpp>
#include "dev_pool.h"
#ifndef DEV
#define GETSTRING(x) auth::variablepool::getStringFromPool(x)
#define GETINT(x) auth::variablepool::getIntFromPool(x)
#else

#define GETSTRING(x) mainpool[x]
#define GETINT(x) atoi(mainpool[x].c_str())
#endif
#define endptr(name) as<decltype(name)>()
namespace Base {
	inline ptrdiff_t baseAddressDifference;
	inline void set_base(uintptr_t address)
	{
#ifdef _M_IX86
		uintptr_t addressDiff = (address - 0x400000);
#elif defined(_M_AMD64)
		uintptr_t addressDiff = (address - 0x140000000);
#endif

		// pointer-style cast to ensure unsigned overflow ends up copied directly into a signed value
		baseAddressDifference = *(ptrdiff_t*)&addressDiff;
	}
	inline constexpr uintptr_t exe_end()
	{
#if defined(IS_RDR3)
		return 0x148000000;
#endif

		return 0x146000000;
	}
	// sets the base to the process main base
	inline void set_base()
	{
		set_base((uintptr_t)GetModuleHandle(NULL));
	}
	template<typename T>
	inline uintptr_t get_adjusted(T address)
	{
		if ((uintptr_t)address >= 0x140000000 && (uintptr_t)address <= exe_end())
		{
			return (uintptr_t)address + baseAddressDifference;
		}

		return (uintptr_t)address;
	}
	template<typename T>
	inline T get_call(T address)
	{
		intptr_t target = *(uintptr_t*)(get_adjusted(address) + 1);
		target += (get_adjusted(address) + 5);

		return (T)target;
	}

	class mem {
	public:
		mem(void* p = {}) : m_ptr(p) {}
		mem(u64 p) : mem((void*)p) {}
	public:
		template <typename t>
		std::enable_if_t<std::is_pointer_v<t>, t> as() {
			return static_cast<t>(m_ptr);
		}
		template <typename t>
		std::enable_if_t<std::is_lvalue_reference_v<t>, t> as() {
			return *static_cast<std::add_pointer_t<std::remove_reference_t<t>>>(m_ptr);
		}
		template <typename t>
		std::enable_if_t<std::is_same_v<t, uintptr_t>, t> as() {
			return (t)m_ptr;
		}
	public:
		mem mov() {
			return add(3).rip();
		}
		mem cmp() {
			return add(3).rip();
		}
		mem lea() {
			return add(2).rip();
		}
		mem call() {
			return add(1).rip();
		}
		mem add(u64 v) {
			return mem(as<u64>() + v);
		}
		mem sub(u64 v) {
			return mem(as<u64>() - v);
		}
		mem rip() {
			return add(as<i32&>()).add(4);
		}
		operator bool() {
			return m_ptr;
		}
	private:
		void* m_ptr{};
	};
	class hmodule {
	public:
		hmodule(str name = {}) : m_name(name), m_handle(get()), m_base(m_handle) {
			auto dosHeader = m_base.as<IMAGE_DOS_HEADER*>();
			auto ntHeader = m_base.add(dosHeader->e_lfanew).as<IMAGE_NT_HEADERS*>();
			m_size = ntHeader->OptionalHeader.SizeOfImage;
		}
	public:
		mem begin() {
			return m_base;
		}
		mem end() {
			return begin().add(size());
		}
		size_t size() {
			return m_size;
		}
	public:
		FARPROC getProcess(str search) {
			return GetProcAddress(m_handle, search.c_str());
		}
		HMODULE get() {
			if (m_name.empty())
				return GetModuleHandleA(NULL);
			return GetModuleHandleA(m_name.data());
		}
	private:
		str m_name{};
		HMODULE m_handle{};
		mem m_base{};
		size_t m_size{};
	};
	inline u16 g_found_sig_count{};
	inline u16 g_total_sig_count{};
	inline u16 g_failed_sig_count{};
	inline std::optional<u8> char_to_hex(cc c) {
		if (c >= 'a' && c <= 'f')
			return static_cast<u8>(static_cast<i32>(c) - 87);
		if (c >= 'A' && c <= 'F')
			return static_cast<u8>(static_cast<i32>(c) - 55);
		if (c >= '0' && c <= '9')
			return static_cast<u8>(static_cast<i32>(c) - 48);
		return {};
	}
	inline std::vector<std::optional<u8>> create_bytes_from_string(str ptr) {
		std::vector<std::optional<u8>> bytes{};
		for (size_t i{}; i != ptr.size() - 1; ++i) {
			if (ptr[i] == ' ')
				continue;
			if (ptr[i] != '?') {
				if (auto c = char_to_hex(ptr[i]); c) {
					if (auto c2 = char_to_hex(ptr[i + 1]); c2)
						bytes.emplace_back(static_cast<uint8_t>((*c * 0x10) + *c2));
				}
			}
			else {
				bytes.push_back({});
			}
		}
		return bytes;
	}
	inline bool does_memory_match(u8* target, std::optional<u8> const* sig, u64 len) {
		for (u64 i{}; i != len; ++i) {
			if (sig[i] && *sig[i] != target[i]) {
				return false;
			}
		}
		return true;
	}
	inline u64 find_pattern_bruteforce(std::vector<std::optional<u8>> bytes, hmodule module = {}) {
		for (u64 i{}; i != module.size() - bytes.size(); ++i) {
			if (does_memory_match(module.begin().add(i).as<u8*>(), bytes.data(), bytes.size())) {
				return module.begin().as<u64>() + i;
			}
		}
		return NULL;
	}
	inline u64 find_pattern_boyer_moore_horspool(std::vector<std::optional<u8>> bytes, hmodule module = {}) {
		u64 max_shift{ bytes.size() };
		u64 max_idx{ max_shift - 1 };
		u64 wild_card_idx{ u64(-1) };
		for (i32 i{ i32(max_idx - 1) }; i >= 0; --i) {
			if (!bytes[i]) {
				max_shift = max_idx - i;
				wild_card_idx = i;
				break;
			}
		}
		u64 shift_table[UINT8_MAX + 1]{};
		for (u64 i{}; i <= UINT8_MAX; ++i)
			shift_table[i] = max_shift;
		for (u64 i{ wild_card_idx + 1 }; i != max_idx; ++i)
			shift_table[*bytes[i]] = max_idx - i;

		for (u64 cur_idx{}; cur_idx != module.size() - bytes.size();) {
			for (u64 sig_idx = max_idx; sig_idx >= 0; --sig_idx) {
				if (bytes[sig_idx] && *module.begin().add(cur_idx + sig_idx).as<u8*>() != *bytes[sig_idx]) {
					cur_idx += shift_table[*module.begin().add(cur_idx + max_idx).as<u8*>()];
					break;
				}
				else if (sig_idx == NULL) {
					return module.begin().add(cur_idx).as<u64>();
				}
			}
		}
		return NULL;
	}
	class scanner {
	public:
		scanner(const str& name, const str& pattern, hmodule module = {}) :
			m_name(name), m_pattern(pattern), m_module(module), m_elements(create_bytes_from_string(m_pattern))
		{}
	public:
		mem get() {
			auto start_time{ std::chrono::high_resolution_clock::now() };
			g_total_sig_count++;
			try {
				mem res{ find_pattern_boyer_moore_horspool(m_elements, m_module) };
				if (res) {
					auto end_time{ std::chrono::high_resolution_clock::now() };
					auto elapsed_time{ std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() };
					if (Base::debug_mode) {
						LOG(Success, "Found {} at GTA5.exe+0x{:X} ({}ms)", m_name, res.as<u64>() - m_module.begin().as<u64>(), elapsed_time);
					}
					g_found_sig_count++;
				}
				else {
					g_failed_sig_count++;
					LOG(Fatal, "Failed to find {}", m_name);
				}
				return res;
			}
			catch (std::exception& ex) {
				g_failed_sig_count++;
				LOG(Fatal, "Failed to find {} (Exception {})", m_name, ex.what());
			}

			return {};
		}
	private:
		str m_name{};
		str m_pattern{};
		hmodule m_module{};
		std::vector<std::optional<u8>> m_elements{};
	};
	inline mem scan(str key, str ptr, hmodule module = {}) {
		return scanner(key, ptr, module).get();
	}
	inline mem scan(str key, hmodule module = {}) {
		return scanner(key, GETSTRING(key), module).get();
	}
	inline std::vector<mem> get_all_results(str ptr, hmodule module = {}) {
		std::vector<std::optional<u8>> bytes{ create_bytes_from_string(ptr) };
		std::vector<mem> results{};
		for (u64 i{}; i != module.size() - bytes.size(); ++i) {
			if (does_memory_match(module.begin().add(i).as<u8*>(), bytes.data(), bytes.size())) {
				results.push_back(module.begin().add(i));
			}
		}
		return results;
	}
}
