#pragma once
#include "src/utility/common/common.h"
#include <src/rage/script/scrNativeHandler.hpp>

class netGameEvent
{
public:
    virtual ~netGameEvent() = default;

    virtual const char* get_name()
    {
        return 0;
    };
    virtual bool is_in_scope(rage::netPlayer* player)
    {
        return 0;
    };
    virtual bool time_to_resend(uint32_t time)
    {
        return 0;
    };
    virtual bool can_change_scope()
    {
        return 0;
    };

    virtual void prepare_data(datBitBuffer* buffer, rage::netPlayer* source_player, rage::netPlayer* target_player) {};
    virtual void handle_data(datBitBuffer* buffer, rage::netPlayer* source_player, rage::netPlayer* target_player) {};

    virtual bool decide(rage::netPlayer* source_player, rage::netPlayer* target_player)
    {
        return 0;
    };

    virtual void prepare_reply(datBitBuffer* buffer, rage::netPlayer* reply_player) {};
    virtual void handle_reply(datBitBuffer* buffer, rage::netPlayer* souce_player) {};

    virtual void prepare_extra_data(datBitBuffer* buffer, bool is_reply, rage::netPlayer* player, rage::netPlayer* player2) {};
    virtual void handle_extra_data(datBitBuffer* buffer, bool is_reply, rage::netPlayer* player, rage::netPlayer* player2) {};

private:
    virtual void unk_0x60() {};
    virtual void unk_0x68() {};
    virtual void unk_0x70() {};
    virtual void unk_0x78() {};

public:
    virtual bool operator==(netGameEvent const& other)
    {
        return 0;
    };
    virtual bool operator!=(netGameEvent const& other)
    {
        return 0;
    };

    virtual bool must_persist()
    {
        return 0;
    };
    virtual bool must_persist_when_out_of_scope()
    {
        return 0;
    };
    virtual bool has_timed_out()
    {
        return 0;
    };

public:
    uint16_t m_id;         // 0x08
    bool m_requires_reply; // 0x0A
private:
    char m_padding1[0x05]; // 0x0B
public:
    rage::netPlayer* m_source_player; // 0x10
    rage::netPlayer* m_target_player; // 0x18
    uint32_t m_resend_time;     // 0x20
private:
    uint16_t m_0x24; // 0x24
    uint8_t m_0x26;  // 0x26
    uint8_t m_0x27;  // 0x27
    uint32_t m_0x28; // 0x28
    char m_padding2[0x04];
};

