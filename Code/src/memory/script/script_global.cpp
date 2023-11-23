#include "script_global.h"

#include "src/memory/pointers/pointers.h"

namespace Base {
	void* script_global::get() const {
		return g_pointers->m_global_base[m_index >> 0x12 & 0x3F] + (m_index & 0x3FFFF);
	}
}