#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WIN7

#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#include <winternl.h>
#include <d3d11.h>
#include <Psapi.h>

#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <map>
#include <vector>
#include <format>
#include <WRL/client.h>
#include <span>

// MENU
#include "src/utility/util.h"
#include "src/memory/memory.h"
#include "src/memory/pointers/pointers.h"
#include "src/memory/script/script_global.h"

// JSON
#include <JSON/json.hpp>
#include <JSON/json_fwd.hpp>

// GTA-V
#include <src/rage/script/scrNativeHandler.hpp>
#include <src/rage/script/scrNativeRegistration.hpp>
#include <src/rage/script/scrNativeRegistrationTable.hpp>

// ImGui
#define IMGUI_DEFINE_MATH_OPERATORS
#include "src/framework/ImGui/imgui.h"
#include "src/framework/ImGui/imgui_internal.h"
#include "src/framework/ImGui/backends/imgui_impl_dx11.h"
#include "src/framework/ImGui/backends/imgui_impl_win32.h"

//Handler
#include <stackwalker/Main/StackWalker/StackWalker.h>
#include <random>

//Mp3 Loading
#include <Mmsystem.h>
#include <mciapi.h>

//Branding
#define BRANDING "Native"
#define LOWER_BRANDING "native"
#define UPPER_BRANDING "NATIVE"
#define ALTERNATING_BRANDING "ur a faggot"

//Build Info
#define VERSION "Alpha"
#define BUILD_DATE __DATE__ " at " __TIME__

// Debug
#define DEBUG_MODE


#define USE_ZYDIS

using u64 = uint64_t;
using i64 = int64_t;
using u32 = uint32_t;
using i32 = int32_t;
using u16 = uint16_t;
using i16 = int16_t;
using u8 = uint8_t;
using i8 = int8_t;
using cc = const char;
using ccp = cc*;
using fp = float;
using db = double;
using str = std::string;
using uptr = uintptr_t;


namespace Base {
	using namespace std::chrono_literals;
	namespace fs = std::filesystem;
	inline HMODULE g_Module{};
	inline bool g_Authed{};
	inline bool g_Running{ true };
	inline u32 g_selected_player{};
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	template <typename t> requires std::is_function_v<t>
	using fnptr = std::add_pointer_t<t>;

	inline bool debug_mode{ false };
}
// StackWalker
class stackWalker : public StackWalker {
public:
	stackWalker() : StackWalker() {}
	stackWalker(ExceptType exType) : StackWalker(exType) {}
	virtual void OnOutput(LPCSTR szText);
	virtual void OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion);
	virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName);
	virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr);
	virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry);
};
// Random Number Generator
class rng {
	std::random_device m_rd{};
	std::mt19937 m_mtRes{};
public:
	template <typename t> requires std::is_integral_v<t>
	rng() : m_mtRes(m_rd()), m_min(std::numeric_limits<t>::min()), m_max(std::numeric_limits<t>::max()) {}
	rng(size_t min, size_t max) : m_mtRes(m_rd()), m_min(min), m_max(max) {}
public:
	template <typename t>
	t get() {
		std::uniform_int_distribution m_intDis(m_min, m_max);
		return static_cast<t>(m_intDis(m_mtRes));
	}
public:
	size_t m_min{};
	size_t m_max{};
};