class netData {
public:
    char* m_data;
};
static_assert(sizeof(netData) == 0x8);
class CHttpRequest {
public:
    char pad_0000[16];
    class netData* m_request_data;
    char pad_0018[64];
    char* m_response_headers;
    char pad_0060[40];
    char* m_request_headers;
    char pad_0090[1112];
    class netData* m_response_data;
    char pad_04F0[4];
    std::uint16_t m_context_length;
    char pad_04F6[18];
    char* m_scheme;
    char* m_host;
    char* m_path;
    char pad_0520[72];
    char* m_user_agent;
    char pad_0570[3032];
    char* m_url_request;
    char pad_1150[1432];
};
class	TimecycleKeyframeData
{
public:
    char pad_0000[32]; //0x0000
    rage::fvector4 m_azimuth_east; //0x0020
    float m_azimuth_east_intensity; //0x0030
    char pad_0034[28]; //0x0034
    rage::fvector4 m_azimuth_west; //0x0050
    float m_azimuth_west_intensity; //0x0060
    char pad_0064[28]; //0x0064
    rage::fvector4 m_azimuth_transition; //0x0080
    float m_azimuth_transition_intensity; //0x0090
    char pad_0094[4]; //0x0094
    float m_azimuth_transition_position; //0x0098
    char pad_009C[20]; //0x009C
    rage::fvector4 m_zenith; //0x00B0
    float m_zenith_intensity; //0x00C0
    char pad_00C4[28]; //0x00C4
    rage::fvector4 m_zenith_transition; //0x00E0
    float m_zenith_transition_intensity; //0x00F0
    float m_zenith_transition_position; //0x00F4
    float m_zenith_transition_east_blend; //0x00F8
    float m_zenith_transition_west_blend; //0x00FC
    float m_zenith_blend_start; //0x0100
    char pad_0104[60]; //0x0104
    rage::fvector3 m_plane; //0x0140
    float m_plane_intensity; //0x014C
    char pad_0150[52]; //0x0150
    float m_hdr; //0x0184
    float m_unk_188; //0x0188
    bool m_update_sky_attributes; //0x018C
    char pad_018D[3]; //0x018D
    uint32_t m_unk_190; //0x0190
    uint32_t m_unk_194; //0x0194
    char pad_0198[8]; //0x0198
    rage::fvector4 m_unk_1A0; //0x01A0
    char pad_01AC[16]; //0x01AC
    rage::fvector4 m_sun; //0x01C0
    char pad_01CC[32]; //0x01CC
    rage::fvector4 m_sun_disc; //0x01F0
    char pad_01FC[32]; //0x01FC
    float m_sun_disc_size; //0x0220
    float m_sun_hdr; //0x0224
    float m_sun_miephase; //0x0228
    float m_sun_miescatter; //0x022C
    float m_sun_mie_intensity_mult; //0x0230
    char pad_0234[28]; //0x0234
    rage::fvector4 m_unk_250; //0x0250
    char pad_025C[16]; //0x025C
    float m_cloud_shadow_strength; //0x0270
    float m_cloud_density_mult; //0x0274
    float m_cloud_density_bias; //0x0278
    float m_cloud_fadeout; //0x027C
    char pad_0280[32]; //0x0280
    float m_unk_2A0; //0x02A0
    float m_cloud_offset; //0x02A4
    float m_cloud_overall_color; //0x02A8
    float m_cloud_hdr; //0x02AC
    char pad_02B0[32]; //0x02B0
    float m_cloud_dither_strength; //0x02D0
    char pad_02D4[44]; //0x02D4
    float m_cloud_edge_strength; //0x0300
    char pad_0304[4]; //0x0304
    float m_cloud_overall_strength; //0x0308
    char pad_030C[16]; //0x030C
    rage::fvector4 m_unk_320; //0x031C
    rage::fvector4 m_cloud_base; //0x032C
    rage::fvector4 m_unk_340; //0x033C
    char pad_0348[16]; //0x0348
    rage::fvector4 m_cloud_1; //0x035C
    char pad_0368[20]; //0x0368
    rage::fvector4 m_cloud_mid; //0x0380
    char pad_038C[32]; //0x038C
    float m_unk_380; //0x03B0
    float m_small_cloud_detail_strength; //0x03B4
    float m_small_cloud_density_mult; //0x03B8
    float m_unk_3BC; //0x03BC
    char pad_03C0[32]; //0x03C0
    rage::fvector4 m_small_cloud; //0x03E0
    char pad_03EC[32]; //0x03EC
    float m_sun_influence_radius; //0x0410
    float m_sun_scatter_inten; //0x0414
    float m_moon_influence_radius; //0x0418
    float m_moon_scatter_inten; //0x041C
    char pad_0420[212]; //0x0420
    float m_stars_iten; //0x04F4
    char pad_04F8[60]; //0x04F8
    float m_moon_disc_size; //0x0534
    char pad_0538[24]; //0x0538
    rage::fvector4 m_moon; //0x0550
    float m_moon_intensity; //0x0560
    char pad_0564[140]; //0x0564
}; //Size: 0x05F0
class CSyncDataBase
{
public:
    virtual ~CSyncDataBase() = default;
    virtual bool SerializeDword(uint32_t* dword, int size) = 0; // 1
    virtual bool SerializeWord(uint16_t* word, int size) = 0; // 2
    virtual bool SerializeByte(uint8_t* byte, int size) = 0; // 3
    virtual bool SerializeInt32(int32_t* i, int size) = 0; // 4
    virtual bool SerializeInt16(int16_t* i, int size) = 0; // 5
    virtual bool SerializeSignedByte(int8_t* byte, int size) = 0; // 6
    virtual bool SerializeBool(bool* flag) = 0; // 7
    virtual bool SerializeInt64(int64_t* i, int size) = 0; // 8
    virtual bool SerializeInt32Alt(int32_t* i, int size) = 0; // 9
    virtual bool SerializeInt16Alt(int16_t* i, int size) = 0; // 10
    virtual bool SerializeSignedByteAlt(int8_t* byte, int size) = 0; // 11
    virtual bool SerializeQword(uint64_t* qword, int size) = 0; // 12
    virtual bool SerializeDwordAlt(uint32_t* dword, int size) = 0; // 13
    virtual bool SerializeWordAlt(uint16_t* word, int size) = 0; // 14
    virtual bool SerializeByteAlt(uint8_t* byte, int size) = 0; // 15
    virtual bool SerializeSignedFloat(float* flt, float divisor, int size) = 0; // 16
    virtual bool SerializeFloat(float* flt, float divisor, int size) = 0; // 17
    virtual bool SerializeNetworkId(uint16_t* net_id) = 0; // 18
    virtual bool SerializeVector3(rage::fvector3* vec3, float divisor, int size) = 0; // 19
    virtual bool SerializeQuaternion(void* unk) = 0; // i have no clue what that is
    virtual bool SerializeVector3SignedZComponent(rage::fvector3* vec3, float divisor, int size) = 0; // 21
    virtual bool SerializeOrientation(rage::fvector4* vec4, float size) = 0; // yes, the size is a float
    virtual bool SerializeArray(void* array, int size) = 0;
    virtual bool SerializeString(char* str, int max_length) = 0;
    virtual bool IsSizeCalculator() = 0;
    virtual bool IsSizeCalculator2() = 0;

    enum class Type
    {
        Reader = 1,
        Writer,
        SizeCalculator,
        Logger
    };

