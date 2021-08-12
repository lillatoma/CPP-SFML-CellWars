#pragma once
#include "includes.h"

struct cell_t
{
	int cell_id;
	float oposX, oposY;
	float posX, posY;
	double velocityX = 0, velocityY = 0;
	float angle = 195;


	int species;
	int owner_id;
	int production_speed; //species/min
	int size;
	int speed = 100;
	float produced;

	void Draw(bool finished);
	void Set(int prs, int spe, int siz, int sp);

	bool isHovered();
};

struct specy_t
{
	bool active = false;
	int owner_id;
	int target_id;
	float posX, posY;
	float speed;

};

struct botprofile_t
{
	int spent_time = 0;
	int decisions_made = 0;


	int intelligence = 0;
	int warmuptime = 4000;
	int decisiontime = 2500;
	float percent_to_freely_decide = 25;
	float percent_to_aggress = 50;

	void SetPercents(float free, float aggr)
	{
		percent_to_aggress = aggr;
		percent_to_freely_decide = free;
	}

	void SetToughness(int intel, int warm, int dec)
	{
		if(intel != 0)
			intelligence = intel;
		if(warm != 0)
			warmuptime = warm;
		if(dec != 0)
			decisiontime = dec;
	}


	void Reset()
	{
		spent_time = 0;
		decisions_made = 0;


		intelligence = 0;
		warmuptime = 4000;
		decisiontime = 2500;
		percent_to_freely_decide = 51;
		percent_to_aggress = 67;
	}
};




struct graphdata_t
{
	int spec[9];
};


struct cmatch_t
{
	bool pause = true;
	graphdata_t graph[14400];
	int graph_timer = 0;
	int timer = 0;
	bool reset_timer = true;
	int cell_count = 0;
	cell_t cells[100];
	specy_t species[10000];
	botprofile_t profiles[8];
	void AddCell(cell_t c, int owner, float x, float y);
	void SimulateSpecies();
	void Produce();
	

	void DrawPowerBar();
	void Draw(bool finished);

	void MoveSpecies(int a, int b);
	float GetDist(int a, int b);
	float GetDist(int a, int b, int tickstogo);
	float GetPercent(int id);
	int GetOwnedCells(int id);
	int GetOwnedSpecies(int id);
	bool isFull(int id);
	int GetEmptyCells();
	
	bool BotSafeThink(int id);
	bool BotFreeThink(int id);
	bool BotAggress(int id);
	bool BotFullThink(int id);

	
	
	void BotThink();

	bool hasWon();
	bool hasEnded();




	bool physics_enabled = true;
	void Physics();
	void CalculateReaction(double &velocityA, double &velocityAY, int massA, double &velocityB, double &velocityBY, int massB, float distX, float distY);
	void CalculateRelease(double &velocityAX, double &velocityAY, int massA, double velocityBX, float angleB);

	void EditGraph();
	void ShowGraph();

	void Reset(bool ap)
	{
		physics_enabled = true;
		cell_count = 0;
		for (int i = 0; i < 10000; i++)species[i].active = false;
		for (int j = 0; j < 8; j++)profiles[j].Reset();
		timer = 0;
		graph_timer = 0;
		if(ap)
			pause = true;

	}
};








struct bgcell_t
{
	int size = 1;
	float posX, posY;

	float velocity = 1.f;
	float angle = 0.f;

	void Initialize()
	{
		size = Random(25, 300);
		posX = Random(0, 1280);
		posY = Random(0, 720);
		velocity = (float)Random(50, 750) / 100;
		angle = Random(0, 360);
	}
};













struct background_t
{
	int CellCount = 0;
	bgcell_t Cells[250];
};



















enum tabs
{
	TAB_INGAME = 1,
	TAB_SHOWGRAPH,
	TAB_CHOOSELEVEL,
	TAB_OPTIONS,
	TAB_MAINMENU
	
};


struct cgame_t
{
	bool auto_pause = true;
	bool show_fps = false;
	bool last_success = false;
	int current_level = 1;
	int level = 1;
	int tab = TAB_MAINMENU;
	background_t bg;
	cmatch_t Match;
	void Initialize();
	void Do();

	void RenderFlash(int i);
	void RenderIngame();
	void RenderGraph();
	void RenderMainMenu();
	void RenderFPS();
	void RenderOptions();
	void RenderSelect();
	void RenderPause();


	void Mouse();
	void LoadMaxLevel();
	void LoadLevel(int l);

	void ApplyBackgroundShader();
	void SimulateBackground();
	void DrawBackground();
};

extern sf::Color g_Colors[10];