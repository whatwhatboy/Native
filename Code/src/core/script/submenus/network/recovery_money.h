#include "src/core/script/drawing/drawing.h"
#include "src/framework/option_types/button.h"
#include <JSON/json.hpp>
namespace Base::submenus::network {
    void send_basket_transaction(rage::joaat_t category, rage::joaat_t item_hash, rage::joaat_t action_type_hash, std::uint32_t value, int flag) {
        g_utils->invoke_transaction(category, item_hash, action_type_hash, value, flag);
    }
    class transaction_mgr {
    public:
        struct transaction {
            const char* name;
            const char* hash;
        };
        std::vector<transaction> transactions = {
            {"Criminal (15M)", "SERVICE_EARN_JOB_BONUS_CRIMINAL_MASTERMIND"},
            {"Gangops (15M)", "SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_4"},
            {"Casino Heist (3.6M)", "SERVICE_EARN_CASINO_HEIST_FINALE"},
            {"Agency (3M)", "SERVICE_EARN_AGENCY_STORY_FINALE"},
            {"Gangops 2 (3M)", "SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_2"},
            {"Cayo Perico (2.5M)", "SERVICE_EARN_ISLAND_HEIST_FINALE"},
            {"Job Bonus (2M)", "SERVICE_EARN_JOB_BONUS_HEIST_AWARD"},
            {"Tuner Robbery (2M)", "SERVICE_EARN_TUNER_ROBBERY_FINALE"},
            {"Hub Sell (2M)", "SERVICE_EARN_FROM_BUSINESS_HUB_SELL"},
            {"Betting (680k)", "SERVICE_EARN_BETTING"},
            {"Professional (400K)", "SERVICE_EARN_ISLAND_HEIST_AWARD_PROFESSIONAL"},
            {"Smuggler Agency (270K)", "SERVICE_EARN_SMUGGLER_AGENCY"},
            {"RDR Bonus (250K)", "SERVICE_EARN_RDR_BONUS_ALL_SLOTS"},
            {"Professional (250K)", "SERVICE_EARN_CASINO_HEIST_AWARD_PROFESSIONAL"},
            {"Professional (250K)", "SERVICE_EARN_CASINO_HEIST_AWARD_PROFESSIONAL"},
            {"Avenger Operations (1M)", "SERVICE_EARN_AVENGER_OPERATIONS"},
            {"Music Trip (1M)", "SERVICE_EARN_MUSIC_STUDIO_SHORT_TRIP"},
            {"Daily Objective Event (1M)", "SERVICE_EARN_DAILY_OBJECTIVE_EVENT"},
            {"Daily Objectives (1M)", "SERVICE_EARN_DAILY_OBJECTIVES"},
            {"Juggalo Story Award (1M)", "SERVICE_EARN_GANGOPS_AWARD_LOYALTY_AWARD_3"},
            {"Pro Thief (300K)", "SERVICE_EARN_ISLAND_HEIST_AWARD_PRO_THIEF"},
            {"Premium (300K)", "SERVICE_EARN_PREMIUM_JOB"},
            {"Elite Thief (350K)", "SERVICE_EARN_CASINO_HEIST_AWARD_ELITE_THIEF"},
            {"Elite Thief (400K)", "SERVICE_EARN_ISLAND_HEIST_AWARD_ELITE_THIEF"},
            {"Cat Burglar (400K)", "SERVICE_EARN_ISLAND_HEIST_AWARD_CAT_BURGLAR"},
            {"Island Heist (400K)", "SERVICE_EARN_ISLAND_HEIST_AWARD_THE_ISLAND_HEIST"},
            {"All Rounder (300K)", "SERVICE_EARN_CASINO_HEIST_AWARD_ALL_ROUNDER"},
            {"Teamwork (200K)", "SERVICE_EARN_ISLAND_HEIST_AWARD_TEAM_WORK"},
            {"Action Figures (200K)", "SERVICE_EARN_COLLECTABLES_ACTION_FIGURES"},
            {"Time Trial (200K)", "SERVICE_EARN_AMBIENT_JOB_TIME_TRIAL"},
            {"Ammunation (200K)", "SERVICE_EARN_AMBIENT_JOB_AMMUNATION_DELIVERY"},
            {"Vehicle Sales (190K)", "SERVICE_EARN_VEHICLE_SALES"},
            {"Agency Boss (120K)", "SERVICE_EARN_BOSS_AGENCY"},
            {"Sightseeing (115K)", "SERVICE_EARN_SIGHTSEEING_REWARD"},
            {"Business Battle (50K)", "SERVICE_EARN_FROM_BUSINESS_BATTLE"},
            {"Yohan Goods (50K)", "SERVICE_EARN_YOHAN_SOURCE_GOODS"},
            {"Mixing It Up (500K)", "SERVICE_EARN_ISLAND_HEIST_AWARD_MIXING_IT_UP"},
            {"Straight Flush (500K)", "SERVICE_EARN_CASINO_AWARD_STRAIGHT_FLUSH"},
            {"Going Alone (200K)", "SERVICE_EARN_ISLAND_HEIST_AWARD_GOING_ALONE"},
            {"High Roller Silver (20K)", "SERVICE_EARN_CASINO_AWARD_HIGH_ROLLER_SILVER"},
            {"Taxi (50K)", "SERVICE_EARN_TAXI_JOB"},
            {"Head 2 Head (30K)", "SERVICE_EARN_REFUND_HEAD_2_HEAD"},
            {"Mercenary (22K)", "SERVICE_EARN_REFUND_HIRE_MERCENARY"},
            {"Bounty (10K)", "SERVICE_EARN_DEATHMATCH_BOUNTY"},
            {"Clear Wanted (3K)", "SERVICE_EARN_REFUND_CLEAR_WANTED"},
        };
        std::vector<transaction> all_transactions = {
            {"Job Bonus (15M)","SERVICE_EARN_JOB_BONUS"},
            {"Bend Job (15M)","SERVICE_EARN_BEND_JOB"},
            {"Gangops Award Mastermind 4 (15M)","SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_4"},
            {"Job Bonus Criminal Mastermind (15M)","SERVICE_EARN_JOB_BONUS_CRIMINAL_MASTERMIND"},
            {"Gangops Award Mastermind 3 (7M)","SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_3"},
            {"Casino Heist Finale (3M)","SERVICE_EARN_CASINO_HEIST_FINALE"},
            {"Agency Story Finale (3M)","SERVICE_EARN_AGENCY_STORY_FINALE"},
            {"Gangops Award Mastermind 2 (3M)","SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_2"},
            {"Island Heist Finale (2M)","SERVICE_EARN_ISLAND_HEIST_FINALE"},
            {"Gangops Finale (2M)","SERVICE_EARN_GANGOPS_FINALE"},
            {"Job Bonus Heist Award (2M)","SERVICE_EARN_JOB_BONUS_HEIST_AWARD"},
            {"Tuner Robbery Finale (2M)","SERVICE_EARN_TUNER_ROBBERY_FINALE"},
            {"Gangops Award Order (2M)","SERVICE_EARN_GANGOPS_AWARD_ORDER"},
            {"Business Hub Sell (2M)","SERVICE_EARN_FROM_BUSINESS_HUB_SELL"},
            {"Gangops Award Loyalty Award 4 (1M)","SERVICE_EARN_GANGOPS_AWARD_LOYALTY_AWARD_4"},
            {"Daily Objectives (1M)","SERVICE_EARN_DAILY_OBJECTIVES"},
            {"Music Studio Short Trip (1M)","SERVICE_EARN_MUSIC_STUDIO_SHORT_TRIP"},
            {"Avenger Operations (1M)","SERVICE_EARN_AVENGER_OPERATIONS"},
            {"Daily Objective Event (1M)","SERVICE_EARN_DAILY_OBJECTIVE_EVENT"},
            {"Juggalo Story Mission (1M)","SERVICE_EARN_JUGGALO_STORY_MISSION"},
            {"Orbital Auto (750K)","SERVICE_EARN_REFUND_ORBITAL_AUTO"},
            {"Gangops Award Loyalty Award 3 (700K)","SERVICE_EARN_GANGOPS_AWARD_LOYALTY_AWARD_3"},
            {"Betting (680K)","SERVICE_EARN_BETTING"},
            {"Island Heist Award Mixing It Up (500K)","SERVICE_EARN_ISLAND_HEIST_AWARD_MIXING_IT_UP"},
            {"Winter 22 Award Juggalo Story (500K)","SERVICE_EARN_WINTER_22_AWARD_JUGGALO_STORY"},
            {"Casino Award Straight Flush (500K)","SERVICE_EARN_CASINO_AWARD_STRAIGHT_FLUSH"},
            {"Orbital Manual (500K)","SERVICE_EARN_REFUND_ORBITAL_MANUAL"},
            {"Island Heist Award Professional (400K)","SERVICE_EARN_ISLAND_HEIST_AWARD_PROFESSIONAL"},
            {"Island Heist Award Cat Burglar (400K)","SERVICE_EARN_ISLAND_HEIST_AWARD_CAT_BURGLAR"},
            {"Island Heist Award Elite Thief (400K)","SERVICE_EARN_ISLAND_HEIST_AWARD_ELITE_THIEF"},
            {"Island Heist Award The Island Heist (400K)","SERVICE_EARN_ISLAND_HEIST_AWARD_THE_ISLAND_HEIST"},
            {"Casino Heist Award Elite Thief (350K)","SERVICE_EARN_CASINO_HEIST_AWARD_ELITE_THIEF"},
            {"Vehicle Export (310K)","SERVICE_EARN_FROM_VEHICLE_EXPORT"},
            {"Blast (300K)","SERVICE_EARN_AMBIENT_JOB_BLAST"},
            {"Premium Job (300K)","SERVICE_EARN_PREMIUM_JOB"},
            {"Gangops Award Loyalty Award 2 (300K)","SERVICE_EARN_GANGOPS_AWARD_LOYALTY_AWARD_2"},
            {"Casino Heist Award All Rounder (300K)","SERVICE_EARN_CASINO_HEIST_AWARD_ALL_ROUNDER"},
            {"Island Heist Award Pro Thief (300K)","SERVICE_EARN_ISLAND_HEIST_AWARD_PRO_THIEF"},
            {"Smuggler Agency (270K)","SERVICE_EARN_SMUGGLER_AGENCY"},
            {"Fixer Award Agency Story (250K)","SERVICE_EARN_FIXER_AWARD_AGENCY_STORY"},
            {"Avenger Ops Bonus (250K)","SERVICE_EARN_AVENGER_OPS_BONUS"},
            {"Casino Heist Award Professional (250K)","SERVICE_EARN_CASINO_HEIST_AWARD_PROFESSIONAL"},
            {"Gangops Award Supporting (200K)","SERVICE_EARN_GANGOPS_AWARD_SUPPORTING"},
            {"Collectables Action Figures (200K)","SERVICE_EARN_COLLECTABLES_ACTION_FIGURES"},
            {"Island Heist Award Going Alone (200K)","SERVICE_EARN_ISLAND_HEIST_AWARD_GOING_ALONE"},
            {"Job Bonus First Time Bonus (200K)","SERVICE_EARN_JOB_BONUS_FIRST_TIME_BONUS"},
            {"Gangops Award First Time Xm Silo (200K)","SERVICE_EARN_GANGOPS_AWARD_FIRST_TIME_XM_SILO"},
            {"Doomsday Finale Bonus (200K)","SERVICE_EARN_DOOMSDAY_FINALE_BONUS"},
            {"Gangops Award First Time Xm Base (200K)","SERVICE_EARN_GANGOPS_AWARD_FIRST_TIME_XM_BASE"},
            {"Collectable Completed Collection (200K)","SERVICE_EARN_COLLECTABLE_COMPLETED_COLLECTION"},
            {"Island Heist Elite Challenge (200K)","SERVICE_EARN_ISLAND_HEIST_ELITE_CHALLENGE"},
            {"Checkpoint Collection (200K)","SERVICE_EARN_AMBIENT_JOB_CHECKPOINT_COLLECTION"},
            {"Gangops Award First Time Xm Submarine (200K)","SERVICE_EARN_GANGOPS_AWARD_FIRST_TIME_XM_SUBMARINE"},
            {"Island Heist Award Team Work (200K)","SERVICE_EARN_ISLAND_HEIST_AWARD_TEAM_WORK"},
            {"Casino Heist Elite Direct (200K)","SERVICE_EARN_CASINO_HEIST_ELITE_DIRECT"},
            {"Casino Heist Elite Stealth (200K)","SERVICE_EARN_CASINO_HEIST_ELITE_STEALTH"},
            {"Time Trial (200K)","SERVICE_EARN_AMBIENT_JOB_TIME_TRIAL"},
            {"Casino Heist Award Undetected (200K)","SERVICE_EARN_CASINO_HEIST_AWARD_UNDETECTED"},
            {"Casino Heist Elite Subterfuge (200K)","SERVICE_EARN_CASINO_HEIST_ELITE_SUBTERFUGE"},
            {"Ammunation Delivery (200K)","SERVICE_EARN_AMBIENT_JOB_AMMUNATION_DELIVERY"},
            {"Gangops Elite Xm Silo (200K)","SERVICE_EARN_GANGOPS_ELITE_XM_SILO"},
            {"Vehicle Sales (190K)","SERVICE_EARN_VEHICLE_SALES"},
            {"Jobs (180K)","SERVICE_EARN_JOBS"},
            {"Rc Time Trial (165K)","SERVICE_EARN_AMBIENT_JOB_RC_TIME_TRIAL"},
            {"Bicycle Time Trial (165K)","SERVICE_EARN_AMBIENT_JOB_BICYCLE_TIME_TRIAL"},
            {"Beast (150K)","SERVICE_EARN_AMBIENT_JOB_BEAST"},
            {"Casino Heist Award In Plain Sight (150K)","SERVICE_EARN_CASINO_HEIST_AWARD_IN_PLAIN_SIGHT"},
            {"Gangops Elite Xm Submarine (150K)","SERVICE_EARN_GANGOPS_ELITE_XM_SUBMARINE"},
            {"Boss Agency (120K)","SERVICE_EARN_BOSS_AGENCY"},
            {"King (120K)","SERVICE_EARN_AMBIENT_JOB_KING"},
            {"Penned In (120K)","SERVICE_EARN_AMBIENT_JOB_PENNED_IN"},
            {"Sightseeing Reward (115K)","SERVICE_EARN_SIGHTSEEING_REWARD"},
            {"Cayo Attrition Bonus Objective (100K)","SERVICE_EARN_CAYO_ATTRITION_BONUS_OBJECTIVE"},
            {"Casino Award High Roller Platinum (100K)","SERVICE_EARN_CASINO_AWARD_HIGH_ROLLER_PLATINUM"},
            {"Bolingbroke Ass (100K)","SERVICE_EARN_TUNER_AWARD_BOLINGBROKE_ASS"},
            {"Casino Award Full House (100K)","SERVICE_EARN_CASINO_AWARD_FULL_HOUSE"},
            {"Agency Security Contract (100K)","SERVICE_EARN_AGENCY_SECURITY_CONTRACT"},
            {"Daily Stash House Completed (100K)","SERVICE_EARN_DAILY_STASH_HOUSE_COMPLETED"},
            {"Casino Award Mission Six First Time (100K)","SERVICE_EARN_CASINO_AWARD_MISSION_SIX_FIRST_TIME"},
            {"Challenges (100K)","SERVICE_EARN_AMBIENT_JOB_CHALLENGES"},
            {"Metal Detector (100K)","SERVICE_EARN_AMBIENT_JOB_METAL_DETECTOR"},
            {"Hot Property (100K)","SERVICE_EARN_AMBIENT_JOB_HOT_PROPERTY"},
            {"Clubhouse Contract (100K)","SERVICE_EARN_AMBIENT_JOB_CLUBHOUSE_CONTRACT"},
            {"Fleeca Bank (100K)","SERVICE_EARN_TUNER_AWARD_FLEECA_BANK"},
            {"Smuggler Plane (100K)","SERVICE_EARN_AMBIENT_JOB_SMUGGLER_PLANE"},
            {"Fixer Award Short Trip (100K)","SERVICE_EARN_FIXER_AWARD_SHORT_TRIP"},
            {"Smuggler Trail (100K)","SERVICE_EARN_AMBIENT_JOB_SMUGGLER_TRAIL"},
            {"Smuggler Ops (100K)","SERVICE_EARN_SMUGGLER_OPS"},
            {"Meth Job (100K)","SERVICE_EARN_TUNER_AWARD_METH_JOB"},
            {"Casino Heist Award Smash N Grab (100K)","SERVICE_EARN_CASINO_HEIST_AWARD_SMASH_N_GRAB"},
            {"Agency Story Prep (100K)","SERVICE_EARN_AGENCY_STORY_PREP"},
            {"Winter 22 Award Daily Stash (100K)","SERVICE_EARN_WINTER_22_AWARD_DAILY_STASH"},
            {"Juggalo Phone Mission (100K)","SERVICE_EARN_JUGGALO_PHONE_MISSION"},
            {"Golden Gun (100K)","SERVICE_EARN_AMBIENT_JOB_GOLDEN_GUN"},
            {"Urban Warfare (100K)","SERVICE_EARN_AMBIENT_JOB_URBAN_WARFARE"},
            {"Agency Payphone Hit (100K)","SERVICE_EARN_AGENCY_PAYPHONE_HIT"},
            {"Freight Train (100K)","SERVICE_EARN_TUNER_AWARD_FREIGHT_TRAIN"},
            {"Winter 22 Award Dead Drop (100K)","SERVICE_EARN_WINTER_22_AWARD_DEAD_DROP"},
            {"Clubhouse Duffle Bag (100K)","SERVICE_EARN_CLUBHOUSE_DUFFLE_BAG"},
            {"Winter 22 Award Random Event (100K)","SERVICE_EARN_WINTER_22_AWARD_RANDOM_EVENT"},
            {"Military Convoy (100K)","SERVICE_EARN_TUNER_AWARD_MILITARY_CONVOY"},
            {"Juggalo Story Mission Participation (100K)","SERVICE_EARN_JUGGALO_STORY_MISSION_PARTICIPATION"},
            {"Crime Scene (100K)","SERVICE_EARN_AMBIENT_JOB_CRIME_SCENE"},
            {"Iaa Raid (100K)","SERVICE_EARN_TUNER_AWARD_IAA_RAID"},
            {"Arena Career Tier Progression 4 (100K)","SERVICE_EARN_ARENA_CAREER_TIER_PROGRESSION_4"},
            {"Auto Shop Delivery Award (100K)","SERVICE_EARN_AUTO_SHOP_DELIVERY_AWARD"},
            {"Casino Award Top Pair (100K)","SERVICE_EARN_CASINO_AWARD_TOP_PAIR"},
            {"Union Depository (100K)","SERVICE_EARN_TUNER_AWARD_UNION_DEPOSITORY"},
            {"Underwater Cargo (100K)","SERVICE_EARN_AMBIENT_JOB_UNDERWATER_CARGO"},
            {"Collectable Item (100K)","SERVICE_EARN_COLLECTABLE_ITEM"},
            {"Winter 22 Award Acid Lab (100K)","SERVICE_EARN_WINTER_22_AWARD_ACID_LAB"},
            {"Maze Bank (100K)","SERVICE_EARN_AMBIENT_JOB_MAZE_BANK"},
            {"Gangops Elite Xm Base (100K)","SERVICE_EARN_GANGOPS_ELITE_XM_BASE"},
            {"Winter 22 Award Taxi (100K)","SERVICE_EARN_WINTER_22_AWARD_TAXI"},
            {"Tuner Daily Vehicle Bonus (100K)","SERVICE_EARN_TUNER_DAILY_VEHICLE_BONUS"},
            {"Bunker Raid (100K)","SERVICE_EARN_TUNER_AWARD_BUNKER_RAID"},
            {"Gangops Setup (90K)","SERVICE_EARN_GANGOPS_SETUP"},
            {"Dead Drop (80K)","SERVICE_EARN_AMBIENT_JOB_DEAD_DROP"},
            {"Hot Target Deliver (80K)","SERVICE_EARN_AMBIENT_JOB_HOT_TARGET_DELIVER"},
            {"Arena Career Tier Progression 3 (75K)","SERVICE_EARN_ARENA_CAREER_TIER_PROGRESSION_3"},
            {"Xmas Mugger (70K)","SERVICE_EARN_AMBIENT_JOB_XMAS_MUGGER"},
            {"Import Export (65K)","SERVICE_EARN_IMPORT_EXPORT"},
            {"Nightclub Dancing Award (60K)","SERVICE_EARN_NIGHTCLUB_DANCING_AWARD"},
            {"Arena Career Tier Progression 2 (55K)","SERVICE_EARN_ARENA_CAREER_TIER_PROGRESSION_2"},
            {"Business Battle (50K)","SERVICE_EARN_FROM_BUSINESS_BATTLE"},
            {"Island Heist Dj Mission (50K)","SERVICE_EARN_ISLAND_HEIST_DJ_MISSION"},
            {"Arena Skill Lvl Award (50K)","SERVICE_EARN_ARENA_SKILL_LVL_AWARD"},
            {"Gang Convoy (50K)","SERVICE_EARN_AMBIENT_JOB_GANG_CONVOY"},
            {"Collectables Signal Jammers Complete (50K)","SERVICE_EARN_COLLECTABLES_SIGNAL_JAMMERS_COMPLETE"},
            {"Heli Hot Target (50K)","SERVICE_EARN_AMBIENT_JOB_HELI_HOT_TARGET"},
            {"Acid Lab Sell Participation (50K)","SERVICE_EARN_ACID_LAB_SELL_PARTICIPATION"},
            {"Contraband (50K)","SERVICE_EARN_FROM_CONTRABAND"},
            {"Casino Award High Roller Gold (50K)","SERVICE_EARN_CASINO_AWARD_HIGH_ROLLER_GOLD"},
            {"Casino Award Mission Three First Time (50K)","SERVICE_EARN_CASINO_AWARD_MISSION_THREE_FIRST_TIME"},
            {"Goon (50K)","SERVICE_EARN_GOON"},
            {"Fixer Award Phone Hit (50K)","SERVICE_EARN_FIXER_AWARD_PHONE_HIT"},
            {"Casino Award Mission Four First Time (50K)","SERVICE_EARN_CASINO_AWARD_MISSION_FOUR_FIRST_TIME"},
            {"Taxi Job (50K)","SERVICE_EARN_TAXI_JOB"},
            {"Casino Award Mission One First Time (50K)","SERVICE_EARN_CASINO_AWARD_MISSION_ONE_FIRST_TIME"},
            {"Shop Robbery (50K)","SERVICE_EARN_AMBIENT_JOB_SHOP_ROBBERY"},
            {"Arena War (50K)","SERVICE_EARN_ARENA_WAR"},
            {"Casino Award Mission Five First Time (50K)","SERVICE_EARN_CASINO_AWARD_MISSION_FIVE_FIRST_TIME"},
            {"Casino Award Lucky Lucky (50K)","SERVICE_EARN_CASINO_AWARD_LUCKY_LUCKY"},
            {"Pass Parcel (50K)","SERVICE_EARN_AMBIENT_JOB_PASS_PARCEL"},
            {"Yohan Source Goods (50K)","SERVICE_EARN_YOHAN_SOURCE_GOODS"},
            {"Tuner Car Club Membership (50K)","SERVICE_EARN_TUNER_CAR_CLUB_MEMBERSHIP"},
            {"Source Research (50K)","SERVICE_EARN_AMBIENT_JOB_SOURCE_RESEARCH"},
            {"Casino Award Mission Two First Time (50K)","SERVICE_EARN_CASINO_AWARD_MISSION_TWO_FIRST_TIME"},
            {"Drug Vehicle (50K)","SERVICE_EARN_AMBIENT_JOB_DRUG_VEHICLE"},
            {"Armored Truck (50K)","SERVICE_EARN_AMBIENT_JOB_ARMORED_TRUCK"},
            {"Hot Target Kill (50K)","SERVICE_EARN_AMBIENT_JOB_HOT_TARGET_KILL"},
            {"Casino Heist Prep Mission (40K)","SERVICE_EARN_CASINO_HEIST_PREP_MISSION"},
            {"Island Heist Prep (40K)","SERVICE_EARN_ISLAND_HEIST_PREP"},
            {"Fmbb Boss Work (40K)","SERVICE_EARN_FROM_FMBB_BOSS_WORK"},
            {"Bb Event Bonus (40K)","SERVICE_EARN_BB_EVENT_BONUS"},
            {"Casino Heist Setup Mission (40K)","SERVICE_EARN_CASINO_HEIST_SETUP_MISSION"},
            {"Casino Mission Reward (40K)","SERVICE_EARN_CASINO_MISSION_REWARD"},
            {"Arena Career Tier Progression 1 (35K)","SERVICE_EARN_ARENA_CAREER_TIER_PROGRESSION_1"},
            {"Casino Story Mission Reward (30K)","SERVICE_EARN_CASINO_STORY_MISSION_REWARD"},
            {"Head 2 Head (30K)","SERVICE_EARN_REFUND_HEAD_2_HEAD"},
            {"Bounty Collected (30K)","SERVICE_EARN_BOUNTY_COLLECTED"},
            {"Gangops Wages (30K)","SERVICE_EARN_GANGOPS_WAGES"},
            {"Gangops Wages Bonus (30K)","SERVICE_EARN_GANGOPS_WAGES_BONUS"},
            {"Fmbb Wage Bonus (30K)","SERVICE_EARN_FMBB_WAGE_BONUS"},
            {"Fmbb Phonecall Mission (30K)","SERVICE_EARN_FROM_FMBB_PHONECALL_MISSION"},
            {"Fixer Award Sec Con (30K)","SERVICE_EARN_FIXER_AWARD_SEC_CON"},
            {"Fixer Rival Delivery (25K)","SERVICE_EARN_FIXER_RIVAL_DELIVERY"},
            {"Hire Mercenary (22K)","SERVICE_EARN_REFUND_HIRE_MERCENARY"},
            {"Tuner Robbery Prep (20K)","SERVICE_EARN_TUNER_ROBBERY_PREP"},
            {"Club Management Participation (20K)","SERVICE_EARN_FROM_CLUB_MANAGEMENT_PARTICIPATION"},
            {"Acid Lab Source Participation (20K)","SERVICE_EARN_ACID_LAB_SOURCE_PARTICIPATION"},
            {"Spin The Wheel Cash (20K)","SERVICE_EARN_SPIN_THE_WHEEL_CASH"},
            {"Gangops Setup Fail (20K)","SERVICE_EARN_GANGOPS_SETUP_FAIL"},
            {"Juggalo Phone Mission Participation (20K)","SERVICE_EARN_JUGGALO_PHONE_MISSION_PARTICIPATION"},
            {"Casino Award High Roller Silver (20K)","SERVICE_EARN_CASINO_AWARD_HIGH_ROLLER_SILVER"},
            {"Acid Lab Setup Participation (20K)","SERVICE_EARN_ACID_LAB_SETUP_PARTICIPATION"},
            {"Tuner Daily Vehicle (20K)","SERVICE_EARN_TUNER_DAILY_VEHICLE"},
            {"Gangops Prep Participation (15K)","SERVICE_EARN_GANGOPS_PREP_PARTICIPATION"},
            {"Gangops Rival Delivery (15K)","SERVICE_EARN_GANGOPS_RIVAL_DELIVERY"},
            {"Bounty Hunter Reward (10K)","SERVICE_EARN_BOUNTY_HUNTER_REWARD"},
            {"Nightclub Troublemaker (10K)","SERVICE_EARN_NCLUB_TROUBLEMAKER"},
            {"Heli Pickup (10K)","SERVICE_EARN_REFUND_HELI_PICKUP"},
            {"Daily Stash House Participation (10K)","SERVICE_EARN_DAILY_STASH_HOUSE_PARTICIPATION"},
            {"Ambient Mugging (10K)","SERVICE_EARN_AMBIENT_MUGGING"},
            {"Wage Payment (10K)","SERVICE_EARN_WAGE_PAYMENT"},
            {"Pickup (10K)","SERVICE_EARN_PICKUP"},
            {"Deathmatch Bounty (10K)","SERVICE_EARN_DEATHMATCH_BOUNTY"},
            {"Destroying Contraband (10K)","SERVICE_EARN_FROM_DESTROYING_CONTRABAND"},
            {"Casino Award High Roller Bronze (10K)","SERVICE_EARN_CASINO_AWARD_HIGH_ROLLER_BRONZE"},
            {"Gangattack Pickup (10K)","SERVICE_EARN_GANGATTACK_PICKUP"},
            {"Wage Payment Bonus (10K)","SERVICE_EARN_WAGE_PAYMENT_BONUS"},
            {"Holdups (10K)","SERVICE_EARN_HOLDUPS"},
            {"Ammo Drop (5K)","SERVICE_EARN_REFUNDAMMODROP"},
            {"Assassinate Target Killed (4K)","SERVICE_EARN_ASSASSINATE_TARGET_KILLED"},
            {"Clear Wanted (3K)","SERVICE_EARN_REFUND_CLEAR_WANTED"},
            {"Hire Mugger (3K)","SERVICE_EARN_REFUND_HIRE_MUGGER"},
            {"Not Badsport (2K)","SERVICE_EARN_NOT_BADSPORT"},
            {"Collectables Signal Jammers (2K)","SERVICE_EARN_COLLECTABLES_SIGNAL_JAMMERS"},
            {"Ambient Pickup (2K)","SERVICE_EARN_AMBIENT_PICKUP"},
            {"Car Drop Off (1K)","SERVICE_EARN_REFUND_BUY_CARDROPOFF"},
            {"Cashing Out (1K)","SERVICE_EARN_CASHING_OUT"},
            {"Salvage Checkpoint Collection (1K)","SERVICE_EARN_SALVAGE_CHECKPOINT_COLLECTION"},
            {"Boat Pickup (750)","SERVICE_EARN_REFUND_BOAT_PICKUP"},
            {"Arena Spec Box Entry (100)","SERVICE_EARN_REFUND_ARENA_SPEC_BOX_ENTRY"},

        };
    public:
        bool is_processing;
        int get_last_price;
    public:
        int get_price(const char* hash, int category = 1474183246) {
            auto price{ NETSHOPPING::NET_GAMESERVER_GET_PRICE(rage::joaat(hash), category, true) };
            get_last_price = price;
            return price;
        }
        void process(const char* hash) {
            is_processing = true;
            send_basket_transaction(1474183246, rage::joaat(hash), g_utils->get_action_for_transaction(hash), get_price(hash), 1);
            is_processing = false;
        }
        void process2(const char* hash, int price, std::string category) {
            is_processing = true;
            send_basket_transaction(rage::joaat(category), rage::joaat(hash), g_utils->get_action_for_transaction(hash), price, 1);
            is_processing = false;
        }
    public:
        void get(const char* hash, const char* flag = "none") {
            for (auto opt : transactions) {
                if (opt.hash == hash) {
                    draw->button(opt.name, [=] {
                        process(opt.hash);
                    });
                }
            }
        }
        void find_all(const char* key) {
            for (auto opt : transactions)
                if (g_utils->has_string_attached(opt.hash, key)) {
                    draw->button(opt.name, [=] {
                        process(opt.hash);
                        });
                }

        }
        void find_all_2(const char* key) {
            for (auto opt : all_transactions) {
                size_t length = strlen(opt.name);
                if (g_utils->has_string_attached(opt.hash, key) && (length < 25)) {
                    draw->button(opt.name, [=] {
                        process(opt.hash);
                        });
                }
            }
        }
    };
    transaction_mgr g_transaction_mgr;
    struct basket_transaction {
        std::string category;
        std::string name;
        int price;
    };
    std::string search_transactions = "";
    std::vector<basket_transaction> all_non_named;
    bool init{ false };
    bool dont_show_invalid{ false };
    void recovery_money() {
        draw->submenu_second("Awards", "recovery:money:awards", [] {
            draw->submenu_second("Cayo Perico", "recovery:money:awards:cayo", [] {
                g_transaction_mgr.find_all("SERVICE_EARN_ISLAND_HEIST_AWARD");
                });
            draw->submenu_second("Casino Heist", "recovery:money:awards:casino", [] {
                g_transaction_mgr.find_all("SERVICE_EARN_CASINO_HEIST_AWARD");
                });
            draw->submenu_second("Tuner", "recovery:money:awards:tuner", [] {
                g_transaction_mgr.find_all_2("SERVICE_EARN_TUNER_AWARD_");
                });
            draw->submenu_second("Mastermind", "recovery:money:awards:mastermind", [] {
                g_transaction_mgr.get("SERVICE_EARN_JOB_BONUS_CRIMINAL_MASTERMIND");
                g_transaction_mgr.get("SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_4");
                g_transaction_mgr.get("SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_2");
                });
            draw->seperator("Misc");
            g_transaction_mgr.get("SERVICE_EARN_JOB_BONUS_HEIST_AWARD");
            });
        draw->submenu_second("Freemode", "recovery:money:freemode", [] {
            g_transaction_mgr.get("SERVICE_EARN_DAILY_OBJECTIVES");
            g_transaction_mgr.get("SERVICE_EARN_BETTING");
            g_transaction_mgr.get("SERVICE_EARN_COLLECTABLES_ACTION_FIGURES");
            g_transaction_mgr.get("SERVICE_EARN_AMBIENT_JOB_TIME_TRIAL");
            g_transaction_mgr.get("SERVICE_EARN_VEHICLE_SALES");
            g_transaction_mgr.get("SERVICE_EARN_FROM_BUSINESS_BATTLE");
            });
        draw->submenu_second("Jobs/Missions", "recovery:money:jobs", [] {
            g_transaction_mgr.get("SERVICE_EARN_CASINO_HEIST_FINALE");
            g_transaction_mgr.get("SERVICE_EARN_AGENCY_STORY_FINALE");
            g_transaction_mgr.get("SERVICE_EARN_ISLAND_HEIST_FINALE");
            g_transaction_mgr.get("SERVICE_EARN_TUNER_ROBBERY_FINALE");
            g_transaction_mgr.get("SERVICE_EARN_AVENGER_OPERATIONS");
            g_transaction_mgr.get("SERVICE_EARN_PREMIUM_JOB");
            g_transaction_mgr.get("SERVICE_EARN_FIXER_AWARD_AGENCY_STORY");
            g_transaction_mgr.get("SERVICE_EARN_AMBIENT_JOB_AMMUNATION_DELIVERY");
            g_transaction_mgr.get("SERVICE_EARN_BOSS_AGENCY");
            g_transaction_mgr.get("SERVICE_EARN_TAXI_JOB");
            });
        draw->submenu_second("Buisnesss", "recovery:money:buisnesss", [] {
            g_transaction_mgr.get("SERVICE_EARN_FROM_BUSINESS_HUB_SELL");
            g_transaction_mgr.get("SERVICE_EARN_FROM_VEHICLE_EXPORT");
            g_transaction_mgr.get("SERVICE_EARN_YOHAN_SOURCE_GOODS");
            });
        draw->submenu_second("Misc", "recovery:money:misc", [] {
            //  g_transaction_mgr.get("SERVICE_EARN_RDR_BONUS_ALL_SLOTS");
            g_transaction_mgr.get("SERVICE_EARN_SIGHTSEEING_REWARD");
            g_transaction_mgr.get("SERVICE_EARN_DEATHMATCH_BOUNTY");
            });
        draw->submenu_second("Refunds", "recovery:money:refunds", [] {
            g_transaction_mgr.find_all_2("SERVICE_EARN_REFUND");
            });
        draw->submenu_second("Ambient", "recovery:money:ambient", [] {
            g_transaction_mgr.find_all_2("SERVICE_EARN_AMBIENT_JOB_");
            });
        draw->submenu_second("All", "recovery:money:all", [] {
            draw->submenu_second("Non-Named", "all:non_named", [] {
                if (init) {
                    draw->toggle("Dont Show Invalid", &dont_show_invalid);
                    draw->seperator("List");
                    for (auto& opt : all_non_named) {
                        if (dont_show_invalid) {
                            if (opt.category == "CATEGORY_SERVICE_WITH_THRESHOLD") {
                                draw->button(std::format("{} ({})", opt.name, std::to_string(opt.price)), [=] {
                                    g_utils->invoke_transaction(rage::joaat(opt.category), rage::joaat(opt.name), g_utils->get_action_for_transaction(opt.name), opt.price, 1);
                                });
                            }
                        }
                        else {
                            draw->button(std::format("{} ({})", opt.name, std::to_string(opt.price)), [=] {
                                g_utils->invoke_transaction(rage::joaat(opt.category), rage::joaat(opt.name), g_utils->get_action_for_transaction(opt.name), opt.price, 1);
                            });
                        }
                    }
                }
                if (!init) {
                    std::ifstream file("D:\\Catalog_928.json");
                    if (!file.is_open()) {
                        std::cout << "Error opening JSON file." << std::endl;
                        return 1;
                    }

                    nlohmann::json data;
                    file >> data;


                    if (data.contains("items") && data["items"].is_array()) {
                        for (const auto& item : data["items"]) {
                            if (item.contains("price") && item.contains("key")) {
                                int price = item["price"];
                                std::string key = item["key"];
                                std::string category = item["category"][0];
                                all_non_named.push_back({ category, key, price });
                            }
                        }
                    }
                    std::sort(all_non_named.begin(), all_non_named.end(),
                        [](const basket_transaction& a, const basket_transaction& b) {
                            return a.price > b.price;
                        });
                    init = true;
                }
            });
            for (auto& opt : g_transaction_mgr.all_transactions) {
                draw->button(opt.name, [=] {
                    g_transaction_mgr.process(opt.hash);
                    });

            }
            });
        draw->submenu_second("Loops", "recovery:money:loops", [] {
            draw->option("one_million_loop");
            draw->option("jobs_loop");
            draw->option("item_loop");
            draw->option("battle_loop");
            draw->seperator("Remove Money");
            draw->option("casino_remove_loop");
            draw->option("betting_loop");
            draw->option("weapon_stash_loop");
        });
        draw->seperator("Quick");
        draw->option("one_million_loop");
        g_transaction_mgr.get("SERVICE_EARN_JOB_BONUS_CRIMINAL_MASTERMIND");
        g_transaction_mgr.get("SERVICE_EARN_CASINO_HEIST_FINALE");
        g_transaction_mgr.get("SERVICE_EARN_JOB_BONUS_HEIST_AWARD");
            
    }
}
