#include "src/hooking/hooking.h"
#include "src/memory/Pointers/Pointers.h"
#include <src/framework/notifications/notifications.h>
namespace Base {
	template<typename T>
	inline bool is_valid_ptr(T ptr) {
		uint64_t address = (uint64_t)ptr;
		if (address < 0x5000) return false;
		if ((address & 0xFFFFFFFF) == 0xFFFFFFFF) return false;
		if ((address & 0xFFFFFFFF) <= 0xFF) return false;

		if (*(uint8_t*)((uint64_t)&address + 6) != 0 || *(uint8_t*)((uint64_t)&address + 7) != 0) return false;

		return true;
	}

	bool hooks::receive_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, i32 object_id, i32 object_flag, rage::datBitBuffer* buffer, i32 timestamp) {
		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN) {
			if (g_protection_manager.m_crashes.m_sync_mismatch) {
				g_notifications->send("Protections", std::format("Blocked 'sync mismatch' crash from {}", src->get_name()));
				return true;
			}
		}
		g_syncing_player = src;
		g_syncing_object_type = object_type;
		RET_CALL_DECL(receive_clone_create, mgr, src, dst, object_type, object_id, object_flag, buffer, timestamp);
	}

	bool is_network_object_owner(CNetGamePlayer* src, rage::netObject* netObject) {
		return src != nullptr && netObject != nullptr && src->m_player_id != -1 && (src->m_player_id == netObject->m_owner_id || src->m_player_id == netObject->m_next_owner_id);
	}

	void hooks::receive_clone_create_ack(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, u16 object_id, i32 ack_code) {

		rage::netObject* obj{ g_pointers->m_get_net_object(mgr, object_id, true) };
		int16_t object_type{ obj == nullptr ? -1 : obj->m_object_type };

		if (object_type < (int16_t)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type >(int16_t)eNetObjType::NET_OBJ_TYPE_TRAIN) {
			if (g_protection_manager.m_crashes.m_sync_mismatch) {
				g_notifications->send("Protections", std::format("Blocked 'sync mismatch' crash from {}", src->get_name()));
				return;
			}
		}

		g_syncing_player = src;
		RET_CALL_DECL(receive_clone_create_ack, mgr, src, dst, object_id, ack_code);
	}

	bool hooks::receive_clone_remove(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, i32 object_id, i32 timestamp) {
		rage::netObject* obj{ g_pointers->m_get_net_object(mgr, object_id, true) };

		if (is_valid_ptr((*g_pointers->m_ped_factory)->m_local_ped)) {
			if (obj == (*g_pointers->m_ped_factory)->m_local_ped->m_net_object) {
				if (g_protection_manager.m_crashes.m_sync_mismatch) {
					g_notifications->send("Protections", std::format("Blocked 'sync mismatch' crash from {}", src->get_name()));
					return true;
				}
			}
		}
		g_syncing_player = src;
		RET_CALL_DECL(receive_clone_remove, mgr, src, dst, object_id, timestamp);
	}

	eAckCode hooks::receive_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, u16 object_id, rage::datBitBuffer* buffer, u16 unk, u32 timestamp) {

		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN) {
			if (g_protection_manager.m_crashes.m_bad_sync) {
				g_notifications->send("Protections", std::format("Blocked 'bad sync' crash from {}", src->get_name()));
				return eAckCode::ACKCODE_FAIL;
			}
		}

		if (auto net_obj = g_pointers->m_get_net_object(mgr, object_id, true); net_obj && net_obj->m_object_type != (int16_t)object_type) {
			if (g_protection_manager.m_crashes.m_sync_mismatch) {
				g_notifications->send("Protections", std::format("Blocked 'sync mismatch' crash from {}", src->get_name()));
				return eAckCode::ACKCODE_FAIL;
			}
		}

		g_syncing_object_type = object_type;

		g_syncing_player = src;
		RET_CALL_DECL(receive_clone_sync, mgr, src, dst, object_type, object_id, buffer, unk, timestamp);
	}

	void hooks::receive_clone_sync_ack(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, rage::datBitBuffer* buffer, u16 object_id, i32 ack_code) {

		rage::netObject* obj{ g_pointers->m_get_net_object(mgr, object_id, true) };
		int16_t object_type{ obj == nullptr ? -1 : obj->m_object_type };

		if (object_type < (int16_t)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type >(int16_t)eNetObjType::NET_OBJ_TYPE_TRAIN) {
			if (g_protection_manager.m_crashes.m_sync_mismatch) {
				//g_notifications->send("Protections", std::format("Blocked 'sync mismatch' crash from {}", src->get_name())); - to many false positives.
				return;
			}
		}
		g_syncing_player = src;

		RET_CALL_DECL(receive_clone_sync_ack, mgr, src, dst, buffer, object_id, ack_code);
	}
}