    Type m_type;
    void* m_sync_log;
    datBitBuffer* m_buffer;
};
static_assert(sizeof(TimecycleKeyframeData) == 0x5F0);
static_assert(sizeof(CHttpRequest) == 0x16E8);
struct rid_data {
    bool is_queued;
    class rage::rlGamerHandle gamer_handle { 0 };
    class rage::rlSessionInfo session_info;
};
inline rid_data m_rid_data{};
namespace rage {
    class netEventMgr;
    class JSONNode
    {
    public:
        char* m_key;                    //0x0000
        char pad_0008[32];              //0x0008
        class rage::JSONNode* m_sibling;//0x0028
        class rage::JSONNode* m_child;  //0x0030
        char* m_value;                  //0x0038
        char pad_0040[8];               //0x0040

        inline JSONNode* get_child_node(const char* name)
        {
            for (auto node = m_child; node; node = node->m_sibling)
            {
                if (strcmp(name, node->m_key) == 0)
                    return node;
            }

            return nullptr;
        }
    };//Size: 0x0048
    static_assert(sizeof(rage::JSONNode) == 0x48);

    class rlPresenceEventInviteAccepted {
    public:
        rlPresenceEventInviteAccepted(rlGamerInfo& gamerInfo, rlSessionInfo& sessionInfo, rlGamerHandle& gamerHandle) : m_gamer_info(gamerInfo), m_session_info(sessionInfo), m_gamer_handle(gamerHandle) {
            m_self = this;
        }
        virtual ~rlPresenceEventInviteAccepted() {}
        virtual void unk_0008() {}

        rlPresenceEventInviteAccepted* m_self; //0x0008
        rlGamerInfo m_gamer_info; //0x0010
        char pad_0100[8]; //0x0100
        rlSessionInfo m_session_info; //0x0108
        rlGamerHandle m_gamer_handle; //0x01D8
    }; //Size: 0x01E8
    static_assert(sizeof(rlPresenceEventInviteAccepted) == 0x1E8);
}
namespace Base {
    class CGameVisuals
    {
    public:
        float m_fog_level; //0x0000
        float m_unk_0x4; //0x0004
        float m_unk_0x8; //0x0008
        float m_fov; //0x000C
    }; //Size: 0x0010
    inline uint64_t read_instruction(uint64_t address, int opcode_size = 3, int opcode_length = 7) {
        return (uint64_t)(*(int*)(address + opcode_size) + address + opcode_length);
    }
    struct explosion_data {
        const char* m_explosion_name;
        int m_unk1;
        int m_unk2;
        float m_damage_at_centre;
        float m_damage_at_edge;
        float m_network_player_modifier;
        float m_network_ped_modifier;
        float m_end_radius;
        float m_init_speed;
        float m_decay_factor;
        float m_force_factor;
        float m_ragdoll_force_modifier;
        float m_self_force_modifier;
        float m_directed_width;
        float m_directed_lifetime;
        float m_cam_shake;
        float m_cam_shake_roll_off_scaling;
        float m_shocking_event_visual_range_override;
        float m_shocking_event_audio_range_override;
        float m_frag_damage;
        bool m_minor_explosion;
        bool m_applies_continuous_damage;
        bool m_post_process_collisions_with_no_force;
        bool m_damage_vehicles;
        bool m_damage_objects;
        bool m_only_affects_live_peds;
        bool m_ignore_exploding_entity;
        bool m_no_occlusion;
        bool m_explode_attach_entity_when_finished;
        bool m_can_set_ped_on_fire;
        bool m_can_set_player_on_fire;
        bool m_suppress_crime;
        bool m_use_distance_damage_calc;
        bool m_prevent_water_explosion_vfx;
        bool m_ignore_ratio_check_for_fire;
        bool m_allow_underwater_explosion;
        int m_unk3;
        float m_unk4;
        float m_unk5;
        char m_unk6[12];
        int m_cam_shake_name_hash;
        int m_vfx_tag_name_hash;
        int m_unk_size;
    };
    struct vfx_wheel {
        float m_slip_min; //0x0004
        float m_slip_max; //0x0008
        float m_pressure_min; //0x000C
        float m_pressure_max; //0x0010
        int m_type1; //0x0014
        BOOL m_unk1; //0x0018
        int m_type2; //0x001c
        BOOL m_unk2; //0x0010
        int m_type3; //0x0024
        BOOL m_unk3; //0x0028
        int m_type4; //0x002c
        BOOL m_unk4; //0x0030
        uint8_t m_r; //0x0034
        uint8_t m_g; //0x0035
        uint8_t m_b; //0x0036
        char _0x0037[1]; //0x0037
        float m_friction_thresh_min; //0x0038
        float m_friction_thresh_max; //0x003C
        uint32_t m_friction_fx1; //0x0040
        uint32_t m_friction_fx2; //0x0044
        uint32_t m_friction_fx3; //0x0048
        float m_disp_thresh_min; //0x004C
        float m_disp_thresh_max; //0x0050
        uint32_t m_displacement_fx1; //0x0054
        uint32_t m_displacement_fx2; //0x0058
        uint32_t m_displacement_fx3; //0x005C
        uint32_t m_displacement_fx_lod; //0x0060
        float m_burn_friction_evo_min; //0x0064
        float m_burn_friction_evo_max; //0x0068
        float m_burn_temp_evo_min; //0x006C
        float m_burn_temp_evo_max; //0x0070
        uint32_t m_burnout_fx1; //0x0074
        uint32_t m_burnout_fx2; //0x0078
        uint32_t m_burnout_fx3; //0x007C
        bool m_lights_on; //0x0080
        uint8_t m_lights_col_min_r; //0x0081
        uint8_t m_lights_col_min_g; //0x0082
        uint8_t m_lights_col_min_b; //0x0083
        uint8_t m_lights_col_max_r; //0x0084
        uint8_t m_lights_col_max_g; //0x0085
        uint8_t m_lights_col_max_b; //0x0086
        char _0x0087[1]; //0x0087
        float m_lights_intensity_min; //0x0088
        float m_lights_intensity_max; //0x008C
        float m_lights_range_min; //0x0090
        float m_lights_range_max; //0x0094
        float m_lights_falloff_min; //0x0098
        float m_lights_falloff_max; //0x009C
    };
    struct ui_element_vector {
        int m_index;
        char _0x0004[0xC];
        Vector4 m_value;
    };

