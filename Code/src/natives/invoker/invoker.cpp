#include "Invoker.h"
#include "src/Memory/Pointers/Pointers.h"
#include "src/Core/Logger/Logger.h"
#include "src/Natives/Natives.h"

extern "C" void	_call_asm(void* context, void* function, void* ret);
namespace Base {
    enum SCRIPT {
        GET_HASH_OF_THIS_SCRIPT_NAME = 0x8A1C8B1738FFE87E
    };
    inline std::vector<uint64_t> g_native_blacklist{};
    inline bool is_blacklisted(uint64_t hash) {
        if (g_native_blacklist.empty())
            return false;
        for (auto& nv : g_native_blacklist) {
            if (nv == hash)
                return true;
        }
        return false;
    }
    inline void add_to_blacklist(uint64_t hash) {
        if (is_blacklisted(hash))
            return;
        if (g_invoker->m_cache[GET_HASH_OF_THIS_SCRIPT_NAME]) {
            NativeCallContext ctx{};
            ctx.Reset();
            g_invoker->m_cache[GET_HASH_OF_THIS_SCRIPT_NAME](&ctx);
            if (*ctx.GetReturn<Hash>()) {
                g_native_blacklist.push_back(hash);
            }
        }
    }
    NativeCallContext::NativeCallContext() {
        Return = &m_ReturnStack[0];
        Args = &m_ArgStack[0];
    }
    void Invoker::cache_handlers() {
        for (auto& pair : g_crossmap) {
            m_cache.emplace(pair.hash, g_pointers->m_script_native_registration_table->get_handler(pair.translatedHash));
        }
    }
    void Invoker::begin() {
        m_call_context.Reset();
    }
    void Invoker::Call(uint64_t hash, NativeCallContext* cxt) {
        if (is_blacklisted(hash)) {
            return;
        }
        if (const auto& it = m_cache.find(hash); it != m_cache.end()) {
            if (const auto& handler = it->second) {
                if (const auto& callCtx = dynamic_cast<rage::scrNativeCallContext*>(cxt)) {
                    _call_asm(callCtx, handler, g_pointers->m_native_return_address);
                }
                else {
                   
                    return;
                }
            }
            else {
                add_to_blacklist(hash);
                return;
            }
        }
        else {
            add_to_blacklist(hash);
            return;
        }
    }
    void Invoker::end(rage::scrNativeHash hash) {
        if (is_blacklisted(hash)) {
            return;
        }
        if (const auto& it = m_cache.find(hash); it != m_cache.end()) {
            if (const auto& handler = it->second) {
                if (const auto& callCtx = dynamic_cast<rage::scrNativeCallContext*>(&m_call_context)) {
                    _call_asm(callCtx, handler, g_pointers->m_native_return_address);
                    g_pointers->m_fix_vectors(&m_call_context);
                }
                else {
                    LOG(Info, "Failed to get the call ctx while invoking 0x{:X}", hash);
                    return;
                }
            }
            else {
                LOG(Info, "Failed to find scrCommand 0x{:X}", hash);
                add_to_blacklist(hash);
                return;
            }
        }
        else {
            LOG(Info, "Failed to translate the hash for 0x{:X}", hash);
            add_to_blacklist(hash);
            return;
        }
    }
}