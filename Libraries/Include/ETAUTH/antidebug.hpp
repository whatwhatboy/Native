#pragma once

namespace auth::antidebug {
	DWORD64 GetProcAddressCustom(void* base, std::string exportname);
	HANDLE customGetModuleHandle(std::string modulename);
	inline int resolveSysCall(std::string modulename, std::string exportname);
	void run();
	void Init();
}