    struct ui_element_vector_constant {
        Vector4 m_value;
        char _0x0004[0xC];
        int m_index;
    };

    struct ui_index {
        int m_index;
    };

    struct ui_element_integer {
        ui_index m_index;
        int m_value;
    };
    struct grc_texture_dx11 { // grcTexture
        char _0x0000[0x28];
        char* m_name;
        char _0x0030[0x8];
        void* m_texture; // ID3D11Resource
        char _0x0040[0x10];
        uint16_t m_width;
        uint16_t m_height;
        uint16_t m_depth;
        char _0x0056[0xA];
        grc_texture_dx11* m_previous;
        grc_texture_dx11* m_next;
        char _0x0070[0x8];
        void* m_shader; // ID3D11ShaderResourceView
        char _0x0080[0x20];
    };
    struct ui_element_shader {
        uint64_t m_raw_element;
        grc_texture_dx11* m_shader;
    };

    struct ui_visual_settings {
        char _0x0000[0x2874];
        float m_rim_light;
        float m_global_environment_reflection;
        float m_gamma;
        float m_mid_blur;
        float m_far_blur;
        float m_sky_multiplier;
        float m_desaturation;
    };
    struct ui_weather {
        char _0x0000[0x10];
        ui_element_vector m_azimuth_east_color;
        char _0x0030[0x10];
        ui_element_vector m_azimuth_west_color;
        char _0x0060[0x10];
        ui_element_vector m_azimuth_transition_color;
        char _0x0090[0x4];
        ui_element_integer m_azimuth_transition_position;
        char _0x009c[0x4];
        ui_element_vector m_zenith_color;
        char _0x00c0[0x10];
        ui_element_vector m_zenith_transition_color;
        char _0x00f0[0x4];
        ui_element_vector_constant m_zenith_constants;
        char _0x0114[0x1C];
        ui_element_vector m_sky_plane_color;
        char _0x0150[0x10];
        ui_index m_sky_plane_params;
        char _0x0164[0x34];
        ui_index m_sun_direction;
        ui_index m_sun_position;
        char _0x01a0[0x10];
        ui_element_vector m_sun_color;
        ui_element_vector m_sun_color_hdr;
        char _0x01f0[0x10];
        ui_element_vector m_sun_disc_color_hdr;
        char _0x0220[0x20];
        ui_element_vector m_sun_constants;
        ui_element_shader m_high_detail_noise;
        ui_element_vector_constant m_cloud_constant1;
        char _0x0290[0x10];
        ui_element_vector_constant m_cloud_constant2;
        char _0x02c0[0x10];
        ui_element_vector_constant m_cloud_constant3;
        char _0x02f0[0x10];
        ui_element_vector_constant m_cloud_detail_constants;
        char _0x0320[0x30];
        ui_element_vector m_cloud_base_minus_mid_colour;
        ui_element_vector m_cloud_mid_color;
        ui_element_vector m_cloud_shadow_minus_base_colour_times_shadow_strength;
        ui_element_vector_constant m_small_cloud_constants;
        char _0x03d0[0x20];
        ui_element_vector m_small_cloud_color_hdr;
        char _0x0410[0x10];
        ui_index m_cloudgen_frequency;
        char _0x0424[0x1C];
        ui_element_vector m_noise_phase;
        char _0x0460[0x20];
        ui_index m_speed_constants;
        char _0x0484[0x1C];
        ui_element_integer m_horizon_level;
        char _0x04a8[0x10];
        ui_element_shader m_dither;
        char _0x04c8[0x18];
        ui_element_shader m_star_field;
        ui_element_integer m_starfield_intensity;
        ui_element_shader m_moon;
        char _0x0508[0x28];
        ui_element_integer m_moon_intensity;
        char _0x0538[0x8];
        ui_element_vector m_moon_color;
        char _0x0560[0x10];
        ui_index m_lunar_cycle;
        char _0x0574[0x1C];
        ui_index m_moon_direction;
        ui_index m_moon_position;
        char _0x0598[0x18];
        ui_element_integer m_noise_frequency;
        ui_element_integer m_noise_scale;
        ui_element_integer m_noise_threshold;
        ui_element_integer m_noise_softness;
        ui_element_integer m_noise_density_offset;
        ui_element_shader m_noise;

