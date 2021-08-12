#pragma once
#include "enums.h"
#include "includes.h"


struct resource_t; struct building_t; struct inner_t; struct outer_t; struct field_t; struct map_t; struct village_t; struct player_t; struct travian_t;

struct resource_t
{
public:
	double Wood, Clay, Iron, Wheat;
	resource_t() {}
	resource_t(double w, double c, double i, double wh)
	{
		Wood = w;
		Clay = c;
		Iron = i;
		Wheat = wh;
	}

	virtual void add(resource_t j)
	{
		Wood += j.Wood;
		Clay += j.Clay;
		Iron += j.Iron;
		Wheat += j.Wheat;
	}
	virtual void subtract(resource_t j)
	{
		Wood -= j.Wood;
		Clay -= j.Clay;
		Iron -= j.Iron;
		Wheat -= j.Wheat;
	}
	virtual void multiply(double num)
	{
		Wood *= num;
		Clay *= num;
		Iron *= num;
		Wheat *= num;
	}
	virtual void setmin(resource_t j)
	{
		Wood = max(j.Wood, Wood);
		Clay = max(j.Clay, Clay);
		Iron = max(j.Iron, Iron);
		Wheat = max(j.Wheat, Wheat);
	}

	virtual void setmax(resource_t j)
	{
		Wood = min(j.Wood, Wood);
		Clay = min(j.Clay, Clay);
		Iron = min(j.Iron, Iron);
		Wheat = min(j.Wheat, Wheat);
	}
	virtual void set(int jw, int jc, int ji, int jwh)
	{
		Wood = jw;
		Clay = jc;
		Iron = ji;
		Wheat = jwh;
	}
	virtual int divide(resource_t re)
	{
		int a, b, c, d;
		a = Wood / re.Wood;
		b = Clay / re.Clay;
		c = Iron / re.Iron;
		d = Wheat / re.Wheat;
		return min(a, min(b, min(c, d)));
	}
	virtual double sum()
	{
		return Wood + Clay + Iron + Wheat;
	}

	void define(double awood, double aclay, double airon, double awheat)
	{
		Wood = awood;
		Clay = aclay;
		Iron = airon;
		Wheat = awheat;
	};

	inline resource_t operator=(const resource_t lhs) { return resource_t(lhs.Wood, lhs.Clay, lhs.Iron, lhs.Wheat); }
};;;;;

inline resource_t operator*=(resource_t lhs, double m) { return resource_t(lhs.Wood*m, lhs.Clay*m, lhs.Iron*m, lhs.Wheat*m); }
inline resource_t operator*=(resource_t lhs, float m) { return resource_t(lhs.Wood*m, lhs.Clay*m, lhs.Iron*m, lhs.Wheat*m); }
inline resource_t operator*=(resource_t lhs, int m) { return resource_t(lhs.Wood*m, lhs.Clay*m, lhs.Iron*m, lhs.Wheat*m); }
inline bool operator<(resource_t lhs, resource_t rhs) { return lhs.Wood < rhs.Wood && lhs.Clay < rhs.Clay && lhs.Iron < rhs.Iron && lhs.Wheat < rhs.Wheat; }
inline bool operator>(resource_t lhs, resource_t rhs) { return lhs.Wood > rhs.Wood && lhs.Clay > rhs.Clay && lhs.Iron > rhs.Iron && lhs.Wheat > rhs.Wheat; }
inline bool operator>=(resource_t lhs, resource_t rhs) { return lhs.Wood >= rhs.Wood && lhs.Clay >= rhs.Clay && lhs.Iron >= rhs.Iron && lhs.Wheat >= rhs.Wheat; }
inline bool operator<=(resource_t lhs, resource_t rhs) { return lhs.Wood <= rhs.Wood && lhs.Clay <= rhs.Clay && lhs.Iron <= rhs.Iron && lhs.Wheat <= rhs.Wheat; }
inline bool operator==(resource_t lhs, resource_t rhs) { return lhs.Wood == rhs.Wood && lhs.Clay == rhs.Clay && lhs.Iron == rhs.Iron && lhs.Wheat == rhs.Wheat; }



struct building_t
{
	bool defined = false;
	short type;
	int level = 0;
	int hi_level = 0;

	resource_t GetBuildCost();
	resource_t GetBuildTime();

	void Define(int id);
};

struct outer_t
{
	bool defined = false;
	building_t buildings[18];

	void Define(int type);
};

struct inner_t
{
	building_t buildings[22];

	void Define(int tribe);
};

struct field_t
{
	bool is_oasis = false;
	int x, y;
	int type;
	village_t* village = nullptr;
	int village_id;


};

struct map_t
{
	field_t fields[801][801];

