#pragma once
#include "src/natives/natives.h"

namespace Base {
	class math {
	public:
		double degree_to_radian(double number) {
			return number * 0.017453292519943295;
		}
		float distance(Vector3 a, Vector3 b) {
			return MISC::GET_DISTANCE_BETWEEN_COORDS(a.x, a.y, a.z, b.x, b.y, b.z, 1);
		}
		inline Vector3 rotation_to_direction(Vector3* rot) {
			float radiansZ = rot->z * 0.0174532924f;
			float radiansX = rot->x * 0.0174532924f;
			float num = abs((float)cos((double)radiansX));
			Vector3 dir{ 0, 0, 0 };
			dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
			dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
			dir.z = (float)sin((double)radiansX);
			return dir;
		}
		inline Vector3 rotation_to_direction(Vector3 rot) {
			float radiansZ = rot.z * 0.0174532924f;
			float radiansX = rot.x * 0.0174532924f;
			float num = abs((float)cos((double)radiansX));
			Vector3 dir{ 0, 0, 0 };
			dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
			dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
			dir.z = (float)sin((double)radiansX);
			return dir;
		}
		inline auto raycast(Entity& raycastHitEntity) {
			BOOL raycastHit;
			auto camRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			Vector3 surfaceNormal;
			Vector3 raycastHitCoords;
			auto camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
			auto cameraDirection = rotation_to_direction(&camRot);
			auto cameraMultiply = cameraDirection * 1999999.0f;
			auto farCoords = camCoords + cameraMultiply;
			int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, PLAYER::PLAYER_PED_ID(), 7);
			SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &raycastHit, &raycastHitCoords, &surfaceNormal, &raycastHitEntity);
			return raycastHit;
		}
		inline BOOL raycast(Vector3& raycastHitCoords) {
			BOOL raycastHit;
			Vector3 surfaceNormal;
			Entity raycastHitEntity;
			auto camRot{ CAM::GET_GAMEPLAY_CAM_ROT(0) };
			auto camCoords{ CAM::GET_GAMEPLAY_CAM_COORD() };
			auto cameraDirection{ rotation_to_direction(&camRot) };
			auto cameraMultiply{ cameraDirection * 1999999.0f };
			auto farCoords{ camCoords + cameraMultiply };
			int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, PLAYER::PLAYER_PED_ID(), 7);
			SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &raycastHit, &raycastHitCoords, &surfaceNormal, &raycastHitEntity);
			return raycastHit;
		}
		

		
	};
	inline math* g_math;
}
