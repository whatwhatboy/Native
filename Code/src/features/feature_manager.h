#include "src/fiber/fiber_helper.h"
#include "src/fiber/script/manager/script_manager.h"
#include "src/fiber/script/fiber_script.h"
#include "submenus/player/player.h"
#include "submenus/weapon/weapon.h"
#include "submenus/vehicle/vehicle.h"
#include "submenus/world/world.h"
#include "types/toggle.h"
#include "utils/utils.h"
#include "types/choose.h"
#include "types/float.h"
#include "types/button.h"
#include "types/toggle_with_choose.h"
#include "types/toggle_with_number.h"
#include "types/keyboard.h"
#include <variant>
#include "submenus/network/network.h"
#include "submenus/misc/misc.h"
#define misc_name "Miscellaneous"
#define get_func(CODE_BLOCK) [] { CODE_BLOCK(); }
#define color_modifiers 0, 255, 1, 0

#define basic_toggle_function(name1 ,name, name2, code) g_feature_manager.add<toggle_option>(name, name2, "", &name1, [=] { if (!name1) return; code; }, [=] { code; })

namespace Base {
	class feature_manager {
	public:
		std::map<ccp, base_option*> m_commands{}; 
	public:
		template <typename type, typename ...targs>
		void add(targs&&... args) {
			type* cmd{ new type(std::forward<targs>(args)...) };
			m_commands.insert({ cmd->m_id.c_str(), std::move(cmd) });
		}
		void remove(ccp id) {
			if (auto it{ m_commands.find(id) }; it != m_commands.end()) {
				delete it->second;
				m_commands.erase(it);
			}
		}
	public:
		template <typename t>
		t* get_command(ccp id) {
			for (auto& e : m_commands) {
				auto& c{ e.second };
				if (c->m_id == id) {
					return (t*)c;
				}
			}
			return nullptr;
		}
	public:
		bool does_exist(ccp id) {
			for (auto& e : m_commands) {
				auto& c{ e.second };
				if (c->m_id == id) {
					return true;
				}
			}
			return false;
		}
		bool does_exist(str id) {
			for (auto& e : m_commands) {
				auto& c{ e.second };
				if (c->m_id == id) {
					return true;
				}
			}
			return false;
		}
		bool does_exist(base_option* base) {
			for (auto& e : m_commands) {
				auto& c{ e.second };
				if (c->m_id == base->m_id) {
					return true;
				}
			}
			return false;	
		}
		void tick() {
			for (auto& c : m_commands) {
				if (c.second->m_looped) {
					if (c.second->m_action) {
						c.second->m_action();
					}
				}
			}
		}
	};
	inline feature_manager g_feature_manager;


	inline void tick_features() {
		g_feature_manager.tick();
	}
	inline void add_features_once() {
		g_player_options.add();
		g_weapon_options.add();
		g_world_options.add();
		g_network_options.add();
		g_misc_options.add();

		if (g_pointers->m_vfx_wheel.first) {
			m_wheel_cache = (vfx_wheel*)malloc((sizeof(vfx_wheel) * g_pointers->m_vfx_wheel.second) * 4);
			memcpy(m_wheel_cache, g_pointers->m_vfx_wheel.first, (sizeof(vfx_wheel) * g_pointers->m_vfx_wheel.second) * 4);
		}

		g_vehicle_options.add();
	}
}