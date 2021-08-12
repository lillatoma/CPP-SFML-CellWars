#include "Interfaces.h"

buildingdata_t buildings[100];

#pragma region culturepoints
//culture points
int CP1[] = { 1,1,2,2,2,3,4,4,5,6,7,9,11,13,15,18,22,27,32,38,46 };
int CP2[] = { 2,3,3,4,5,6,7,9,10,12,15,18,21,26,31,37,44,53,64,77 };
int CP3[] = { 3 };
int CP4[] = { 4,4,5,6,7,9,11,13,15,19,22,27,32,39,46,55,67,80,96,115 };
int CP5[] = { 5,6,7,8,10,12,14,17,21,25,30,36,43,51,62,74,89,106,128,153 };
int CP6[] = { 6,7,9,10,12,15,18,21,26,31,37,45,53,64,77,92,111,133,160,192 };
int CP7[] = { 7,9,10,12,15,18,21,26,31,37,45,53,64,77,92,111,133,160,192,230 };
#pragma endregion
#pragma region pops
//population
int P0[] = { 0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20 };
int P1[] = { 1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,22,24,26,28,30 };
int P2[] = { 2,3,4,5,6,8,10,12,14,16,18,20,22,24,26,29,32,35,38,41 };
int P3[] = { 3,5,7,9,11,13,15,17,19,21,24,27,30,33,36,39,42,45,48,51 };
int P4[] = { 4,6,8,10,12,15,18,21,24,27,30,33,36,39,42,46,50,54,58,62 };
int P5[] = { 5,8,11,14,17,20,23,26,29,32,36,40,44,48,52,56,60,64,68,72 };
int P6[] = { 6,9,12,15,18,22,26,30,34,38,42,46,50,54,58,63,68,73,78,83 };
#pragma endregion
#pragma region storage
//storage lvalue
int ST[] = { 0,1200,1700,2300,3100,4000,5000,6300,7800,9600,11800,14400,17600,21600,25900,31300,37900,45700,55100,66400,80000 };
int CR[] = { 0,200,260,340,440,560,720,920,1200,1540,2000 };
#pragma endregion
#pragma region timemodify
//timemodifiers
float BT[] = { 0.25, 1,1.04,1.08,1.12,1.16,1.2,1.25,1.29,1.34,1.39,1.44,1.5,1.55,1.61,1.67,1.73,1.8,1.87,1.93,2.01 };
#pragma endregion
#pragma region passivedefence
//passive defence
int RES_DEF[] = { 0,2,8,18,32,50,72,98,128,162,200,242,288,338,392,450,512,578,648,722,800 };
#pragma endregion

resource_t FiveClamp(resource_t res)
{
	resource_t best;
	best.Wood = (int)res.Wood - (int)res.Wood % 5;
	best.Clay = (int)res.Clay - (int)res.Clay % 5;
	best.Iron = (int)res.Iron - (int)res.Iron % 5;
	best.Wheat = (int)res.Wheat - (int)res.Wheat % 5;
	return best;
}

resource_t IBuildings::CalculateNext(resource_t &ls, float multi)
{

	ls.Wood *= multi;
	ls.Clay *= multi;
	ls.Iron *= multi;
	ls.Wheat *= multi;
	return ls;
}

void CalculateLevels(resource_t start, resource_t res[100], float multi, int max_l)
{
	res[0] = start;
	auto help = start;
	res[0].Wood = FiveClamp(help).Wood;
	res[0].Clay = FiveClamp(help).Clay;
	res[0].Iron = FiveClamp(help).Iron;
	res[0].Wheat = FiveClamp(help).Wheat;
	for (int i = 1; i < max_l; i++)
	{
		IBuildings::CalculateNext(help, multi);
		res[i].Wood = FiveClamp(help).Wood;
		res[i].Clay = FiveClamp(help).Clay;
		res[i].Iron = FiveClamp(help).Iron;
		res[i].Wheat = FiveClamp(help).Wheat;
	}
	for (int i = 1; i < max_l; i++)
	{
	}

}

