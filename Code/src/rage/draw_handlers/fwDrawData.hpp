#pragma once

#include <cstdint>

namespace rage
{
	class CVehicleStreamRender {
	public:
        char _0x0000[0x8]; // unk
        float m_tire_height; // unk
        char _0x000C[0xB94]; // unk
        float m_tire_width; // 0x08

	};
#pragma pack(push, 4)
    class fwDrawData
    {
    public:
        char pad_0x0000[0x370]; //0x0000
        //CVehicleSteamRenderGFX* m_vehicleStreamRenderGfx; //0x0370 
        CVehicleStreamRender* m_vehicle_stream_render; //0x0370
        char pad_0x0378[0x8B0]; //0x0378
    };
   
#pragma pack(pop)
}
