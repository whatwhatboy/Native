#include "config_flags.hpp"

namespace Base::config_flags {
    void disable_arrests::init() {
        if (!m_enabled) return;
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_CanBeArrested, false);
    }
    void disable_arrests::on_disable() {
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_CanBeArrested, true);
    }

    void swimming::init() {
        if (!m_enabled) return;
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_IsSwimming, true);
    }
    void swimming::on_disable() {
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_IsSwimming, false);
    }

    void is_climbing_ladder::init() {
        if (!m_enabled) return;
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_IsClimbingLadder, true);
    }
    void is_climbing_ladder::on_disable() {
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_IsClimbingLadder, false);
    }

    void dont_take_off_helmet::init() {
        if (!m_enabled) return;
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_DontTakeOffHelmet, true);
    }
    void dont_take_off_helmet::on_disable() {
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_DontTakeOffHelmet, false);
    }

    void disable_wanted_level_sharing::init() {
        if (!m_enabled) return;
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_DontInfluenceWantedLevel, true);
    }
    void disable_wanted_level_sharing::on_disable() {
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_DontInfluenceWantedLevel, false);
    }

    void electrocution_ragdoll::init() {
        if (!m_enabled) return;
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_JustGetsPulledOutWhenElectrocuted, true);
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromElectrocution, true);
    }
    void electrocution_ragdoll::on_disable() {
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_JustGetsPulledOutWhenElectrocuted, false);
        PED::SET_PED_CONFIG_FLAG(g_utils->self(), ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromElectrocution, false);
    }

    void always_aiming::init() {
        if (!m_enabled) return;
        g_utils->cped()->forced_aim(true);
    }
    void always_aiming::on_disable() {
        g_utils->cped()->forced_aim(false);
    }
}