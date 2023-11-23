#pragma once
#include "src/natives/natives.h"
#include "src/fiber/fiber_helper.h"
#include "script_handler.h"
#include <src/memory/script/script_local.h>
#include "bits.h"
#include <src/rage/script/tlsContext.hpp>

namespace Base {
	static inline const script_global launcher_global(2756336);
	inline GtaThread* find_script_thread(rage::joaat_t hash) {
		for (auto thread : *g_pointers->m_script_threads) {
			if (thread && thread->m_context.m_thread_id && thread->m_handler && thread->m_script_hash == hash) {
				return thread;
			}
		}

		return nullptr;
	}
	inline bool force_host(rage::joaat_t hash) {
		if (auto launcher{ find_script_thread(hash) }; launcher && launcher->m_net_component) {
			for (int i = 0; !((CGameScriptHandlerNetComponent*)launcher->m_net_component)->is_local_player_host(); i++) {
				if (i > 200)
					return false;

				((CGameScriptHandlerNetComponent*)launcher->m_net_component)->send_host_migration_event(g_pointers->m_get_net_player(PLAYER::PLAYER_ID()));
				fiber::current()->wait(10ms);

				if (!launcher->m_stack || !launcher->m_net_component)
					return false;
			}
		}

		return true;
	}
    inline void start_launcher_script(int script_id) {
        g_fiber_pool.queue([script_id] {
            auto check_players_in_state = [](GtaThread* launcher, int state) -> bool {
                if (!launcher->m_net_component) return false;

                for (auto i = 0; i < 31; i++) {
                    if (auto player{ g_pointers->m_get_net_player(i) }; player && player->is_valid()) {
                        if (((CGameScriptHandlerNetComponent*)launcher->m_net_component)->is_player_a_participant(player)) {
                            if (*script_local(launcher->m_stack, 233).at(player->m_player_id, 3).at(2).as<int*>() == state)
                                return true;
                        }
                    }
                }
                return false;
            };

            if (auto launcher{ find_script_thread(rage::joaat("am_launcher")) }) {
                if (!force_host(rage::joaat("am_launcher"))) return;
                launcher->m_context.m_state = rage::eThreadState::unk_3;
                auto run_until_timeout = [&](int state, int target_state) {
                    for (int i = 0; check_players_in_state(launcher, state) && i <= 200; i++) {
                        *launcher_global.at(3).at(1).as<int*>() = 0;
                        *launcher_global.at(2).as<int*>() = target_state;
                        fiber::current()->wait(10ms);
                    }
                };

                run_until_timeout(5, 6);
                run_until_timeout(6, 7);
                run_until_timeout(7, 0);

                bits::set_bit(launcher_global.at(1).as<int*>(), 1);
                *launcher_global.at(2).as<int*>() = 6;
                *script_local(launcher->m_stack, 233).at(PLAYER::PLAYER_ID(), 3).at(2).as<int*>() = 6;
                *launcher_global.at(3).at(1).as<int*>() = script_id;

                launcher->m_context.m_state = rage::eThreadState::running;
            }
        });
    }
	inline rage::scrThread* is_mission_started(const char* hash) {
        if (auto thread{ find_script_thread(rage::joaat(hash)) })
			return thread;

		return nullptr;
	}
	template<typename F, typename... Args>
	void execute_as_script(rage::scrThread* thread, F&& callback, Args&&... args) {
		auto tls_ctx = rage::tlsContext::get();
		auto og_thread = tls_ctx->m_script_thread;

		tls_ctx->m_script_thread = thread;
		tls_ctx->m_is_script_thread_active = true;

		std::invoke(std::forward<F>(callback), std::forward<Args>(args)...);

		tls_ctx->m_script_thread = og_thread;
		tls_ctx->m_is_script_thread_active = og_thread != nullptr;
	}

	template<typename F, typename... Args>
	void execute_as_script(rage::joaat_t script_hash, F&& callback, Args&&... args) {
		for (auto thread : *g_pointers->m_script_threads) {
			if (!thread || !thread->m_context.m_thread_id || thread->m_context.m_script_hash != script_hash)
				continue;

			execute_as_script(thread, callback, args...);
			return;
		}
	}

}
