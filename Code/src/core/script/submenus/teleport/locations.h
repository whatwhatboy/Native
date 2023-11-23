#pragma once
#include "src/utility/common/common.h"

namespace Base::locations {
	struct location {
		str m_name{};
		float m_x{};
		float m_y{};
		float m_z{};
	};
	std::vector<location> clothing_stores = {
			{"Portola Dr", -717.7412, -157.45372, 36.98848},
			{"San Andreas Ave", -1203.4531, -779.71606, 17.331877},
			{"Palomino Ave", -816.63257, -1081.0043, 11.129381},
			{"Innocence Blvd", 86.37321, -1391.4883, 29.22132},
			{"Sinner St", 416.34998, -807.63043, 29.37371},
			{"Hawick Ave", 128.25337, -208.36128, 54.56384},
			{"Las Lagunas Blvd", -153.05571, -306.84018, 38.662342},
			{"Cougar Ave", -1457.5942, -230.37291, 49.33974},
			{"Route 66", 1197.8345, 2701.9758, 38.15611},
			{"Paleto Blvd", -2.5890994, 6518.673, 31.533188},
			{"Grapeseed Main St", 1685.6029, 4820.4297, 41.991486},
			{"Great Ocean Hw", -3167.559, 1057.4398, 20.85868},
			{"Route 66 2", -1094.2131, 2704.4207, 19.071579}
	};
	std::vector<location> los_santos_customs = {
		{"Burton", -1145.980, -1991.769, 13.163},
		{"Strawberry", 731.524, -1088.811, 23.226},
		{"La Mesa", 477.440, -1313.230, 29.230},
		{"Los Santos International Airport", -1143.814, -1991.130, 13.180},
		{"West Vinewood", -448.892, -1695.792, 18.139},
		{"Rockford Hills", -1152.678, -2008.684, 13.180},
		{"Grand Senora Desert", 110.414, 6625.628, 31.787},
		{"Harmony", 1173.466, 2644.987, 37.782},
		{"Paleto Bay", -1491.002, 4975.068, 63.944}
	};
	std::vector<location> landmarks = {
		{"Los Santos International Airport", -1034.6, -2733.4, 13.8},
		{"Del Perro Pier", -1857.0, -1220.6, 13.3},
		{"Vinewood Sign", 722.3, 1207.5, 345.6},
		{"Observatory", -438.8, 1076.1, 352.4},
		{"Mount Chiliad", 425.4, 5614.3, 766.5},
		{"Pacific Bluffs Country Club", -2956.3, 478.2, 15.0},
		{"Richman Mansion", -1351.0, 190.6, 56.1},
		{"FIB Building", 135.7, -749.5, 258.2},
		{"Eclipse Towers", -775.8, 341.4, 213.8},
		{"Lombank West", -1579.8, -565.7, 108.5},
		{"Pillbox Hill Medical Center", 307.1, -590.4, 43.3},
		{"Lifeinvader Office", -1081.9, -263.5, 37.8},
		{"Weazel Plaza", -909.8, -444.2, 120.0},
		{"Palmer-Taylor Power Station", 2720.5, 1577.0, 83.6},
		{"Galileo Observatory", -438.8, 1076.1, 352.4},
		{"Los Santos City Hall", -547.2, -199.9, 38.2},
		{"Vinewood Bowl", 687.3, 1243.6, 337.3},
		{"Mirror Park", 1056.2, -3041.6, 5.9}
	};

	std::vector<location> inside = {
		{"Bahama Mamas West", -1388.0, -618.4, 30.8},
		{"The Music Locker", -1697.1, -562.1, 146.0},
		{"Vanilla Unicorn Dressing Room", 121.2, -1289.2, 29.3},
		{"Bahama Mamas Dressing Room", -1385.6, -624.1, 30.8},
		{"Diamond Casino & Resort", 922.7, 46.4, 81.1},
		{"Vanilla Unicorn Manager's Office", 117.7, -1288.8, 29.3},
		{"Bahama Mamas Manager's Office", -1386.3, -622.3, 30.8},


		{"Eclipse Towers, Apartment 3", -774.0, 334.4, 160.6},
		{"Del Perro Heights, Apartment 7", -1477.1, -538.1, 55.5},

		// Offices
		{"Maze Bank Tower", -75.5, -826.3, 243.4},
		{"Arcadius Business Center", -141.4, -615.5, 168.9},

		// Bars
		{"Tequila-la", -561.7, 274.5, 82.2},
		{"O'Neil's Farm", 2444.3, 4973.4, 45.8},
		{"Yellow Jack Inn", 1985.7, 3053.9, 47.2},

		// Strip Clubs
		{"Vanilla Unicorn", 126.1, -1298.6, 29.2},
		{"Bahama Mamas", -1388.6, -618.0, 30.8},
	};
	std::vector<location> police_stations = {
		{"Los Santos", 436.1, -982.3, 30.7},
		{"Mission Row", 431.2, -981.9, 30.7}
	};
	std::vector<location> hospitals = {
		{"Mount Zonah", 295.2, -1446.0, 29.9},
		{"Pillbox Hill", 307.3, -1439.9, 29.8}
	};

	std::vector<location> airstrips {
			{ "LSIA", -1328.78f, -2197.64f, 13.94f },
			{ "Grapeseed", 2136.51f, 4810.95f, 41.20f }
	};

	std::vector<location> gun_shops = {
		{"Vespucci Beach", -662.040, -935.106, 20.829},
		{"Cypress Flats", 811.523, -2157.350, 29.619},
		{"Strawberry", 1693.448, 3759.685, 34.705},
		{"Tataviam Mountains", 254.491, -48.120, 69.941},
		{"El Burro Heights", 2567.641, 294.452, 107.735},
		{"Paleto Bay", -331.366, 6082.516, 31.454}
	};

	std::vector<location> tatto_shops = {
		{"Vespucci Beach", -1153.045, -1425.367, 4.954},
		{"Hawick", -298.389, 6227.558, 31.489},
		{"Alta", 1322.402, -1651.573, 52.275},
		{"Mirror Park", 1206.785, -517.901, 66.206},
		{"Grapeseed", 1697.051, 4829.229, 41.063},
		{"Sandy Shores", 1863.867, 3749.758, 33.031}
	};
}