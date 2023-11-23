#pragma once
#include "src/hooking/hooking.h"
#include "src/memory/pointers/pointers.h"
#include "src/rage/base/CObject.hpp"
#include "src/features/utils/model_info.h"
#include "src/rage/netsync/nodes/vehicle/CVehicleProximityMigrationDataNode.hpp"
#include "src/rage/netsync/nodes/player/CPlayerSectorPosNode.hpp"

namespace Base {
	struct sync_node_id
	{
		Hash id;
		const char* name;

		constexpr sync_node_id() {
			id = 0;
			name = "INVALID NODE ID!";
		}

		template<size_t N>
		constexpr sync_node_id(char const (&idd)[N]) {
			id = rage::consteval_joaat(idd);
			name = idd;
		}

		constexpr operator Hash() const {
			return id;
		}
	};
	using sync_node_vft_to_ids = std::unordered_map<uint64_t, sync_node_id>;
	using sync_tree_node_array_index_to_node_id_t = std::vector<sync_node_id>;
	struct sync_node_finder_t
	{
		static constexpr size_t sync_tree_count = size_t(eNetObjType::NET_OBJ_TYPE_TRAIN) + 1;

		std::array<sync_node_vft_to_ids, sync_tree_count> sync_trees_sync_node_addr_to_ids;

