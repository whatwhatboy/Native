#include "src/hooking/hooking.h"

namespace Base {
	enum class eTaskFlags : uint32_t {
		ParachuteWhenCoordThresholdIsReached = (1 << 3),
		CamShakeOnFall = (1 << 4),
		PlayRagdollAnim = (1 << 5),
		PlayDiveAnim = (1 << 7),
		NoFallAnimation = (1 << 10),
		NoSlowFall = (1 << 11),
		Unk12 = (1 << 12),
		SuperJump = (1 << 15),
		LandOnJump = (1 << 16),
		BeastJump = (1 << 17),
		BeastJumpWithSuper = SuperJump | BeastJump,
		GracefulLanding = NoFallAnimation | NoSlowFall | Unk12 | LandOnJump,
		RagdollOnFall = BeastJump | PlayRagdollAnim
	};

	u64* hooks::fall_task_constructor(u64* _this, u32 flags) {
		if (g_hooking_features.fall.beast)
			flags |= (u32)eTaskFlags::BeastJump;
		if (g_hooking_features.fall.super)
			flags |= (u32)eTaskFlags::SuperJump;
		if (g_hooking_features.fall.dive)
			flags |= (u32)eTaskFlags::PlayDiveAnim;
		if (g_hooking_features.fall.shake_camera)
			flags |= (u32)eTaskFlags::CamShakeOnFall;
		if (g_hooking_features.fall.land)
			flags |= (u32)eTaskFlags::LandOnJump;

		RET_CALL_DECL(fall_task_constructor, _this, flags);
	}
	u64 hooks::jump_task_constructor(u64 _this, u32 flags) {
		if (g_hooking_features.jump.beast)
			flags |= (u32)eTaskFlags::BeastJump;
		if (g_hooking_features.jump.super)
			flags |= (u32)eTaskFlags::SuperJump;
		if (g_hooking_features.jump.dive)
			flags |= (u32)eTaskFlags::PlayDiveAnim;
		if (g_hooking_features.jump.shake_camera)
			flags |= (u32)eTaskFlags::CamShakeOnFall;
		if (g_hooking_features.jump.land)
			flags |= (u32)eTaskFlags::LandOnJump;

		if (g_hooking_features.super_jump)
			flags |= 1 << 15;
		if (g_hooking_features.beast_jump)
			flags |= (1 << 15) | (1 << 17);

		RET_CALL_DECL(jump_task_constructor, _this, flags);
	}
}