#pragma once
#include "base_submenu.h"
#include "src/memory/pointers/pointers.h"

namespace Base::Framework {
	class player_submenu : public BaseSubmenu<player_submenu> {
	public:
		explicit player_submenu() = default;
		~player_submenu() noexcept = default;
		explicit player_submenu(u8* selectedPlayer, std::uint32_t id, std::function<void(player_submenu*)> action) :
			m_SelectedPlayer(selectedPlayer) {
			set_id(id);
			set_action(std::move(action));
		}
	public:
		player_submenu(player_submenu const&) = default;
		player_submenu& operator=(player_submenu const&) = default;
		player_submenu(player_submenu&&) = default;
		player_submenu& operator=(player_submenu&&) = default;
	public:
		str get_name() override {
			return g_pointers->m_get_player_name(*m_SelectedPlayer);
		}
	private:
		u8* m_SelectedPlayer;
	};
}
