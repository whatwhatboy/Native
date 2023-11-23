#pragma once
#include "src/utility/common/common.h"
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
struct drop_shader {
    uint32_t m_name_hash;
    char _1[4];
    float m_velocity;
    float m_gravity;
    char _2[16];
    Vector4 m_box_centre_offset;
    Vector4 m_box_size;
    Vector4 m_life_min_max;
    Vector4 m_velocity_min;
    Vector4 m_velocity_max;
    char _3[32];
    grc_texture_dx11* m_texture_1;
    grc_texture_dx11* m_texture_2;
    Vector4 m_texture_rows_cols_start_end;
    Vector4 m_texture_anim_rate_scale_over_life_start_2_end_2;
    Vector4 m_size_min_max;
    Vector4 m_color;
    Vector2 m_fade_in_out;
    Vector2 m_fade_near_far;
    Vector4 m_fade_grd_off_lo_hi;
    Vector4 m_rot_speed_min_max;
    Vector4 m_directional_z_offset_min_max;
    Vector4 m_dir_vel_add_cam_speed_min_max_mult;
    float m_edge_softness;
    char _4[8];
    float m_particle_color_percentage;
    float m_background_distortion_visibility_percentage;
    float m_background_distortion_alpha_booster;
    float m_background_distortion_amount;
    uint32_t m_background_distortion_blur_level;
    float m_local_lights_multiplier;
    char _5[12];
};
struct shader {
    drop_shader* m_drop;
    ColorFloat m_internal_color;
    float m_luminance = 1.f;
};