        void set_sky(bool enabled) {
            *(bool*)((uint64_t)this - 0x60) = enabled;
        }
    };
    class dat_bit_buffer;
    class netEventMgr;
    class hash_list
    {
    public:
        std::uint64_t* list; //0x0000
        std::int32_t capacity; //0x0008
        char pad_000C[4]; //0x000C
        std::int32_t free; //0x0010
        char pad_0014[4]; //0x0014
        std::uint64_t item_size; //0x0018
        char pad_0020[16]; //0x0020
        std::uint32_t* data; //0x0030
        char pad_0038[16]; //0x0038
        std::int32_t occupied; //0x0048
        const std::uint64_t get(std::int32_t index) const {
            if ((this->data[index >> 5] >> (index & 0x1F)) & 1)
                return this->list[index];
            return NULL;
        }
    }; // Size: 0x004C
    template<typename T>
    struct vector4 {
        T x;
        T y;
        T z;
        T w;
        bool is_empty() {
            if (x == 0 && y == 0 && z == 0) {
                return true;
            }
            return false;
        }
    };
    struct waypoint_data {
        vector4<float>* m_points;
        char _0x0008[0x3C];
        uint32_t m_count;
    };
    struct hash_list2 {
        uint64_t m_count;
        uint64_t m_list;
    };
    struct explosion_fx {
        uint32_t m_name_hash;
        char Unk[0x20];
        float m_scale;
        char Unk2[0x38];
    };
    struct HashNode {
        uint32_t m_hash;
        uint16_t m_data;
        uint16_t m_padding;
        HashNode* m_next;
    };
    struct hash_node {
        uint32_t hash;
        uint16_t data;
        uint16_t padding;
        hash_node* next;
    };
    class transaction_queue
    {
    public:
        char pad_0000[57]; //0x0000
        bool busy_one;//0x0039
        char pad_003A[14]; //0x003A
        bool busy_two; //0x0048
        char pad_0049[7]; //0x0049
        bool busy_three; //0x0050
    };
    template <class T>
    class RageNode {
    public:
        char pad_0000[8];
        T* Data;
        class RageNode* Next;
        class RageNode* Last;
    };
    struct net_shop_queue {
        char _0x0000[32];
        void* m_first;
        void* m_last;
        char _0x0030[9];
        bool m_is_busy1;
        char _0x003A[14];
        bool m_is_busy2;
        char _0x0049[7];
        bool m_is_busy3;
    };
    inline HMODULE g_Kernel32{ GetModuleHandleA("kernel32") };
    struct hook_detour {
        LPVOID pTarget;
        void* pDetour;
        LPVOID* ppOriginal;
    };
    struct vfx_liquid {
        float m_duration_foot;
        float m_duration_wheel_in;
        float m_life_foot;
        float m_life_wheel;
        char _0x0010[0x48];
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        char _0x005C[0x4];
    };
    template<typename T>
    struct vector2 {
        T x;
        T y;

        vector2<T>() {}

        vector2<T>(T in_x, T in_y)
            : x(in_x), y(in_y) {}

        vector2<T> operator*(float value) {
            return vector2<T>(x * value, y * value);
        }

        vector2<T> operator*=(float value) {
            return vector2<T>(x * value, y * value);
        }

        vector2<T> operator*(vector2<T>& value) {
            return vector2<T>(x * value.x, y * value.y);
        }

        vector2<T> operator+=(vector2<T>& value) {
            x += value.x;
            y += value.y;
            return vector2<T>(x, y);
        }

        vector2<T> operator-(float value) {
            return vector2<T>(x - value, y - value);
        }

        vector2<T> operator-=(float value) {
            return vector2<T>(x - value, y - value);
        }

        vector2<T> operator-(vector2<T>& value) {
            return vector2<T>(x - value.x, y - value.y);
        }

        vector2<T> operator+(float value) {
            return vector2<T>(x + value, y + value);
        }

        vector2<T> operator+=(float value) {
            return vector2<T>(x + value, y + value);
        }

        vector2<T> operator+(vector2<T>& value) {
            return vector2<T>(x + value.x, y + value.y);
        }