	int RandomPlotType();
	void GenerateMap();
	void DrawAField(int x, int y, int cx, int cy, int s);
	void DrawAVillage(int x, int y, int cx, int cy, int s);
	int DrawFieldInfo(int x, int y);
};

struct village_t
{
	int id;
	char* name = "Village";
	field_t* field = nullptr;
	player_t* owner = nullptr;
	village_t* next = nullptr;
	inner_t inner;
	outer_t outer;

	resource_t res;

	void Initialize(field_t* fi, player_t* pl);
};

struct player_t
{
	int id = 0;
	travian_t* base = nullptr;
	player_t* next = nullptr;
	village_t* villages[100];
	int selected_village = 0;
	int tribe;

	void BuildOuter(int id);
	void BuildInner(int id);


	void Initialize(float range, int tribe);
};

class buildingentry_t
{
public:
	resource_t cost;
	unsigned int Time;
	unsigned char Pop;
	unsigned int Culture_points;

	buildingentry_t() {}

	buildingentry_t(int wood, int clay, int iron, int wheat, int time, int pop, int cp)
	{
		cost.Wood = wood;
		cost.Clay = clay;
		cost.Iron = iron;
		cost.Wheat = wheat;
		Time = time;
		Pop = pop;
		Culture_points = cp;
	}

	buildingentry_t(resource_t res, int time, int pop, int cp)
	{
		cost = res;
		Time = time;
		Pop = pop;
		Culture_points = cp;
	}
	//inline resource_t operator=(const resource_t lhs) { return resource_t(lhs.Wood, lhs.Clay, lhs.Iron, lhs.Wheat); }
	inline buildingentry_t operator=(const buildingentry_t ls) { return buildingentry_t(ls.cost, ls.Time, ls.Pop, ls.Culture_points); }
};

struct buildingdata_t
{
	char max_possible_level;
	buildingentry_t level[100];
};


class event_t
{
public:
	bool Valid = false;
	unsigned char eventtype;
	unsigned int requesting_id;
	unsigned int targetted_id;
	unsigned int event_force_time;

	//build calls
	unsigned char building_id;
	unsigned char building_level;

	//troop calls
	//army_t arms;

	//trade calls
	//resource_t res;
	double Wood;
	double Clay;
	double Iron;
	double Wheat;

	//new village call
	int vil_x, vil_y;


};

class eventtable_t
{
public:
	travian_t* main;
	unsigned int Time = 0;
	event_t events[100000];
	int active_events = 0; //probably unsafe
};

struct travian_t
{
	int Tab = 2;
	//Map
	float map_x = 4, map_y = 0.f;
	map_t Map;
	player_t players;
	village_t villages;
	player_t* local;
	eventtable_t events;


	village_t* GenerateNewVillage(int cx, int cy);
	


	
	void Initalize();
	void AddNewPlayer();
	void AddLocalPlayer();
	void Draw();

	void DrawResourceBar();
	void DrawActiveConstructions();
	void DrawOuter();
	void DrawInner();
	void DrawUniqueBuildingMessage(int &selected);

	void DrawMap();
	village_t* GetVillage(int id);
	player_t* GetPlayer(int id);
	
	
	void DrawMenu();

	void Produce();
};


struct IBuildings
{
	static void CreateAllBuildings();

	static char* GetBuildingName(int id);
	static resource_t GetCost(int building_type, int level);
	static unsigned int GetTime(village_t* v, int building_type, int level);
	static unsigned int ConvertTime(int basetime, int level);
	static buildingentry_t CreateEntry(int wood, int clay, int iron, int wheat, int time, int pop, int cp);
	static buildingentry_t CreateEntry(resource_t res, int time, int pop, int cp);
	static void AddLevel(buildingdata_t* __building, buildingentry_t level_info, int level);
	static resource_t CalculateNext(resource_t &ls, float multi);

	static int GetProductionForLevel(int level);
	static resource_t GetProduction(village_t* v);

	static int GetHighestInnerLevelFromHandle(int buildingtype, village_t* v);
	static int GetHighestOuterLevelFromHandle(int buildingtype, village_t* v);

	static resource_t GetMaxStorage(village_t* v);
};

struct IEvents
{
	static void TimeTravel(eventtable_t* et,int time);
	static void SortEvents(eventtable_t* table);
	static void DoEvents(eventtable_t* et);
	static void CreateGlobalEvent(eventtable_t* et, event_t e);




	static void CreateOuterBuildCall(eventtable_t* et, village_t* v, int building_id);
	static void CreateInnerBuildCall(eventtable_t* et, village_t* v, int building_id);
	static int GetHighestTime(eventtable_t* table, village_t* v, int EVENT);
	static int CountEvents(eventtable_t* table, village_t* v, int EVENT);
};