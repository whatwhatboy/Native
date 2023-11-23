#include "handler.h"
#include "src/utility/common/common.h"
#pragma comment(lib, "Zydis.lib")
#include <Zydis/Zydis.h>
#include <MinHook/src/hde/hde64.h>
#include "Disassembler.h"
#include <src/framework/notifications/notifications.h>

namespace Base::Exceptions {
	void exceptionContext::printRegisters() {
		LOG(Registers, "RAX: 0x{:X} || RSI: 0x{:X}", m_context.Rax, m_context.Rsi);
		LOG(Registers, "RBX: 0x{:X} || RDI: 0x{:X}", m_context.Rbx, m_context.Rdi);
		LOG(Registers, "RCX: 0x{:X} || RBP: 0x{:X}", m_context.Rcx, m_context.Rbp);
		LOG(Registers, "RDX: 0x{:X} || RSP: 0x{:X}", m_context.Rdx, m_context.Rsp);
		LOG(Registers, "R8: 0x{:X} || R9: 0x{:X}", m_context.R8, m_context.R9);
		LOG(Registers, "R10: 0x{:X} || R11: 0x{:X}", m_context.R10, m_context.R11);
		LOG(Registers, "R12: 0x{:X} || R13: 0x{:X}", m_context.R12, m_context.R13);
		LOG(Registers, "R14: 0x{:X} || R15: 0x{:X}", m_context.R14, m_context.R15);
	}
	uint8_t getInstructionLength(uint8_t* code) {
		hde64s hde{};
		if (uint8_t len = hde64_disasm((void*)code, &hde); len) {
			return len;
		}
		else if (uint8_t len = x64::getInstructionLength(code); len) {
			return len;
		}
		else {
			ZyanU64 OpcodeAddress{ (uint64_t)code };
			ZydisDisassembledInstruction instruction{};
			if (ZYAN_SUCCESS(ZydisDisassembleIntel(ZYDIS_MACHINE_MODE_LONG_64, OpcodeAddress, reinterpret_cast<void*>(OpcodeAddress), 32, &instruction))) {
				return instruction.info.length;
			}
		}
		return NULL;
	}
	bool attemptStackRecovery(PEXCEPTION_POINTERS exceptionInfo) {
		auto& ctx = exceptionInfo->ContextRecord;
		if (const auto len = getInstructionLength(reinterpret_cast<uint8_t*>(ctx->Rip)); len) {
			ctx->Rip += len;
			return true;
		}
		else {
		}
		return false;
	}
	std::string getExceptionType(ULONG_PTR type) {
		if (auto t = g_exceptionErrorReasons.find(type); t != g_exceptionErrorReasons.end()) {
			return t->second;
		}
		return "unknown";
	}
	LONG CALLBACK onExceptionCallback(PEXCEPTION_POINTERS exceptionInfo) {
		stackWalker sw(StackWalker::AfterExcept);
		exceptionContext ctx{ exceptionInfo };
		if (!ctx.m_fileoffset.empty()) {
			switch (ctx.m_code) {
			case CONTROL_C_EXIT: { return EXCEPTION_CONTINUE_EXECUTION; } break;
			case EXCEPTION_BREAKPOINT: { return EXCEPTION_CONTINUE_SEARCH; } break;
			case EXCEPTION_ACCESS_VIOLATION: {
				std::stringstream exceptionAddr{};
				auto exceptionTypeStr = getExceptionType(ctx.m_type);
				auto exceptionName = !g_exceptionErrorReasons[ctx.m_code].empty() ? g_exceptionErrorReasons[ctx.m_code] : std::to_string(ctx.m_code);
				exceptionAddr << std::hex << std::uppercase << ctx.m_deathAddress;
				LOG(Exception, "The game suffered an fatal exception, you may need to restart the game. ({} at {}, reason of {} was {}{})", exceptionName.c_str(), ctx.m_fileoffset, exceptionName.c_str(), exceptionTypeStr.c_str(), ctx.m_type != 8 && exceptionName != "unknown" ? "" : exceptionAddr.str().c_str());
			} break;
			default: {
				auto exceptionName = !g_exceptionErrorReasons[ctx.m_code].empty() ? g_exceptionErrorReasons[ctx.m_code] : std::to_string(ctx.m_code);
				LOG(Exception, "The game suffered a exception of unknown severity, you may need to restart the game. ({} at {}, reason of exception is unknown)", exceptionName.c_str(), ctx.m_fileoffset);
			}
			}
		}
		LOG(Exception, "Dumping registers...");
		ctx.printRegisters();
		LOG(Exception, "Showing callstack...");
		sw.ShowCallstack(GetCurrentThread(), &ctx.m_context);
		if (attemptStackRecovery(exceptionInfo)) {
			return EXCEPTION_CONTINUE_EXECUTION;
			LOG(Exception, "Attempting exception search for an valid point in the stack...");
		}
		else {
			LOG(Exception, "Failed stack recovery, re-attempting exception search for an valid point in the stack...");
		}
		return EXCEPTION_CONTINUE_SEARCH;
	}
	bool onExceptionCallback_TryExcept(PEXCEPTION_POINTERS exceptionInfo) {
		if (onExceptionCallback(exceptionInfo) != EXCEPTION_CONTINUE_EXECUTION)
			return false;
		return true;
	}
	LONG CALLBACK exceptionHandler(PEXCEPTION_POINTERS exceptionInfo) {
		return onExceptionCallback(exceptionInfo);
	}
	LONG CALLBACK unhandledExceptionHandler(PEXCEPTION_POINTERS exceptionInfo) {
		return onExceptionCallback(exceptionInfo);
	}
	void init() {
		vecExcepHandlerHandle = AddVectoredExceptionHandler(FALSE, PVECTORED_EXCEPTION_HANDLER(exceptionHandler));
		SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER(unhandledExceptionHandler));
	}
	void uninit() {
		if (vecExcepHandlerHandle)
			RemoveVectoredExceptionHandler(vecExcepHandlerHandle);
	}
}