        vector2<T> operator/(float value) {
            if (value == 0.f || x == 0 || y == 0) return vector2<T>(0, 0);
            return vector2<T>(x / value, y / value);
        }

        vector2<T> operator/=(float value) {
            if (value == 0.f || x == 0 || y == 0) return vector2<T>(0, 0);
            return vector2<T>(x / value, y / value);
        }

        vector2<T> operator/(vector2<T>& value) {
            return vector2<T>(x / value.x, y / value.y);
        }

        bool operator==(vector2<T>& value) {
            return x == value.x && y == value.y;
        }

        float get_distance(vector2<T>& value) {
            return ((float)sqrt(pow(value.x - x, 2) + pow(value.y - y, 2) * 1.0));
        }

        float get_length() {
            return (float)sqrt((x * x) + (y * y));
        }

        void normalize() {
            float Length = get_length();
            x /= Length;
            y /= Length;
        }
    };
    struct ocean_wave_quad {
        vector2<short> m_min;
        vector2<short> m_max;
        short m_amplitude;
        vector2<uint8_t> m_direction;
    };

    struct ocean_calming_quad {
        vector2<short> m_min;
        vector2<short> m_max;
        float m_dampening;
    };
    struct ocean_quad {
        vector2<short> m_min;
        vector2<short> m_max;
        uint32_t m_alpha;
        char _0x000C[0x8];
        float m_height;
        char _0x0024[0x4];
    };

    struct ocean_quad_info {
        uint64_t m_quad_pool;
        short m_quad_count;
    };

    struct ocean_quads {
        ocean_quad_info* m_ocean;
        ocean_quad_info* m_wave;
        ocean_quad_info* m_calming;
    };
    enum eDispatchType {
        PoliceAutomobile = 1,
        PoliceHelicopter,
        FireDepartment,
        SwatAutomobile,
        AmbulanceDepartment,
        PoliceRiders,
        PoliceVehicleRequest,
        PoliceRoadBlock,
        PoliceAutomobileWaitPulledOver,
        PoliceAutomobileWaitCruising,
        Gangs,
        SwatHelicopter,
        PoliceBoat,
        ArmyVehicle,
        BikerBackup,
        Assassin,
    };
    class CDispatch {
    public:
        char pad_0000[32]; //0x0000
        bool m_is_active; //0x0020
    }; //Size: 0x0020
    class CDispatchmentTable {
    public:
        void* unk_0000; //0x0000
        CDispatch m_dispatch[15]; //0x0008

        CDispatch& get(enum eDispatchType service) {
            return *reinterpret_cast<CDispatch*>(uint64_t(this) + (static_cast<uint64_t>(service) * 8));
        }
    }; //Size: 0x0078
    struct net_msg_identifier {
        uint64_t m_rockstar_id;
        uint8_t m_type;
        char _0x0009[0xB];
    };
    struct blacklisted_player {
        net_msg_identifier m_player;
        uint32_t m_timestamp;
        blacklisted_player* m_next;
        blacklisted_player* m_last;
    };
    struct rockstar_identifier {
        uint64_t m_rockstar_id;
        uint32_t m_type;
        uint32_t m_sub_type;
    };
    struct gs_session {
        uint64_t m_peer_token;
        uint64_t m_peer_token2;
        uint64_t m_peer_token3;
        rockstar_identifier m_rockstar_id;
        char _0x0028[0x48];

        uint32_t get_local_ip() {
            return *(uint32_t*)((uint64_t)this + 0x64);
        }
    };
    struct network_base_config {
        char _0x0000[0x20];
        uint64_t m_unk_ptr;
        uint64_t m_unk_ptr2;
        char _0x0030[0x198F8];
        net_msg_identifier m_last_blacklisted; // 0x19928
        uint32_t m_last_blacklisted_timestamp;
        char _0x184b0[0x280];
        blacklisted_player* m_first_blacklisted_player;
        blacklisted_player* m_last_blacklisted_player;

        void set_network_session_was_invited(bool invited) {
            *(bool*)((uint64_t)this + 0x86A5) = invited;
        }

        gs_session* get_gs_session() {
            return (gs_session*)((uint64_t)this + 0x178);
        }

        uint64_t get_net_msg_manager() {
            return *(uint64_t*)((uint64_t)this + 0x48);
        }
    };

    struct netTransaction {
        int m_id;
        int m_variation;
        int m_price;
        int m_multiplier;
        int m_value;
    };

    struct netShopTransactionBasket {
        char _0x0000[0x8];
        int m_transaction_id;
        char _0x000C[0xC];
        int m_category;
        char _0x001C[0x8];
        int m_action;
        int m_target; // 4 = bank etc
        char _0x002C[0xB4];
        netTransaction m_transactions[71];
        int m_transaction_count;
    };

    struct transactionNode {
        char _0x0000[0x8];
        netShopTransactionBasket* m_transaction;
        transactionNode* m_next;
    };

    struct tc_keyframe_uncompressed {
        float m_vars[(429 + 15) & ~15];

