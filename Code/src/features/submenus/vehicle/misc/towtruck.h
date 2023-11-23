#pragma once
#include "src/natives/natives.h"
#include "src/features/utils/utils.h"
#include "src/features/feature_manager.h"
#include "src/utility/enum.h"
namespace Base {
    namespace towtruck {
        namespace util {
            Vector3 subtractVectors(const Vector3& v1, const Vector3& v2) {
                return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
            }
            float getVectorLength(Vector3 vector) {
                float length = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
                return length;
            }
            float getModelLength(Hash model) {
                Vector3 front, back;
                MISC::GET_MODEL_DIMENSIONS(model, &front, &back);
                float length = getVectorLength(subtractVectors(front, back));
                return length;
            }
            enum class entityPosition {
                front,
                behind,
                left,
                right,
                invalid
            };
            entityPosition getEntityPositionFromEntity(Entity entity1, Entity entity2) {
                Vector3 pos1 = ENTITY::GET_ENTITY_COORDS(entity1, true);
                Vector3 pos2 = ENTITY::GET_ENTITY_COORDS(entity2, true);
                Vector3 forward1 = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity1);
                Vector3 forward2 = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity2);

                Vector3 relativePos = subtractVectors(pos2, pos1);

                float forward1Magnitude = sqrt(forward1.x * forward1.x + forward1.y * forward1.y + forward1.z * forward1.z);
                float relativePosMagnitude = sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y + relativePos.z * relativePos.z);

                Vector3 forward1Normalized = { forward1.x / forward1Magnitude, forward1.y / forward1Magnitude, forward1.z / forward1Magnitude };
                Vector3 relativePosNormalized = { relativePos.x / relativePosMagnitude, relativePos.y / relativePosMagnitude, relativePos.z / relativePosMagnitude };

                float dotProductForward = forward1Normalized.x * relativePosNormalized.x + forward1Normalized.y * relativePosNormalized.y + forward1Normalized.z * relativePosNormalized.z;
                float dotProductRight = forward1Normalized.x * forward2.y - forward1Normalized.y * forward2.x;

                if (dotProductForward > 0.0f) {
                    if (std::abs(dotProductRight) < std::abs(dotProductForward))
                        return (dotProductRight > 0.0f) ? entityPosition::left : entityPosition::right;
                    else
                        return entityPosition::front;
                }
                else
                    return entityPosition::behind;