		std::array<sync_tree_node_array_index_to_node_id_t, sync_tree_count> sync_trees_node_array_index_to_node_id = {
			{
				// AUTOMOBILE
				{
					{"CVehicleCreationDataNode"},
					{"CAutomobileCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// BIKE
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},
					{"CBikeGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// BOAT
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},
					{"CBoatGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// DOOR
				{
					{"CDoorCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDoorScriptInfoDataNode"},
					{"CDoorScriptGameStateDataNode"},

					{"CDoorMovementDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
				},
				// HELI
				{
					{"CVehicleCreationDataNode"},
					{"CAutomobileCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},
					{"CHeliHealthDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},
					{"CHeliControlDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// OBJECT
				{
					{"CObjectCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CObjectGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CObjectScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CPhysicalHealthDataNode"},

					{"CSectorDataNode"},
					{"CObjectSectorPosNode"},
					{"CObjectOrientationNode"},
					{"CPhysicalVelocityDataNode"},
					{"CPhysicalAngVelocityDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
				},
				// PED
				{
					{"CPedCreationDataNode"},
					{"CPedScriptCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CPedGameStateDataNode"},
					{"CPedComponentReservationDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CPedScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPedAttachDataNode"},
					{"CPedHealthDataNode"},
					{"CPedMovementGroupDataNode"},
					{"CPedAIDataNode"},
					{"CPedAppearanceDataNode"},

					{"CPedOrientationDataNode"},
					{"CPedMovementDataNode"},

					{"CPedTaskTreeDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},

					{"CSectorDataNode"},
					{"CPedSectorPosMapNode"},
					{"CPedSectorPosNavMeshNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CPedInventoryDataNode"},
					{"CPedTaskSequenceDataNode"},
				},
				// PICKUP
				{
					{"CPickupCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},

					{"CPickupScriptGameStateNode"},
					{"CPhysicalGameStateDataNode"},
					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},
					{"CPhysicalHealthDataNode"},

					{"CPhysicalAttachDataNode"},

					{"CSectorDataNode"},
					{"CPickupSectorPosNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CPhysicalAngVelocityDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
				},
				// PICKUP_PLACEMENT
				{
					{"CPickupPlacementCreationDataNode"},
					{"CMigrationDataNode"},
					{"CGlobalFlagsDataNode"},
					{"CPickupPlacementStateDataNode"},
				},
				// PLANE
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},
					{"CPlaneGameStateDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},
					{"CPlaneControlDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// SUBMARINE
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},
					{"CSubmarineGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},
					{"CSubmarineControlDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// PLAYER
				{
					{"CPlayerCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CPedGameStateDataNode"},
					{"CPedComponentReservationDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPlayerGameStateDataNode"},

					{"CPedAttachDataNode"},
					{"CPedHealthDataNode"},
					{"CPedMovementGroupDataNode"},
					{"CPedAIDataNode"},
					{"CPlayerAppearanceDataNode"},
					{"CPlayerPedGroupDataNode"},
					{"CPlayerAmbientModelStreamingNode"},
					{"CPlayerGamerDataNode"},
					{"CPlayerExtendedGameStateNode"},

					{"CPedOrientationDataNode"},
					{"CPedMovementDataNode"},

					{"CPedTaskTreeDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},
					{"CPedTaskSpecificDataNode"},

					{"CSectorDataNode"},
					{"CPlayerSectorPosNode"},
					{"CPlayerCameraDataNode"},
					{"CPlayerWantedAndLOSDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
				},
				// TRAILER
				{
					{"CVehicleCreationDataNode"},
					{"CAutomobileCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
				// TRAIN
				{
					{"CVehicleCreationDataNode"},

					{"CGlobalFlagsDataNode"},
					{"CDynamicEntityGameStateDataNode"},
					{"CPhysicalGameStateDataNode"},
					{"CVehicleGameStateDataNode"},
					{"CTrainGameStateDataNode"},

					{"CEntityScriptGameStateDataNode"},
					{"CPhysicalScriptGameStateDataNode"},
					{"CVehicleScriptGameStateDataNode"},
					{"CEntityScriptInfoDataNode"},

					{"CPhysicalAttachDataNode"},
					{"CVehicleAppearanceDataNode"},
					{"CVehicleDamageStatusDataNode"},
					{"CVehicleComponentReservationDataNode"},
					{"CVehicleHealthDataNode"},
					{"CVehicleTaskDataNode"},

					{"CSectorDataNode"},
					{"CSectorPositionDataNode"},
					{"CEntityOrientationDataNode"},
					{"CPhysicalVelocityDataNode"},
					{"CVehicleAngVelocityDataNode"},

					{"CVehicleSteeringDataNode"},
					{"CVehicleControlDataNode"},
					{"CVehicleGadgetDataNode"},

					{"CMigrationDataNode"},
					{"CPhysicalMigrationDataNode"},
					{"CPhysicalScriptMigrationDataNode"},
					{"CVehicleProximityMigrationDataNode"},
				},
			},
		};
	};
	class sync_node_finder
	{
	private:
		static inline sync_node_finder_t finder;
		static inline bool inited = false;

	public:
		static const sync_node_id& find(eNetObjType obj_type, uintptr_t addr)
		{
			return finder.sync_trees_sync_node_addr_to_ids[(int)obj_type][addr];
		}

		static sync_node_vft_to_ids& get_object_nodes(eNetObjType obj_type)
		{
			return finder.sync_trees_sync_node_addr_to_ids[(int)obj_type];
		}

		static bool is_initialized()
		{
			return inited;
		}

		static void init()
		{
			for (int i = (int)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE; i <= (int)eNetObjType::NET_OBJ_TYPE_TRAIN; i++)
			{
				if (i == (int)eNetObjType::NET_OBJ_TYPE_TRAILER)
					continue;

				rage::netSyncTree* tree = g_pointers->m_get_sync_tree_for_type(*g_pointers->m_network_object_mgr, i);

				if (tree->m_child_node_count != finder.sync_trees_node_array_index_to_node_id[i].size())
				{
					throw std::runtime_error("Failed to cache nodes");
				}

				for (int j = 0; j < tree->m_child_node_count; j++)
				{
					const uintptr_t addr = (uintptr_t)tree->m_child_nodes[j];

					const sync_node_id node_id = finder.sync_trees_node_array_index_to_node_id[i][j];

					finder.sync_trees_sync_node_addr_to_ids[i][addr] = node_id;
				}
			}

			inited = true;
		}
	};

	inline CObject* get_entity_attached_to(CObject* entity)
	{
		if (!entity)
			return nullptr;

		if (!entity->gap50)
			return nullptr;

		__int64 component = *(__int64*)((__int64)(entity->gap50) + 0x48);

		if (!component)
			return nullptr;

		int unk_count = *(int*)(component + 0x5C) & 0xF;

		if (unk_count < 2)
			return nullptr;

		return *(CObject**)(component);
	}

	inline bool is_attachment_infinite(rage::netObject* object, uint16_t attached_to_net_id, int from_bone, int to_bone)
	{
		if (object == nullptr)
			return false;

		auto target = g_pointers->m_get_net_object(*g_pointers->m_network_object_mgr, attached_to_net_id, false);

		while (target)
		{
			if (target == object)
				return true;

			auto next = get_entity_attached_to(target->GetGameObject());

			if (!next)
				return false;

			if (!next->m_net_object)
				return false;

			target = next->m_net_object;
		}

		return false;
	}

	inline bool is_in_vehicle(CPed* ped, CVehicle* vehicle)
	{
		if (!ped || !vehicle)
			return false;

		if (ped == vehicle->m_driver)
			return true;

		for (int i = 0; i < 15; i++)
			if (vehicle->m_passengers[i] == ped)
				return true;

		return false;
	}
	auto get_local_player() {
		return (*g_pointers->m_ped_factory)->m_local_ped;
	}
	inline bool is_local_player_an_occupant(CVehicleProximityMigrationDataNode* node)
	{
		for (int i = 0; i < 16; i++)
		{
			if (node->m_has_occupants[i] && node->m_occupants[i] == get_local_player()->m_net_object->m_object_id)
				return true;
		}

		return false;
	}

	inline bool is_invalid_override_pos(float x, float y)
	{
		bool crash = ((int)round(fmaxf(0.0, (x + 149.0) - -8192.0) / 75.0)) >= 255 || ((int)round(fmaxf(0.0, (y + 149.0) - -8192.0) / 75.0)) >= 255;

		return crash;
	}

	inline std::string get_task_type_string(int type)
	{
		std::string buffer = "";

		for (auto& value : task_type_names)
		{
			if (value.first == type)
			{
				buffer += value.second;
				buffer += '|';
			}

			if (value.first > type)
				break; // a minor optimization
		}

		if (buffer.length() > 1)
			buffer.pop_back();
		else
			buffer = "Unknown";

		buffer += " (" + std::to_string(type) + ")";

		return buffer;
	}

	inline bool is_valid_clan_tag(char* data, bool system_clan)
	{
		int length = strlen(data);

		if (length <= (system_clan ? 2 : 3))
			return false;

		for (int i = 0; i < length; i++)
		{
			if (data[i] >= '0' && data[i] <= '9')
				continue;

			if (data[i] >= 'A' && data[i] <= 'Z')
				continue;

			if (data[i] >= 'a' && data[i] <= 'z')
				continue;

			return false;
		}

		return true;
	}

	inline bool is_valid_interior_game(uint32_t interior_index)
	{
		if ((int)(__int64)*(int16_t*)&interior_index >= (int)(*g_pointers->m_interior_proxy_pool)->m_size) // this is the bug, should have been an unsigned compare instead
			return false;

		// some more checks that aren't broken

		auto a1 = (uint16_t*)&interior_index;

		__int16 v2;          // ax
		unsigned __int16 v3; // ax
		bool v4;             // cf
		bool v5;             // zf
		unsigned __int16 v6; // ax

		if (*a1 == 0xFFFF)
			return false;

		v2 = a1[1];
		if ((v2 & 1) != 0)
		{
			v6 = v2 >> 2;
			v4 = v6 < 0xFFu;
			v5 = v6 == 255;
		}
		else
		{
			v3 = v2 >> 2;
			v4 = v3 < 0x1Fu;
			v5 = v3 == 31;
		}
		return v4 || v5;
	}

	inline bool is_valid_interior_fixed(uint32_t interior_index)
	{
		if ((uint32_t)(__int64)*(int16_t*)&interior_index >= (uint32_t)(*g_pointers->m_interior_proxy_pool)->m_size)
			return false;

		return true;
	}

	bool is_crash_ped_task(eTaskTypeIndex type)
	{
		if (type == eTaskTypeIndex::CTaskUnalerted && g_syncing_object_type == eNetObjType::NET_OBJ_TYPE_PLAYER)
			return true;

		return false;
	}

	bool is_crash_vehicle_task(eTaskTypeIndex type)
	{
		switch (type)
		{
		case eTaskTypeIndex::CTaskVehicleGoToPlane:
		case eTaskTypeIndex::CTaskVehicleLandPlane:
		case eTaskTypeIndex::CTaskVehiclePlayerDrivePlane:
		case eTaskTypeIndex::CTaskVehiclePlaneChase: return g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_PLANE;
		case eTaskTypeIndex::CTaskVehicleGoToHelicopter:
		case eTaskTypeIndex::CTaskVehiclePoliceBehaviourHelicopter:
		case eTaskTypeIndex::CTaskVehiclePlayerDriveHeli:
		case eTaskTypeIndex::CTaskVehicleLand:
		case eTaskTypeIndex::CTaskVehicleHeliProtect: return g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_HELI;
		case eTaskTypeIndex::CTaskVehicleGoToBoat:
		case eTaskTypeIndex::CTaskVehicleCruiseBoat:
		case eTaskTypeIndex::CTaskVehicleFleeBoat:
		case eTaskTypeIndex::CTaskVehiclePoliceBehaviourBoat:
		case eTaskTypeIndex::CTaskVehiclePlayerDriveBoat:
			return g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_BOAT;
		case eTaskTypeIndex::CTaskVehicleGoToSubmarine:
		case eTaskTypeIndex::CTaskVehiclePlayerDriveSubmarine:
			return g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_SUBMARINE;
		case eTaskTypeIndex::CTaskVehicleFleeAirborne:
			return g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_HELI && g_syncing_object_type != eNetObjType::NET_OBJ_TYPE_PLANE;
		}

		return false;
	}

	eNetObjType vehicle_type_to_object_type(eVehicleType type)
	{
		switch (type)
		{
		case eVehicleType::VEHICLE_TYPE_CAR:
		case eVehicleType::VEHICLE_TYPE_SUBMARINECAR:
		case eVehicleType::VEHICLE_TYPE_AUTOGYRO:
		case eVehicleType::VEHICLE_TYPE_QUADBIKE:
		case eVehicleType::VEHICLE_TYPE_AMPHIBIOUS_QUADBIKE:
		case eVehicleType::VEHICLE_TYPE_AMPHIBIOUS_AUTOMOBILE: return eNetObjType::NET_OBJ_TYPE_AUTOMOBILE;
		case eVehicleType::VEHICLE_TYPE_HELI:
		case eVehicleType::VEHICLE_TYPE_BLIMP: return eNetObjType::NET_OBJ_TYPE_HELI;
		case eVehicleType::VEHICLE_TYPE_PLANE: return eNetObjType::NET_OBJ_TYPE_PLANE;
		case eVehicleType::VEHICLE_TYPE_BIKE:
		case eVehicleType::VEHICLE_TYPE_BICYCLE: return eNetObjType::NET_OBJ_TYPE_BIKE;
		case eVehicleType::VEHICLE_TYPE_TRAILER: return eNetObjType::NET_OBJ_TYPE_TRAILER;
		case eVehicleType::VEHICLE_TYPE_TRAIN: return eNetObjType::NET_OBJ_TYPE_TRAIN;
		case eVehicleType::VEHICLE_TYPE_SUBMARINE: return eNetObjType::NET_OBJ_TYPE_SUBMARINE;
		case eVehicleType::VEHICLE_TYPE_BOAT: return eNetObjType::NET_OBJ_TYPE_BOAT;
		case eVehicleType::VEHICLE_TYPE_DRAFT: return eNetObjType::NET_OBJ_TYPE_AUTOMOBILE; // this appears to be unused
		}

		return eNetObjType::NET_OBJ_TYPE_AUTOMOBILE;
	}

	bool get_player_sector_pos(rage::netSyncNodeBase* node, float& x, float& y, rage::netObject* object)
	{
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling)
			{
				if (get_player_sector_pos(child, x, y, object))
					return true;
			}
		}
		else if (node->IsDataNode())
		{
			const auto& node_id = sync_node_finder::find((eNetObjType)object->m_object_type, (uintptr_t)node);

			if ((((CProjectBaseSyncDataNode*)node)->flags & 1) == 0)
				return false;

			if (node_id == sync_node_id("CPlayerSectorPosNode"))
			{
				CPlayerSectorPosNode* player_sector_pos_node = (CPlayerSectorPosNode*)(node);
				x = player_sector_pos_node->m_sector_pos.x;
				y = player_sector_pos_node->m_sector_pos.y;
				return true;
			}
		}
		return false;
	}

}