        __forceinline float* get_var_ptr(int index) {
            return &m_vars[index];
        }

        __forceinline float get_var(int index) const {
            return m_vars[index];
        }

        __forceinline void set_var(int index, float value) {
            m_vars[index] = value;
        }
    };

    struct tc_keyframe {
        uint16_t m_vars[(429 + 15) & ~15];

        __forceinline float get_var(int index) const {
            uint32_t e, z, s;

            e = (uint32_t)m_vars[index] << 16;
            s = 0x80000000u & e;
            e = 0x7fff0000u & e;
            z = (uint32_t)(((int)(e) | -(int)(e)) >> 31);
            z = 0x38000000u & z;
            e = ((e >> 3) + z) | s;

            return *(float*)&e;
        }

        __forceinline void set_var(int index, float value) {
            uint32_t i, e, l, o;
            i = *(uint32_t*)&value;
            e = 0x7fffffffu & i;
            e = 0x38000000u - e;
            l = (int)(0x00000000u + e) >> 31;
            o = (int)(0x0fffffffu + e) >> 31;
            e = (uint32_t)(-(int)e) >> 13;
            e = e | o;
            e = e & ((0x00007fffu & l));
            e = e | ((0x80000000u & i) >> 16);

            m_vars[index] = (uint16_t)e;
        }
    };

    struct tc_frame_info {
        tc_keyframe_uncompressed m_keyframe;
    };

    struct tc_cycle {
        tc_keyframe m_keyframe[2][13];
        uint32_t m_name;
        char _0x57C4[0x1C];
    };

    struct timecycle {
        char _0x0000[0x68];
        tc_cycle* m_cycles;
        char _0x0070[0x8E0 - 0x70];
        tc_keyframe_uncompressed m_replay_frame;
        tc_keyframe_uncompressed m_replay_default_frame;
        char _0x1660[0x40];
        tc_keyframe_uncompressed m_keyframe_cached_for_replay_jump;
        tc_frame_info m_frame_info;

        __forceinline void set_var(int index, float value) {
            for (int i = 0; i < 16; i++) {
                tc_cycle& cycle = m_cycles[i];
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 13; k++) {
                        cycle.m_keyframe[j][k].set_var(index, value);
                    }
                }
            }

            m_replay_frame.set_var(index, value);
            m_replay_default_frame.set_var(index, value);
            m_keyframe_cached_for_replay_jump.set_var(index, value);
            m_frame_info.m_keyframe.set_var(index, value);
        }
        __forceinline auto get_var(int index) {
            for (int i = 0; i < 16; i++) {
                tc_cycle& cycle = m_cycles[i];
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 13; k++) {
                       return cycle.m_keyframe[j][k].get_var(index);
                    }
                }
            }
        }
    };

    class CNetShopTransaction
    {
    public:
        std::uint32_t m_id; //0x0000
        std::uint32_t m_variation; //0x0004
        std::uint32_t m_price; //0x0008
        std::uint32_t m_multiplier; //0x000C
        std::uint32_t m_value; //0x0010
    }; //Size: 0x0014
    static_assert(sizeof(CNetShopTransaction) == 0x14);

    class CNetShopTransactionBasket
    {
    public:
        virtual ~CNetShopTransactionBasket() = default;

        std::uint32_t m_transaction_id; //0x0008
        char pad_000C[12]; //0x000C
        std::uint32_t m_category; //0x0018
        char pad_001C[8]; //0x001C
        std::uint32_t m_action; //0x0020
        std::uint32_t m_target; //0x0024
        char pad_0002C[180]; //0x0002C
        CNetShopTransaction m_transactions[71]; //0x00E0
        std::uint32_t m_transaction_count; //0x066C
    }; //Size: 0x0670
    static_assert(sizeof(CNetShopTransactionBasket) == 0x670);
