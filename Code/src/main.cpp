#include "core/core/core.h"
#include <src/utility/common/common.h>
#include <ETAUTH/pipe.hpp>
#include <ETAUTH/socket.hpp>
#include <ETAUTH/antidebug.hpp>
#include <ETAUTH/utils.hpp>
#include <VLIZER/VirtualizerSDK.h>
using namespace Base;
BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID) {
    g_Module = hInstance;
    switch (reason) {
    case DLL_PROCESS_ATTACH: {
#ifndef DEV
        VIRTUALIZER_LION_BLACK_START

        auth::antidebug::Init();
        auth::antidebug::run();
        int piperesult{ auth::pipe::setupPipe() };
        if (piperesult == 0)
            auth::socket::login(4);
        else
            auth::utils::nuke();
        if (auth::socket::GetStatus() != auth::socket::authstatus::E_SUCCESS) {
            auth::utils::nuke();
        }
#endif
        core::main::attach();
#ifndef DEV
        VIRTUALIZER_LION_BLACK_END
#endif
    }
    break;
    case DLL_PROCESS_DETACH: {
#ifndef DEV
        VIRTUALIZER_LION_BLACK_START
        auth::pipe::shutDown();
#endif
        core::main::detach();
#ifndef DEV
        VIRTUALIZER_LION_BLACK_END
#endif
    }
    break;
    }
    
    return TRUE;
}
