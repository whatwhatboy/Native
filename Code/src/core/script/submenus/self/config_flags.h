#pragma once
#include "src/core/script/drawing/drawing.h"

namespace Base::submenus::self::config_flags {
	namespace flags {
        bool avoid_tear_gas;
        bool stopped_speech_upon_freezing;
        bool disable_goto_writhe_when_injured;
        bool only_use_forced_seat_when_entering_heli_in_group;
        bool thrown_from_vehicle_due_to_exhaustion;
        bool update_enclosed_search_region;
        bool disable_weird_ped_events;
        bool should_charge_now;
        bool ragdolling_on_boat;
        bool has_brandished_weapon;
        bool allow_minor_reactions_as_mission_ped;
        bool block_dead_body_shocking_events_when_dead;
        bool ped_has_been_seen;
        bool ped_is_in_reuse_pool;
        bool disable_turret_or_rear_seat_preference = false;
        bool disable_wanted_helicopter_spawning = false;
        bool use_target_perception_for_creating_aimed_at_events = false;
        bool disable_homing_missile_lockon = false;
        bool force_ignore_max_melee_active_support_combatants = false;
        bool stay_in_defensive_area_when_in_vehicle = false;
        bool dont_shout_target_position = false;
        bool disable_helmet_armor = false;
        bool created_by_concealed_player = false;
        bool permanently_disable_potential_to_be_walked_into_response = false;
        bool prevent_vehicle_exit_due_to_invalid_weapon = false;
        bool ignore_net_session_friendly_fire_check_for_allow_damage = false;
        bool dont_leave_combat_if_target_player_is_attacked_by_police = false;
        bool check_locked_before_warp = false;
        bool dont_shuffle_in_vehicle_to_make_room = false;
        bool give_weapon_on_getup = false;
        bool dont_hit_vehicle_with_projectiles = false;
        bool disable_forced_entry_for_open_vehicles_from_try_locked_door = false;
        bool fires_dummy_rockets = false;
        bool ped_is_arresting = false;
        bool is_decoy_ped = false;
        bool has_established_decoy = false;
        bool block_dispatched_helicopters_from_landing = false;
        bool dont_cry_for_help_on_stun = false;
        bool hit_by_tranq_weapon = false;
        bool can_be_incapacitated = false;
        bool forced_aim_from_arrest = false;
        bool dont_change_target_from_melee = false;
        bool disable_health_regeneration_when_stunned = false;
        bool ragdoll_floats_indefinitely = false;
        bool block_electric_weapon_damage = false;