#pragma pack(pop)

    class CNetworkShoppingMgr
    {
    public:
        virtual ~CNetworkShoppingMgr() = default;

        char pad_0008[24]; //0x0008
        rage::atDList<rage::atDNode<CNetShopTransactionBasket*>> m_transaction_nodes; //0x0020
        char pad_0030[9]; //0x0030
        bool m_is_busy1; //0x0039
        char pad_003A[14]; //0x003A
        bool m_is_busy2; //0x0048
        char pad_0049[7]; //0x0049
        bool m_is_busy3; //0x0050
        char pad_0051[79]; //0x0051
        void* m_inventory_items; //0x00A0
        char pad_00A8[24]; //0x00A8
        char m_gs_token[36]; //0x00C0
        char pad_00E4[28]; //0x00E4
        std::uint32_t m_transaction_noce_seed; //0x0100
        char pad_0104[44]; //0x0104
        std::uint32_t m_transaction_count; //0x0130
        char pad_0134[396]; //0x0134
        char* m_balance; //0x02C0

        std::uint32_t get_transaction_nonce() {
            return m_transaction_noce_seed + m_transaction_count;
        }
    }; //Size: 0x02C8
    static_assert(sizeof(CNetworkShoppingMgr) == 0x2C8);

    enum class eAckCode : uint32_t
    {
        ACKCODE_SUCCESS,
        ACKCODE_FAIL,
        ACKCODE_WRONG_OWNER,
        ACKCODE_OUT_OF_SEQUENCE,
        ACKCODE_NO_OBJECT,
        ACKCODE_TOO_MANY_OBJECTS,
        ACKCODE_CANT_APPLY_DATA,
        ACKCODE_MATCH_NOT_STARTED,
        ACKCODE_NONE
    };
    enum class eNetObjType
    {
        NET_OBJ_TYPE_AUTOMOBILE,
        NET_OBJ_TYPE_BIKE,
        NET_OBJ_TYPE_BOAT,
        NET_OBJ_TYPE_DOOR,
        NET_OBJ_TYPE_HELI,
        NET_OBJ_TYPE_OBJECT,
        NET_OBJ_TYPE_PED,
        NET_OBJ_TYPE_PICKUP,
        NET_OBJ_TYPE_PICKUP_PLACEMENT,
        NET_OBJ_TYPE_PLANE,
        NET_OBJ_TYPE_SUBMARINE,
        NET_OBJ_TYPE_PLAYER,
        NET_OBJ_TYPE_TRAILER,
        NET_OBJ_TYPE_TRAIN
    };
    enum class eNetObjectFlags : uint16_t
    {
        NET_OBJ_FLAGS_FROM_SCRIPT = 1 << 2,
        NET_OBJ_FLAGS_SCRIPTED = 1 << 6,
    };
    class netObjectMgrBase
    {
    public:
        class atDNetObjectNode : public rage::atDNode<rage::netObject*>
        {
        };

    public:
        virtual ~netObjectMgrBase() = default;

        virtual void Initialize() = 0;
        virtual void Shutdown() = 0;
        virtual void Update(bool) = 0;

        virtual void AddEntity(void*, void*) = 0;
        virtual void UnregisterNetworkObject_(void* unk, bool force) = 0;
        virtual void UnregisterNetworkObject(rage::netObject* object, int reason, bool force1, bool force2) = 0;

        virtual void ChangeOwner(rage::netObject* object, CNetGamePlayer* player, int migrationType) = 0;

        virtual void HandleJoiningPlayer(CNetGamePlayer* player) = 0;
        virtual void HandleLeavingPlayer(CNetGamePlayer* player) = 0;

        virtual void _0x50(CNetGamePlayer* player) = 0;
        virtual void _0x58() = 0;

        virtual void RegisterNetworkObject(rage::netObject* object) = 0;

        virtual void PackCloneCreate(rage::netObject* object, CNetGamePlayer* player, datBitBuffer* buffer) = 0;
        virtual bool PackCloneRemove(rage::netObject* object, CNetGamePlayer* player, bool) = 0;

        virtual void _0x78(rage::netObject* object, void*) = 0;
        virtual void _0x80() = 0;
        virtual void _0x88() = 0;
        virtual const char* _0x90(int) = 0;

        virtual bool HandleCloneCreate(CNetGamePlayer* source, CNetGamePlayer* target, eNetObjType object_type, uint16_t object_id, eNetObjectFlags object_flags, void*, uint32_t timestamp) = 0;
        virtual void HandleCloneCreateAck(CNetGamePlayer* source, CNetGamePlayer* target, uint16_t object_flags, eAckCode ack_code) = 0;

        virtual int HandleCloneSync(CNetGamePlayer* source, CNetGamePlayer* target, eNetObjType object_type, uint16_t object_id, void*, uint16_t, uint32_t timestamp) = 0;
        virtual void HandleCloneSyncAck(CNetGamePlayer* source, CNetGamePlayer* target, void*, uint16_t objectId, eAckCode ack_code) = 0;

        virtual void HandleCloneRemove(CNetGamePlayer* source, CNetGamePlayer* target, uint16_t object_id, int) = 0;
        virtual void HandleCloneRemoveAck(CNetGamePlayer* source, CNetGamePlayer* target, uint16_t object_id, eAckCode ack_code) = 0;

        virtual void _0xC8() = 0;

    public:
        rage::atDList<atDNetObjectNode> m_objects_owned_by_player[32];
    };
    class CNetworkObjectMgr : public netObjectMgrBase
    {
    public:
        rage::netObject* find_object_by_id(uint16_t object_id, bool can_delete_be_pending)
        {
            return nullptr;
        }
    };
   
}

struct CWaterQuad
{
    short MinX;   // 0x0
    short MinY;   // 0x2
    short MaxX;   // 0x4
    short MaxY;   // 0x6
    std::uint32_t Color;   // 0x8
    char unk1[4]; // 0xC
    char unk2[4]; // 0x10
    float Z;      // 0x14
    std::uint32_t Flags;   // 0x18
};
static_assert(sizeof(CWaterQuad) == 0x1C);