char* IBuildings::GetBuildingName(int id)
{
	static char* l[] = { "Main Building", "Embassy", "Cranny", "Marketplace", "Town Hall", "Residence", "Palace", "Treasury", "Trade Office", "Brewery", "Horse-Drinking Through", "Rally point", "Stone Wall", "Palisade", "Earth wall", "Barracks", "Academy", "Blacksmith", "Stable", "Stonemason", "Workshop", "Hero's mansion", "Tournament Square", "Great Barracks", "Great Stable", "Warehouse", "Granary", "Sawmill", "Brickyard", "Iron Foundry", "Mill", "Bakery", "Woodcutter", "Clay Pit", "Iron Mine", "Wheat Farm" };

	return l[id];
}

void IBuildings::CreateAllBuildings()
{
	for (int i = 0; i < 100; i++)
	{
		buildings[i].max_possible_level = -1;
	}
	//RESOURCES
	{
		//WOOD
		{
			int Time[20] = { 4,10,19,35,59,98,160,259,419,674,18 * 60 + 1,28 * 60 + 54,46 * 60 + 18,74 * 60 + 8,118 * 60 + 40,189 * 60 + 55,303 * 60 + 56,486 * 60 + 21,778 * 60 + 13,1245 * 60 + 12 };

			resource_t costs[100];
			CalculateLevels(resource_t(40, 100, 50, 60), costs, 1.67, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P2[i], CP1[i]);
				AddLevel(&buildings[WOOD], entry, i);
			}
		}
		//CLAY
		{
			int Time[20] = { 4,9,18,32,54,91,149,242,390,628,1008,26 * 60 + 56,43 * 60 + 10,69 * 60 + 7,6639,177 * 60 + 7,283 * 60 + 26,453 * 60 + 33,725 * 60 + 45,1161 * 60 + 15 };

			resource_t costs[100];
			CalculateLevels(resource_t(80, 40, 80, 40), costs, 1.67, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P2[i], CP1[i]);
				AddLevel(&buildings[CLAY], entry, i);
			}
		}
		//IRON
		{
			int Time[20] = { 7,15,27,48,80,131,213,344,555,14 * 60 + 51,23 * 60 + 50,38 * 60 + 11,61 * 60 + 9,97 * 60 + 54,156 * 60 + 42,250 * 60 + 46,401 * 60 + 17,642 * 60 + 7,1027 * 60 + 27,1643 * 60 + 59 };

			resource_t costs[100];
			CalculateLevels(resource_t(100, 80, 30, 60), costs, 1.67, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P3[i], CP1[i]);
				AddLevel(&buildings[IRON], entry, i);
			}
		}
		//CROP
		{
			int Time[20] = { 3,7,15,27,47,78,129,210,340,728,14 * 60 + 40,23 * 60 + 31,37 * 60 + 41,60 * 60 + 22,96 * 60 + 39,154 * 60 + 41,247 * 60 + 34,396 * 60 + 10,633 * 60 + 55,1014 * 60 + 20 };

			resource_t costs[100];
			CalculateLevels(resource_t(70, 90, 70, 20), costs, 1.67, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P0[i], CP1[i]);
				AddLevel(&buildings[WHEAT], entry, i);
			}
		}
		//MILL
		{
			int Time[20] = { 10 * 3,22 * 3,39 * 3,66 * 3,106 * 3 };

			resource_t costs[100];
			CalculateLevels(resource_t(500, 440, 380, 1240), costs, 1.800, 5);

			for (int i = 0; i < 5; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P3[i], CP1[i]);
				AddLevel(&buildings[MILL], entry, i);
			}
		}
		//CLAYBONUS
		{
			int Time[20] = { 15 * 3,30 * 3,52 * 3,85 * 3,134 * 3 };

			resource_t costs[100];
			CalculateLevels(resource_t(440, 480, 320, 50), costs, 1.800, 5);

			for (int i = 0; i < 5; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P3[i], CP1[i]);
				AddLevel(&buildings[CLAYBONUS], entry, i);
			}
		}
		//WOODBONUS
		{
			int Time[20] = { 16 * 3,31 * 3,54 * 3,88 * 3,138 * 3 };

			resource_t costs[100];
			CalculateLevels(resource_t(520, 380, 290, 90), costs, 1.800, 5);

			for (int i = 0; i < 5; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P4[i], CP1[i]);
				AddLevel(&buildings[WOODBONUS], entry, i);
			}
		}
		//IRONBONUS
		{
			int Time[20] = { 68,122,203,324,506 };

			resource_t costs[100];
			CalculateLevels(resource_t(200, 450, 510, 120), costs, 1.800, 5);

			for (int i = 0; i < 5; i++)
			{
				int asd[] = { 6,3,3,3,3 };
				auto entry = CreateEntry(costs[i], Time[i], asd[i], CP1[i]);
				AddLevel(&buildings[IRONBONUS], entry, i);
			}
		}
		//BAKERY
		{
			int Time[20] = { 61,112,188,302,473 };

			resource_t costs[100];
			CalculateLevels(resource_t(1200, 1480, 870, 1600), costs, 1.800, 5);

			for (int i = 0; i < 5; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P4[i], CP1[i]);
				AddLevel(&buildings[BAKERY], entry, i);
			}
		}
		//WAREHOUSE
		{
			int Time[] = { 33,43,55,69,85,104,126,151,180,214,253,299,352,413,484,567,662,774,902,1052 };

			resource_t costs[100];
			CalculateLevels(resource_t(130, 160, 90, 40), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P1[i], CP1[i]);
				AddLevel(&buildings[WAREHOUSE], entry, i);
			}
		}
		//GRANARY
		{
			int Time[] = { 26,36,46,59,73,90,109,132,158,219,224,265,312,367,431,505,591,690,806,940 };

			resource_t costs[100];
			CalculateLevels(resource_t(80, 100, 70, 20), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P1[i], CP1[i]);
				AddLevel(&buildings[GRANARY], entry, i);
			}
		}



	}
	//INFRASTRUCTURE
	{
		//MAIN
		{
			int Time[20] = { 34,44,54,64,76,90,105,121,139,159,182,209,235,266,301,339,382,430,484,543 };
			resource_t costs[100];
			CalculateLevels(resource_t(70, 40, 60, 20), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P2[i], CP2[i]);
				AddLevel(&buildings[MAIN], entry, i);
			}
		}

		//MEGBASSY
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(180, 130, 150, 80), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P3[i], CP5[i]);
				AddLevel(&buildings[EMBASSY], entry, i);
			}
		}
		//cranny
		{
			int Time[20] = { 5,11,17,25,34,44,57,71,87,107 };
			resource_t costs[100];
			CalculateLevels(resource_t(40, 50, 30, 10), costs, 1.28, 20);

			for (int i = 0; i < 10; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P0[i], CP1[i]);
				AddLevel(&buildings[CRANNY], entry, i);
			}
		}
		//MARKET
		{
			int Time[20] = { 30,40,51,64,79,97,118,141,169,201,239,282,332,390,458,536,627,732,854,996 };
			resource_t costs[100];
			CalculateLevels(resource_t(80, 70, 120, 70), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P4[i], CP4[i]);
				AddLevel(&buildings[MARKETPLACE], entry, i);
			}
		}
		//TOWN HALL
		{
			int Time[20] = { 188,246,291,342,402,472,552,645,12 * 60 + 34,14 * 60 + 39,17 * 60 + 05,19 * 60 + 54,23 * 60 + 11,26 * 60 + 58,31 * 60 + 22,36 * 60 + 28,42 * 60 + 23,49 * 60 + 15,57 * 60 + 13,66 * 60 + 28 };
			resource_t costs[100];
			CalculateLevels(resource_t(1250, 1110, 1260, 600), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P4[i], CP6[i]);
				AddLevel(&buildings[TOWNHALL], entry, i);
			}
		}
		//RESIDENCE
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(580, 460, 350, 180), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P1[i], CP2[i]);
				AddLevel(&buildings[RESIDENCE], entry, i);
			}
		}
		//PALACE
		{
			int Time[20] = { 83, 101, 123,147,176,209,248,292,344,404,544,555,649,12 * 60 + 37, 14 * 60 + 44,17 * 60 + 10,1200,23 * 60 + 17,27 * 60 + 5,31 * 60 + 31 };
			resource_t costs[100];
			CalculateLevels(resource_t(550, 800, 750, 250), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P1[i], CP6[i]);
				AddLevel(&buildings[PALACE], entry, i);
			}
		}
		//TRADEOFFICE
		{
			int Time[] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(580, 460, 350, 180), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P3[i], CP4[i]);
				AddLevel(&buildings[TRADEOFFICE], entry, i);
			}
		}
		//TREASURY
		{
			int Time[] = { 133,159,190,225,266,315,369,503,508,594,694,13 * 60 + 31,15 * 60 + 45,18 * 60 + 22,21 * 60 + 23,24 * 60 + 53,28 * 60 + 57,33 * 60 + 40,39 * 60 + 9,45 * 60 + 29 };
			resource_t costs[100];
			CalculateLevels(resource_t(2880, 3630, 4570, 990), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P4[i], CP7[i]);
				AddLevel(&buildings[TREASURY], entry, i);
			}
		}
		//brewery
		{
			int Time[20] = { 133,164,201,243,292,348,414,491,579, 688 };
			resource_t costs[100];
			CalculateLevels(resource_t(1460, 930, 1250, 1740), costs, 1.40, 20);

			for (int i = 0; i < 10; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P6[i], CP5[i]);
				AddLevel(&buildings[BREWERY], entry, i);
			}
		}
		//HORSE DRINKING
		{
			int Time[20] = { 36,52,71,92,117,145,179,217,262,314,375,445,526,620,729,14 * 6019,16 * 60 + 43,19 * 60 + 33,22 * 60 + 51,26 * 60 + 41 };
			resource_t costs[100];
			CalculateLevels(resource_t(780, 420, 660, 540), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P5[i], CP4[i]);
				AddLevel(&buildings[HORSEDRINKING], entry, i);
			}
		}
	}
	//MILITARY
	{
		//RALLYPOINT
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(110, 160, 90, 70), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P1[i], CP1[i]);
				AddLevel(&buildings[RALLYPOINT], entry, i);
			}
		}
		//BARRACKS
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(210, 140, 260, 120), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P4[i], CP1[i]);
				AddLevel(&buildings[BARRACKS], entry, i);
			}
		}
		//ACADEMY
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(220, 160, 90, 40), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P4[i], CP5[i]);
				AddLevel(&buildings[ACADEMY], entry, i);
			}
		}
		//BLACKSMITH
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(180, 250, 500, 160), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P4[i], CP2[i]);
				AddLevel(&buildings[BLACKSMITH], entry, i);
			}
		}
		//STABLE
		{
			int Time[20] = { 36,47,60,74,91,111,134,160,191,227,268,316,361,436,511,598,11 * 60 + 38,13 * 60 + 35,15 * 60 + 51,18 * 60 + 28 };
			resource_t costs[100];
			CalculateLevels(resource_t(260, 140, 220, 100), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P5[i], CP2[i]);
				AddLevel(&buildings[STABLE], entry, i);
			}
		}


		//WORKSHOP
		{
			int Time[] = { 50,63,78,95,115,139,166,198,235,277,327,384,451,528,617,721,14 * 60 + 2,16 * 60 + 21,19 * 60 + 3,22 * 60 + 11 };
			resource_t costs[100];
			CalculateLevels(resource_t(480, 510, 600, 320), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P3[i], CP4[i]);
				AddLevel(&buildings[WORKSHOP], entry, i);
			}
		}
		//TOURNAMENT SQUARE
		{
			int Time[] = { 58,72,89,108,131,156,187,222,262,309,364,427,501,585,684,13 * 60 + 18,15 * 60 + 31,18 * 60 + 5,21 * 60 + 4,24 * 60 + 31 };
			resource_t costs[100];
			CalculateLevels(resource_t(1750, 2250, 1530, 240), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P1[i], CP1[i]);
				AddLevel(&buildings[TOURNAMENTSQUARE], entry, i);
			}
		}
		//HERO MANSION
		{
			int Time[] = { 38,44,51,59,69,80,93,108,125,145,169,196,227,264,306,355,412,478,554,643 };
			resource_t costs[100];
			CalculateLevels(resource_t(700, 670, 700, 240), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P2[i], CP1[i]);
				AddLevel(&buildings[HEROMANSION], entry, i);
			}
		}
		//STONEMASON
		{
			int Time[] = { 36,52,71,92,117,145,179,217,262,314,375,445,526,620,729,14 * 60 + 16,16 * 60 + 43,19 * 60 + 33,22 * 60 + 51,26 * 60 + 41 };
			resource_t costs[100];
			CalculateLevels(resource_t(155, 130, 125, 70), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P2[i], CP1[i]);
				AddLevel(&buildings[STONEMASON], entry, i);
			}
		}
		//ROMANWALL
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(70, 90, 170, 70), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P0[i], CP1[i]);
				AddLevel(&buildings[ROMANWALL], entry, i);
			}
		}
		//GAULWALL
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(160, 100, 80, 60), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P0[i], CP1[i]);
				AddLevel(&buildings[GAULWALL], entry, i);
			}
		}
		//GERMANWALL
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(120, 200, 0, 80), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P0[i], CP1[i]);
				AddLevel(&buildings[GERMANWALL], entry, i);
			}
		}
		//GIANTSTABLE
		{
			int Time[20] = { 36,47,60,74,91,111,134,160,191,227,268,316,361,436,511,598,11 * 60 + 38,13 * 60 + 35,15 * 60 + 51,18 * 60 + 28 };
			resource_t costs[100];
			CalculateLevels(resource_t(780, 420, 660, 300), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P5[i], CP2[i]);
				AddLevel(&buildings[GREATSTABLE], entry, i);
			}
		}
		//GIANTBARRACKS
		{
			int Time[20] = { 33,43,55,69,85,104,126,151,180,214,253,299,362,413,484,567,662,12 * 60 + 54,902,17 * 60 + 32 };
			resource_t costs[100];
			CalculateLevels(resource_t(630, 420, 780, 360), costs, 1.28, 20);

			for (int i = 0; i < 20; i++)
			{
				auto entry = CreateEntry(costs[i], Time[i], P4[i], CP1[i]);
				AddLevel(&buildings[GREATBARRACKS], entry, i);
			}
		}

	}

}

