#pragma once
#include <MinHook/include/MinHook.h>
#include <src/utility/common/common.h>
#include "src/core/logger/logger.h"

class MinHook {
public:
	MinHook() { MH_Initialize(); }
	~MinHook() { MH_Uninitialize(); }
public:
	template <typename T>
	static bool Create(ccp name, T Target, T Detour, T* Originial) {
		MH_STATUS Status{ MH_CreateHook(Target, LPVOID(Detour), (LPVOID*)Originial) };
		if (Status == MH_STATUS::MH_OK) {
			if (Base::debug_mode) {
				LOG(Success, "Created hook {}", name);
			}
			return true;
		}
		if (Status != MH_STATUS::MH_ERROR_NOT_INITIALIZED && Status != MH_STATUS::MH_ERROR_UNSUPPORTED_FUNCTION && Status != MH_STATUS::MH_ERROR_MEMORY_ALLOC && Status != MH_STATUS::MH_ERROR_MEMORY_PROTECT) {
			if (std::optional<LPVOID> CorrectedTarget{ GetCorrectedTarget<T>(Target) }; CorrectedTarget.has_value()) {
				Status = MH_CreateHook(CorrectedTarget.value(), LPVOID(Detour), (LPVOID*)Originial);
				if (Status == MH_STATUS::MH_OK) {
					if (Base::debug_mode) {
						LOG(Success, "Created hook {}", name);
					}
					return true;
				}
				else {
					LOG(Fatal, "Failed to create hook {}", name);
				}
				return false;
			}
		}
		return false;
	}
	template <typename T>
	static bool Destroy(T Target) {
		return MH_RemoveHook(LPVOID(Target)) == MH_STATUS::MH_OK;
	}
	template <typename T>
	static bool QueueEnable(T Target) {
		return MH_QueueEnableHook(LPVOID(Target)) == MH_STATUS::MH_OK;
	}
	template <typename T>
	static bool QueueDisable(T Target) {
		return MH_QueueDisableHook(LPVOID(Target)) == MH_STATUS::MH_OK;
	}
	static bool Apply() {
		return MH_ApplyQueued() == MH_STATUS::MH_OK;
	}
public:
	template <typename T>
	static std::optional<LPVOID> GetCorrectedTarget(T Target) {
		uint8_t* Bytes{ decltype(Bytes)(Target) };
		for (int8_t i{}; i != 0xF; ++i) {
			if (Bytes[i] == 0xE8) {
				Bytes = *(uint8_t**)(&Bytes[i]);
				break;
			}
		}
		return Bytes;
	}
};
class detour {
public:
	detour(char const* name, void* ptr, void* dtr, bool hook = true) : m_name(name), m_ptr(ptr), m_og(ptr), m_dtr(dtr), m_hook(hook) {
		if (m_hook) {
			MinHook::Create(name, m_ptr, m_dtr, &m_og);
		}
	}
	~detour() {
		if (m_hook) {
			MinHook::Destroy(m_ptr);
		}
	}
public:
	void enable() {
		if (m_hook) {
			MinHook::QueueEnable(m_ptr);
		}
	}
	void disable() {
		if (m_hook) {
			MinHook::QueueDisable(m_ptr);
		}
	}
public:
	inline static void enable_all() {
		MH_QueueEnableHook(MH_ALL_HOOKS);
	}
	inline static void disable_all() {
		MH_QueueDisableHook(MH_ALL_HOOKS);
	}
public:
	template <typename t>
	t get_original() {
		return static_cast<t>(m_og);
	}
public:
	ccp m_name{};
	void* m_dtr{};
	void* m_ptr{};
	void* m_og{};
	bool m_hook{};
};