        bool ped_was_reused;
        bool disable_shocking_events;
        bool moved_using_low_lod_physics_since_last_active;
        bool never_react_to_ped_on_roof;
        bool force_play_flee_scenario_exit_on_next_script_command;
        bool just_bumped_into_vehicle;
        bool disable_shocking_driving_on_pavement_events;
        bool should_throw_smoke_now;
        bool disable_ped_constraints;
        bool force_initial_peek_in_cover;
        bool created_by_dispatch;
        bool point_gun_left_hand_supporting;
        bool disable_jumping_from_vehicles_after_leader;
        bool dont_activate_ragdoll_from_player_ped_impact;
        bool dont_activate_ragdoll_from_ai_ragdoll_impact;
        bool dont_activate_ragdoll_from_player_ragdoll_impact;
        bool disable_quadruped_spring;
        bool is_in_cluster;
        bool shout_to_group_on_player_melee;
        bool ignored_by_auto_open_doors;
        bool prefer_injured_getup;
        bool force_ignore_melee_active_combatant;
        bool check_los_for_sound_events;
        bool jacked_abandoned_car;
        bool can_say_followed_by_player_audio;
        bool activate_ragdoll_from_minor_player_contact;
        bool has_portable_pickup_attached;
        bool force_pose_character_cloth;
        bool has_cloth_collision_bounds;
        bool has_high_heels;
        bool treat_as_ambient_ped_for_driver_lock_on;
        bool dont_behave_like_law;
        bool created_by_factory = false;
        bool can_be_shot_in_vehicle = false;
        bool no_critical_hits = false;
        bool drowns_in_water = false;
        bool drowns_in_sinking_vehicle = false;
        bool dies_instantly_when_swimming = false;
        bool has_bulletproof_vest = false;
        bool upper_body_damage_anims_only = false;
        bool never_fall_off_skis = false;
        bool never_ever_target_this_ped = false;
        bool this_ped_is_a_target_priority = false;
        bool targettable_with_no_los = false;
        bool doesnt_listen_to_player_group_commands = false;
        bool never_leaves_group = false;
        bool doesnt_drop_weapons_when_dead = false;
        bool set_delayed_weapon_as_current = false;
        bool keep_tasks_after_cleanup = false;
        bool block_non_temporary_events = false;
        bool has_a_script_brain = false;
        bool waiting_for_script_brain_to_load = false;
        bool allow_medics_to_revive_me = false;
        bool money_has_been_given_by_script = false;
        bool not_allowed_to_crouch = false;
        bool death_pickups_persist = false;
        bool ignore_seen_melee = false;
        bool force_die_if_injured = false;
        bool dont_drag_me_out_car = false;
        bool stay_in_car_on_jack = false;
        bool force_die_in_car = false;
        bool get_out_undriveable_vehicle = false;
        bool will_remain_on_boat_after_mission_ends = false;
        bool dont_store_as_persistent = false;
        bool will_fly_through_windscreen = false;
        bool die_when_ragdoll = false;
        bool has_helmet = false;
        bool use_helmet = false;
        bool dont_take_off_helmet = false;
        bool hide_in_cutscene = false;
        bool ped_is_enemy_to_player = false;
        bool disable_evasive_dives = false;
        bool ped_generates_dead_body_events = false;
        bool dont_attack_player_without_wanted_level = false;
        bool dont_influence_wanted_level = false;
        bool disable_player_lockon = false;
        bool disable_lockon_to_random_peds = false;
        bool allow_lockon_to_friendly_players = false;
        bool disable_horn_audio_when_dead = false;
        bool ped_being_deleted = false;
        bool block_weapon_switching = false;
        bool block_group_ped_aimed_at_response = false;
        bool will_follow_leader_any_means = false;
        bool blipped_by_script = false;
        bool draw_radar_visual_field = false;
        bool stop_weapon_firing_on_impact = false;
        bool disable_auto_fall_off_tests = false;
        bool steer_around_dead_bodies = false;
        bool constrain_to_nav_mesh = false;
        bool syncing_animated_props = false;
        bool is_firing = false;
        bool was_firing = false;
        bool is_standing = false;
        bool was_standing = false;
        bool in_vehicle = false;
        bool on_mount = false;
        bool attached_to_vehicle = false;
        bool is_swimming = false;
        bool was_swimming = false;
        bool is_skiing = false;
        bool is_sitting = false;
        bool killed_by_stealth = false;
        bool killed_by_takedown = false;
        bool knocked_out = false;
        bool clear_radar_blip_on_death = false;
        bool just_got_off_train = false;
        bool just_got_on_train = false;
        bool using_cover_point = false;
        bool is_in_the_air = false;
        bool knocked_up_into_air = false;
        bool is_aiming_gun = false;
        bool has_just_left_car = false;
        bool target_when_injured_allowed = false;
        bool curr_left_foot_coll_nm = false;
        bool prev_left_foot_coll_nm = false;
        bool curr_right_foot_coll_nm = false;
        bool prev_right_foot_coll_nm = false;
        bool has_been_bumped_in_car = false;
        bool in_water_task_quit_to_climb_ladder = false;
        bool nm_two_handed_weapon_both_hands_constrained = false;
        bool created_blood_pool_timer = false;
        bool dont_activate_ragdoll_from_any_ped_impact = false;
        bool group_ped_failed_to_enter_cover = false;
        bool already_chatted_on_phone = false;
        bool already_reacted_to_ped_on_roof = false;
        bool force_ped_load_cover = false;
        bool block_cowering_in_cover = false;
        bool block_peeking_in_cover = false;
        bool just_left_car_not_checked_for_doors = false;
        bool vault_from_cover = false;
        bool auto_conversation_look_ats = false;
        bool using_crouched_ped_capsule = false;
        bool has_dead_ped_been_reported = false;
        bool forced_aim = false;
        bool fall_out_of_vehicle_when_killed = false;
        bool get_out_burning_vehicle = false;
        bool bumped_by_player = false;
        bool run_from_fires_and_explosions = false;
        bool treat_as_player_during_targeting = false;
        bool is_hand_cuffed = false;
        bool is_ankle_cuffed = false;
        bool disable_melee = false;
        bool disable_unarmed_drivebys = false;
        bool just_gets_pulled_out_when_electrocuted = false;
        bool unused_replace_me = false;
        bool will_not_hotwire_law_enforcement_vehicle = false;
        bool will_commandeer_rather_than_jack = false;
        bool can_be_agitated = false;
        bool force_ped_to_face_left_in_cover = false;
        bool force_ped_to_face_right_in_cover = false;
        bool block_ped_from_turning_in_cover = false;
        bool keep_relationship_group_after_cleanup = false;
        bool force_ped_to_be_dragged = false;
        bool prevent_ped_from_reacting_to_being_jacked = false;
        bool is_scuba = false;
        bool will_arrest_rather_than_jack = false;
        bool remove_dead_extra_far_away = false;
        bool riding_train = false;
        bool arrest_result = false;
        bool can_attack_friendly = false;
        bool will_jack_any_player = false;
        bool bumped_by_player_vehicle = false;
        bool dodged_player_vehicle = false;
        bool will_jack_wanted_players_rather_than_steal_car = false;
        bool no_cop_wanted_aggro = false;
        bool disable_ladder_climbing = false;
        bool stairs_detected = false;
        bool slope_detected = false;
        bool helmet_has_been_shot = false;
        bool cower_instead_of_flee = false;
        bool can_activate_ragdoll_when_vehicle_upside_down = false;
        bool always_respond_to_cries_for_help = false;
        bool disable_blood_pool_creation = false;
        bool should_fix_if_no_collision = false;
        bool can_perform_arrest = false;
        bool can_perform_uncuff = false;
        bool can_be_arrested = false;
        bool mover_constricted_by_opposing_collisions = false;
        bool player_prefer_front_seat_mp = false;
        bool dont_activate_ragdoll_from_impact_object = false;
        bool dont_activate_ragdoll_from_melee = false;
        bool dont_activate_ragdoll_from_water_jet = false;
        bool dont_activate_ragdoll_from_drowning = false;
        bool dont_activate_ragdoll_from_falling = false;
        bool dont_activate_ragdoll_from_rubber_bullet = false;
        bool is_holding_prop = false;
        bool blocks_pathing_when_dead = false;
        bool force_play_normal_scenario_exit_on_next_script_command = false;
        bool force_play_immediate_scenario_exit_on_next_script_command = false;
        bool force_skin_character_cloth = false;
        bool leave_engine_on_when_exiting_vehicles = false;
        bool phone_disable_texting_animations = false;
        bool phone_disable_talking_animations = false;
        bool phone_disable_camera_animations = false;
        bool disable_blind_firing_in_shot_reactions = false;
        bool allow_nearby_cover_usage = false;
        bool in_strafe_transition = false;
        bool can_play_in_car_idles = false;
        bool can_attack_non_wanted_player_as_law = false;
        bool will_take_damage_when_vehicle_crashes = false;
        bool ai_can_drive_player_as_rear_passenger = false;
        bool player_can_jack_friendly_players = false;
        bool on_stairs = false;
        bool simulating_aiming = false;
        bool ai_driver_allow_friendly_passenger_seat_entry = false;
        bool parent_car_is_being_removed = false;
        bool allow_mission_ped_to_use_injured_movement = false;
        bool can_lose_helmet_on_damage = false;
        bool never_do_scenario_exit_probe_checks = false;
        bool suppress_low_lod_ragdoll_switch_when_corpse_settles = false;
        bool prevent_using_lower_priority_seats = false;
        bool just_left_vehicle_needs_reset = false;
        bool teleport_if_cant_reach_player = false;
        bool peds_in_vehicle_position_needs_reset = false;
        bool peds_fully_in_seat = false;
        bool allow_player_lock_on_if_friendly = false;
        bool use_camera_heading_for_desired_direction_lock_on_test = false;
        bool teleport_to_leader_vehicle = false;
        bool avoidance_ignore_weird_ped_buffer = false;
        bool on_stair_slope = false;
        bool has_played_nm_getup = false;
        bool dont_blip_cop = false;
        bool spawned_at_extended_range_scenario = false;
        bool walk_alongside_leader_when_close = false;
        bool kill_when_trapped = false;
        bool edge_detected = false;
        bool always_wake_up_physics_of_intersected_peds = false;
        bool equipped_ambient_load_out_weapon = false;
        bool avoidance_ignore_vehicles = false;
        bool spawned_at_scenario = false;
        bool disable_police_investigating_body = false;
        bool disable_writhe_shoot_from_ground = false;
        bool lower_priority_of_warp_seats = false;
        bool disable_talk_to = false;
        bool dont_blip; // Stops a ped being blipped by the wanted system
        bool is_switching_weapon; // Ped is running the swap weapon task
        bool ignore_leg_ik_restrictions; // If set, the ped will ignore leg IK request restrictions for non-player peds.
        bool script_force_no_timeslice_intelligence_update; // If set, the ped will never have their intelligence update time sliced across frames.
        bool jacked_out_of_my_vehicle; // If set, this ped has been jacked out of its vehicle.
        bool went_into_combat_after_being_jacked; // If set, this ped went into combat because of being jacked.
        bool dont_activate_ragdoll_for_vehicle_grab; // Blocks ragdoll activation when grabbing vehicle doors
        bool force_package_character_cloth; // Set the flag for forcing package on character cloth when cloth is created on the ped
        bool dont_remove_with_valid_order; //
        bool allow_task_do_nothing_timeslicing; // If set, this ped will timeslice its DoNothing Task when computing the default task.
        bool forced_to_stay_in_cover_due_to_player_switch;
        bool force_prone_character_cloth; // Set the flag to place character cloth in a prone state when cloth is created on the ped
        bool not_allowed_to_jack_any_players;
        bool in_to_strafe_transition;
        bool killed_by_standard_melee; // Killed by standard melee
        bool always_leave_train_upon_arrival; // Does this ped always (not randomly) leave the train when it arrives at a station
        bool force_play_directed_normal_scenario_exit_on_next_script_command; // Set flag to determine that a directed normal exit should be used for new tasks on this scenario ped.
        bool only_writhe_from_weapon_damage; // Only allow ped to writhe from weapon damage, not from other stuff, like small vehicle impacts
        bool use_slo_mo_blood_vfx; // Flags the ped to use the slo mo blood vfx instead of the normal ones
        bool equip_jetpack; // Equip/put on the jetpack if we have one in our inventory
        bool prevent_dragged_out_of_car_threat_response; // Don't do threat response when dragged out of a car
        bool script_has_completely_disabled_collision; // Script has completely disabled collision on this ped via SET_ENTITY_COMPLETELY_DISABLE_COLLISION
        bool never_do_scenario_nav_checks; // This ped will not check for the navmesh when exiting their scenario.
        bool force_synchronous_scenario_exit_checking; // This ped will expensively probe for a scenario exit location in one frame.
        bool throwing_grenade_while_aiming; // Set true in CTaskAimGunOnFoot::Aiming_OnUpdate, false in CTaskAimAndThrowProjectile::CleanUp.
        bool headbob_to_radio_enabled; // Set in.
        bool force_deep_surface_check; // Don't do distance from the camera culling of the deep surface check, needed for detecting snow, mud, etc.,
        bool disable_deep_surface_anims; // Disable deep surface anims to prevent them from slowing the ped down,
        bool dont_blip_not_synced; // Don't blip this ped, this is not synced over the network to allow the script to individually control a ped's blippedness on different machines
        bool is_ducking_in_vehicle; // Ped is ducking inside a vehicle.
        bool prevent_auto_shuffle_to_turret_seat;
        bool disable_event_interior_status_check; // Disables the ignore events based on interior status check which normally has peds inside ignoring events from outside
        bool has_reserve_parachute; // Does the ped have a reserve chute that they can deploy
        bool use_reserve_parachute; // Use reserve parachute settings.
        bool treat_dislike_as_hate_when_in_combat; // If this ped is in combat then any ped they dislike they will consider the relationship hate instead
        bool only_update_target_wanted_if_seen; // If the target is a player, we will only set the WL or update the radar if they are seen
        bool allow_auto_shuffle_to_drivers_seat; // Allows this ped to auto shuffle to the driver's seat of a vehicle if the driver is dead (law and MP peds would do this normally)
        bool dont_activate_ragdoll_from_smoke_grenade; // Blocks ragdoll activation when damaged by a smoke grenade
        bool link_mbr_to_owner_on_chain; // This ped will attempt to match the speed of the owner while following its current scenario chain.
        bool ambient_friend_bumped_by_player; // The player has walked into our ambient friend.
        bool ambient_friend_bumped_by_player_vehicle; // The player has driven into our ambient friend.
        bool in_fps_unholster_transition; // Player is playing the unholster transition in FPS mode
        bool prevent_reacting_to_silenced_clone_bullets; // Prevents the ped from reacting to silenced bullets fired from network clone peds
        bool disable_injured_cry_for_help_events; // Blocks ped from creating the injured cry for help events (run over, tazed, or melee would usually do this)
        bool never_leave_train; // Prevents peds riding trains from getting off them
        bool dont_drop_jetpack_on_death; // When dead, don't drop the equipped jetpack
        bool use_fps_unholster_transition_during_combat_roll; // Player is playing the unholster transition in FPS mode
        bool exiting_fps_combat_roll; // Player is exiting combat roll in FPS mode
        bool script_has_control_of_player; // True when the script is controlling the movement of the player
        bool play_fps_idle_fidgets_for_projectile; // True when we should be playing idle fidgets for projectiles
        bool disable_auto_equip_helmets_in_bikes; // Set from the interaction menu
        bool disable_auto_equip_helmets_in_aircraft; // Set from the interaction menu
        bool was_playing_fps_getup; // Was playing getup animations in FPS mode
        bool was_playing_fps_melee_action_result; // Was playing action result animations in FPS mode
        bool prefer_no_priority_removal; // Unless scenario conditions apply, make this ped go through normal deletion but not priority deletion.
        bool fps_fidgets_aborted_on_fire; // True when the FPS idle fidgets are aborted because the player fired the gun
        bool force_fps_ik_with_upper_body_anim; // True when upper body anims are used during various tasks.
        bool switching_characters_in_first_person; // True we switch a character in first person mode (in CGameWorld::ChangePlayerPed)
        bool is_climbing_ladder; // True when the ped is climbing a ladder
        bool has_bare_feet; // Set when the ped has no shoes
        bool unused_replace_me_2;
        bool go_on_without_vehicle_if_unable_to_get_back_to_road; // It will force the ped to abandon its vehicle (when using TaskGoToPointAnyMeans) if it is unable to get back to the road
        bool block_dropping_health_snacks_on_death; // Set by the script to prevent peds from dropping snack health pickups on death (in CPed::CreateDeadPedPickups).
        bool reset_last_vehicle_on_vehicle_exit; // Reset the ped's stored MyVehicle pointer when this ped leaves their vehicle.
        bool force_threat_response_to_non_friend_to_friend_melee_actions; // Forces threat response to melee actions from non-friend to friend peds.
        bool dont_respond_to_random_peds_damage; // Do not respond to random peds damage
        bool allow_continuous_threat_response_wanted_level_updates; // Shares logic of OnlyUpdateTargetWantedIfSeen but will continue to check even after the initial WL is set
        bool keep_target_loss_response_on_cleanup; // On cleanup, the ped will not reset their target loss response
        bool players_dont_drag_me_out_of_car; // Similar to DontDragMeOutCar except it only prevents players from dragging the ped out and allows AI to still do so
        bool broadcast_responded_to_threat_when_going_to_point_shooting; // Whenever the ped starts shooting while going to a point, it triggers a responded to threat broadcast
        bool ignore_ped_type_for_is_friendly_with; // If this is set then IsFriendlyWith will ignore the ped type checks (i.e., two PEDTYPE_COP peds are not automatically friendly)
        bool treat_non_friendly_as_hate_when_in_combat; // Any non-friendly ped will be considered as hated instead
        bool dont_leave_vehicle_if_leader_not_in_vehicle; // Suppresses exit vehicle task being created in CEventLeaderExitedCarAsDriver::CreateResponseTask.
        bool change_from_permanent_to_ambient_pop_type_on_migration; // Change ped to ambient pop type on migration.
        bool allow_melee_reaction_if_melee_proof_is_on; // Allow melee reaction to come through even if proof is on.
        bool using_lowrider_leans; // Ped is playing lowrider lean animations due to vehicle suspension modification.
        bool using_alternate_lowrider_leans; // Ped is playing alternate lowrider lean animations (i.e., arm on window) due to vehicle suspension modification.
        bool use_normal_explosion_damage_when_blown_up_in_vehicle; // If this is set, the ped won't be instantly killed if the vehicle is blown up (from CAutomobile::BlowUpCar -> KillPedsInVehicle). Instead, they will take normal explosive damage and be forced to exit the vehicle if they're still alive.
        bool disable_homing_missile_lock_for_vehicle_ped_inside; // Blocks locking on of the vehicle that the ped is inside.
        bool disable_take_off_scuba_gear; // Same as CPED_RESET_FLAG_DisableTakeOffScubaGear but on a config flag.
        bool ignore_melee_fist_weapon_damage_mult; // Melee fist weapons (i.e., knuckle duster) won't apply relative health damage scaler (m_MeleeRightFistTargetHealthDamageScaler in weapon info).
        bool law_peds_can_flee_from_non_wanted_player; // Allows law ped to flee even if the ped is not wanted and CWanted::m_AllRandomsFlee is set.
        bool force_blip_security_peds_if_player_is_wanted; // Forces security peds (not cop peds) to be blipped on the minimap if the player is wanted. Set on the local player.
        bool is_holstering_weapon; // Ped is running the swap weapon task and holstering the previous weapon, but has not started drawing the new one.
        bool use_go_to_point_for_scenario_navigation; // Don't use the nav mesh for navigating to scenario points. DLC Hack for yachts
        bool dont_clear_local_passengers_wanted_level; // Don't clear local ped's wanted level when the remote ped in the same car has his wanted level cleared by script.
        bool block_auto_swap_on_weapon_pickups; // Block auto weapon swaps for weapon pickups.
        bool this_ped_is_a_target_priority_for_ai; // Increase AI targeting score for peds with this flag.
        bool is_switching_helmet_visor; // Indicates that the ped is playing the switch visor up/down anim
        bool force_helmet_visor_switch; // Forces ped to do a visor helmet switch if able to.
        bool is_performing_vehicle_melee; // Indicates that the ped is performing a vehicle melee action.
        bool use_override_footstep_pt_fx; // The ped should use any override footstep effects that are set up.
        bool disable_vehicle_combat; // Disables vehicle combat.
        bool treat_as_friendly_for_targeting_and_damage; // Prevents this ped from being locked on and blocks the ability to damage/fire at ped.
        bool allow_bike_alternate_animations; // Allows players on motorcycles to use the alternate animation set when available.
        bool treat_as_friendly_for_targeting_and_damage_non_synced; // Prevents this ped from being locked on and blocks the ability to damage/fire at ped. This flag is not synced, so it will only work on the machine that sets it
        bool use_lockpick_vehicle_entry_animations; // When set, will attempt to use lockpick animations designed for Franklin in SP mode when breaking into a car.
        bool ignore_interior_check_for_sprinting; // When set, the player will be able to sprint inside interiors even if it is tagged to prevent it.
        bool swat_heli_spawn_within_last_spotted_location; // When set, swat helicopters will spawn within the last spotted location instead of the actual ped location (and the target is a player).
        bool disable_start_engine; // prevents ped from playing start engine anims (and turning the engine on)
        bool ignore_being_on_fire; // makes ped ignore being on fire (fleeing, reacting to CEventOnFire event)
       
        
        bool is_injured; // When true, the ped will use injured movement anim sets and getup animations.
        bool dont_enter_vehicles_in_players_group; // When true, will follow the player around if in their group but won't enter vehicles.
        bool swimming_tasks_running; // Stronger than is_swimming, persists as long as the tasks are active.
        bool prevent_all_melee_taunts; // Disable all melee taunts for this particular ped.
        bool force_direct_entry; // Will force this ped to use the direct entry point for any vehicle they try to enter, or warp in.
        bool always_see_approaching_vehicles; // This ped will always see approaching vehicles (even from behind).
        bool can_dive_away_from_approaching_vehicles; // This ped can dive away from approaching vehicles.
        bool allow_player_to_interrupt_vehicle_entry_exit; // Will allow the player to interrupt a ped's scripted entry/exit task as if they had triggered it themselves.
        bool only_attack_law_if_player_is_wanted; // This ped won't attack cops unless the player is wanted.
        bool player_in_contact_with_kinematic_ped; // Gets set to true if the player ped is colliding against a ped in kinematic mode.
        bool player_in_contact_with_something_other_than_kinematic_ped; // Gets set to true if the player ped is colliding against something that isn't a ped in kinematic mode.
        bool peds_jacking_me_dont_get_in; // If set, any ped jacking this ped will not get in as part of the jack.
        bool additional_rappelling_ped;
        bool ped_ignores_anim_interrupt_events; // AI peds only, will not early out of anims.
        bool is_in_custody; // Signifies a player is in custody.
        bool force_standard_bump_reaction_thresholds; // By default, armed and friendly peds have increased resistance to being bumped by players and friendly vehicles. Setting this flag will make them use the standard thresholds instead.
        bool law_will_only_attack_if_player_is_wanted; // If set, this ped can only be attacked by law if the player is wanted.
        bool is_agitated; // If set, this ped is agitated.
        bool prevent_auto_shuffle_to_drivers_seat; // MP only, prevents passengers from auto shuffling over to the driver's seat if it becomes free.
        bool use_kinematic_mode_when_stationary; // When enabled, the ped will continually set the kinematic mode reset flag when stationary.
        bool enable_weapon_blocking; // When enabled, non-player peds can use WeaponBlocking behaviors.
        bool has_hurt_started;
        bool disable_hurt; // Will prevent the peds from going into hurt combat mode.
        bool player_is_weird; // Should this player ped periodically generate shocking events for being weird.
        bool ped_had_phone_conversation; // Has this ped had a phone conversation before.
        bool began_crossing_road; // Indicates ped started crossing the road in case of interruption.
        bool warp_into_leaders_vehicle; // Warp into the leader's vehicle.
        bool do_nothing_when_on_foot_by_default; // Do nothing when on foot by default.
        bool using_scenario; // Set when the ped is using a scenario. Call CPed::UpdateSpatialArrayTypeFlags() if changing.
        bool visible_on_screen; // Set when the ped is visible on screen, as determined by CPedAILodManager.
        bool dont_collide_with_kinematic; // If true, the ped will not collide with other kinematic peds.
        bool activate_on_switch_from_low_physics_lod; // If set, activate physics when switching from low to regular physics LOD.
        bool dont_activate_ragdoll_on_ped_collision_when_dead; // Peds with this flag set won't be allowed to reactivate their ragdoll when hit by another ragdoll.
        bool dont_activate_ragdoll_on_vehicle_collision_when_dead; // Peds with this flag set won't be allowed to reactivate their ragdoll when hit by a vehicle.
        bool has_been_in_armed_combat; // Is set if this ped has ever been in armed combat.
        bool use_diminishing_ammo_rate; // Set for when we want to diminish the ammo at a slower rate. Used specifically in cases where AI do not have infinite ammo.
        bool avoidance_ignore_all; // This ped won't steer around anyone.
        bool avoidance_ignored_by_all; // Other peds won't steer around this ped.
        bool avoidance_ignore_group1; // This ped won't steer around peds marked group 1.
        bool avoidance_member_of_group1; // This ped is marked as a member of avoidance group 1.
        bool forced_to_use_specific_group_seat_index; // Ped is forced to use a specific seat index set by SET_PED_GROUP_MEMBER_PASSENGER_INDEX.
        bool low_physics_lod_may_place_on_nav_mesh; // If set, peds in low LOD physics will be placed so that their feet rest on the navmesh.
        bool disable_explosion_reactions; // If set, peds will disable all explosion reactions.
        bool dodged_player; // Whether this ped has just dodged a player.
        bool waiting_for_player_control_interrupt; // Set when the player switches to an AI ped and keeps the scripted task of the AI ped.
        bool forced_to_stay_in_cover; // Ped won't move out of cover when set (not even to fire).
        bool generates_sound_events; // Does this ped generate sound events?
        bool listens_to_sound_events; // Does this ped have the ability to respond to sound events?
        bool allow_to_be_targeted_in_a_vehicle; // Ped can be targeted inside a vehicle.
        bool wait_for_direct_entry_point_to_be_free_when_exiting;
        bool only_require_one_press_to_exit_vehicle;
        bool force_exit_to_skydive;
        bool steers_around_vehicles; // Enables/disables the low-level steering behavior around vehicles.
        bool allow_ped_in_vehicles_override_task_flags; // If set, allow the ped to be set in vehicles even if the ped's TaskData would otherwise disallow it.
        bool dont_enter_leaders_vehicle; // If set, the ped will not enter the leader's vehicle.
        bool disable_exit_to_skydive;
        bool script_has_disabled_collision; // Script disabled collision on this ped via SET_ENTITY_COLLISION, this leaves on collision against explosions and weapons.
        bool use_ambient_model_scaling; // This ped is drawn randomly scaled from [0.5,1.0].
        bool dont_watch_first_on_next_hurry_away; // Hurry away without watching the next time this ped runs CTaskHurryAway.
        bool disable_potential_to_be_walked_into_response; // Make EVENT_POTENTIAL_BE_WALKED_INTO not affect this ped.
        bool disable_ped_avoidance; // This ped will not avoid other peds while navigating.
        bool force_ragdoll_upon_death; // When the ped dies, it will ragdoll instead of potentially choosing an animated death.
        bool can_lose_props_on_damage; // When ped receives damage, any prop glasses could be knocked off.
        bool disable_panic_in_vehicle;
        bool allowed_to_detach_trailer; // Allow this ped to detach trailers from vehicles.
        bool has_shot_been_reacted_to_from_front;
        bool has_shot_been_reacted_to_from_back;
        bool has_shot_been_reacted_to_from_left;
        bool has_shot_been_reacted_to_from_right;
        bool allow_block_dead_ped_ragdoll_activation;
        bool steers_around_peds = false; // Enables/disables the low-level steering behaviour around peds and objects
        bool steers_around_objects = false; // Enables/disables the low-level steering behaviour around peds and objects
        bool open_door_arm_ik = false; // Set if the ped should enable open door arm IK
        bool force_reload = false; // Force a reload of the current weapon
        bool dont_activate_ragdoll_from_vehicle_impact = false; // Blocks ragdoll activation when hit by a vehicle
        bool dont_activate_ragdoll_from_bullet_impact = false; // Blocks ragdoll activation when hit by a bullet
        bool dont_activate_ragdoll_from_explosions = false; // Blocks ragdoll activation when hit by an explosive
        bool dont_activate_ragdoll_from_fire = false; // Blocks ragdoll activation when set on fire
        bool dont_activate_ragdoll_from_electrocution = false; // Blocks ragdoll activation when electrocuted
        bool is_being_dragged_to_safety = false; // Whether this ped is being dragged to safety
        bool has_been_dragged_to_safety = false; // Whether this ped has been dragged to safety
        bool keep_weapon_holstered_unless_fired = false; // Ignores the creation of the weapon object unless the gun is shot.
        bool force_script_controlled_knockout = false; // Forces a melee knockout state for the victim ped

	}
	void toggle(ePedConfigFlags flag, bool* tog) {
		PED::SET_PED_CONFIG_FLAG(g_utils->self(), (int)flag, *tog);
	}
	bool is_toggled(ePedConfigFlags flag) {
		return PED::GET_PED_CONFIG_FLAG(g_utils->self(), (int)flag, 1);
	}
	void draw_flag(const char* name, std::pair<ePedConfigFlags, bool*> pair) {
		draw->toggle(name, pair.second, [=] { toggle(pair.first, pair.second); });
	}
    struct config_flag_s {
        const char* name;
        ePedConfigFlags flag;
        bool* toggle;
    };
    std::vector<config_flag_s> g_config_flags;
	void init() {
        for (auto& fl : g_config_flags) {
            draw->toggle(fl.name, fl.toggle, [=] { toggle(fl.flag, fl.toggle); });
        }
	}
    bool config_toggles[461];
    void push_f(const char* name, ePedConfigFlags flag, bool* tog) {
        *tog = is_toggled(flag);
        g_config_flags.push_back({ name, flag, tog });
    }
	void on_click() {
        g_config_flags.clear();
        push_f("Created By Factory", ePedConfigFlags::CPED_CONFIG_FLAG_CreatedByFactory, &flags::created_by_factory);
        push_f("Can Be Shot In Vehicle", ePedConfigFlags::CPED_CONFIG_FLAG_CanBeShotInVehicle, &flags::can_be_shot_in_vehicle);
        push_f("No Critical Hits", ePedConfigFlags::CPED_CONFIG_FLAG_NoCriticalHits, &flags::no_critical_hits);
        push_f("Drowns In Water", ePedConfigFlags::CPED_CONFIG_FLAG_DrownsInWater, &flags::drowns_in_water);
        push_f("Drowns In Sinking Vehicle", ePedConfigFlags::CPED_CONFIG_FLAG_DrownsInSinkingVehicle, &flags::drowns_in_sinking_vehicle);
        push_f("Dies Instantly When Swimming", ePedConfigFlags::CPED_CONFIG_FLAG_DiesInstantlyWhenSwimming, &flags::dies_instantly_when_swimming);
        push_f("Has Bullet Proof Vest", ePedConfigFlags::CPED_CONFIG_FLAG_HasBulletProofVest, &flags::has_bulletproof_vest);
        push_f("Never Fall Off Skis", ePedConfigFlags::CPED_CONFIG_FLAG_NeverFallOffSkis, &flags::never_fall_off_skis);
        push_f("Never Target This Ped", ePedConfigFlags::CPED_CONFIG_FLAG_NeverEverTargetThisPed, &flags::never_ever_target_this_ped);
        push_f("This Ped Is A Target Priority", ePedConfigFlags::CPED_CONFIG_FLAG_ThisPedIsATargetPriority, &flags::this_ped_is_a_target_priority);
        push_f("Targettable With No Los", ePedConfigFlags::CPED_CONFIG_FLAG_TargettableWithNoLos, &flags::targettable_with_no_los);
        push_f("Doesnt Listen To Player Group Commands", ePedConfigFlags::CPED_CONFIG_FLAG_DoesntListenToPlayerGroupCommands, &flags::doesnt_listen_to_player_group_commands);
        push_f("Never Leaves Group", ePedConfigFlags::CPED_CONFIG_FLAG_NeverLeavesGroup, &flags::never_leaves_group);
        push_f("Doesnt Drop Weapons When Dead", ePedConfigFlags::CPED_CONFIG_FLAG_DoesntDropWeaponsWhenDead, &flags::doesnt_drop_weapons_when_dead);
        push_f("Set Delayed Weapon As Current", ePedConfigFlags::CPED_CONFIG_FLAG_SetDelayedWeaponAsCurrent, &flags::set_delayed_weapon_as_current);
        push_f("Keep Tasks After Clean Up", ePedConfigFlags::CPED_CONFIG_FLAG_KeepTasksAfterCleanUp, &flags::keep_tasks_after_cleanup);
        push_f("Block Non Temporary Events", ePedConfigFlags::CPED_CONFIG_FLAG_BlockNonTemporaryEvents, &flags::block_non_temporary_events);
        push_f("Has A Script Brain", ePedConfigFlags::CPED_CONFIG_FLAG_HasAScriptBrain, &flags::has_a_script_brain);
        push_f("Waiting For Script Brain To Load", ePedConfigFlags::CPED_CONFIG_FLAG_WaitingForScriptBrainToLoad, &flags::waiting_for_script_brain_to_load);
        push_f("Allow Medics To Revive Me", ePedConfigFlags::CPED_CONFIG_FLAG_AllowMedicsToReviveMe, &flags::allow_medics_to_revive_me);
        push_f("Money Has Been Given By Script", ePedConfigFlags::CPED_CONFIG_FLAG_MoneyHasBeenGivenByScript, &flags::money_has_been_given_by_script);
        push_f("Not Allowed To Crouch", ePedConfigFlags::CPED_CONFIG_FLAG_NotAllowedToCrouch, &flags::not_allowed_to_crouch);
        push_f("Death Pickups Persist", ePedConfigFlags::CPED_CONFIG_FLAG_DeathPickupsPersist, &flags::death_pickups_persist);
        push_f("Ignore Seen Melee", ePedConfigFlags::CPED_CONFIG_FLAG_IgnoreSeenMelee, &flags::ignore_seen_melee);
        push_f("Force Die If Injured", ePedConfigFlags::CPED_CONFIG_FLAG_ForceDieIfInjured, &flags::force_die_if_injured);
        push_f("Dont Drag Me Out Car", ePedConfigFlags::CPED_CONFIG_FLAG_DontDragMeOutCar, &flags::dont_drag_me_out_car);
        push_f("Stay In Car On Jack", ePedConfigFlags::CPED_CONFIG_FLAG_StayInCarOnJack, &flags::stay_in_car_on_jack);
        push_f("Force Die In Car", ePedConfigFlags::CPED_CONFIG_FLAG_ForceDieInCar, &flags::force_die_in_car);
        push_f("Get Out Undriveable Vehicle", ePedConfigFlags::CPED_CONFIG_FLAG_GetOutUndriveableVehicle, &flags::get_out_undriveable_vehicle);
        push_f("Will Remain On Boat After Mission Ends", ePedConfigFlags::CPED_CONFIG_FLAG_WillRemainOnBoatAfterMissionEnds, &flags::will_remain_on_boat_after_mission_ends);
        push_f("Dont Store As Persistent", ePedConfigFlags::CPED_CONFIG_FLAG_DontStoreAsPersistent, &flags::dont_store_as_persistent);
        push_f("Will Fly Through Windscreen", ePedConfigFlags::CPED_CONFIG_FLAG_WillFlyThroughWindscreen, &flags::will_fly_through_windscreen);
        push_f("Die When Ragdoll", ePedConfigFlags::CPED_CONFIG_FLAG_DieWhenRagdoll, &flags::die_when_ragdoll);
        push_f("Has Helmet", ePedConfigFlags::CPED_CONFIG_FLAG_HasHelmet, &flags::has_helmet);
        push_f("Use Helmet", ePedConfigFlags::CPED_CONFIG_FLAG_UseHelmet, &flags::use_helmet);
        push_f("Dont Take Off Helmet", ePedConfigFlags::CPED_CONFIG_FLAG_DontTakeOffHelmet, &flags::dont_take_off_helmet);
        push_f("Hide In Cutscene", ePedConfigFlags::CPED_CONFIG_FLAG_HideInCutscene, &flags::hide_in_cutscene);
        push_f("Ped Is Enemy To Player", ePedConfigFlags::CPED_CONFIG_FLAG_PedIsEnemyToPlayer, &flags::ped_is_enemy_to_player);
        push_f("Disable Evasive Dives", ePedConfigFlags::CPED_CONFIG_FLAG_DisableEvasiveDives, &flags::disable_evasive_dives);
        push_f("Ped Generates Dead Body Events", ePedConfigFlags::CPED_CONFIG_FLAG_PedGeneratesDeadBodyEvents, &flags::ped_generates_dead_body_events);
        push_f("Dont Attack Player Without Wanted Level", ePedConfigFlags::CPED_CONFIG_FLAG_DontAttackPlayerWithoutWantedLevel, &flags::dont_attack_player_without_wanted_level);
        push_f("Dont Influence Wanted Level", ePedConfigFlags::CPED_CONFIG_FLAG_DontInfluenceWantedLevel, &flags::dont_influence_wanted_level);
        push_f("Disable Player Lockon", ePedConfigFlags::CPED_CONFIG_FLAG_DisablePlayerLockon, &flags::disable_player_lockon);
        push_f("Disable Lockon To Random Peds", ePedConfigFlags::CPED_CONFIG_FLAG_DisableLockonToRandomPeds, &flags::disable_lockon_to_random_peds);
        push_f("Allow Lockon To Firendly Players", ePedConfigFlags::CPED_CONFIG_FLAG_AllowLockonToFriendlyPlayers, &flags::allow_lockon_to_friendly_players);
        push_f("Disable Horn Audio When Dead", ePedConfigFlags::CPED_CONFIG_FLAG_DisableHornAudioWhenDead, &flags::disable_horn_audio_when_dead);
        push_f("Ped Being Deleted", ePedConfigFlags::CPED_CONFIG_FLAG_PedBeingDeleted, &flags::ped_being_deleted);
        push_f("Block Weapon Switching", ePedConfigFlags::CPED_CONFIG_FLAG_BlockWeaponSwitching, &flags::block_weapon_switching);
        push_f("Block Group Ped Aimed At Response", ePedConfigFlags::CPED_CONFIG_FLAG_BlockGroupPedAimedAtResponse, &flags::block_group_ped_aimed_at_response);
        push_f("Will Follow Leader Any Means", ePedConfigFlags::CPED_CONFIG_FLAG_WillFollowLeaderAnyMeans, &flags::will_follow_leader_any_means);
        push_f("Blipped By Script", ePedConfigFlags::CPED_CONFIG_FLAG_BlippedByScript, &flags::blipped_by_script);
        push_f("Draw Radar Visual Field", ePedConfigFlags::CPED_CONFIG_FLAG_DrawRadarVisualField, &flags::draw_radar_visual_field);
        push_f("Stop Weapon Firing On Impact", ePedConfigFlags::CPED_CONFIG_FLAG_StopWeaponFiringOnImpact, &flags::stop_weapon_firing_on_impact);
        push_f("Disable Auto Fall Off Tests", ePedConfigFlags::CPED_CONFIG_FLAG_DissableAutoFallOffTests, &flags::disable_auto_fall_off_tests);
        push_f("Steer Around Dead Bodies", ePedConfigFlags::CPED_CONFIG_FLAG_SteerAroundDeadBodies, &flags::steer_around_dead_bodies);
        push_f("Constrain To NavMesh", ePedConfigFlags::CPED_CONFIG_FLAG_ConstrainToNavMesh, &flags::constrain_to_nav_mesh);
        push_f("Syncing Animated Props", ePedConfigFlags::CPED_CONFIG_FLAG_SyncingAnimatedProps, &flags::syncing_animated_props);
        push_f("Is Firing", ePedConfigFlags::CPED_CONFIG_FLAG_IsFiring, &flags::is_firing);
        push_f("Was Firing", ePedConfigFlags::CPED_CONFIG_FLAG_WasFiring, &flags::was_firing);
        push_f("Is Standing", ePedConfigFlags::CPED_CONFIG_FLAG_IsStanding, &flags::is_standing);
        push_f("Was Standing", ePedConfigFlags::CPED_CONFIG_FLAG_WasStanding, &flags::was_standing);
        push_f("In Vehicle", ePedConfigFlags::CPED_CONFIG_FLAG_InVehicle, &flags::in_vehicle);
        push_f("On Mount", ePedConfigFlags::CPED_CONFIG_FLAG_OnMount, &flags::on_mount);
        push_f("Attached To Vehicle", ePedConfigFlags::CPED_CONFIG_FLAG_AttachedToVehicle, &flags::attached_to_vehicle);
        push_f("Is Swimming", ePedConfigFlags::CPED_CONFIG_FLAG_IsSwimming, &flags::is_swimming);
        push_f("Was Swimming", ePedConfigFlags::CPED_CONFIG_FLAG_WasSwimming, &flags::was_swimming);
        push_f("Is Skiing", ePedConfigFlags::CPED_CONFIG_FLAG_IsSkiing, &flags::is_skiing);
        push_f("Is Sitting", ePedConfigFlags::CPED_CONFIG_FLAG_IsSitting, &flags::is_sitting);
        push_f("Killed By Stealth", ePedConfigFlags::CPED_CONFIG_FLAG_KilledByStealth, &flags::killed_by_stealth);
        push_f("Killed By Takedown", ePedConfigFlags::CPED_CONFIG_FLAG_KilledByTakedown, &flags::killed_by_takedown);
        push_f("Knockedout", ePedConfigFlags::CPED_CONFIG_FLAG_Knockedout, &flags::knocked_out);
        push_f("Clear Radar Blip On Death", ePedConfigFlags::CPED_CONFIG_FLAG_ClearRadarBlipOnDeath, &flags::clear_radar_blip_on_death);
        push_f("Just Got Off Train", ePedConfigFlags::CPED_CONFIG_FLAG_JustGotOffTrain, &flags::just_got_off_train);
        push_f("Just Got On Train", ePedConfigFlags::CPED_CONFIG_FLAG_JustGotOnTrain, &flags::just_got_on_train);
        push_f("Using Cover Point", ePedConfigFlags::CPED_CONFIG_FLAG_UsingCoverPoint, &flags::using_cover_point);
        push_f("Is In The Air", ePedConfigFlags::CPED_CONFIG_FLAG_IsInTheAir, &flags::is_in_the_air);
        push_f("Knocked Up Into Air", ePedConfigFlags::CPED_CONFIG_FLAG_KnockedUpIntoAir, &flags::knocked_up_into_air);
        push_f("Is Aiming Gun", ePedConfigFlags::CPED_CONFIG_FLAG_IsAimingGun, &flags::is_aiming_gun);
        push_f("Has Just Left Car", ePedConfigFlags::CPED_CONFIG_FLAG_HasJustLeftCar, &flags::has_just_left_car);
        push_f("Target When Injured Allowed", ePedConfigFlags::CPED_CONFIG_FLAG_TargetWhenInjuredAllowed, &flags::target_when_injured_allowed);
        push_f("Curr Left Foot Coll NM", ePedConfigFlags::CPED_CONFIG_FLAG_CurrLeftFootCollNM, &flags::curr_left_foot_coll_nm);
        push_f("Curr Left Foot Coll NM", ePedConfigFlags::CPED_CONFIG_FLAG_CurrLeftFootCollNM, &flags::curr_left_foot_coll_nm);
        push_f("Prev Left Foot Coll NM", ePedConfigFlags::CPED_CONFIG_FLAG_PrevLeftFootCollNM, &flags::prev_left_foot_coll_nm);
        push_f("Curr Right Foot Coll NM", ePedConfigFlags::CPED_CONFIG_FLAG_CurrRightFootCollNM, &flags::curr_right_foot_coll_nm);
        push_f("Prev Right Foot Coll NM", ePedConfigFlags::CPED_CONFIG_FLAG_PrevRightFootCollNM, &flags::prev_right_foot_coll_nm);
        push_f("Has Been Bumped In Car", ePedConfigFlags::CPED_CONFIG_FLAG_HasBeenBumpedInCar, &flags::has_been_bumped_in_car);
        push_f("In Water Task Quit To Climb Ladder", ePedConfigFlags::CPED_CONFIG_FLAG_InWaterTaskQuitToClimbLadder, &flags::in_water_task_quit_to_climb_ladder);
        push_f("NM Two-Handed Weapon Both Hands Constrained", ePedConfigFlags::CPED_CONFIG_FLAG_NMTwoHandedWeaponBothHandsConstrained, &flags::nm_two_handed_weapon_both_hands_constrained);
        push_f("Created Blood Pool Timer", ePedConfigFlags::CPED_CONFIG_FLAG_CreatedBloodPoolTimer, &flags::created_blood_pool_timer);
        push_f("Don't Activate Ragdoll From Any Ped Impact", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromAnyPedImpact, &flags::dont_activate_ragdoll_from_any_ped_impact);
        push_f("Group Ped Failed To Enter Cover", ePedConfigFlags::CPED_CONFIG_FLAG_GroupPedFailedToEnterCover, &flags::group_ped_failed_to_enter_cover);
        push_f("Already Chatted On Phone", ePedConfigFlags::CPED_CONFIG_FLAG_AlreadyChattedOnPhone, &flags::already_chatted_on_phone);
        push_f("Already Reacted To Ped On Roof", ePedConfigFlags::CPED_CONFIG_FLAG_AlreadyReactedToPedOnRoof, &flags::already_reacted_to_ped_on_roof);
        push_f("Force Ped Load Cover", ePedConfigFlags::CPED_CONFIG_FLAG_ForcePedLoadCover, &flags::force_ped_load_cover);
        push_f("Block Cowering In Cover", ePedConfigFlags::CPED_CONFIG_FLAG_BlockCoweringInCover, &flags::block_cowering_in_cover);
        push_f("Block Peeking In Cover", ePedConfigFlags::CPED_CONFIG_FLAG_BlockPeekingInCover, &flags::block_peeking_in_cover);
        push_f("Just Left Car Not Checked For Doors", ePedConfigFlags::CPED_CONFIG_FLAG_JustLeftCarNotCheckedForDoors, &flags::just_left_car_not_checked_for_doors);
        push_f("Vault From Cover", ePedConfigFlags::CPED_CONFIG_FLAG_VaultFromCover, &flags::vault_from_cover);
        push_f("Auto Conversation Look Ats", ePedConfigFlags::CPED_CONFIG_FLAG_AutoConversationLookAts, &flags::auto_conversation_look_ats);
        push_f("Using Crouched Ped Capsule", ePedConfigFlags::CPED_CONFIG_FLAG_UsingCrouchedPedCapsule, &flags::using_crouched_ped_capsule);
        push_f("Has Dead Ped Been Reported", ePedConfigFlags::CPED_CONFIG_FLAG_HasDeadPedBeenReported, &flags::has_dead_ped_been_reported);
        push_f("Forced Aim", ePedConfigFlags::CPED_CONFIG_FLAG_ForcedAim, &flags::forced_aim);
        push_f("Steers Around Peds", ePedConfigFlags::CPED_CONFIG_FLAG_SteersAroundPeds, &flags::steers_around_peds);
        push_f("Steers Around Objects", ePedConfigFlags::CPED_CONFIG_FLAG_SteersAroundObjects, &flags::steers_around_objects);
        push_f("Open Door Arm IK", ePedConfigFlags::CPED_CONFIG_FLAG_OpenDoorArmIK, &flags::open_door_arm_ik);
        push_f("Force Reload", ePedConfigFlags::CPED_CONFIG_FLAG_ForceReload, &flags::force_reload);
        push_f("Don't Activate Ragdoll From Vehicle Impact", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromVehicleImpact, &flags::dont_activate_ragdoll_from_vehicle_impact);
        push_f("Don't Activate Ragdoll From Bullet Impact", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromBulletImpact, &flags::dont_activate_ragdoll_from_bullet_impact);
        push_f("Don't Activate Ragdoll From Explosions", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromExplosions, &flags::dont_activate_ragdoll_from_explosions);
        push_f("Don't Activate Ragdoll From Fire", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromFire, &flags::dont_activate_ragdoll_from_fire);
        push_f("Don't Activate Ragdoll From Electrocution", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromElectrocution, &flags::dont_activate_ragdoll_from_electrocution);
        push_f("Is Being Dragged To Safety", ePedConfigFlags::CPED_CONFIG_FLAG_IsBeingDraggedToSafety, &flags::is_being_dragged_to_safety);
        push_f("Has Been Dragged To Safety", ePedConfigFlags::CPED_CONFIG_FLAG_HasBeenDraggedToSafety, &flags::has_been_dragged_to_safety);
        push_f("Keep Weapon Holstered Unless Fired", ePedConfigFlags::CPED_CONFIG_FLAG_KeepWeaponHolsteredUnlessFired, &flags::keep_weapon_holstered_unless_fired);
        push_f("Force Script Controlled Knockout", ePedConfigFlags::CPED_CONFIG_FLAG_ForceScriptControlledKnockout, &flags::force_script_controlled_knockout);
        push_f("Fall Out Of Vehicle When Killed", ePedConfigFlags::CPED_CONFIG_FLAG_FallOutOfVehicleWhenKilled, &flags::fall_out_of_vehicle_when_killed);
        push_f("Get Out Burning Vehicle", ePedConfigFlags::CPED_CONFIG_FLAG_GetOutBurningVehicle, &flags::get_out_burning_vehicle);
        push_f("Bumped By Player", ePedConfigFlags::CPED_CONFIG_FLAG_BumpedByPlayer, &flags::bumped_by_player);
        push_f("Run From Fires And Explosions", ePedConfigFlags::CPED_CONFIG_FLAG_RunFromFiresAndExplosions, &flags::run_from_fires_and_explosions);
        push_f("Treat As Player During Targeting", ePedConfigFlags::CPED_CONFIG_FLAG_TreatAsPlayerDuringTargeting, &flags::treat_as_player_during_targeting);
        push_f("Is Handcuffed", ePedConfigFlags::CPED_CONFIG_FLAG_IsHandCuffed, &flags::is_hand_cuffed);
        push_f("Is Ankle Cuffed", ePedConfigFlags::CPED_CONFIG_FLAG_IsAnkleCuffed, &flags::is_ankle_cuffed);
        push_f("Disable Melee", ePedConfigFlags::CPED_CONFIG_FLAG_DisableMelee, &flags::disable_melee);
        push_f("Disable Unarmed Drivebys", ePedConfigFlags::CPED_CONFIG_FLAG_DisableUnarmedDrivebys, &flags::disable_unarmed_drivebys);
        push_f("Just Gets Pulled Out When Electrocuted", ePedConfigFlags::CPED_CONFIG_FLAG_JustGetsPulledOutWhenElectrocuted, &flags::just_gets_pulled_out_when_electrocuted);
        push_f("Unused Replace Me", ePedConfigFlags::CPED_CONFIG_FLAG_UNUSED_REPLACE_ME, &flags::unused_replace_me);
        push_f("Will Not Hotwire Law Enforcement Vehicle", ePedConfigFlags::CPED_CONFIG_FLAG_WillNotHotwireLawEnforcementVehicle, &flags::will_not_hotwire_law_enforcement_vehicle);
        push_f("Will Commandeer Rather Than Jack", ePedConfigFlags::CPED_CONFIG_FLAG_WillCommandeerRatherThanJack, &flags::will_commandeer_rather_than_jack);
        push_f("Can Be Agitated", ePedConfigFlags::CPED_CONFIG_FLAG_CanBeAgitated, &flags::can_be_agitated);
        push_f("Force Ped To Face Left In Cover", ePedConfigFlags::CPED_CONFIG_FLAG_ForcePedToFaceLeftInCover, &flags::force_ped_to_face_left_in_cover);
        push_f("Force Ped To Face Right In Cover", ePedConfigFlags::CPED_CONFIG_FLAG_ForcePedToFaceRightInCover, &flags::force_ped_to_face_right_in_cover);
        push_f("Block Ped From Turning In Cover", ePedConfigFlags::CPED_CONFIG_FLAG_BlockPedFromTurningInCover, &flags::block_ped_from_turning_in_cover);
        push_f("Keep Relationship Group After Cleanup", ePedConfigFlags::CPED_CONFIG_FLAG_KeepRelationshipGroupAfterCleanUp, &flags::keep_relationship_group_after_cleanup);
        push_f("Force Ped To Be Dragged", ePedConfigFlags::CPED_CONFIG_FLAG_ForcePedToBeDragged, &flags::force_ped_to_be_dragged);
        push_f("Prevent Ped From Reacting To Being Jacked", ePedConfigFlags::CPED_CONFIG_FLAG_PreventPedFromReactingToBeingJacked, &flags::prevent_ped_from_reacting_to_being_jacked);
        push_f("Is Scuba", ePedConfigFlags::CPED_CONFIG_FLAG_IsScuba, &flags::is_scuba);
        push_f("Will Arrest Rather Than Jack", ePedConfigFlags::CPED_CONFIG_FLAG_WillArrestRatherThanJack, &flags::will_arrest_rather_than_jack);
        push_f("Remove Dead Extra Far Away", ePedConfigFlags::CPED_CONFIG_FLAG_RemoveDeadExtraFarAway, &flags::remove_dead_extra_far_away);
        push_f("Riding Train", ePedConfigFlags::CPED_CONFIG_FLAG_RidingTrain, &flags::riding_train);
        push_f("Arrest Result", ePedConfigFlags::CPED_CONFIG_FLAG_ArrestResult, &flags::arrest_result);
        push_f("Can Attack Friendly", ePedConfigFlags::CPED_CONFIG_FLAG_CanAttackFriendly, &flags::can_attack_friendly);
        push_f("Will Jack Any Player", ePedConfigFlags::CPED_CONFIG_FLAG_WillJackAnyPlayer, &flags::will_jack_any_player);
        push_f("Bumped By Player Vehicle", ePedConfigFlags::CPED_CONFIG_FLAG_BumpedByPlayerVehicle, &flags::bumped_by_player_vehicle);
        push_f("Dodged Player Vehicle", ePedConfigFlags::CPED_CONFIG_FLAG_DodgedPlayerVehicle, &flags::dodged_player_vehicle);
        push_f("Will Jack Wanted Players Rather Than Steal Car", ePedConfigFlags::CPED_CONFIG_FLAG_WillJackWantedPlayersRatherThanStealCar, &flags::will_jack_wanted_players_rather_than_steal_car);
        push_f("No Cop Wanted Aggro", ePedConfigFlags::CPED_CONFIG_FLAG_NoCopWantedAggro, &flags::no_cop_wanted_aggro);
        push_f("Disable Ladder Climbing", ePedConfigFlags::CPED_CONFIG_FLAG_DisableLadderClimbing, &flags::disable_ladder_climbing);
        push_f("Stairs Detected", ePedConfigFlags::CPED_CONFIG_FLAG_StairsDetected, &flags::stairs_detected);
        push_f("Slope Detected", ePedConfigFlags::CPED_CONFIG_FLAG_SlopeDetected, &flags::slope_detected);
        push_f("Helmet Has Been Shot", ePedConfigFlags::CPED_CONFIG_FLAG_HelmetHasBeenShot, &flags::helmet_has_been_shot);
        push_f("Cower Instead Of Flee", ePedConfigFlags::CPED_CONFIG_FLAG_CowerInsteadOfFlee, &flags::cower_instead_of_flee);
        push_f("Can Activate Ragdoll When Vehicle Upside Down", ePedConfigFlags::CPED_CONFIG_FLAG_CanActivateRagdollWhenVehicleUpsideDown, &flags::can_activate_ragdoll_when_vehicle_upside_down);
        push_f("Always Respond To Cries For Help", ePedConfigFlags::CPED_CONFIG_FLAG_AlwaysRespondToCriesForHelp, &flags::always_respond_to_cries_for_help);
        push_f("Disable Blood Pool Creation", ePedConfigFlags::CPED_CONFIG_FLAG_DisableBloodPoolCreation, &flags::disable_blood_pool_creation);
        push_f("Should Fix If No Collision", ePedConfigFlags::CPED_CONFIG_FLAG_ShouldFixIfNoCollision, &flags::should_fix_if_no_collision);
        push_f("Can Perform Arrest", ePedConfigFlags::CPED_CONFIG_FLAG_CanPerformArrest, &flags::can_perform_arrest);
        push_f("Can Perform Uncuff", ePedConfigFlags::CPED_CONFIG_FLAG_CanPerformUncuff, &flags::can_perform_uncuff);
        push_f("Can Be Arrested", ePedConfigFlags::CPED_CONFIG_FLAG_CanBeArrested, &flags::can_be_arrested);
        push_f("Mover Constricted By Opposing Collisions", ePedConfigFlags::CPED_CONFIG_FLAG_MoverConstrictedByOpposingCollisions, &flags::mover_constricted_by_opposing_collisions);
        push_f("Player Prefer Front Seat MP", ePedConfigFlags::CPED_CONFIG_FLAG_PlayerPreferFrontSeatMP, &flags::player_prefer_front_seat_mp);
        push_f("Don't Activate Ragdoll From Impact Object", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromImpactObject, &flags::dont_activate_ragdoll_from_impact_object);
        push_f("Don't Activate Ragdoll From Melee", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromMelee, &flags::dont_activate_ragdoll_from_melee);
        push_f("Don't Activate Ragdoll From Water Jet", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromWaterJet, &flags::dont_activate_ragdoll_from_water_jet);
        push_f("Don't Activate Ragdoll From Drowning", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromDrowning, &flags::dont_activate_ragdoll_from_drowning);
        push_f("Don't Activate Ragdoll From Falling", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromFalling, &flags::dont_activate_ragdoll_from_falling);
        push_f("Don't Activate Ragdoll From Rubber Bullet", ePedConfigFlags::CPED_CONFIG_FLAG_DontActivateRagdollFromRubberBullet, &flags::dont_activate_ragdoll_from_rubber_bullet);
        push_f("Is Injured", ePedConfigFlags::CPED_CONFIG_FLAG_IsInjured, &flags::is_injured);
        push_f("Dont Enter Vehicles In Players Group", CPED_CONFIG_FLAG_DontEnterVehiclesInPlayersGroup, &flags::dont_enter_vehicles_in_players_group);
        push_f("Swimming Tasks Running", CPED_CONFIG_FLAG_SwimmingTasksRunning, &flags::swimming_tasks_running);
        push_f("Prevent All Melee Taunts", CPED_CONFIG_FLAG_PreventAllMeleeTaunts, &flags::prevent_all_melee_taunts);
        push_f("Force Direct Entry", CPED_CONFIG_FLAG_ForceDirectEntry, &flags::force_direct_entry);
        push_f("Always See Approaching Vehicles", CPED_CONFIG_FLAG_AlwaysSeeApproachingVehicles, &flags::always_see_approaching_vehicles);
        push_f("Can Dive Away From Approaching Vehicles", CPED_CONFIG_FLAG_CanDiveAwayFromApproachingVehicles, &flags::can_dive_away_from_approaching_vehicles);
        push_f("Allow Player To Interrupt Vehicle Entry Exit", CPED_CONFIG_FLAG_AllowPlayerToInterruptVehicleEntryExit, &flags::allow_player_to_interrupt_vehicle_entry_exit);
        push_f("Only Attack Law If Player Is Wanted", CPED_CONFIG_FLAG_OnlyAttackLawIfPlayerIsWanted, &flags::only_attack_law_if_player_is_wanted);
        push_f("Player In Contact With Kinematic Ped", CPED_CONFIG_FLAG_PlayerInContactWithKinematicPed, &flags::player_in_contact_with_kinematic_ped); push_f("Player In Contact With Kinematic Ped", CPED_CONFIG_FLAG_PlayerInContactWithKinematicPed, &flags::player_in_contact_with_kinematic_ped);
        push_f("Player In Contact With Something Other Than Kinematic Ped", CPED_CONFIG_FLAG_PlayerInContactWithSomethingOtherThanKinematicPed, &flags::player_in_contact_with_something_other_than_kinematic_ped);
        push_f("Peds Jacking Me Don't Get In", CPED_CONFIG_FLAG_PedsJackingMeDontGetIn, &flags::peds_jacking_me_dont_get_in);
        push_f("Additional Rappelling Ped", CPED_CONFIG_FLAG_AdditionalRappellingPed, &flags::additional_rappelling_ped);
        push_f("Ped Ignores Anim Interrupt Events", CPED_CONFIG_FLAG_PedIgnoresAnimInterruptEvents, &flags::ped_ignores_anim_interrupt_events);
        push_f("Is In Custody", CPED_CONFIG_FLAG_IsInCustody, &flags::is_in_custody);
        push_f("Force Standard Bump Reaction Thresholds", CPED_CONFIG_FLAG_ForceStandardBumpReactionThresholds, &flags::force_standard_bump_reaction_thresholds);
        push_f("Law Will Only Attack If Player Is Wanted", CPED_CONFIG_FLAG_LawWillOnlyAttackIfPlayerIsWanted, &flags::law_will_only_attack_if_player_is_wanted);
        push_f("Is Agitated", CPED_CONFIG_FLAG_IsAgitated, &flags::is_agitated);
        push_f("Prevent Auto Shuffle To Driver's Seat", CPED_CONFIG_FLAG_PreventAutoShuffleToDriversSeat, &flags::prevent_auto_shuffle_to_drivers_seat);
        push_f("Use Kinematic Mode When Stationary", CPED_CONFIG_FLAG_UseKinematicModeWhenStationary, &flags::use_kinematic_mode_when_stationary);
        push_f("Enable Weapon Blocking", CPED_CONFIG_FLAG_EnableWeaponBlocking, &flags::enable_weapon_blocking);
        push_f("Has Hurt Started", CPED_CONFIG_FLAG_HasHurtStarted, &flags::has_hurt_started);
        push_f("Disable Hurt", CPED_CONFIG_FLAG_DisableHurt, &flags::disable_hurt);
        push_f("Player Is Weird", CPED_CONFIG_FLAG_PlayerIsWeird, &flags::player_is_weird);
        push_f("Ped Had Phone Conversation", CPED_CONFIG_FLAG_PedHadPhoneConversation, &flags::ped_had_phone_conversation);
        push_f("Began Crossing Road", CPED_CONFIG_FLAG_BeganCrossingRoad, &flags::began_crossing_road);
        push_f("Warp Into Leader's Vehicle", CPED_CONFIG_FLAG_WarpIntoLeadersVehicle, &flags::warp_into_leaders_vehicle);
        push_f("Do Nothing When On Foot By Default", CPED_CONFIG_FLAG_DoNothingWhenOnFootByDefault, &flags::do_nothing_when_on_foot_by_default);
        push_f("Using Scenario", CPED_CONFIG_FLAG_UsingScenario, &flags::using_scenario);
        push_f("Visible On Screen", CPED_CONFIG_FLAG_VisibleOnScreen, &flags::visible_on_screen);
        push_f("Don't Collide With Kinematic", CPED_CONFIG_FLAG_DontCollideWithKinematic, &flags::dont_collide_with_kinematic);
        push_f("Activate On Switch From Low Physics LOD", CPED_CONFIG_FLAG_ActivateOnSwitchFromLowPhysicsLod, &flags::activate_on_switch_from_low_physics_lod);
        push_f("Don't Activate Ragdoll On Ped Collision When Dead", CPED_CONFIG_FLAG_DontActivateRagdollOnPedCollisionWhenDead, &flags::dont_activate_ragdoll_on_ped_collision_when_dead);
        push_f("Don't Activate Ragdoll On Vehicle Collision When Dead", CPED_CONFIG_FLAG_DontActivateRagdollOnVehicleCollisionWhenDead, &flags::dont_activate_ragdoll_on_vehicle_collision_when_dead);
        push_f("Has Been In Armed Combat", CPED_CONFIG_FLAG_HasBeenInArmedCombat, &flags::has_been_in_armed_combat);
        push_f("Use Diminishing Ammo Rate", CPED_CONFIG_FLAG_UseDiminishingAmmoRate, &flags::use_diminishing_ammo_rate);
        push_f("Avoidance Ignore All", CPED_CONFIG_FLAG_Avoidance_Ignore_All, &flags::avoidance_ignore_all);
        push_f("Avoidance Ignored by All", CPED_CONFIG_FLAG_Avoidance_Ignored_by_All, &flags::avoidance_ignored_by_all);
        push_f("Avoidance Ignore Group1", CPED_CONFIG_FLAG_Avoidance_Ignore_Group1, &flags::avoidance_ignore_group1);
        push_f("Avoidance Member of Group1", CPED_CONFIG_FLAG_Avoidance_Member_of_Group1, &flags::avoidance_member_of_group1);
        push_f("Forced To Use Specific Group Seat Index", CPED_CONFIG_FLAG_ForcedToUseSpecificGroupSeatIndex, &flags::forced_to_use_specific_group_seat_index);
        push_f("Low Physics LOD May Place On Nav Mesh", CPED_CONFIG_FLAG_LowPhysicsLodMayPlaceOnNavMesh, &flags::low_physics_lod_may_place_on_nav_mesh);
        push_f("Disable Explosion Reactions", CPED_CONFIG_FLAG_DisableExplosionReactions, &flags::disable_explosion_reactions);
        push_f("Dodged Player", CPED_CONFIG_FLAG_DodgedPlayer, &flags::dodged_player);
        push_f("Waiting For Player Control Interrupt", CPED_CONFIG_FLAG_WaitingForPlayerControlInterrupt, &flags::waiting_for_player_control_interrupt);
        push_f("Forced To Stay In Cover", CPED_CONFIG_FLAG_ForcedToStayInCover, &flags::forced_to_stay_in_cover);
        push_f("Generates Sound Events", CPED_CONFIG_FLAG_GeneratesSoundEvents, &flags::generates_sound_events);
        push_f("Listens To Sound Events", CPED_CONFIG_FLAG_ListensToSoundEvents, &flags::listens_to_sound_events);
        push_f("Allow To Be Targeted In A Vehicle", CPED_CONFIG_FLAG_AllowToBeTargetedInAVehicle, &flags::allow_to_be_targeted_in_a_vehicle);
        push_f("Wait For Direct Entry Point To Be Free When Exiting", CPED_CONFIG_FLAG_WaitForDirectEntryPointToBeFreeWhenExiting, &flags::wait_for_direct_entry_point_to_be_free_when_exiting);
        push_f("Only Require One Press To Exit Vehicle", CPED_CONFIG_FLAG_OnlyRequireOnePressToExitVehicle, &flags::only_require_one_press_to_exit_vehicle);
        push_f("Force Exit To SkyDive", CPED_CONFIG_FLAG_ForceExitToSkyDive, &flags::force_exit_to_skydive);
        push_f("Steers Around Vehicles", CPED_CONFIG_FLAG_SteersAroundVehicles, &flags::steers_around_vehicles);
        push_f("Allow Ped In Vehicles Override Task Flags", CPED_CONFIG_FLAG_AllowPedInVehiclesOverrideTaskFlags, &flags::allow_ped_in_vehicles_override_task_flags);
        push_f("Don't Enter Leader's Vehicle", CPED_CONFIG_FLAG_DontEnterLeadersVehicle, &flags::dont_enter_leaders_vehicle);
        push_f("Disable Exit To SkyDive", CPED_CONFIG_FLAG_DisableExitToSkyDive, &flags::disable_exit_to_skydive);
        push_f("Script Has Disabled Collision", CPED_CONFIG_FLAG_ScriptHasDisabledCollision, &flags::script_has_disabled_collision);
        push_f("Use Ambient Model Scaling", CPED_CONFIG_FLAG_UseAmbientModelScaling, &flags::use_ambient_model_scaling);
        push_f("Don't Watch First On Next HurryAway", CPED_CONFIG_FLAG_DontWatchFirstOnNextHurryAway, &flags::dont_watch_first_on_next_hurry_away);
        push_f("Disable Potential To Be Walked Into Response", CPED_CONFIG_FLAG_DisablePotentialToBeWalkedIntoResponse, &flags::disable_potential_to_be_walked_into_response);
        push_f("Disable Ped Avoidance", CPED_CONFIG_FLAG_DisablePedAvoidance, &flags::disable_ped_avoidance);
        push_f("Force Ragdoll Upon Death", CPED_CONFIG_FLAG_ForceRagdollUponDeath, &flags::force_ragdoll_upon_death);
        push_f("Can Lose Props On Damage", CPED_CONFIG_FLAG_CanLosePropsOnDamage, &flags::can_lose_props_on_damage);
        push_f("Disable Panic In Vehicle", CPED_CONFIG_FLAG_DisablePanicInVehicle, &flags::disable_panic_in_vehicle);
        push_f("Allowed To Detach Trailer", CPED_CONFIG_FLAG_AllowedToDetachTrailer, &flags::allowed_to_detach_trailer);
        push_f("Has Shot Been Reacted To From Front", CPED_CONFIG_FLAG_HasShotBeenReactedToFromFront, &flags::has_shot_been_reacted_to_from_front);
        push_f("Has Shot Been Reacted To From Back", CPED_CONFIG_FLAG_HasShotBeenReactedToFromBack, &flags::has_shot_been_reacted_to_from_back);
        push_f("Has Shot Been Reacted To From Left", CPED_CONFIG_FLAG_HasShotBeenReactedToFromLeft, &flags::has_shot_been_reacted_to_from_left);
        push_f("Has Shot Been Reacted To From Right", CPED_CONFIG_FLAG_HasShotBeenReactedToFromRight, &flags::has_shot_been_reacted_to_from_right);
        push_f("Allow Block Dead Ped Ragdoll Activation", CPED_CONFIG_FLAG_AllowBlockDeadPedRagdollActivation, &flags::allow_block_dead_ped_ragdoll_activation);
        push_f("Is Holding Prop", CPED_CONFIG_FLAG_IsHoldingProp, &flags::is_holding_prop);
        push_f("Blocks Pathing When Dead", CPED_CONFIG_FLAG_BlocksPathingWhenDead, &flags::blocks_pathing_when_dead);
        push_f("Force Play Normal Scenario Exit On Next Script Command", CPED_CONFIG_FLAG_ForcePlayNormalScenarioExitOnNextScriptCommand, &flags::force_play_normal_scenario_exit_on_next_script_command);
        push_f("Force Play Immediate Scenario Exit On Next Script Command", CPED_CONFIG_FLAG_ForcePlayImmediateScenarioExitOnNextScriptCommand, &flags::force_play_immediate_scenario_exit_on_next_script_command);
        push_f("Force Skin Character Cloth", CPED_CONFIG_FLAG_ForceSkinCharacterCloth, &flags::force_skin_character_cloth);
        push_f("Leave Engine On When Exiting Vehicles", CPED_CONFIG_FLAG_LeaveEngineOnWhenExitingVehicles, &flags::leave_engine_on_when_exiting_vehicles);
        push_f("Phone Disable Texting Animations", CPED_CONFIG_FLAG_PhoneDisableTextingAnimations, &flags::phone_disable_texting_animations);
        push_f("Phone Disable Talking Animations", CPED_CONFIG_FLAG_PhoneDisableTalkingAnimations, &flags::phone_disable_talking_animations);
        push_f("Phone Disable Camera Animations", CPED_CONFIG_FLAG_PhoneDisableCameraAnimations, &flags::phone_disable_camera_animations);
        push_f("Disable Blind Firing In Shot Reactions", CPED_CONFIG_FLAG_DisableBlindFiringInShotReactions, &flags::disable_blind_firing_in_shot_reactions);
        push_f("Allow Nearby Cover Usage", CPED_CONFIG_FLAG_AllowNearbyCoverUsage, &flags::allow_nearby_cover_usage);
        push_f("In Strafe Transition", CPED_CONFIG_FLAG_InStrafeTransition, &flags::in_strafe_transition);
        push_f("Can Play In Car Idles", CPED_CONFIG_FLAG_CanPlayInCarIdles, &flags::can_play_in_car_idles);
        push_f("Can Attack Non-Wanted Player As Law", CPED_CONFIG_FLAG_CanAttackNonWantedPlayerAsLaw, &flags::can_attack_non_wanted_player_as_law);
        push_f("Will Take Damage When Vehicle Crashes", CPED_CONFIG_FLAG_WillTakeDamageWhenVehicleCrashes, &flags::will_take_damage_when_vehicle_crashes);
        push_f("AI Driver Allow Friendly Passenger Seat Entry", CPED_CONFIG_FLAG_AIDriverAllowFriendlyPassengerSeatEntry, &flags::ai_driver_allow_friendly_passenger_seat_entry);
        push_f("Player Can Jack Friendly Players", CPED_CONFIG_FLAG_PlayerCanJackFriendlyPlayers, &flags::player_can_jack_friendly_players);
        push_f("On Stairs", CPED_CONFIG_FLAG_OnStairs, &flags::on_stairs);
        push_f("Simulating Aiming", CPED_CONFIG_FLAG_SimulatingAiming, &flags::simulating_aiming);
        push_f("AI Can Drive Player As Rear Passenger", CPED_CONFIG_FLAG_AICanDrivePlayerAsRearPassenger, &flags::ai_can_drive_player_as_rear_passenger);
        push_f("Parent Car Is Being Removed", CPED_CONFIG_FLAG_ParentCarIsBeingRemoved, &flags::parent_car_is_being_removed);
        push_f("Allow Mission Ped To Use Injured Movement", CPED_CONFIG_FLAG_AllowMissionPedToUseInjuredMovement, &flags::allow_mission_ped_to_use_injured_movement);
        push_f("Can Lose Helmet On Damage", CPED_CONFIG_FLAG_CanLoseHelmetOnDamage, &flags::can_lose_helmet_on_damage);
        push_f("Never Do Scenario Exit Probe Checks", CPED_CONFIG_FLAG_NeverDoScenarioExitProbeChecks, &flags::never_do_scenario_exit_probe_checks);
        push_f("Suppress Low LOD Ragdoll Switch When Corpse Settles", CPED_CONFIG_FLAG_SuppressLowLODRagdollSwitchWhenCorpseSettles, &flags::suppress_low_lod_ragdoll_switch_when_corpse_settles);
        push_f("Prevent Using Lower Priority Seats", CPED_CONFIG_FLAG_PreventUsingLowerPrioritySeats, &flags::prevent_using_lower_priority_seats);
        push_f("Just Left Vehicle Needs Reset", CPED_CONFIG_FLAG_JustLeftVehicleNeedsReset, &flags::just_left_vehicle_needs_reset);
        push_f("Teleport If Can't Reach Player", CPED_CONFIG_FLAG_TeleportIfCantReachPlayer, &flags::teleport_if_cant_reach_player);
        push_f("Peds In Vehicle Position Needs Reset", CPED_CONFIG_FLAG_PedsInVehiclePositionNeedsReset, &flags::peds_in_vehicle_position_needs_reset);
        push_f("Peds Fully In Seat", CPED_CONFIG_FLAG_PedsFullyInSeat, &flags::peds_fully_in_seat);
        push_f("Allow Player Lock-On If Friendly", CPED_CONFIG_FLAG_AllowPlayerLockOnIfFriendly, &flags::allow_player_lock_on_if_friendly);
        push_f("Use Camera Heading For Desired Direction Lock-On Test", CPED_CONFIG_FLAG_UseCameraHeadingForDesiredDirectionLockOnTest, &flags::use_camera_heading_for_desired_direction_lock_on_test);
        push_f("Teleport To Leader Vehicle", CPED_CONFIG_FLAG_TeleportToLeaderVehicle, &flags::teleport_to_leader_vehicle);
        push_f("Avoidance Ignore Weird Ped Buffer", CPED_CONFIG_FLAG_Avoidance_Ignore_WeirdPedBuffer, &flags::avoidance_ignore_weird_ped_buffer);
        push_f("On Stair Slope", CPED_CONFIG_FLAG_OnStairSlope, &flags::on_stair_slope);
        push_f("Has Played NM Getup", CPED_CONFIG_FLAG_HasPlayedNMGetup, &flags::has_played_nm_getup);
        push_f("Don't Blip Cop", CPED_CONFIG_FLAG_DontBlipCop, &flags::dont_blip_cop);
        push_f("Spawned At Extended Range Scenario", CPED_CONFIG_FLAG_SpawnedAtExtendedRangeScenario, &flags::spawned_at_extended_range_scenario);
        push_f("Walk Alongside Leader When Close", CPED_CONFIG_FLAG_WalkAlongsideLeaderWhenClose, &flags::walk_alongside_leader_when_close);
        push_f("Kill When Trapped", CPED_CONFIG_FLAG_KillWhenTrapped, &flags::kill_when_trapped);
        push_f("Edge Detected", CPED_CONFIG_FLAG_EdgeDetected, &flags::edge_detected);
        push_f("Always Wake Up Physics Of Intersected Peds", CPED_CONFIG_FLAG_AlwaysWakeUpPhysicsOfIntersectedPeds, &flags::always_wake_up_physics_of_intersected_peds);
        push_f("Equipped Ambient LoadOut Weapon", CPED_CONFIG_FLAG_EquippedAmbientLoadOutWeapon, &flags::equipped_ambient_load_out_weapon);
        push_f("Avoid Tear Gas", CPED_CONFIG_FLAG_AvoidTearGas, &flags::avoid_tear_gas);
        push_f("Stopped Speech Upon Freezing", CPED_CONFIG_FLAG_StoppedSpeechUponFreezing, &flags::stopped_speech_upon_freezing);
        push_f("Disable GoToWrithe When Injured", CPED_CONFIG_FLAG_DisableGoToWritheWhenInjured, &flags::disable_goto_writhe_when_injured);
        push_f("Only Use Forced Seat When Entering Heli In Group", CPED_CONFIG_FLAG_OnlyUseForcedSeatWhenEnteringHeliInGroup, &flags::only_use_forced_seat_when_entering_heli_in_group);
        push_f("Thrown From Vehicle Due To Exhaustion", CPED_CONFIG_FLAG_ThrownFromVehicleDueToExhaustion, &flags::thrown_from_vehicle_due_to_exhaustion);
        push_f("Update Enclosed Search Region", CPED_CONFIG_FLAG_UpdateEnclosedSearchRegion, &flags::update_enclosed_search_region);
        push_f("Disable Weird Ped Events", CPED_CONFIG_FLAG_DisableWeirdPedEvents, &flags::disable_weird_ped_events);
        push_f("Should Charge Now", CPED_CONFIG_FLAG_ShouldChargeNow, &flags::should_charge_now);
        push_f("Ragdolling On Boat", CPED_CONFIG_FLAG_RagdollingOnBoat, &flags::ragdolling_on_boat);
        push_f("Has Brandished Weapon", CPED_CONFIG_FLAG_HasBrandishedWeapon, &flags::has_brandished_weapon);
        push_f("Allow Minor Reactions As Mission Ped", CPED_CONFIG_FLAG_AllowMinorReactionsAsMissionPed, &flags::allow_minor_reactions_as_mission_ped);
        push_f("Block Dead Body Shocking Events When Dead", CPED_CONFIG_FLAG_BlockDeadBodyShockingEventsWhenDead, &flags::block_dead_body_shocking_events_when_dead);
        push_f("Ped Has Been Seen", CPED_CONFIG_FLAG_PedHasBeenSeen, &flags::ped_has_been_seen);
        push_f("Ped Is In Reuse Pool", CPED_CONFIG_FLAG_PedIsInReusePool, &flags::ped_is_in_reuse_pool);
        push_f("Ped Was Reused", CPED_CONFIG_FLAG_PedWasReused, &flags::ped_was_reused);
        push_f("Disable Shocking Events", CPED_CONFIG_FLAG_DisableShockingEvents, &flags::disable_shocking_events);
        push_f("Moved Using Low LOD Physics Since Last Active", CPED_CONFIG_FLAG_MovedUsingLowLodPhysicsSinceLastActive, &flags::moved_using_low_lod_physics_since_last_active);
        push_f("Never React To Ped On Roof", CPED_CONFIG_FLAG_NeverReactToPedOnRoof, &flags::never_react_to_ped_on_roof);
        push_f("Force Play Flee Scenario Exit On Next Script Command", CPED_CONFIG_FLAG_ForcePlayFleeScenarioExitOnNextScriptCommand, &flags::force_play_flee_scenario_exit_on_next_script_command);
        push_f("Just Bumped Into Vehicle", CPED_CONFIG_FLAG_JustBumpedIntoVehicle, &flags::just_bumped_into_vehicle);
        push_f("Disable Shocking Driving On Pavement Events", CPED_CONFIG_FLAG_DisableShockingDrivingOnPavementEvents, &flags::disable_shocking_driving_on_pavement_events);
        push_f("Should Throw Smoke Now", CPED_CONFIG_FLAG_ShouldThrowSmokeNow, &flags::should_throw_smoke_now);
        push_f("Disable Ped Constraints", CPED_CONFIG_FLAG_DisablePedConstraints, &flags::disable_ped_constraints);
        push_f("Force Initial Peek In Cover", CPED_CONFIG_FLAG_ForceInitialPeekInCover, &flags::force_initial_peek_in_cover);
        push_f("Created By Dispatch", CPED_CONFIG_FLAG_CreatedByDispatch, &flags::created_by_dispatch);
        push_f("Point Gun Left Hand Supporting", CPED_CONFIG_FLAG_PointGunLeftHandSupporting, &flags::point_gun_left_hand_supporting);
        push_f("Disable Jumping From Vehicles After Leader", CPED_CONFIG_FLAG_DisableJumpingFromVehiclesAfterLeader, &flags::disable_jumping_from_vehicles_after_leader);
        push_f("Dont Activate Ragdoll From Player Ped Impact", CPED_CONFIG_FLAG_DontActivateRagdollFromPlayerPedImpact, &flags::dont_activate_ragdoll_from_player_ped_impact);
        push_f("Dont Activate Ragdoll From Ai Ragdoll Impact", CPED_CONFIG_FLAG_DontActivateRagdollFromAiRagdollImpact, &flags::dont_activate_ragdoll_from_ai_ragdoll_impact);
        push_f("Dont Activate Ragdoll From Player Ragdoll Impact", CPED_CONFIG_FLAG_DontActivateRagdollFromPlayerRagdollImpact, &flags::dont_activate_ragdoll_from_player_ragdoll_impact);
        push_f("Disable Quadruped Spring", CPED_CONFIG_FLAG_DisableQuadrupedSpring, &flags::disable_quadruped_spring);
        push_f("Is In Cluster", CPED_CONFIG_FLAG_IsInCluster, &flags::is_in_cluster);
        push_f("Shout To Group On Player Melee", CPED_CONFIG_FLAG_ShoutToGroupOnPlayerMelee, &flags::shout_to_group_on_player_melee);
        push_f("Ignored By Auto Open Doors", CPED_CONFIG_FLAG_IgnoredByAutoOpenDoors, &flags::ignored_by_auto_open_doors);
        push_f("Prefer Injured Getup", CPED_CONFIG_FLAG_PreferInjuredGetup, &flags::prefer_injured_getup);
        push_f("Force Ignore Melee Active Combatant", CPED_CONFIG_FLAG_ForceIgnoreMeleeActiveCombatant, &flags::force_ignore_melee_active_combatant);
        push_f("Check LoS For Sound Events", CPED_CONFIG_FLAG_CheckLoSForSoundEvents, &flags::check_los_for_sound_events);
        push_f("Jacked Abandoned Car", CPED_CONFIG_FLAG_JackedAbandonedCar, &flags::jacked_abandoned_car);
        push_f("Can Say Followed By Player Audio", CPED_CONFIG_FLAG_CanSayFollowedByPlayerAudio, &flags::can_say_followed_by_player_audio);
        push_f("Activate Ragdoll From Minor Player Contact", CPED_CONFIG_FLAG_ActivateRagdollFromMinorPlayerContact, &flags::activate_ragdoll_from_minor_player_contact);
        push_f("Has Portable Pickup Attached", CPED_CONFIG_FLAG_HasPortablePickupAttached, &flags::has_portable_pickup_attached);
        push_f("Force Pose Character Cloth", CPED_CONFIG_FLAG_ForcePoseCharacterCloth, &flags::force_pose_character_cloth);
        push_f("Has Cloth Collision Bounds", CPED_CONFIG_FLAG_HasClothCollisionBounds, &flags::has_cloth_collision_bounds);
        push_f("Has High Heels", CPED_CONFIG_FLAG_HasHighHeels, &flags::has_high_heels);
        push_f("Treat As Ambient Ped For Driver Lock-On", CPED_CONFIG_FLAG_TreatAsAmbientPedForDriverLockOn, &flags::treat_as_ambient_ped_for_driver_lock_on);
        push_f("Don't Behave Like Law", CPED_CONFIG_FLAG_DontBehaveLikeLaw, &flags::dont_behave_like_law);
        push_f("Spawned At Scenario", CPED_CONFIG_FLAG_SpawnedAtScenario, &flags::spawned_at_scenario);
        push_f("Disable Police Investigating Body", CPED_CONFIG_FLAG_DisablePoliceInvestigatingBody, &flags::disable_police_investigating_body);
        push_f("Disable Writhe Shoot From Ground", CPED_CONFIG_FLAG_DisableWritheShootFromGround, &flags::disable_writhe_shoot_from_ground);
        push_f("Lower Priority Of Warp Seats", CPED_CONFIG_FLAG_LowerPriorityOfWarpSeats, &flags::lower_priority_of_warp_seats);
        push_f("Disable Talk To", CPED_CONFIG_FLAG_DisableTalkTo, &flags::disable_talk_to);
        push_f("Dont Blip", CPED_CONFIG_FLAG_DontBlip, &flags::dont_blip);
        push_f("Is Switching Weapon", CPED_CONFIG_FLAG_IsSwitchingWeapon, &flags::is_switching_weapon);
        push_f("Ignore Leg IK Restrictions", CPED_CONFIG_FLAG_IgnoreLegIkRestrictions, &flags::ignore_leg_ik_restrictions);
        push_f("Script Force No Timeslice Intelligence Update", CPED_CONFIG_FLAG_ScriptForceNoTimesliceIntelligenceUpdate, &flags::script_force_no_timeslice_intelligence_update);
        push_f("Jacked Out Of My Vehicle", CPED_CONFIG_FLAG_JackedOutOfMyVehicle, &flags::jacked_out_of_my_vehicle);
        push_f("Went Into Combat After Being Jacked", CPED_CONFIG_FLAG_WentIntoCombatAfterBeingJacked, &flags::went_into_combat_after_being_jacked);
        push_f("Dont Activate Ragdoll For Vehicle Grab", CPED_CONFIG_FLAG_DontActivateRagdollForVehicleGrab, &flags::dont_activate_ragdoll_for_vehicle_grab);
        push_f("Force Package Character Cloth", CPED_CONFIG_FLAG_ForcePackageCharacterCloth, &flags::force_package_character_cloth);
        push_f("Dont Remove With Valid Order", CPED_CONFIG_FLAG_DontRemoveWithValidOrder, &flags::dont_remove_with_valid_order);
        push_f("Allow Task Do Nothing Timeslicing", CPED_CONFIG_FLAG_AllowTaskDoNothingTimeslicing, &flags::allow_task_do_nothing_timeslicing);
        push_f("Forced To Stay In Cover Due To Player Switch", CPED_CONFIG_FLAG_ForcedToStayInCoverDueToPlayerSwitch, &flags::forced_to_stay_in_cover_due_to_player_switch);
        push_f("Force Prone Character Cloth", CPED_CONFIG_FLAG_ForceProneCharacterCloth, &flags::force_prone_character_cloth);
        push_f("Not Allowed To Jack Any Players", CPED_CONFIG_FLAG_NotAllowedToJackAnyPlayers, &flags::not_allowed_to_jack_any_players);
        push_f("In To Strafe Transition", CPED_CONFIG_FLAG_InToStrafeTransition, &flags::in_to_strafe_transition);
        push_f("Killed By Standard Melee", CPED_CONFIG_FLAG_KilledByStandardMelee, &flags::killed_by_standard_melee);
        push_f("Always Leave Train Upon Arrival", CPED_CONFIG_FLAG_AlwaysLeaveTrainUponArrival, &flags::always_leave_train_upon_arrival);
        push_f("Force Play Directed Normal Scenario Exit On Next Script Command", CPED_CONFIG_FLAG_ForcePlayDirectedNormalScenarioExitOnNextScriptCommand, &flags::force_play_directed_normal_scenario_exit_on_next_script_command);
        push_f("Only Writhe From Weapon Damage", CPED_CONFIG_FLAG_OnlyWritheFromWeaponDamage, &flags::only_writhe_from_weapon_damage);
        push_f("Use Slo-Mo Blood VFX", CPED_CONFIG_FLAG_UseSloMoBloodVfx, &flags::use_slo_mo_blood_vfx);
        push_f("Equip Jetpack", CPED_CONFIG_FLAG_EquipJetpack, &flags::equip_jetpack);
        push_f("Prevent Dragged Out Of Car Threat Response", CPED_CONFIG_FLAG_PreventDraggedOutOfCarThreatResponse, &flags::prevent_dragged_out_of_car_threat_response);
        push_f("Script Has Completely Disabled Collision", CPED_CONFIG_FLAG_ScriptHasCompletelyDisabledCollision, &flags::script_has_completely_disabled_collision);
        push_f("Never Do Scenario Nav Checks", CPED_CONFIG_FLAG_NeverDoScenarioNavChecks, &flags::never_do_scenario_nav_checks);
        push_f("Force Synchronous Scenario Exit Checking", CPED_CONFIG_FLAG_ForceSynchronousScenarioExitChecking, &flags::force_synchronous_scenario_exit_checking);
        push_f("Throwing Grenade While Aiming", CPED_CONFIG_FLAG_ThrowingGrenadeWhileAiming, &flags::throwing_grenade_while_aiming);
        push_f("Headbob To Radio Enabled", CPED_CONFIG_FLAG_HeadbobToRadioEnabled, &flags::headbob_to_radio_enabled);
        push_f("Force Deep Surface Check", CPED_CONFIG_FLAG_ForceDeepSurfaceCheck, &flags::force_deep_surface_check);
        push_f("Disable Deep Surface Anims", CPED_CONFIG_FLAG_DisableDeepSurfaceAnims, &flags::disable_deep_surface_anims);
        push_f("Dont Blip Not Synced", CPED_CONFIG_FLAG_DontBlipNotSynced, &flags::dont_blip_not_synced);
        push_f("Is Ducking In Vehicle", CPED_CONFIG_FLAG_IsDuckingInVehicle, &flags::is_ducking_in_vehicle);
        push_f("Prevent Auto Shuffle To Turret Seat", CPED_CONFIG_FLAG_PreventAutoShuffleToTurretSeat, &flags::prevent_auto_shuffle_to_turret_seat);
        push_f("Disable Event Interior Status Check", CPED_CONFIG_FLAG_DisableEventInteriorStatusCheck, &flags::disable_event_interior_status_check);
        push_f("Has Reserve Parachute", CPED_CONFIG_FLAG_HasReserveParachute, &flags::has_reserve_parachute);
        push_f("Use Reserve Parachute", CPED_CONFIG_FLAG_UseReserveParachute, &flags::use_reserve_parachute);
        push_f("Treat Dislike As Hate When In Combat", CPED_CONFIG_FLAG_TreatDislikeAsHateWhenInCombat, &flags::treat_dislike_as_hate_when_in_combat);
        push_f("Only Update Target Wanted If Seen", CPED_CONFIG_FLAG_OnlyUpdateTargetWantedIfSeen, &flags::only_update_target_wanted_if_seen);
        push_f("Allow Auto Shuffle To Driver's Seat", CPED_CONFIG_FLAG_AllowAutoShuffleToDriversSeat, &flags::allow_auto_shuffle_to_drivers_seat);
        push_f("Dont Activate Ragdoll From Smoke Grenade", CPED_CONFIG_FLAG_DontActivateRagdollFromSmokeGrenade, &flags::dont_activate_ragdoll_from_smoke_grenade);
        push_f("Link MBR To Owner On Chain", CPED_CONFIG_FLAG_LinkMBRToOwnerOnChain, &flags::link_mbr_to_owner_on_chain);
        push_f("Ambient Friend Bumped By Player", CPED_CONFIG_FLAG_AmbientFriendBumpedByPlayer, &flags::ambient_friend_bumped_by_player);
        push_f("Ambient Friend Bumped By Player Vehicle", CPED_CONFIG_FLAG_AmbientFriendBumpedByPlayerVehicle, &flags::ambient_friend_bumped_by_player_vehicle);
        push_f("In FPS Unholster Transition", CPED_CONFIG_FLAG_InFPSUnholsterTransition, &flags::in_fps_unholster_transition);
        push_f("Prevent Reacting to Silenced Clone Bullets", CPED_CONFIG_FLAG_PreventReactingToSilencedCloneBullets, &flags::prevent_reacting_to_silenced_clone_bullets);
        push_f("Disable Injured Cry for Help Events", CPED_CONFIG_FLAG_DisableInjuredCryForHelpEvents, &flags::disable_injured_cry_for_help_events);
        push_f("Never Leave Train", CPED_CONFIG_FLAG_NeverLeaveTrain, &flags::never_leave_train);
        push_f("Don't Drop Jetpack On Death", CPED_CONFIG_FLAG_DontDropJetpackOnDeath, &flags::dont_drop_jetpack_on_death);
        push_f("Use FPS Unholster Transition During Combat Roll", CPED_CONFIG_FLAG_UseFPSUnholsterTransitionDuringCombatRoll, &flags::use_fps_unholster_transition_during_combat_roll);
        push_f("Exiting FPS Combat Roll", CPED_CONFIG_FLAG_ExitingFPSCombatRoll, &flags::exiting_fps_combat_roll);
        push_f("Script Has Control of Player", CPED_CONFIG_FLAG_ScriptHasControlOfPlayer, &flags::script_has_control_of_player);
        push_f("Play FPS Idle Fidgets for Projectile", CPED_CONFIG_FLAG_PlayFPSIdleFidgetsForProjectile, &flags::play_fps_idle_fidgets_for_projectile);
        push_f("Disable Auto Equip Helmets in Bikes", CPED_CONFIG_FLAG_DisableAutoEquipHelmetsInBikes, &flags::disable_auto_equip_helmets_in_bikes);
        push_f("Disable Auto Equip Helmets in Aircraft", CPED_CONFIG_FLAG_DisableAutoEquipHelmetsInAircraft, &flags::disable_auto_equip_helmets_in_aircraft);
        push_f("Was Playing FPS Getup", CPED_CONFIG_FLAG_WasPlayingFPSGetup, &flags::was_playing_fps_getup);
        push_f("Was Playing FPS Melee Action Result", CPED_CONFIG_FLAG_WasPlayingFPSMeleeActionResult, &flags::was_playing_fps_melee_action_result);
        push_f("Prefer No Priority Removal", CPED_CONFIG_FLAG_PreferNoPriorityRemoval, &flags::prefer_no_priority_removal);
        push_f("FPS Fidgets Aborted on Fire", CPED_CONFIG_FLAG_FPSFidgetsAbortedOnFire, &flags::fps_fidgets_aborted_on_fire);
        push_f("Force FPS IK with Upper Body Anim", CPED_CONFIG_FLAG_ForceFPSIKWithUpperBodyAnim, &flags::force_fps_ik_with_upper_body_anim);
        push_f("Switching Characters in First Person", CPED_CONFIG_FLAG_SwitchingCharactersInFirstPerson, &flags::switching_characters_in_first_person);
        push_f("Is Climbing Ladder", CPED_CONFIG_FLAG_IsClimbingLadder, &flags::is_climbing_ladder);
        push_f("Has Bare Feet", CPED_CONFIG_FLAG_HasBareFeet, &flags::has_bare_feet);
        push_f("Unused Replace Me 2", CPED_CONFIG_FLAG_UNUSED_REPLACE_ME_2, &flags::unused_replace_me_2);
        push_f("Go On Without Vehicle If Unable to Get Back to Road", CPED_CONFIG_FLAG_GoOnWithoutVehicleIfItIsUnableToGetBackToRoad, &flags::go_on_without_vehicle_if_unable_to_get_back_to_road);
        push_f("Block Dropping Health Snacks on Death", CPED_CONFIG_FLAG_BlockDroppingHealthSnacksOnDeath, &flags::block_dropping_health_snacks_on_death);
        push_f("Reset Last Vehicle on Vehicle Exit", CPED_CONFIG_FLAG_ResetLastVehicleOnVehicleExit, &flags::reset_last_vehicle_on_vehicle_exit);
        push_f("Force Threat Response to Non-Friend to Friend Melee Actions", CPED_CONFIG_FLAG_ForceThreatResponseToNonFriendToFriendMeleeActions, &flags::force_threat_response_to_non_friend_to_friend_melee_actions);
        push_f("Don't Respond to Random Peds Damage", CPED_CONFIG_FLAG_DontRespondToRandomPedsDamage, &flags::dont_respond_to_random_peds_damage);
        push_f("Allow Continuous Threat Response Wanted Level Updates", CPED_CONFIG_FLAG_AllowContinuousThreatResponseWantedLevelUpdates, &flags::allow_continuous_threat_response_wanted_level_updates);
        push_f("Keep Target Loss Response On Cleanup", CPED_CONFIG_FLAG_KeepTargetLossResponseOnCleanup, &flags::keep_target_loss_response_on_cleanup);
        push_f("Players Don't Drag Me Out of Car", CPED_CONFIG_FLAG_PlayersDontDragMeOutOfCar, &flags::players_dont_drag_me_out_of_car);
        push_f("Broadcast Responded to Threat When Going to Point Shooting", CPED_CONFIG_FLAG_BroadcastRepondedToThreatWhenGoingToPointShooting, &flags::broadcast_responded_to_threat_when_going_to_point_shooting);
        push_f("Ignore Ped Type for Is Friendly With", CPED_CONFIG_FLAG_IgnorePedTypeForIsFriendlyWith, &flags::ignore_ped_type_for_is_friendly_with);
        push_f("Treat Non-Friendly as Hate When in Combat", CPED_CONFIG_FLAG_TreatNonFriendlyAsHateWhenInCombat, &flags::treat_non_friendly_as_hate_when_in_combat);
        push_f("Don't Leave Vehicle If Leader Not in Vehicle", CPED_CONFIG_FLAG_DontLeaveVehicleIfLeaderNotInVehicle, &flags::dont_leave_vehicle_if_leader_not_in_vehicle);
        push_f("Change From Permanent to Ambient Pop Type On Migration", CPED_CONFIG_FLAG_ChangeFromPermanentToAmbientPopTypeOnMigration, &flags::change_from_permanent_to_ambient_pop_type_on_migration);
        push_f("Allow Melee Reaction If Melee Proof Is On", CPED_CONFIG_FLAG_AllowMeleeReactionIfMeleeProofIsOn, &flags::allow_melee_reaction_if_melee_proof_is_on);
        push_f("Using Lowrider Leans", CPED_CONFIG_FLAG_UsingLowriderLeans, &flags::using_lowrider_leans);
        push_f("Using Alternate Lowrider Leans", CPED_CONFIG_FLAG_UsingAlternateLowriderLeans, &flags::using_alternate_lowrider_leans);
        push_f("Use Normal Explosion Damage When Blown Up In Vehicle", CPED_CONFIG_FLAG_UseNormalExplosionDamageWhenBlownUpInVehicle, &flags::use_normal_explosion_damage_when_blown_up_in_vehicle);
        push_f("Disable Homing Missile Lock For Vehicle Ped Inside", CPED_CONFIG_FLAG_DisableHomingMissileLockForVehiclePedInside, &flags::disable_homing_missile_lock_for_vehicle_ped_inside);
        push_f("Disable Take Off Scuba Gear", CPED_CONFIG_FLAG_DisableTakeOffScubaGear, &flags::disable_take_off_scuba_gear);
        push_f("Ignore Melee Fist Weapon Damage Mult", CPED_CONFIG_FLAG_IgnoreMeleeFistWeaponDamageMult, &flags::ignore_melee_fist_weapon_damage_mult);
        push_f("Law Peds Can Flee From Non-Wanted Player", CPED_CONFIG_FLAG_LawPedsCanFleeFromNonWantedPlayer, &flags::law_peds_can_flee_from_non_wanted_player);
        push_f("Force Blip Security Peds If Player Is Wanted", CPED_CONFIG_FLAG_ForceBlipSecurityPedsIfPlayerIsWanted, &flags::force_blip_security_peds_if_player_is_wanted);
        push_f("Is Holstering Weapon", CPED_CONFIG_FLAG_IsHolsteringWeapon, &flags::is_holstering_weapon);
        push_f("Use Go To Point For Scenario Navigation", CPED_CONFIG_FLAG_UseGoToPointForScenarioNavigation, &flags::use_go_to_point_for_scenario_navigation);
        push_f("Don't Clear Local Passengers Wanted Level", CPED_CONFIG_FLAG_DontClearLocalPassengersWantedLevel, &flags::dont_clear_local_passengers_wanted_level);
        push_f("Block Auto Swap On Weapon Pickups", CPED_CONFIG_FLAG_BlockAutoSwapOnWeaponPickups, &flags::block_auto_swap_on_weapon_pickups);
        push_f("This Ped Is A Target Priority For AI", CPED_CONFIG_FLAG_ThisPedIsATargetPriorityForAI, &flags::this_ped_is_a_target_priority_for_ai);
        push_f("Is Switching Helmet Visor", CPED_CONFIG_FLAG_IsSwitchingHelmetVisor, &flags::is_switching_helmet_visor);
        push_f("Force Helmet Visor Switch", CPED_CONFIG_FLAG_ForceHelmetVisorSwitch, &flags::force_helmet_visor_switch);
        push_f("Is Performing Vehicle Melee", CPED_CONFIG_FLAG_IsPerformingVehicleMelee, &flags::is_performing_vehicle_melee);
        push_f("Use Override Footstep PtFx", CPED_CONFIG_FLAG_UseOverrideFootstepPtFx, &flags::use_override_footstep_pt_fx);
        push_f("Disable Vehicle Combat", CPED_CONFIG_FLAG_DisableVehicleCombat, &flags::disable_vehicle_combat);
        push_f("Treat As Friendly For Targeting And Damage", CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamage, &flags::treat_as_friendly_for_targeting_and_damage);
        push_f("Allow Bike Alternate Animations", CPED_CONFIG_FLAG_AllowBikeAlternateAnimations, &flags::allow_bike_alternate_animations);
        push_f("Treat As Friendly For Targeting And Damage (Non-Synced)", CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamageNonSynced, &flags::treat_as_friendly_for_targeting_and_damage_non_synced);
        push_f("Use Lockpick Vehicle Entry Animations", CPED_CONFIG_FLAG_UseLockpickVehicleEntryAnimations, &flags::use_lockpick_vehicle_entry_animations);
        push_f("Ignore Interior Check For Sprinting", CPED_CONFIG_FLAG_IgnoreInteriorCheckForSprinting, &flags::ignore_interior_check_for_sprinting);
        push_f("Swat Heli Spawn Within Last Spotted Location", CPED_CONFIG_FLAG_SwatHeliSpawnWithinLastSpottedLocation, &flags::swat_heli_spawn_within_last_spotted_location);
        push_f("Disable Start Engine", CPED_CONFIG_FLAG_DisableStartEngine, &flags::disable_start_engine);
        push_f("Ignore Being On Fire", CPED_CONFIG_FLAG_IgnoreBeingOnFire, &flags::ignore_being_on_fire);
        push_f("Disable Turret Or Rear Seat Preference", CPED_CONFIG_FLAG_DisableTurretOrRearSeatPreference, &flags::disable_turret_or_rear_seat_preference);
        push_f("Disable Wanted Helicopter Spawning", CPED_CONFIG_FLAG_DisableWantedHelicopterSpawning, &flags::disable_wanted_helicopter_spawning);
        push_f("Use Target Perception For Creating Aimed At Events", CPED_CONFIG_FLAG_UseTargetPerceptionForCreatingAimedAtEvents, &flags::use_target_perception_for_creating_aimed_at_events);
        push_f("Disable Homing Missile Lockon", CPED_CONFIG_FLAG_DisableHomingMissileLockon, &flags::disable_homing_missile_lockon);
        push_f("Force Ignore Max Melee Active Support Combatants", CPED_CONFIG_FLAG_ForceIgnoreMaxMeleeActiveSupportCombatants, &flags::force_ignore_max_melee_active_support_combatants);
        push_f("Stay In Defensive Area When In Vehicle", CPED_CONFIG_FLAG_StayInDefensiveAreaWhenInVehicle, &flags::stay_in_defensive_area_when_in_vehicle);
        push_f("Don't Shout Target Position", CPED_CONFIG_FLAG_DontShoutTargetPosition, &flags::dont_shout_target_position);
        push_f("Disable Helmet Armor", CPED_CONFIG_FLAG_DisableHelmetArmor, &flags::disable_helmet_armor);
        push_f("Created By Concealed Player", CPED_CONFIG_FLAG_CreatedByConcealedPlayer, &flags::created_by_concealed_player);
        push_f("Permanently Disable Potential To Be Walked Into Response", CPED_CONFIG_FLAG_PermanentlyDisablePotentialToBeWalkedIntoResponse, &flags::permanently_disable_potential_to_be_walked_into_response);
        push_f("Prevent Vehicle Exit Due To Invalid Weapon", CPED_CONFIG_FLAG_PreventVehExitDueToInvalidWeapon, &flags::prevent_vehicle_exit_due_to_invalid_weapon);
        push_f("Ignore Net Session Friendly Fire Check For Allow Damage", CPED_CONFIG_FLAG_IgnoreNetSessionFriendlyFireCheckForAllowDamage, &flags::ignore_net_session_friendly_fire_check_for_allow_damage);
        push_f("Don't Leave Combat If Target Player Is Attacked By Police", CPED_CONFIG_FLAG_DontLeaveCombatIfTargetPlayerIsAttackedByPolice, &flags::dont_leave_combat_if_target_player_is_attacked_by_police);
        push_f("Check Locked Before Warp", CPED_CONFIG_FLAG_CheckLockedBeforeWarp, &flags::check_locked_before_warp);
        push_f("Don't Shuffle In Vehicle To Make Room", CPED_CONFIG_FLAG_DontShuffleInVehicleToMakeRoom, &flags::dont_shuffle_in_vehicle_to_make_room);
        push_f("Give Weapon On Getup", CPED_CONFIG_FLAG_GiveWeaponOnGetup, &flags::give_weapon_on_getup);
        push_f("Don't Hit Vehicle With Projectiles", CPED_CONFIG_FLAG_DontHitVehicleWithProjectiles, &flags::dont_hit_vehicle_with_projectiles);
        push_f("Disable Forced Entry For Open Vehicles From TryLockedDoor", CPED_CONFIG_FLAG_DisableForcedEntryForOpenVehiclesFromTryLockedDoor, &flags::disable_forced_entry_for_open_vehicles_from_try_locked_door);
        push_f("Fires Dummy Rockets", CPED_CONFIG_FLAG_FiresDummyRockets, &flags::fires_dummy_rockets);
        push_f("Ped Is Arresting", CPED_CONFIG_FLAG_PedIsArresting, &flags::ped_is_arresting);
        push_f("Is Decoy Ped", CPED_CONFIG_FLAG_IsDecoyPed, &flags::is_decoy_ped);
        push_f("Has Established Decoy", CPED_CONFIG_FLAG_HasEstablishedDecoy, &flags::has_established_decoy);
        push_f("Block Dispatched Helicopters From Landing", CPED_CONFIG_FLAG_BlockDispatchedHelicoptersFromLanding, &flags::block_dispatched_helicopters_from_landing);
        push_f("Don't Cry For Help On Stun", CPED_CONFIG_FLAG_DontCryForHelpOnStun, &flags::dont_cry_for_help_on_stun);
        push_f("Hit By Tranq Weapon", CPED_CONFIG_FLAG_HitByTranqWeapon, &flags::hit_by_tranq_weapon);
        push_f("Can Be Incapacitated", CPED_CONFIG_FLAG_CanBeIncapacitated, &flags::can_be_incapacitated);
        push_f("Forced Aim From Arrest", CPED_CONFIG_FLAG_ForcedAimFromArrest, &flags::forced_aim_from_arrest);
        push_f("Don't Change Target From Melee", CPED_CONFIG_FLAG_DontChangeTargetFromMelee, &flags::dont_change_target_from_melee);
        push_f("Disable Health Regeneration When Stunned", CPED_CONFIG_FLAG_DisableHealthRegenerationWhenStunned, &flags::disable_health_regeneration_when_stunned);
        push_f("Ragdoll Floats Indefinitely", CPED_CONFIG_FLAG_RagdollFloatsIndefinitely, &flags::ragdoll_floats_indefinitely);
        push_f("Block Electric Weapon Damage", CPED_CONFIG_FLAG_BlockElectricWeaponDamage, &flags::block_electric_weapon_damage);
	}

}