                return entityPosition::invalid;
            }
            Vector3 getVehicleBackCoordinates(Entity vehicle) {
                Hash vehMod = ENTITY::GET_ENTITY_MODEL(vehicle);
                Vector3 backCoordinates = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(vehicle, Vector3(0, -(getModelLength(vehMod) + 2), 0));
                return backCoordinates;

            }
            bool wasVehicleTowModeActivated{ false };
            bool wasVehicleTowModeActivated2{ false };
            Entity towingEntity;
            void applyForceToPosition(Entity entity, Vector3 pos, Vector3 velocity, float frequency, float ratio) {
                float random = MISC::GET_RANDOM_FLOAT_IN_RANGE(0.00002f, 0.00008f);
                ENTITY::APPLY_FORCE_TO_ENTITY2(entity, 3, Vector3((pos.x * (frequency * frequency)) - ((2.045f + random) * frequency * ratio * velocity.x), (pos.y * (frequency * frequency)) - ((2.035f + random) * frequency * ratio * velocity.y),
                    (pos.z * (frequency * frequency)) - ((2.025f + random) * frequency * ratio * velocity.z)),
                    Vector3(0.0f, 0.0f, 0.0f),
                    0, 0, 1, 1, 0, 1
                );
            }
        }
        namespace settings {
            float frequency{ 2.0 };
            float ratio{ 0.3 };
            bool setRotation{ false };
            bool drawLine{ true };
        }
        bool enabled{ false };
        void init() {
            if (!enabled) {
                if (util::wasVehicleTowModeActivated) {
                    util::towingEntity = 0;
                    util::wasVehicleTowModeActivated2 = false;
                    util::wasVehicleTowModeActivated = false;
                }
            }
            if (g_utils->vehicle() && enabled) {
                if (!util::wasVehicleTowModeActivated2) {
                    util::wasVehicleTowModeActivated2 = true;
                }
                if (!util::towingEntity) {
                    for (auto entity : g_pools->vehicles()) {
                        if (entity && ENTITY::DOES_ENTITY_EXIST(entity) && ENTITY::IS_ENTITY_A_VEHICLE(entity)) {
                            auto currentEntityCoords{ g_utils->coords(entity) };
                            auto selfVehicleCoords{ util::getVehicleBackCoordinates(g_utils->vehicle()) };
                            auto selfVehicleCoordsNonBack{ g_utils->coords(g_utils->vehicle()) };
                            if (MISC::GET_DISTANCE_BETWEEN_COORDS(currentEntityCoords.x, currentEntityCoords.y, currentEntityCoords.z, selfVehicleCoords.x, selfVehicleCoords.y, selfVehicleCoords.z, true) < 3.00f) {
                                if (util::getEntityPositionFromEntity(g_utils->vehicle(), entity) == util::entityPosition::behind) {
                                    if (!util::wasVehicleTowModeActivated)
                                        if (ENTITY::GET_ENTITY_SPEED(g_utils->vehicle()) == 0)
                                            util::wasVehicleTowModeActivated = true;

                                    if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)control_types::input_duck))
                                        util::towingEntity = entity;
                                    if (settings::drawLine)
                                        GRAPHICS::DRAW_LINE(currentEntityCoords.x, currentEntityCoords.y, currentEntityCoords.z, selfVehicleCoordsNonBack.x, selfVehicleCoordsNonBack.y, selfVehicleCoordsNonBack.z, 255, 0, 0, 255);
                                }
                            }
                        }
                    }
                }
                else {
                    util::wasVehicleTowModeActivated = true;
                    if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)control_types::input_duck))
                        util::towingEntity = 0;
                    auto selfVehicleBackCoords{ util::getVehicleBackCoordinates(g_utils->vehicle()) };
                    auto selfVehicleCoords{ g_utils->coords(g_utils->vehicle()) };
                    auto towingCarCoords{ g_utils->coords(util::towingEntity) };
                    auto distance{ g_math->distance(selfVehicleBackCoords, towingCarCoords) };
                    auto direction{ util::subtractVectors(selfVehicleBackCoords, towingCarCoords) };
                    if (settings::drawLine)
                        GRAPHICS::DRAW_LINE(towingCarCoords.x, towingCarCoords.y, towingCarCoords.z, selfVehicleCoords.x, selfVehicleCoords.y, selfVehicleCoords.z, 255, 255, 255, 255);
                    if (distance > 3.f) {
                        NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(util::towingEntity);
                        util::applyForceToPosition(util::towingEntity, direction, ENTITY::GET_ENTITY_VELOCITY(util::towingEntity), settings::frequency, settings::ratio);
                        if (settings::setRotation)
                            ENTITY::SET_ENTITY_ROTATION(util::towingEntity, ENTITY::GET_ENTITY_ROTATION(util::towingEntity, 2).x, ENTITY::GET_ENTITY_ROTATION(util::towingEntity, 2).y, ENTITY::GET_ENTITY_ROTATION(g_utils->vehicle(), 2).z, 2, 0);
                    }


                }

            }
        }

    }

	void add_towtruck() {
		g_feature_manager.add<toggle_option>("towtruck", "Enabled", "", &towtruck::enabled, towtruck::init);

        g_feature_manager.add<toggle_option>("towtruck_draw_line", "Draw Line", "", &towtruck::settings::drawLine);
        g_feature_manager.add<toggle_option>("towtruck_set_rotation", "Set Rotation", "", &towtruck::settings::setRotation);
        g_feature_manager.add<float_option>("towtruck_ratio", "Ratio", "", &towtruck::settings::ratio, 0, 5, 0.1, 1);
        g_feature_manager.add<float_option>("towtruck_frequency", "Frequency", "", &towtruck::settings::frequency, 0, 10, 0.1, 1);
	}
}
