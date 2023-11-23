#pragma once
#include "src/memory/pointers/pointers.h"
#include "src/utility/enum.h"
#include "src/hooking/dat_bit_buffer/dat_bit_buffer.h"

namespace Base
{
	class packet
	{
	public:
		char m_data[0x4000]{};
		dat_bit_buffer m_buffer;

		packet();
		void send(uint32_t msg_id);
		void send(CNetGamePlayer* player, int connection_id);
		void send(int peer_id, int connection_id);

		operator dat_bit_buffer& () {
			return m_buffer;
		}

		template<typename T>
		void write(T data, int length) {
			m_buffer.Write<T>(data, length);
		}

		void write_message(eNetMessage message) {
			write<int>(0x3246, 14);
			if ((int)message > 0xFF)
			{
				write<bool>(true, 1);
				write<eNetMessage>(message, 16);
			}
			else
			{
				write<bool>(false, 1);
				write<eNetMessage>(message, 8);
			}
		}

		void write_peer_id(uint64_t peer_id) {
			char b[8];
			dat_bit_buffer buf(b, 8);
			buf.WriteQWord(peer_id, 64);
			m_buffer.WriteArray(b, 8 * buf.GetDataLength());
		}
	};
}