#pragma once
#include "src/utility/common/common.h"

namespace Base::Framework {
	struct veh_preivew {
		str m_dict;
		str m_asset;
	};
	inline std::vector<std::pair<str, veh_preivew>> g_vehicle_previews {
		{ "conada2", {"candc_2023_01", "conada2_b"} },
		{ "raiju", {"candc_2023_01", "raiju_b"} },
		{ "streamer216", {"candc_2023_01", "streamer216_b"} },
		{ "limo2", {"candc_apartments", "limo2_b"} },
		{ "caracara", {"candc_assault", "caracara_b"} },
		{ "menacer", {"candc_battle", "menacer_b"} },
		{ "mule4", {"candc_battle", "mule4_b"} },
		{ "oppressor2", {"candc_battle", "oppressor2_b"} },
		{ "pounder2", {"candc_battle", "pounder2_b"} },
		{ "scramjet", {"candc_battle", "scramjet_b"} },
		{ "strikeforce", {"candc_battle", "strikeforce_b"} },
		{ "blazer2", {"candc_casinoheist", "blazer2_b"} },
		{ "boxville", {"candc_casinoheist", "boxville_b"} },
		{ "burrito2", {"candc_casinoheist", "burrito2_b"} },
		{ "firetruk", {"candc_casinoheist", "firetruk_b"} },
		{ "jb7002", {"candc_casinoheist", "jb7002_b"} },
		{ "lguard", {"candc_casinoheist", "lguard_b"} },
		{ "minitank", {"candc_casinoheist", "minitank_b"} },
		{ "stockade", {"candc_casinoheist", "stockade_b"} },
		{ "zhaba", {"candc_casinoheist", "zhaba_b"} },

		{ "airbus", {"candc_default", "airbus_b"} },
		{ "barracks", {"candc_default", "barracks_b"} },
		{ "boxville4", {"candc_default", "boxville4_b"} },
		{ "bus", {"candc_default", "bus_b"} },
		{ "buzzard", {"candc_default", "buzzard_b"} },
		{ "cargobob", {"candc_default", "cargobob_b"} },
		{ "coach", {"candc_default", "coach_b"} },
		{ "crusader", {"candc_default", "crusader_b"} },
		{ "dubsta3", {"candc_default", "dubsta3_b"} },
		{ "dukes", {"candc_default", "dukes_b"} },
		{ "dump", {"candc_default", "dump_b"} },
		{ "hydra", {"candc_default", "hydra_b"} },
		{ "insurgent", {"candc_default", "insurgent_b"} },
		{ "insurgent2", {"candc_default", "insurgent2_b"} },
		{ "journey", {"candc_default", "journey_b"} },
		{ "marshall", {"candc_default", "marshall_flag20_b"} },
		{ "mesa", {"candc_default", "mesa_b"} },
		{ "mesa3", {"candc_default", "mesa3_b"} },
		{ "monster", {"candc_default", "monster_b"} },
		{ "mule", {"candc_default", "mule_b"} },
		{ "mule3", {"candc_default", "mule3_b"} },
		{ "pbus", {"candc_default", "pbus_b"} },
		{ "rentbus", {"candc_default", "rentbus_b"} },
		{ "rhino", {"candc_default", "rhino_b"} },
		{ "savage", {"candc_default", "savage_b"} },
		{ "technical", {"candc_default", "technical_b"} },
		{ "valkyrie", {"candc_default", "valkyrie_b"} },

		{ "brickade", {"candc_executive1", "brickade_b"} },
		{ "cargobob2", {"candc_executive1", "cargobob2_b"} },

		{ "apc", {"candc_gunrunning", "apc_b"} },
		{ "ardent", {"candc_gunrunning", "ardent_b"} },
		{ "dune3", {"candc_gunrunning", "dune3_b"} },
		{ "halftrack", {"candc_gunrunning", "halftrack_b"} },
		{ "nightshark", {"candc_gunrunning", "nightshark_b"} },
		{ "oppressor", {"candc_gunrunning", "oppressor_b"} },
		{ "tampa3", {"candc_gunrunning", "tampa3_b"} },
		{ "trsmall2", {"candc_gunrunning", "trsmall2_b"} },

		{ "alkonost", {"candc_heist4", "alkonost_b"} },
		{ "annihlator2", {"candc_heist4", "annihlator2_b"} },
		{ "avisa", {"candc_heist4", "avisa_b"} },
		{ "dinghy5", {"candc_heist4", "dinghy5_b"} },
		{ "manchez2", {"candc_heist4", "manchez2_b" } },
		{ "patrolboat", {"candc_heist4", "patrolboat_b" } },
		{ "sparrow3", {"candc_heist4", "sparrow3_b" } },
		{ "squaddie", {"candc_heist4", "squaddie_b" } },
		{ "toreador", {"candc_heist4", "toreador_b" } },
		{ "verus", {"candc_heist4", "verus_b" } },
		{ "vetir", { "candc_heist4", "vetir_b" } },
		{ "winky", { "candc_heist4", "winky_b" } },

		{ "blazer5", { "candc_importexport", "blazer5_b" } },
		{ "boxville5", { "candc_importexport", "boxville5_b" } },
		{ "dune5", { "candc_importexport", "dune5_b" } },
		{ "phantom2", { "candc_importexport", "phantom2_b" } },
		{ "ruiner2", { "candc_importexport", "ruiner2_b" } },
		{ "technical2", { "candc_importexport", "technical2_b" } },
		{ "voltic2", { "candc_importexport", "voltic2_b" } },
		{ "wastlndr", { "candc_importexport", "wastlndr_b" } },

		{ "bombushka", { "candc_smuggler", "bombushka_b" } },
		{ "hunter", { "candc_smuggler", "hunter_b" } },
		{ "lazer", { "candc_smuggler", "lazer_b" } },
		{ "mogul", { "candc_smuggler", "mogul_b" } },
		{ "molotok", { "candc_smuggler", "molotok_b" } },
		{ "nokota", { "candc_smuggler", "nokota_b" } },
		{ "pyro", { "candc_smuggler", "pyro_b" } },
		{ "rogue", { "candc_smuggler", "rogue_b" } },
		{ "starling", { "candc_smuggler", "starling_b" } },
		{ "tula", { "candc_smuggler", "tula_b" } },

		{ "akula", { "candc_xmas2017", "akula_b" } },
		{ "barrage", { "candc_xmas2017", "barrage_b" } },
		{ "chernobog", { "candc_xmas2017", "chernobog_b" } },
		{ "deluxo", { "candc_xmas2017", "deluxo_b" } },
		{ "khanjali", { "candc_xmas2017", "khanjali_b" } },
		{ "riot2", { "candc_xmas2017", "riot2_b" } },
		{ "stromberg", { "candc_xmas2017", "stromberg_b" } },
		{ "thruster", { "candc_xmas2017", "thruster_b" } },
		{ "volatol", { "candc_xmas2017", "volatol_b" } },

		{ "brickade2", { "candc_xmas2022", "brickade2_b" } },
		{ "taxi", { "candc_xmas2022", "taxi_b" } },

		{ "dinghy3", { "dock_default", "dinghy3_b" } },
		{ "jetmax", { "dock_default", "jetmax_b" } },
		{ "marquis", { "dock_default", "marquis_b" } },
		{ "seashark", { "dock_default", "seashark_b" } },
		{ "speeder", { "dock_default", "speeder_b" } },
		{ "squalo", { "dock_default", "squalo_b" } },
		{ "sub2", { "dock_default", "sub2_b" } },
		{ "suntrap", { "dock_default", "suntrap_b" } },
		{ "toro", { "dock_default", "toro_b" } },
		{ "tropic", { "dock_default", "tropic_b" } },

		{ "tug", { "dock_dlc_executive1", "tug_b" } },
		{ "longfin", { "dock_dlc_heist4", "longfin_b" } },
		{ "longfin", { "dock_dlc_heist4", "longfin_b" } },

		{ "annihl", { "elt_default", "annihl_b" } },
		{ "cuban800", { "elt_default", "cuban800_b" } },
		{ "dodo", { "elt_default", "dodo_b" } },
		{ "duster", { "elt_default", "duster_b" } },
		{ "frogger", { "elt_default", "frogger_b" } },
		{ "luxor", { "elt_default", "luxor_b" } },
		{ "mammatus", { "elt_default", "mammatus_b" } },
		{ "maverick", { "elt_default", "maverick_b" } },
		{ "shamal", { "elt_default", "shamal_b" } },
		{ "stunt", { "elt_default", "stunt_b" } },
		{ "titan", { "elt_default", "titan_b" } },
		{ "velum", { "elt_default", "velum_b" } },
		{ "velum2", { "elt_default", "velum2_b" } },

		{ "svolito", { "elt_dlc_apartments", "svolito_b" } },
		{ "svolito2", { "elt_dlc_apartments", "svolito2_b" } },

		{ "sparrow", { "elt_dlc_assault", "sparrow_b" } },

		{ "blimp3", { "elt_dlc_battle", "blimp3_blimp3_elt_1_b" } },

		{ "vestra", { "elt_dlc_business", "vestra_b" } },

		{ "nimbus", { "elt_dlc_executive1", "nimbus_b" } },
		{ "volatus", { "elt_dlc_executive1", "volatus_b" } },

		{ "luxor2", { "elt_dlc_luxe", "luxor2_b" } },
		{ "swift2", { "elt_dlc_luxe", "swift2_b" } },

		{ "besra", { "elt_dlc_pilot", "besra_b" } },
		{ "miljet", { "elt_dlc_pilot", "miljet_b" } },
		{ "swift", { "elt_dlc_pilot", "swift_elt_dlc_liv1_b" } },

		{ "alphaz1", { "elt_dlc_smuggler", "alphaz1_b" } },
		{ "havok", { "elt_dlc_smuggler", "havok_b" } },
		{ "howard", { "elt_dlc_smuggler", "howard_b" } },
		{ "microlight", { "elt_dlc_smuggler", "microlight_b" } },
		{ "seabreeze", { "elt_dlc_smuggler", "seabreeze_b" } },

		{ "conada", { "elt_dlc_sum2", "conada_b" } },

		{ "adder", { "lgm_default", "adder_b" } },
		{ "banshee", { "lgm_default", "banshee_b" } },
		{ "bullet", { "lgm_default", "bullet_b" } },
		{ "carbon", { "lgm_default", "carbon_b" } },
		{ "carboniz", { "lgm_default", "carboniz_b" } },
		{ "cheetah", { "lgm_default", "cheetah_b" } },
		{ "cogcabri", { "lgm_default", "cogcabri_b" } },
		{ "comet2", { "lgm_default", "comet2_b" } },
		{ "coquette", { "lgm_default", "coquette_b" } },
		{ "elegy2", { "lgm_default", "elegy2_b" } },
		{ "entityxf", { "lgm_default", "entityxf_b" } },
		{ "exemplar", { "lgm_default", "exemplar_b" } },
		{ "feltzer", { "lgm_default", "feltzer_b" } },
		{ "hotknife", { "lgm_default", "hotknife_b" } },
		{ "infernus", { "lgm_default", "infernus_b" } },
		{ "jb700", { "lgm_default", "jb700_b" } },
		{ "khamel", { "lgm_default", "khamel_b" } },
		{ "monroe", { "lgm_default", "monroe_b" } },
		{ "ninef", { "lgm_default", "ninef_b" } },
		{ "ninef2", { "lgm_default", "ninef2_b" } },
		{ "ninef2", { "lgm_default", "ninef2_b" } },
		{ "rapidgt", { "lgm_default", "rapidgt_b" } },
		{ "rapidgt2", { "lgm_default", "rapidgt2_b" } },
		{ "stinger", { "lgm_default", "stinger_b" } },
		{ "stingerg", { "lgm_default", "stingerg_b" } },
		{ "superd", { "lgm_default", "superd_b" } },
		{ "surano_convertable", { "lgm_default", "surano_convertable_b" } },
		{ "vacca", { "lgm_default", "vacca_b" } },
		{ "voltic_tless", { "lgm_default", "voltic_tless_b" } },
		{ "ztype", { "lgm_default", "ztype_b" } },

		{ "buffalo5", { "lgm_dlc_2023_01", "buffalo5_b" } },
		{ "coureur", { "lgm_dlc_2023_01", "coureur_b" } },
		{ "stingertt", { "lgm_dlc_2023_01", "stingertt_b" } },

		{ "baller3", { "lgm_dlc_apartments", "baller3_web_vehicle_regular_b" } },
		{ "cog55", { "lgm_dlc_apartments", "cog55_web_vehicle_regular_b" } },
		{ "cognosc", { "lgm_dlc_apartments", "cognosc_web_vehicle_regular_b" } },
		{ "mamba", { "lgm_dlc_apartments", "mamba_b" } },
		{ "niteshad", { "lgm_dlc_apartments", "niteshad_b" } },
		{ "schafter3", { "lgm_dlc_apartments", "schafter3_web_vehicle_regular_b" } },
		{ "schafter4", { "lgm_dlc_apartments", "schafter4_web_vehicle_regular_b" } },
		{ "verlier", { "lgm_dlc_apartments", "verlier_b" } },

		{ "clique", { "lgm_dlc_arena", "clique_b" } },
		{ "cliquexmas", { "lgm_dlc_arena", "cliquexmas_b" } },
		{ "deveste", { "lgm_dlc_arena", "deveste_b" } },
		{ "deviant", { "lgm_dlc_arena", "deviant_b" } },
		{ "italigto", { "lgm_dlc_arena", "italigto_b" } },
		{ "schlagen", { "lgm_dlc_arena", "schlagen_b" } },
		{ "toros", { "lgm_dlc_arena", "toros_b" } },

		{ "entity2", { "lgm_dlc_assault", "entity2_b" } },
		{ "flashgt", { "lgm_dlc_assault", "flashgt_b" } },
		{ "gb200", { "lgm_dlc_assault", "gb200_b" } },
		{ "jester3", { "lgm_dlc_assault", "jester3_b" } },
		{ "taipan", { "lgm_dlc_assault", "taipan_b" } },
		{ "tezeract", { "lgm_dlc_assault", "tezeract_b" } },
		{ "tyrant", { "lgm_dlc_assault", "tyrant_b" } },

		{ "freecrawler", { "lgm_dlc_battle", "freecrawler_b" } },
		{ "stafford", { "lgm_dlc_battle", "stafford_b" } },
		{ "swinger", { "lgm_dlc_battle", "swinger_b" } },

		{ "hakuchou2", { "lgm_dlc_biker", "hakuchou2_b" } },
		{ "raptor", { "lgm_dlc_biker", "raptor_b" } },
		{ "shotaro", { "lgm_dlc_biker", "shotaro_b" } },

		{ "alpha", { "lgm_dlc_business", "alpha_b" } },
		{ "jester", { "lgm_dlc_business", "jester_b" } },
		{ "turismor", { "lgm_dlc_business", "turismor_b" } },

		{ "banshee_tless", { "lgm_dlc_business2", "banshee_tless_b" } },
		{ "coquette_tless", { "lgm_dlc_business2", "coquette_tless_b" } },
		{ "huntley", { "lgm_dlc_business2", "huntley_b" } },
		{ "massacro", { "lgm_dlc_business2", "massacro_b" } },
		{ "stinger_tless", { "lgm_dlc_business2", "stinger_tless_b" } },
		{ "thrust", { "lgm_dlc_business2", "thrust_b" } },
		{ "voltic_htop", { "lgm_dlc_business2", "voltic_htop_b" } },
		{ "zentorno", { "lgm_dlc_business2", "zentorno_b" } },

		{ "formula", { "lgm_dlc_casinoheist", "formula_b" } },
		{ "formula2", { "lgm_dlc_casinoheist", "formula2_b" } },
		{ "furia", { "lgm_dlc_casinoheist", "furia_b" } },
		{ "imorgon", { "lgm_dlc_casinoheist", "imorgon_b" } },
		{ "komoda", { "lgm_dlc_casinoheist", "komoda_b" } },
		{ "rebla", { "lgm_dlc_casinoheist", "rebla_b" } },
		{ "stryder", { "lgm_dlc_casinoheist", "stryder_b" } },
		{ "vstr", { "lgm_dlc_casinoheist", "vstr_b" } },

		{ "bestiagts", { "lgm_dlc_executive1", "bestiagts_b" } },
		{ "fmj", { "lgm_dlc_executive1", "fmj_b" } },
		{ "pfister811", { "lgm_dlc_executive1", "pfister811_b" } },
		{ "prototipo", { "lgm_dlc_executive1", "prototipo_b" } },
		{ "reaper", { "lgm_dlc_executive1", "reaper_b" } },
		{ "seven70", { "lgm_dlc_executive1", "seven70_b" } },
		{ "windsor2", { "lgm_dlc_executive1", "windsor2_b" } },
		{ "xls", { "lgm_dlc_executive1", "xls_web_vehicle_regular_b" } },

		{ "cheetah2", { "lgm_dlc_gunrunning", "cheetah2_b" } },
		{ "torero", { "lgm_dlc_gunrunning", "torero_b" } },
		{ "vagner", { "lgm_dlc_gunrunning", "vagner_b" } },
		{ "xa21", { "lgm_dlc_gunrunning", "xa21_b" } },

		{ "casco", { "lgm_dlc_heist", "casco_b" } },
		{ "lectro", { "lgm_dlc_heist", "lectro_b" } },

		{ "italirsx", { "lgm_dlc_heist4", "italirsx_b" } },

		{ "penetrator", { "lgm_dlc_importexport", "penetrator_b" } },
		{ "tempesta", { "lgm_dlc_importexport", "tempesta_b" } },

		{ "furore", { "lgm_dlc_lts_creator", "furore_b" } },

		{ "brawler", { "lgm_dlc_luxe", "brawler_b" } },
		{ "chino", { "lgm_dlc_luxe", "chino_b" } },
		{ "coquette3", { "lgm_dlc_luxe", "coquette3_b" } },
		{ "feltzer3", { "lgm_dlc_luxe", "feltzer3_b" } },
		{ "osiris", { "lgm_dlc_luxe", "osiris_b" } },
		{ "t20", { "lgm_dlc_luxe", "t20_b" } },
		{ "vindicator", { "lgm_dlc_luxe", "vindicator_b" } },
		{ "virgo", { "lgm_dlc_luxe", "virgo_b" } },
		{ "windsor", { "lgm_dlc_luxe", "windsor_windsor_lgm_1_b" } },

		{ "coquette2", { "lgm_dlc_pilot", "coquette2_b" } },
		{ "coquette2_tless", { "lgm_dlc_pilot", "coquette2_tless_b" } },

		{ "astron", { "lgm_dlc_security", "astron_b" } },
		{ "baller7", { "lgm_dlc_security", "baller7_b" } },
		{ "champion", { "lgm_dlc_security", "champion_b" } },
		{ "cinquemila", { "lgm_dlc_security", "cinquemila_b" } },
		{ "comet7", { "lgm_dlc_security", "comet7_b" } },
		{ "deity", { "lgm_dlc_security", "deity_b" } },
		{ "ignus", { "lgm_dlc_security", "ignus_b" } },
		{ "jubilee", { "lgm_dlc_security", "jubilee_b" } },
		{ "reever", { "lgm_dlc_security", "reever_b" } },

		{ "cyclone", { "lgm_dlc_smuggler", "cyclone_b" } },
		{ "rapidgt3", { "lgm_dlc_smuggler", "rapidgt3_b" } },
		{ "visione", { "lgm_dlc_smuggler", "visione_b" } },

		{ "gp1", { "lgm_dlc_specialraces", "gp1_b" } },
		{ "infernus2", { "lgm_dlc_specialraces", "infernus2_b" } },
		{ "ruston", { "lgm_dlc_specialraces", "ruston_b" } },
		{ "turismo2", { "lgm_dlc_specialraces", "turismo2_b" } },

		{ "le7b", { "lgm_dlc_stunt", "le7b_lms_le7b_livery_1_b" } },
		{ "lynx", { "lgm_dlc_stunt", "lynx_lms_lynx_livery_1_b" } },
		{ "sheava", { "lgm_dlc_stunt", "sheava_lms_sheava_livery_1_b" } },
		{ "tyrus", { "lgm_dlc_stunt", "tyrus_lms_tyrus_livery_1_b" } },

		{ "conada", { "lgm_dlc_sum2", "conada_b" } },
		{ "corsita", { "lgm_dlc_sum2", "corsita_b" } },
		{ "lm87", { "lgm_dlc_sum2", "lm87_b" } },
		{ "omnisegt", { "lgm_dlc_sum2", "omnisegt_b" } },
		{ "sm722", { "lgm_dlc_sum2", "sm722_b" } },
		{ "tenf", { "lgm_dlc_sum2", "tenf_b" } },	
		{ "torero2", { "lgm_dlc_sum2", "torero2_b" } },

		{ "coquette4", { "lgm_dlc_summer2020", "coquette4_b" } },
		{ "openwheel1", { "lgm_dlc_summer2020", "openwheel1_b" } },
		{ "openwheel2", { "lgm_dlc_summer2020", "openwheel2_b" } },
		{ "tigon", { "lgm_dlc_summer2020", "tigon_b" } },

		{ "comet6", { "lgm_dlc_tuner", "comet6_b" } },
		{ "cypher", { "lgm_dlc_tuner", "cypher_b" } },
		{ "euros", { "lgm_dlc_tuner", "euros_b" } },
		{ "growler", { "lgm_dlc_tuner", "growler_b" } },
		{ "jester4", { "lgm_dlc_tuner", "jester4_b" } },
		{ "tailgater2", { "lgm_dlc_tuner", "tailgater2_b" } },
		{ "vectre", { "lgm_dlc_tuner", "vectre_b" } },
		{ "zr350", { "lgm_dlc_tuner", "zr350_b" } },

		{ "roosevelt", { "lgm_dlc_valentines", "roosevelt_b" } },
		{ "roosevelt2", { "lgm_dlc_valentines2", "roosevelt2_b" } },

		{ "drafter", { "lgm_dlc_vinewood", "drafter_b" } },
		{ "emerus", { "lgm_dlc_vinewood", "emerus_b" } },
		{ "jugular", { "lgm_dlc_vinewood", "jugular_b" } },
		{ "krieger", { "lgm_dlc_vinewood", "krieger_b" } },
		{ "locust", { "lgm_dlc_vinewood", "locust_b" } },
		{ "neo", { "lgm_dlc_vinewood", "neo_b" } },
		{ "novak", { "lgm_dlc_vinewood", "novak_b" } },
		{ "paragon", { "lgm_dlc_vinewood", "paragon_b" } },
		{ "rrocket", { "lgm_dlc_vinewood", "rrocket_b" } },
		{ "s80", { "lgm_dlc_vinewood", "s80_b" } },
		{ "thrax", { "lgm_dlc_vinewood", "thrax_b" } },
		{ "zorrusso", { "lgm_dlc_vinewood", "zorrusso_b" } },

		{ "autarch", { "lgm_dlc_xmas2017", "autarch_b" } },
		{ "comet4", { "lgm_dlc_xmas2017", "comet4_b" } },
		{ "comet5", { "lgm_dlc_xmas2017", "comet5_b" } },
		{ "gt500", { "lgm_dlc_xmas2017", "gt500_b" } },
		{ "hustler", { "lgm_dlc_xmas2017", "hustler_b" } },
		{ "neon", { "lgm_dlc_xmas2017", "neon_b" } },
		{ "pariah", { "lgm_dlc_xmas2017", "pariah_b" } },
		{ "raiden", { "lgm_dlc_xmas2017", "raiden_b" } },
		{ "revolter", { "lgm_dlc_xmas2017", "revolter_b" } },
		{ "savestra", { "lgm_dlc_xmas2017", "savestra_b" } },
		{ "sc1", { "lgm_dlc_xmas2017", "sc1_b" } },
		{ "streiter", { "lgm_dlc_xmas2017", "streiter_b" } },
		{ "viseris", { "lgm_dlc_xmas2017", "viseris_b" } },
		{ "z190", { "lgm_dlc_xmas2017", "z190_b" } },

		{ "broadway", { "lgm_dlc_xmas2022", "broadway_b" } },
		{ "entity3", { "lgm_dlc_xmas2022", "entity3_b" } },
		{ "panthere", { "lgm_dlc_xmas2022", "panthere_b" } },
		{ "powersurge", { "lgm_dlc_xmas2022", "powersurge_b" } },
		{ "r300", { "lgm_dlc_xmas2022", "r300_b" } },
		{ "virtue", { "lgm_dlc_xmas2022", "virtue_b" } },
	};
}