void IBuildings::AddLevel(buildingdata_t* __building, buildingentry_t level_info, int level)
{
	__building->level[level].cost.Wood = level_info.cost.Wood;
	__building->level[level].cost.Clay = level_info.cost.Clay;
	__building->level[level].cost.Iron = level_info.cost.Iron;
	__building->level[level].cost.Wheat = level_info.cost.Wheat;
	__building->level[level].Culture_points = level_info.Culture_points;
	__building->level[level].Pop = level_info.Pop;
	__building->level[level].Time = level_info.Time;
	__building->max_possible_level = max(__building->max_possible_level, level);

}





buildingentry_t IBuildings::CreateEntry(int wood, int clay, int iron, int wheat, int time, int pop, int cp)
{
	return buildingentry_t(wood, clay, iron, wheat, time, pop, cp);

}
buildingentry_t IBuildings::CreateEntry(resource_t res,int time, int pop, int cp)
{
	return buildingentry_t(res.Wood,res.Clay,res.Iron,res.Wheat, time, pop, cp);

}

int IBuildings::GetHighestInnerLevelFromHandle(int building_type, village_t* v)
{
	int highest_level = -1;

	for (int i = 0; i < 22; i++)
	{
		if (v->inner.buildings[i].type == building_type && v->inner.buildings[i].level > highest_level)highest_level = v->inner.buildings[i].level;
		//if (v->inner_type[i] == building_type && v->inner_level[i] > highest_level)highest_level = v->inner_level[i];

	}
	return highest_level;
}
int IBuildings::GetHighestOuterLevelFromHandle(int building_type, village_t* v)
{
	int highest_level = -1;

	for (int i = 0; i < 18; i++)
	{
		if (v->outer.buildings[i].type == building_type && v->outer.buildings[i].level > highest_level)highest_level = v->outer.buildings[i].level;
		//if (v->outer_type[i] == building_type && v->outer_level[i] > highest_level)highest_level = v->outer_level[i];

	}

	return highest_level;
}

