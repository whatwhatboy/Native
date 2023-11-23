#include "src/features/feature_manager.h"
#include "types.h"

namespace Base {
	class hotkey_manager {
	public:
		std::map<str, hotkey*> m_hotkeys;
	public:
		void add(hotkey h);
		void remove(str id);
	public:
		int get_keycode_from_letter(str letter);
		void tick();
	} inline g_hotkey_manager;
}