
#define RAGE_JOAAT rage::joaat
#include "src/rage/netsync/netSyncNodeBase.hpp"
#include "can_apply_data_helpers.h"
#include "src/rage/netsync/netSyncDataNode.hpp"
#include "src/rage/netsync/netSyncTree.hpp"
#include "src/rage/netsync/nodes/automobile/CAutomobileCreationNode.hpp"
#include "src/rage/netsync/nodes/door/CDoorCreationDataNode.hpp"
#include "src/rage/netsync/nodes/door/CDoorMovementDataNode.hpp"
#include "src/rage/netsync/nodes/door/CDoorScriptGameStateDataNode.hpp"
#include "src/rage/netsync/nodes/door/CDoorScriptInfoDataNode.hpp"
#include "src/rage/netsync/nodes/dynamic_entity/CDynamicEntityGameStateDataNode.hpp"
#include "src/rage/netsync/nodes/entity/CEntityScriptGameStateDataNode.hpp"
#include "src/rage/netsync/nodes/entity/CEntityScriptInfoDataNode.hpp"
#include "src/rage/netsync/nodes/object/CObjectCreationDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedAIDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedAttachDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedComponentReservationDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedCreationDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedGameStateDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedHealthDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedInventoryDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedMovementDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedOrientationDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedScriptCreationDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedTaskSequenceDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedTaskSpecificDataNode.hpp"
#include "src/rage/netsync/nodes/ped/CPedTaskTreeDataNode.hpp"
#include "src/rage/netsync/nodes/physical/CPhysicalAngVelocityDataNode.hpp"
#include "src/rage/netsync/nodes/physical/CPhysicalAttachDataNode.hpp"
#include "src/rage/netsync/nodes/physical/CPhysicalGameStateDataNode.hpp"
#include "src/rage/netsync/nodes/physical/CPhysicalHealthDataNode.hpp"
#include "src/rage/netsync/nodes/physical/CPhysicalMigrationDataNode.hpp"
#include "src/rage/netsync/nodes/physical/CPhysicalScriptGameStateDataNode.hpp"
#include "src/rage/netsync/nodes/physical/CPhysicalScriptMigrationDataNode.hpp"
#include "src/rage/netsync/nodes/physical/CPhysicalVelocityDataNode.hpp"
#include "src/rage/netsync/nodes/pickup/CPickupCreationDataNode.hpp"
#include "src/rage/netsync/nodes/pickup_placement/CPickupPlacementCreationDataNode.hpp"
#include "src/rage/netsync/nodes/player/CPlayerAmbientModelStreamingNode.hpp"
#include "src/rage/netsync/nodes/player/CPlayerAppearanceDataNode.hpp"
#include "src/rage/netsync/nodes/player/CPlayerCameraDataNode.hpp"
#include "src/rage/netsync/nodes/player/CPlayerCreationDataNode.hpp"
#include "src/rage/netsync/nodes/player/CPlayerExtendedGameStateNode.hpp"
#include "src/rage/netsync/nodes/player/CPlayerGameStateDataNode.hpp"
#include "src/rage/netsync/nodes/player/CPlayerGamerDataNode.hpp"
#include "src/rage/netsync/nodes/player/CPlayerWantedAndLOSDataNode.hpp"
#include "src/rage/netsync/nodes/proximity_migrateable/CGlobalFlagsDataNode.hpp"
#include "src/rage/netsync/nodes/proximity_migrateable/CMigrationDataNode.hpp"
#include "src/rage/netsync/nodes/proximity_migrateable/CSectorDataNode.hpp"
#include "src/rage/netsync/nodes/proximity_migrateable/CSectorPositionDataNode.hpp"
#include "src/rage/netsync/nodes/train/CTrainGameStateDataNode.hpp"
#include "src/rage/netsync/nodes/vehicle/CVehicleComponentReservationDataNode.hpp"
#include "src/rage/netsync/nodes/vehicle/CVehicleControlDataNode.hpp"
#include "src/rage/netsync/nodes/vehicle/CVehicleCreationDataNode.hpp"
#include "src/rage/netsync/nodes/vehicle/CVehicleGadgetDataNode.hpp"
#include "src/rage/netsync/nodes/vehicle/CVehicleProximityMigrationDataNode.hpp"
#include "src/rage/netsync/nodes/vehicle/CVehicleTaskDataNode.hpp"
#include <src/natives/natives.h>
#include "src/framework/notifications/notifications.h"
namespace Base {
	inline Network* get_network()
	{
		return *g_pointers->m_network;
	}
	static std::vector<std::pair<Hash, std::vector<uint64_t>>> trees = {
		{RAGE_JOAAT("CAutomobileSyncTree"),
			{
				RAGE_JOAAT("CVehicleCreationDataNode"),
				RAGE_JOAAT("CAutomobileCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CVehicleGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CVehicleAppearanceDataNode"),
				RAGE_JOAAT("CVehicleDamageStatusDataNode"),
				RAGE_JOAAT("CVehicleComponentReservationDataNode"),
				RAGE_JOAAT("CVehicleHealthDataNode"),
				RAGE_JOAAT("CVehicleTaskDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CSectorPositionDataNode"),
				RAGE_JOAAT("CEntityOrientationDataNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CVehicleAngVelocityDataNode"),
				RAGE_JOAAT("CVehicleSteeringDataNode"),
				RAGE_JOAAT("CVehicleControlDataNode"),
				RAGE_JOAAT("CVehicleGadgetDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
				RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
			}},
		{RAGE_JOAAT("CBikeSyncTree"),
			{
				RAGE_JOAAT("CVehicleCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CVehicleGameStateDataNode"),
				RAGE_JOAAT("CBikeGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CVehicleAppearanceDataNode"),
				RAGE_JOAAT("CVehicleDamageStatusDataNode"),
				RAGE_JOAAT("CVehicleComponentReservationDataNode"),
				RAGE_JOAAT("CVehicleHealthDataNode"),
				RAGE_JOAAT("CVehicleTaskDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CSectorPositionDataNode"),
				RAGE_JOAAT("CEntityOrientationDataNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CVehicleAngVelocityDataNode"),
				RAGE_JOAAT("CVehicleSteeringDataNode"),
				RAGE_JOAAT("CVehicleControlDataNode"),
				RAGE_JOAAT("CVehicleGadgetDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
				RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
			}},
		{RAGE_JOAAT("CBoatSyncTree"),
			{
				RAGE_JOAAT("CVehicleCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CVehicleGameStateDataNode"),
				RAGE_JOAAT("CBoatGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CVehicleAppearanceDataNode"),
				RAGE_JOAAT("CVehicleDamageStatusDataNode"),
				RAGE_JOAAT("CVehicleComponentReservationDataNode"),
				RAGE_JOAAT("CVehicleHealthDataNode"),
				RAGE_JOAAT("CVehicleTaskDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CSectorPositionDataNode"),
				RAGE_JOAAT("CEntityOrientationDataNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CVehicleAngVelocityDataNode"),
				RAGE_JOAAT("CVehicleSteeringDataNode"),
				RAGE_JOAAT("CVehicleControlDataNode"),
				RAGE_JOAAT("CVehicleGadgetDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
				RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
			}},
		{RAGE_JOAAT("CDoorSyncTree"),
			{
				RAGE_JOAAT("CDoorCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDoorScriptInfoDataNode"),
				RAGE_JOAAT("CDoorScriptGameStateDataNode"),
				RAGE_JOAAT("CDoorMovementDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
			}},
		{RAGE_JOAAT("CHeliSyncTree"),
			{
				RAGE_JOAAT("CVehicleCreationDataNode"),
				RAGE_JOAAT("CAutomobileCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CVehicleGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CVehicleAppearanceDataNode"),
				RAGE_JOAAT("CVehicleDamageStatusDataNode"),
				RAGE_JOAAT("CVehicleComponentReservationDataNode"),
				RAGE_JOAAT("CVehicleHealthDataNode"),
				RAGE_JOAAT("CVehicleTaskDataNode"),
				RAGE_JOAAT("CHeliHealthDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CSectorPositionDataNode"),
				RAGE_JOAAT("CEntityOrientationDataNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CVehicleAngVelocityDataNode"),
				RAGE_JOAAT("CVehicleSteeringDataNode"),
				RAGE_JOAAT("CVehicleControlDataNode"),
				RAGE_JOAAT("CVehicleGadgetDataNode"),
				RAGE_JOAAT("CHeliControlDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
				RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
			}},
		{RAGE_JOAAT("CObjectSyncTree"),
			{
				RAGE_JOAAT("CObjectCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CObjectGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CObjectScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CPhysicalHealthDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CObjectSectorPosNode"),
				RAGE_JOAAT("CObjectOrientationNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CPhysicalAngVelocityDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
			}},
		{RAGE_JOAAT("CPedSyncTree"),
			{
				RAGE_JOAAT("CPedCreationDataNode"),
				RAGE_JOAAT("CPedScriptCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CPedGameStateDataNode"),
				RAGE_JOAAT("CPedComponentReservationDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CPedScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPedAttachDataNode"),
				RAGE_JOAAT("CPedHealthDataNode"),
				RAGE_JOAAT("CPedMovementGroupDataNode"),
				RAGE_JOAAT("CPedAIDataNode"),
				RAGE_JOAAT("CPedAppearanceDataNode"),
				RAGE_JOAAT("CPedOrientationDataNode"),
				RAGE_JOAAT("CPedMovementDataNode"),
				RAGE_JOAAT("CPedTaskTreeDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CPedSectorPosMapNode"),
				RAGE_JOAAT("CPedSectorPosNavMeshNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
				RAGE_JOAAT("CPedInventoryDataNode"),
				RAGE_JOAAT("CPedTaskSequenceDataNode"),
			}},
		{RAGE_JOAAT("CPickupSyncTree"),
			{
				RAGE_JOAAT("CPickupCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPickupScriptGameStateNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalHealthDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CPickupSectorPosNode"),
				RAGE_JOAAT("CEntityOrientationDataNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CPhysicalAngVelocityDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
			}},
		{RAGE_JOAAT("CPickupPlacementSyncTree"),
			{
				RAGE_JOAAT("CPickupPlacementCreationDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CPickupPlacementStateDataNode"),
			}},
		{RAGE_JOAAT("CPlaneSyncTree"),
			{
				RAGE_JOAAT("CVehicleCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CVehicleGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CVehicleAppearanceDataNode"),
				RAGE_JOAAT("CVehicleDamageStatusDataNode"),
				RAGE_JOAAT("CVehicleComponentReservationDataNode"),
				RAGE_JOAAT("CVehicleHealthDataNode"),
				RAGE_JOAAT("CVehicleTaskDataNode"),
				RAGE_JOAAT("CPlaneGameStateDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CSectorPositionDataNode"),
				RAGE_JOAAT("CEntityOrientationDataNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CVehicleAngVelocityDataNode"),
				RAGE_JOAAT("CVehicleSteeringDataNode"),
				RAGE_JOAAT("CVehicleControlDataNode"),
				RAGE_JOAAT("CVehicleGadgetDataNode"),
				RAGE_JOAAT("CPlaneControlDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
				RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
			}},
		{RAGE_JOAAT("CSubmarineSyncTree"),
			{
				RAGE_JOAAT("CVehicleCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CVehicleGameStateDataNode"),
				RAGE_JOAAT("CSubmarineGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CVehicleAppearanceDataNode"),
				RAGE_JOAAT("CVehicleDamageStatusDataNode"),
				RAGE_JOAAT("CVehicleComponentReservationDataNode"),
				RAGE_JOAAT("CVehicleHealthDataNode"),
				RAGE_JOAAT("CVehicleTaskDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CSectorPositionDataNode"),
				RAGE_JOAAT("CEntityOrientationDataNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CVehicleAngVelocityDataNode"),
				RAGE_JOAAT("CVehicleSteeringDataNode"),
				RAGE_JOAAT("CVehicleControlDataNode"),
				RAGE_JOAAT("CVehicleGadgetDataNode"),
				RAGE_JOAAT("CSubmarineControlDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
				RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
			}},
		{RAGE_JOAAT("CPlayerSyncTree"),
			{
				RAGE_JOAAT("CPlayerCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CPedGameStateDataNode"),
				RAGE_JOAAT("CPedComponentReservationDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPlayerGameStateDataNode"),
				RAGE_JOAAT("CPedAttachDataNode"),
				RAGE_JOAAT("CPedHealthDataNode"),
				RAGE_JOAAT("CPedMovementGroupDataNode"),
				RAGE_JOAAT("CPedAIDataNode"),
				RAGE_JOAAT("CPlayerAppearanceDataNode"),
				RAGE_JOAAT("CPlayerPedGroupDataNode"),
				RAGE_JOAAT("CPlayerAmbientModelStreamingNode"),
				RAGE_JOAAT("CPlayerGamerDataNode"),
				RAGE_JOAAT("CPlayerExtendedGameStateNode"),
				RAGE_JOAAT("CPedOrientationDataNode"),
				RAGE_JOAAT("CPedMovementDataNode"),
				RAGE_JOAAT("CPedTaskTreeDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CPedTaskSpecificDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CPlayerSectorPosNode"),
				RAGE_JOAAT("CPlayerCameraDataNode"),
				RAGE_JOAAT("CPlayerWantedAndLOSDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
			}},
		{RAGE_JOAAT("CAutomobileSyncTree"),
			{
				RAGE_JOAAT("CVehicleCreationDataNode"),
				RAGE_JOAAT("CAutomobileCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CVehicleGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CVehicleAppearanceDataNode"),
				RAGE_JOAAT("CVehicleDamageStatusDataNode"),
				RAGE_JOAAT("CVehicleComponentReservationDataNode"),
				RAGE_JOAAT("CVehicleHealthDataNode"),
				RAGE_JOAAT("CVehicleTaskDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CSectorPositionDataNode"),
				RAGE_JOAAT("CEntityOrientationDataNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CVehicleAngVelocityDataNode"),
				RAGE_JOAAT("CVehicleSteeringDataNode"),
				RAGE_JOAAT("CVehicleControlDataNode"),
				RAGE_JOAAT("CVehicleGadgetDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
				RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
			}},
		{RAGE_JOAAT("CTrainSyncTree"),
			{
				RAGE_JOAAT("CVehicleCreationDataNode"),
				RAGE_JOAAT("CGlobalFlagsDataNode"),
				RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
				RAGE_JOAAT("CPhysicalGameStateDataNode"),
				RAGE_JOAAT("CVehicleGameStateDataNode"),
				RAGE_JOAAT("CTrainGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptGameStateDataNode"),
				RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
				RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
				RAGE_JOAAT("CEntityScriptInfoDataNode"),
				RAGE_JOAAT("CPhysicalAttachDataNode"),
				RAGE_JOAAT("CVehicleAppearanceDataNode"),
				RAGE_JOAAT("CVehicleDamageStatusDataNode"),
				RAGE_JOAAT("CVehicleComponentReservationDataNode"),
				RAGE_JOAAT("CVehicleHealthDataNode"),
				RAGE_JOAAT("CVehicleTaskDataNode"),
				RAGE_JOAAT("CSectorDataNode"),
				RAGE_JOAAT("CSectorPositionDataNode"),
				RAGE_JOAAT("CEntityOrientationDataNode"),
				RAGE_JOAAT("CPhysicalVelocityDataNode"),
				RAGE_JOAAT("CVehicleAngVelocityDataNode"),
				RAGE_JOAAT("CVehicleSteeringDataNode"),
				RAGE_JOAAT("CVehicleControlDataNode"),
				RAGE_JOAAT("CVehicleGadgetDataNode"),
				RAGE_JOAAT("CMigrationDataNode"),
				RAGE_JOAAT("CPhysicalMigrationDataNode"),
				RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
				RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
			}},
	};

	auto nodes = std::to_array<std::pair<Hash, uint64_t>>({ {RAGE_JOAAT("CAutomobileCreationDataNode"), 0}, {RAGE_JOAAT("CBikeGameStateDataNode"), 0}, {RAGE_JOAAT("CBoatGameStateDataNode"), 0}, {RAGE_JOAAT("CDoorCreationDataNode"), 0}, {RAGE_JOAAT("CDoorMovementDataNode"), 0}, {RAGE_JOAAT("CDoorScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CDoorScriptInfoDataNode"), 0}, {RAGE_JOAAT("CDynamicEntityGameStateDataNode"), 0}, {RAGE_JOAAT("CEntityOrientationDataNode"), 0}, {RAGE_JOAAT("CEntityScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CEntityScriptInfoDataNode"), 0}, {RAGE_JOAAT("CGlobalFlagsDataNode"), 0}, {RAGE_JOAAT("CHeliControlDataNode"), 0}, {RAGE_JOAAT("CHeliHealthDataNode"), 0}, {RAGE_JOAAT("CMigrationDataNode"), 0}, {RAGE_JOAAT("CObjectCreationDataNode"), 0}, {RAGE_JOAAT("CObjectGameStateDataNode"), 0}, {RAGE_JOAAT("CObjectOrientationNode"), 0}, {RAGE_JOAAT("CObjectScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CObjectSectorPosNode"), 0}, {RAGE_JOAAT("CPedAIDataNode"), 0}, {RAGE_JOAAT("CPedAppearanceDataNode"), 0}, {RAGE_JOAAT("CPedAttachDataNode"), 0}, {RAGE_JOAAT("CPedComponentReservationDataNode"), 0}, {RAGE_JOAAT("CPedCreationDataNode"), 0}, {RAGE_JOAAT("CPedGameStateDataNode"), 0}, {RAGE_JOAAT("CPedHealthDataNode"), 0}, {RAGE_JOAAT("CPedInventoryDataNode"), 0}, {RAGE_JOAAT("CPedMovementDataNode"), 0}, {RAGE_JOAAT("CPedMovementGroupDataNode"), 0}, {RAGE_JOAAT("CPedOrientationDataNode"), 0}, {RAGE_JOAAT("CPedScriptCreationDataNode"), 0}, {RAGE_JOAAT("CPedScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CPedSectorPosMapNode"), 0}, {RAGE_JOAAT("CPedSectorPosNavMeshNode"), 0}, {RAGE_JOAAT("CPedTaskSequenceDataNode"), 0}, {RAGE_JOAAT("CPedTaskSpecificDataNode"), 0}, {RAGE_JOAAT("CPedTaskTreeDataNode"), 0}, {RAGE_JOAAT("CPhysicalAngVelocityDataNode"), 0}, {RAGE_JOAAT("CPhysicalAttachDataNode"), 0}, {RAGE_JOAAT("CPhysicalGameStateDataNode"), 0}, {RAGE_JOAAT("CPhysicalHealthDataNode"), 0}, {RAGE_JOAAT("CPhysicalMigrationDataNode"), 0}, {RAGE_JOAAT("CPhysicalScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CPhysicalScriptMigrationDataNode"), 0}, {RAGE_JOAAT("CPhysicalVelocityDataNode"), 0}, {RAGE_JOAAT("CPickupCreationDataNode"), 0}, {RAGE_JOAAT("CPickupPlacementCreationDataNode"), 0}, {RAGE_JOAAT("CPickupPlacementStateDataNode"), 0}, {RAGE_JOAAT("CPickupScriptGameStateNode"), 0}, {RAGE_JOAAT("CPickupSectorPosNode"), 0}, {RAGE_JOAAT("CPlaneControlDataNode"), 0}, {RAGE_JOAAT("CPlaneGameStateDataNode"), 0}, {RAGE_JOAAT("CPlayerAmbientModelStreamingNode"), 0}, {RAGE_JOAAT("CPlayerAppearanceDataNode"), 0}, {RAGE_JOAAT("CPlayerCameraDataNode"), 0}, {RAGE_JOAAT("CPlayerCreationDataNode"), 0}, {RAGE_JOAAT("CPlayerExtendedGameStateNode"), 0}, {RAGE_JOAAT("CPlayerGameStateDataNode"), 0}, {RAGE_JOAAT("CPlayerGamerDataNode"), 0}, {RAGE_JOAAT("CPlayerPedGroupDataNode"), 0}, {RAGE_JOAAT("CPlayerSectorPosNode"), 0}, {RAGE_JOAAT("CPlayerWantedAndLOSDataNode"), 0}, {RAGE_JOAAT("CSectorDataNode"), 0}, {RAGE_JOAAT("CSectorPositionDataNode"), 0}, {RAGE_JOAAT("CSubmarineControlDataNode"), 0}, {RAGE_JOAAT("CSubmarineGameStateDataNode"), 0}, {RAGE_JOAAT("CTrainGameStateDataNode"), 0}, {RAGE_JOAAT("CVehicleAngVelocityDataNode"), 0}, {RAGE_JOAAT("CVehicleAppearanceDataNode"), 0}, {RAGE_JOAAT("CVehicleComponentReservationDataNode"), 0}, {RAGE_JOAAT("CVehicleControlDataNode"), 0}, {RAGE_JOAAT("CVehicleCreationDataNode"), 0}, {RAGE_JOAAT("CVehicleDamageStatusDataNode"), 0}, {RAGE_JOAAT("CVehicleGadgetDataNode"), 0}, {RAGE_JOAAT("CVehicleGameStateDataNode"), 0}, {RAGE_JOAAT("CVehicleHealthDataNode"), 0}, {RAGE_JOAAT("CVehicleProximityMigrationDataNode"), 0}, {RAGE_JOAAT("CVehicleScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CVehicleSteeringDataNode"), 0}, {RAGE_JOAAT("CVehicleTaskDataNode"), 0} });

	void cache_nodes() {
		for (int i = (int)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE; i <= (int)eNetObjType::NET_OBJ_TYPE_TRAIN; i++) {
			if (i == (int)eNetObjType::NET_OBJ_TYPE_TRAILER)
				continue;
			rage::netSyncTree* tree{ g_pointers->m_get_sync_tree_for_type(*g_pointers->m_network_object_mgr, i) };
			if (tree->m_child_node_count > trees[i].second.size()) {
				throw std::runtime_error("Failed to cache nodes");
			}
			for (int j = 0; j < tree->m_child_node_count; j++) {
				PVOID vft = *(PVOID*)tree->m_child_nodes[j];
				for (auto& n : nodes) {
					if (n.first == trees[i].second[j]) {
						n.second = (uint64_t)vft;
						break;
					}
				}
			}
		}
	}

	constexpr auto crash_objects = { RAGE_JOAAT("prop_dummy_01"), RAGE_JOAAT("prop_dummy_car"), RAGE_JOAAT("prop_dummy_light"), RAGE_JOAAT("prop_dummy_plane"), RAGE_JOAAT("prop_distantcar_night"), RAGE_JOAAT("prop_distantcar_day"), RAGE_JOAAT("hei_bh1_08_details4_em_night"), RAGE_JOAAT("dt1_18_sq_night_slod"), RAGE_JOAAT("ss1_12_night_slod"), RAGE_JOAAT("hash_b334b5e2_qyquzxq_collision"), RAGE_JOAAT("h4_prop_bush_bgnvla_med_01"), RAGE_JOAAT("h4_prop_bush_bgnvla_lrg_01"), RAGE_JOAAT("h4_prop_bush_buddleia_low_01"), RAGE_JOAAT("h4_prop_bush_ear_aa"), RAGE_JOAAT("h4_prop_bush_ear_ab"), RAGE_JOAAT("h4_prop_bush_fern_low_01"), RAGE_JOAAT("h4_prop_bush_fern_tall_cc"), RAGE_JOAAT("h4_prop_bush_mang_ad"), RAGE_JOAAT("h4_prop_bush_mang_low_aa"), RAGE_JOAAT("h4_prop_bush_mang_low_ab"), RAGE_JOAAT("h4_prop_bush_seagrape_low_01"), RAGE_JOAAT("prop_h4_ground_cover"), RAGE_JOAAT("h4_prop_weed_groundcover_01"), RAGE_JOAAT("h4_prop_grass_med_01"), RAGE_JOAAT("h4_prop_grass_tropical_lush_01"), RAGE_JOAAT("h4_prop_grass_wiregrass_01"), RAGE_JOAAT("h4_prop_weed_01_plant"), RAGE_JOAAT("h4_prop_weed_01_row"), RAGE_JOAAT("urbanweeds02_l1"), RAGE_JOAAT("proc_forest_grass01"), RAGE_JOAAT("prop_small_bushyba"), RAGE_JOAAT("v_res_d_dildo_a"), RAGE_JOAAT("v_res_d_dildo_b"), RAGE_JOAAT("v_res_d_dildo_c"), RAGE_JOAAT("v_res_d_dildo_d"), RAGE_JOAAT("v_res_d_dildo_e"), RAGE_JOAAT("v_res_d_dildo_f"), RAGE_JOAAT("v_res_skateboard"), RAGE_JOAAT("prop_battery_01"), RAGE_JOAAT("prop_barbell_01"), RAGE_JOAAT("prop_barbell_02"), RAGE_JOAAT("prop_bandsaw_01"), RAGE_JOAAT("prop_bbq_3"), RAGE_JOAAT("v_med_curtainsnewcloth2"), RAGE_JOAAT("bh1_07_flagpoles"), RAGE_JOAAT("hash_058a7eb5_deihiws_collision"), RAGE_JOAAT("proc_dry_plants_01"), RAGE_JOAAT("proc_leafyplant_01"), RAGE_JOAAT("proc_grassplantmix_02"), RAGE_JOAAT("proc_dryplantsgrass_01"), RAGE_JOAAT("proc_dryplantsgrass_02"), RAGE_JOAAT("proc_dryplantsgrass_02"), RAGE_JOAAT("proc_grasses01"), RAGE_JOAAT("prop_dryweed_002_a"), RAGE_JOAAT("prop_fernba"), RAGE_JOAAT("prop_weed_001_aa"), RAGE_JOAAT("urbangrnfrnds_01"), RAGE_JOAAT("urbanweeds01"), RAGE_JOAAT("prop_dandy_b"), RAGE_JOAAT("v_proc2_temp"), RAGE_JOAAT("prop_fernbb"), RAGE_JOAAT("proc_drygrassfronds01"), RAGE_JOAAT("prop_log_ae"), RAGE_JOAAT("prop_grass_da"), RAGE_JOAAT("prop_fragtest_cnst_04"), rage::joaat("PICKUP_CUSTOM_SCRIPT")};
	bool is_crash_object(rage::joaat_t model) {
		for (auto iterator : crash_objects)
			if (iterator == model)
				return true;
		return false;
	}

	constexpr auto crash_peds = { RAGE_JOAAT("slod_human"), RAGE_JOAAT("slod_small_quadped"), RAGE_JOAAT("slod_large_quadped") };
	bool is_crash_ped(rage::joaat_t model) {
		for (auto iterator : crash_peds)
			if (iterator == model)
				return true;
		return false;
	}

	constexpr auto crash_vehicles = { RAGE_JOAAT("arbitergt"), RAGE_JOAAT("astron2"), RAGE_JOAAT("cyclone2"), RAGE_JOAAT("ignus2"), RAGE_JOAAT("s95") };
	bool is_crash_vehicle(rage::joaat_t model) {
		for (auto iterator : crash_vehicles)
			if (iterator == model)
				return true;
		return false;
	}

	void protection_notify(str name, str plr_name) {
		g_notifications->send("Protections", std::format("Blocked '{}' crash from {}", name, plr_name));
	}

	bool check_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, rage::netObject* object) {
		if (node->IsParentNode()) {
			for (auto child{ node->m_first_child }; child; child = child->m_next_sibling) {
				if (check_node(child, sender, object))
					return true;
			}
		}
		else if (node->IsDataNode()) {
			const auto addr{ (uintptr_t)node };
			const auto& node_id{ sync_node_finder::find((eNetObjType)object->m_object_type, addr) };

			if ((((CProjectBaseSyncDataNode*)node)->flags & 1) == 0)
				return false;

			switch (node_id) {
			case sync_node_id("CVehicleCreationDataNode"): {
				const auto creation_node{ (CVehicleCreationDataNode*)(node) };

				if (is_crash_vehicle(creation_node->m_model) && g_protection_manager.m_crashes.m_invalid_vehicle) {
					g_notifications->send("Protections", std::format("Blocked 'invalid vehicle model' crash from {}", sender->get_name()));
					return true;
				}
				if (auto info = model_info::get_vehicle_model(creation_node->m_model)) {
					if (vehicle_type_to_object_type(info->m_vehicle_type) != g_syncing_object_type && g_protection_manager.m_crashes.m_sync_mismatch) {
						g_notifications->send("Protections", std::format("Blocked 'sync mismatch' crash from {}", sender->get_name()));
						return true;
					}
				}
				break;
			}
			case sync_node_id("CDoorCreationDataNode"): {
				const auto creation_node{ (CDoorCreationDataNode*)(node) };

				if (is_crash_object(creation_node->m_model) && g_protection_manager.m_crashes.m_invalid_door) {
					g_notifications->send("Protections", std::format("Blocked 'invalid door model' crash from {}", sender->get_name()));
					return true;
				}
				break;
			}
			case sync_node_id("CPickupCreationDataNode"): {
				const auto creation_node{ (CPickupCreationDataNode*)(node) };
				if (creation_node->m_custom_model && is_crash_object(creation_node->m_custom_model) && g_protection_manager.m_crashes.m_invalid_pickup) {
					g_notifications->send("Protections", std::format("Blocked 'invalid pickup model' crash from {}", sender->get_name()));
					return true;
				}

				for (int i = 0; i < creation_node->m_num_weapon_components; i++) {
					uint64_t buffer[20]{};
					if (!WEAPON::GET_WEAPON_COMPONENT_HUD_STATS(creation_node->m_weapon_component[i], (Any*)buffer) && g_protection_manager.m_crashes.m_invalid_component) {
						g_notifications->send("Protections", std::format("Blocked 'invalid component' crash from {}", sender->get_name()));
						return true;
					}
				}
				break;
			}
			case sync_node_id("CPhysicalAttachDataNode"): {
				const auto attach_node{ (CPhysicalAttachDataNode*)(node) };

				if (attach_node->m_attached && (object->m_object_id == attach_node->m_attached_to || is_attachment_infinite(object, attach_node->m_attached_to, attach_node->m_attach_bone, attach_node->m_other_attach_bone))) {
					if (g_protection_manager.m_crashes.m_infinite_attachment) {
						protection_notify("infinite attachment", sender->get_name());
						return true;
					}
				}

				if (attach_node->m_attached && object && object->m_object_type == (int16_t)eNetObjType::NET_OBJ_TYPE_TRAILER) {
					if (auto net_obj = g_pointers->m_get_net_object(*g_pointers->m_network_object_mgr, attach_node->m_attached_to, false)) {
						if (auto entity = net_obj->GetGameObject()) {
							if (entity->m_entity_type != 3 && g_protection_manager.m_crashes.m_infinite_attachment)
							{
								protection_notify("infinite attachment", sender->get_name());
								return true;
							}
						}
					}
				}

				break;
			}
			case sync_node_id("CPedCreationDataNode"): {
				const auto creation_node{ (CPedCreationDataNode*)(node) };

				if (is_crash_ped(creation_node->m_model) && g_protection_manager.m_crashes.m_invalid_ped) {
					protection_notify("invalid ped", sender->get_name());
					return true;
				}
				else if (creation_node->m_has_prop && is_crash_object(creation_node->m_prop_model) && g_protection_manager.m_crashes.m_invalid_prop) {
					protection_notify("invalid prop", sender->get_name());
					return true;
				}
				break;
			}
			case sync_node_id("CPedAttachDataNode"): {
				const auto attach_node{ (CPedAttachDataNode*)(node) };

				if (attach_node->m_attached && (object->m_object_id == attach_node->m_attached_to|| is_attachment_infinite(object, attach_node->m_attached_to, attach_node->m_attachment_bone, attach_node->m_attachment_bone))) {
					if (g_protection_manager.m_crashes.m_infinite_attachment) {
						if (auto game_object{ (CPed*)object->GetGameObject() }) {
							if (!game_object->m_player_info) {
								protection_notify("infinite attachment", sender->get_name());
							}
						}

						return true;
					}
				}

				break;
			}
			case sync_node_id("CObjectCreationDataNode"): {
				const auto creation_node{ (CObjectCreationDataNode*)(node) };

				if (is_crash_object(creation_node->m_model) && g_protection_manager.m_crashes.m_invalid_object) {
					protection_notify("invalid object", sender->get_name());
					return true;
				}
				break;
			}
			case sync_node_id("CPlayerAppearanceDataNode"): {
				const auto player_appearance_node{ (CPlayerAppearanceDataNode*)(node) };

				if (is_crash_ped(player_appearance_node->m_model_hash) && g_protection_manager.m_crashes.m_invalid_player) {
					protection_notify("invalid player", sender->get_name());
					return true;
				}

				player_appearance_node->m_mobile_phone_gesture_active = false;
				break;
			}
			case sync_node_id("CPlayerCreationDataNode"):{
				const auto player_creation_node{ (CPlayerCreationDataNode*)(node) };
				if (is_crash_ped(player_creation_node->m_model) && g_protection_manager.m_crashes.m_invalid_player) {
					protection_notify("invalid player", sender->get_name());
					return true;
				}
				break;
			}
			case sync_node_id("CSectorDataNode"): {
				float player_sector_pos_x{}, player_sector_pos_y{};
				get_player_sector_pos(node->m_root->m_next_sync_node, player_sector_pos_x, player_sector_pos_y, object);

				const auto sector_node{ (CSectorDataNode*)(node) };
				auto posX{ (sector_node->m_pos_x - 512.0f) * 54.0f };
				auto posY{ (sector_node->m_pos_y - 512.0f) * 54.0f };
				if (is_invalid_override_pos(posX + player_sector_pos_x, posY + player_sector_pos_y) && g_protection_manager.m_crashes.m_invalid_sector_position) {
					protection_notify("invalid sector position", sender->get_name());
					return true;
				}
				break;
			}
			case sync_node_id("CPlayerGameStateDataNode"): {
				const auto game_state_node{ (CPlayerGameStateDataNode*)(node) };

				if (game_state_node->m_is_overriding_population_control_sphere && is_invalid_override_pos(game_state_node->m_population_control_sphere_x, game_state_node->m_population_control_sphere_y)) {
					if (get_network()->m_game_session_ptr->is_host() && g_protection_manager.m_crashes.m_invalid_sector_position)
						protection_notify("invalid sector position", sender->get_name());

					return true;
				}

				break;
			}
			case sync_node_id("CTrainGameStateDataNode"): {
				const auto train_node{ (CTrainGameStateDataNode*)(node) };
				int track_id{ train_node->m_track_id };

				if (track_id != -1 && (track_id < 0 || track_id >= 12) && g_protection_manager.m_crashes.m_invalid_train_config) {
					protection_notify("invalid train config", sender->get_name());
					return true;
				}

				int train_config_index{ train_node->m_train_config_index };
				int carriage_config_index{ train_node->m_carriage_config_index };

				if (train_config_index != -1) {
					if ((uint32_t)train_config_index >= g_pointers->m_train_config_array->size() && g_protection_manager.m_crashes.m_invalid_train_config) {
						protection_notify("invalid train config", sender->get_name());
						return true;
					}

					if (carriage_config_index != -1) {
						if ((uint32_t)carriage_config_index >= (*g_pointers->m_train_config_array)[train_config_index].m_carraige_configs.size() && g_protection_manager.m_crashes.m_invalid_train_config) {
							protection_notify("invalid train config", sender->get_name());
							return true;
						}
					}
				}

				break;
			}
			case sync_node_id("CVehicleProximityMigrationDataNode"): {
				if (object && (*g_pointers->m_ped_factory)->m_local_ped && (*g_pointers->m_ped_factory)->m_local_ped->m_net_object) {
					const auto migration_node{ (CVehicleProximityMigrationDataNode*)(node) };

					if (!(*g_pointers->m_ped_factory)->m_local_ped->m_vehicle || !(*g_pointers->m_ped_factory)->m_local_ped->m_vehicle->m_net_object || (*g_pointers->m_ped_factory)->m_local_ped->m_vehicle->m_net_object->m_object_id != object->m_object_id || !is_in_vehicle((*g_pointers->m_ped_factory)->m_local_ped, (*g_pointers->m_ped_factory)->m_local_ped->m_vehicle)) {
						if (is_local_player_an_occupant(migration_node)) {
							return true;
						}
					}
				}

				break;
			}
			case sync_node_id("CPedGameStateDataNode"): {
				const auto game_state_node{ (CPedGameStateDataNode*)(node) };

				if (game_state_node->m_on_mount && g_protection_manager.m_crashes.m_invalid_mount_flag) {
					protection_notify("mount flag", sender->get_name());
					return true;
				}
				for (int i = 0; i < game_state_node->m_num_equiped_gadgets; i++) {
					if (game_state_node->m_gadget_hash[i] != RAGE_JOAAT("gadget_parachute") && game_state_node->m_gadget_hash[i] != RAGE_JOAAT("gadget_nightvision") && g_protection_manager.m_crashes.m_invalid_gadget) {
						protection_notify("invalid gadget", sender->get_name());
						return true;
					}
				}
				break;
			}
			case sync_node_id("CVehicleControlDataNode"): {
				const auto control_node{ (CVehicleControlDataNode*)(node) };

				if (control_node->m_is_submarine_car) {
					if (auto vehicle = (CVehicle*)object->GetGameObject()) {
						if (auto model_info = static_cast<CVehicleModelInfo*>(vehicle->m_model_info)) {
							if (model_info->m_vehicle_type != eVehicleType::VEHICLE_TYPE_SUBMARINECAR && g_protection_manager.m_crashes.m_invalid_control_data)
							{
								protection_notify("invalid control data", sender->get_name());
								return true;
							}
						}
					}
				}

				break;
			}
			case sync_node_id("CPlayerCameraDataNode"): {
				const auto camera_node{ (CPlayerCameraDataNode*)(node) };

				if (is_invalid_override_pos(camera_node->m_free_cam_pos_x, camera_node->m_free_cam_pos_y)) {
					if (get_network()->m_game_session_ptr->is_host() && g_protection_manager.m_crashes.m_invalid_camera_position)
						protection_notify("invalid camera position", sender->get_name());
					return true;
				}

				break;
			}
			case sync_node_id("CVehicleGadgetDataNode"): {
				const auto gadget_node{ (CVehicleGadgetDataNode*)(node) };

				for (int i = 0; i < gadget_node->m_gadget_count; i++) {
					if (gadget_node->m_gadget_data[i].m_gadget_type > 6 && g_protection_manager.m_crashes.m_out_of_bounds_gadget) {
						protection_notify("out of bounds gadget type", sender->get_name());
						return true;
					}
				}
				break;
			}
			case sync_node_id("CPedTaskTreeDataNode"): {
				const auto task_node{ (CPedTaskTreeDataNode*)(node) };

				for (int i = 0; i < 8; i++) {
					if (task_node->m_task_bitset & (1 << i)) {
						if (is_crash_ped_task((eTaskTypeIndex)task_node->m_tasks[i].m_task_type) && g_protection_manager.m_crashes.m_invalid_tasks) {
							protection_notify("invalid task", sender->get_name());
							return true;
						}
					}
				}

				break;
			}
			case sync_node_id("CVehicleTaskDataNode"): {
				const auto task_node{ (CVehicleTaskDataNode*)(node) };

				if (is_crash_vehicle_task((eTaskTypeIndex)task_node->m_task_type) && g_protection_manager.m_crashes.m_invalid_tasks) {
					protection_notify("invalid task", sender->get_name());
					return true;
				}

				break;
			}
			case sync_node_id("CEntityScriptInfoDataNode"): {
				const auto script_node{ (CEntityScriptInfoDataNode*)(node) };

				if (script_node->m_has_script_info) {
					if (script_node->m_script_info.m_local_handle == 0 && g_protection_manager.m_crashes.m_invalid_script_information) {
						protection_notify("invalid script information", sender->get_name());
						return true;
					}
				}
				break;
			}
			case sync_node_id("CDynamicEntityGameStateDataNode"): {
				const auto game_state_node{ (CDynamicEntityGameStateDataNode*)(node) };

				if (is_valid_interior_game(game_state_node->m_interior_index) && !is_valid_interior_fixed(game_state_node->m_interior_index) && g_protection_manager.m_crashes.m_invalid_interior) {
					protection_notify("invalid interior", sender->get_name());
					return true;
				}
			}
			}
		}
		return false;
	}

	bool hooks::can_apply_data(rage::netSyncTree* tree, rage::netObject* object) {
		static bool init = ([] { cache_nodes(); }(), true);

		if (tree->m_child_node_count && tree->m_next_sync_node && check_node(tree->m_next_sync_node, g_syncing_player, object)) {
			return false;
		}

		RET_CALL_DECL(can_apply_data, tree, object);
	}
}