int IBuildings::GetProductionForLevel(int level)
{
	static int Production_Values[] = { 3,7,13,21,31,46,70,98,140,203,280,392,525,693,889,1120,1400,1820,2240,2800,3430 };

	return Production_Values[level];
}

resource_t IBuildings::GetProduction(village_t* v)
{
	resource_t r;
	int Wood = 0, Clay = 0, Iron = 0, Wheat = 0;

	for (int i = 0; i < 18; i++)
	{
		if (v->outer.buildings[i].type == WOOD)Wood += GetProductionForLevel(v->outer.buildings[i].level);
		else if (v->outer.buildings[i].type == CLAY)Clay += GetProductionForLevel(v->outer.buildings[i].level);
		else if (v->outer.buildings[i].type == IRON)Iron += GetProductionForLevel(v->outer.buildings[i].level);
		else if (v->outer.buildings[i].type == WHEAT)Wheat += GetProductionForLevel(v->outer.buildings[i].level);
	}

	int WB, CB, IB, WHB, WHB2;

	WB = GetHighestInnerLevelFromHandle(WOODBONUS, v);
	CB = GetHighestInnerLevelFromHandle(CLAYBONUS, v);
	IB = GetHighestInnerLevelFromHandle(IRONBONUS, v);
	WHB = GetHighestInnerLevelFromHandle(MILL, v);
	WHB2 = GetHighestInnerLevelFromHandle(BAKERY, v);

	if (WHB2 > 0)
	{
		if(WHB < 0)
		WHB = 0;
		WHB += WHB2;
	}

	if (WB > 0)Wood *= (1.f + WB*0.05f);
	if (CB > 0)Clay *= (1.f + CB*0.05f);
	if (IB > 0)Iron *= (1.f + IB*0.05f);
	if (WHB > 0)Wheat *= (1.f + WHB*0.05f);



	r.define(Wood, Clay, Iron, Wheat);

	
	return r;
}

unsigned int IBuildings::GetTime(village_t* v, int building_type, int level)
{
	return buildings[building_type].level[level].Time / BT[GetHighestInnerLevelFromHandle(MAIN, v)];
}

unsigned int IBuildings::ConvertTime(int basetime, int level)
{
	return basetime / BT[level];
}

resource_t IBuildings::GetCost(int building_type, int level)
{
	return buildings[building_type].level[level].cost;
}

resource_t IBuildings::GetMaxStorage(village_t* v)
{
	int Ware = 0, Gran = 0;

	for (int i = 0; i < 22; i++)
	{
		if (v->inner.buildings[i].type == WAREHOUSE)Ware += ST[v->inner.buildings[i].level];
		if (v->inner.buildings[i].type == GRANARY)Gran += ST[v->inner.buildings[i].level];
	}
	if (GetHighestInnerLevelFromHandle(WAREHOUSE, v) < 1)Ware = 800;
	if (GetHighestInnerLevelFromHandle(GRANARY, v) < 1)Gran = 800;

	return resource_t(Ware, Ware, Ware, Gran);
}