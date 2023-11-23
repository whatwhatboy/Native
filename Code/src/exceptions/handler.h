#pragma once
#include "Disassembler.h"
#include "src/Core/Logger/Logger.h"
#define ZYDIS_STATIC_BUILD

namespace modules {
	inline std::map<std::string, std::pair<uint64_t, uint64_t>> g_moduleMap{};
	inline decltype(g_moduleMap) getAllModuleInfos() {
		decltype(g_moduleMap) map{};
		HMODULE modules[1024]{};
		HANDLE process{ GetCurrentProcess() };
		DWORD cbNeeded{};
		if (K32EnumProcessModules(process, modules, 1024, &cbNeeded)) {
			for (int32_t i{}; i != (cbNeeded / sizeof(HMODULE)); ++i) {
				//Get the full path to the module's file.
				char modNameCharArray[MAX_PATH];
				if (K32GetModuleFileNameExA(process, modules[i], modNameCharArray, MAX_PATH)) {
					std::string modName(modNameCharArray);
					MODULEINFO info{};
					if (K32GetModuleInformation(process, modules[i], &info, sizeof(MODULEINFO))) {
						map.emplace(modName, std::make_pair(uintptr_t(info.lpBaseOfDll), uintptr_t(info.SizeOfImage)));
					}
				}
			}
		}
		return map;
	}
	template <typename addressType = uintptr_t>
	inline char const* getModuleNameFromAddressImpl(addressType address) {
		for (auto const& [key, val] : g_moduleMap) {
			if (uintptr_t(address) > val.first && uintptr_t(address) < (val.first + val.second)) {
				return std::format("{}+0x{:X}", key.substr(key.find_last_of('\\') + 1, key.find('.') + 3), uintptr_t(address) - val.first).c_str();
			}
		}
		return {};
	}
	template <typename addressType = uintptr_t>
	inline char const* getModuleNameFromAddress(addressType address) {
		if (g_moduleMap.empty())
			g_moduleMap = getAllModuleInfos();
		auto returnValue = getModuleNameFromAddressImpl<addressType>(address);
		if (!returnValue) {
			g_moduleMap.clear();
			g_moduleMap = getAllModuleInfos(); //Incase the module isn't found, we update the module map and try again.
			returnValue = getModuleNameFromAddressImpl<addressType>(address);
		}
		return returnValue;
	}
}
namespace Base::Exceptions {
	class exceptionContext {
	public:
		exceptionContext(EXCEPTION_POINTERS* exception)
			: m_record(*exception->ExceptionRecord), m_context(*exception->ContextRecord), m_type(m_record.ExceptionInformation[0]), m_deathAddress(m_record.ExceptionInformation[1])
		{
			m_code = m_record.ExceptionCode;
			m_exceptionAddress = (uint64_t)m_record.ExceptionAddress;
		}
	public:
		void printRegisters();
	public:
		uint32_t m_code{};
		uint64_t m_exceptionAddress{};
		EXCEPTION_RECORD& m_record;
		CONTEXT& m_context;
		uint64_t& m_type;
		uint64_t& m_deathAddress;
		std::string m_fileoffset{};
	};
	extern bool attemptStackRecovery(PEXCEPTION_POINTERS exceptionInfo);
	inline std::map<long, std::string> g_exceptionTypes = {
		{ 0x00000000L, "STATUS_WAIT_0" },
		{ 0x00000080L, "STATUS_ABANDONED_WAIT_0" },
		{ 0x000000C0L, "STATUS_USER_APC" },
		{ 0x00000102L, "STATUS_TIMEOUT" },
		{ 0x00000103L, "STATUS_PENDING" },
		{ 0x00010001L, "DBG_EXCEPTION_HANDLED" },
		{ 0x00010002L, "DBG_CONTINUE" },
		{ 0x40000005L, "STATUS_SEGMENT_NOTIFICATION" },
		{ 0x40000015L, "STATUS_FATAL_APP_EXIT" },
		{ 0x40010001L, "DBG_REPLY_LATER" },
		{ 0x40010003L, "DBG_TERMINATE_THREAD" },
		{ 0x40010004L, "DBG_TERMINATE_PROCESS" },
		{ 0x40010005L, "DBG_CONTROL_C" },
		{ 0x40010006L, "DBG_PRINTEXCEPTION_C" },
		{ 0x40010007L, "DBG_RIPEXCEPTION" },
		{ 0x40010008L, "DBG_CONTROL_BREAK" },
		{ 0x40010009L, "DBG_COMMAND_EXCEPTION" },
		{ 0x4001000AL, "DBG_PRINTEXCEPTION_WIDE_C" },
		{ 0x80000001L, "STATUS_GUARD_PAGE_VIOLATION" },
		{ 0x80000002L, "STATUS_DATATYPE_MISALIGNMENT" },
		{ 0x80000003L, "STATUS_BREAKPOINT" },
		{ 0x80000004L, "STATUS_SINGLE_STEP" },
		{ 0x80000026L, "STATUS_LONGJUMP" },
		{ 0x80000029L, "STATUS_UNWIND_CONSOLIDATE" },
		{ 0x80010001L, "DBG_EXCEPTION_NOT_HANDLED" },
		{ 0xC0000005L, "STATUS_ACCESS_VIOLATION" },
		{ 0xC0000006L, "STATUS_IN_PAGE_ERROR" },
		{ 0xC0000008L, "STATUS_INVALID_HANDLE" },
		{ 0xC000000DL, "STATUS_INVALID_PARAMETER" },
		{ 0xC0000017L, "STATUS_NO_MEMORY" },
		{ 0xC000001DL, "STATUS_ILLEGAL_INSTRUCTION" },
		{ 0xC0000025L, "STATUS_NONCONTINUABLE_EXCEPTION" },
		{ 0xC0000026L, "STATUS_INVALID_DISPOSITION" },
		{ 0xC000008CL, "STATUS_ARRAY_BOUNDS_EXCEEDED" },
		{ 0xC000008DL, "STATUS_FLOAT_DENORMAL_OPERAND" },
		{ 0xC000008EL, "STATUS_FLOAT_DIVIDE_BY_ZERO" },
		{ 0xC000008FL, "STATUS_FLOAT_INEXACT_RESULT" },
		{ 0xC0000090L, "STATUS_FLOAT_INVALID_OPERATION" },
		{ 0xC0000091L, "STATUS_FLOAT_OVERFLOW" },
		{ 0xC0000092L, "STATUS_FLOAT_STACK_CHECK" },
		{ 0xC0000093L, "STATUS_FLOAT_UNDERFLOW" },
		{ 0xC0000094L, "STATUS_INTEGER_DIVIDE_BY_ZERO" },
		{ 0xC0000095L, "STATUS_INTEGER_OVERFLOW" },
		{ 0xC0000096L, "STATUS_PRIVILEGED_INSTRUCTION" },
		{ 0xC00000FDL, "STATUS_STACK_OVERFLOW" },
		{ 0xC0000135L, "STATUS_DLL_NOT_FOUND" },
		{ 0xC0000138L, "STATUS_ORDINAL_NOT_FOUND" },
		{ 0xC0000139L, "STATUS_ENTRYPOINT_NOT_FOUND" },
		{ 0xC000013AL, "STATUS_CONTROL_C_EXIT" },
		{ 0xC0000142L, "STATUS_DLL_INIT_FAILED" },
		{ 0xC00001B2L, "STATUS_CONTROL_STACK_VIOLATION" },
		{ 0xC00002B4L, "STATUS_FLOAT_MULTIPLE_FAULTS" },
		{ 0xC00002B5L, "STATUS_FLOAT_MULTIPLE_TRAPS" },
		{ 0xC00002C9L, "STATUS_REG_NAT_CONSUMPTION" },
		{ 0xC0000374L, "STATUS_HEAP_CORRUPTION" },
		{ 0xC0000409L, "STATUS_STACK_BUFFER_OVERRUN" },
		{ 0xC0000417L, "STATUS_INVALID_CRUNTIME_PARAMETER" },
		{ 0xC0000420L, "STATUS_ASSERTION_FAILURE" },
		{ 0xC00004A2L, "STATUS_ENCLAVE_VIOLATION" },
		{ 0xC0000515L, "STATUS_INTERRUPTED" },
		{ 0xC0000516L, "STATUS_THREAD_NOT_RUNNING" },
		{ 0xC0000718L, "STATUS_ALREADY_REGISTERED" },
		{ 0xC015000FL, "STATUS_SXS_EARLY_DEACTIVATION" },
		{ 0xC0150010L, "STATUS_SXS_INVALID_DEACTIVATION" },
	};
	inline std::map<ULONG_PTR, std::string> g_exceptionErrorReasons = {
		{ 0, "a attempt to read an invalid address" },
		{ 1, "a attempt to write to an invalid address" },
		{ 8, "an data exception prevention (DEP)" },
	};
	extern std::string getExceptionType(ULONG_PTR type);
	extern LONG CALLBACK onExceptionCallback(PEXCEPTION_POINTERS exceptionInfo);
	extern bool onExceptionCallback_TryExcept(PEXCEPTION_POINTERS exceptionInfo);
	extern LONG CALLBACK exceptionHandler(PEXCEPTION_POINTERS exceptionInfo);
	extern LONG CALLBACK unhandledExceptionHandler(PEXCEPTION_POINTERS exceptionInfo);
	inline PVOID vecExcepHandlerHandle{};
	extern void init();
	extern void uninit();
}