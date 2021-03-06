#pragma once
#include "includes.h"

struct cell_t
{
	int cell_id;
	float oposX, oposY; //original position of the cell
	float posX, posY; //position at a specific moment of the cell
	double velocityX = 0, velocityY = 0; //velocity of the cell at a specific moment
	float angle = 195;


	int species; //species at a specific moment
	int owner_id; //
	int production_speed; //species/min
	int size; //hypotenuse of a cell
	int speed = 100; //speed of how fast the virus species are ejected
	float produced;

	////////////////////////////////////////////////////////////
	/// Draws a cell using the SFML graphics engine
	/// 
	/// 'finished' : Input for the current match being finished. True if it's finished, false if it's playing.
	/// 'finished' is also true if the game is paused.
	////////////////////////////////////////////////////////////
	void Draw(bool finished);


	////////////////////////////////////////////////////////////
	/// This function changes some attributes of a cell_t instance
	/// 
	/// 'prs' : Input for 'production_speed'
	/// 'spe' : Input for 'species'
	/// 'siz' : Input for 'size'
	/// 'sp' : Input for 'speed'
	////////////////////////////////////////////////////////////
	void Set(int prs, int spe, int siz, int sp);

	////////////////////////////////////////////////////////////
	/// Returns 'true' if the cursor is on the cell
	/// Returns 'false' if the cursor is outside of the cell
	////////////////////////////////////////////////////////////
	bool isHovered();
};

////////////////////////////////////////////////////////////
/// Representing object of an ejected virus
/// Excuse me for the grammar
////////////////////////////////////////////////////////////
struct specy_t
{
	bool active = false;
	int owner_id; //Index of the original cell
	int target_id; //Index of the target cell
	float posX, posY; //Current position of a virus
	float speed; //Speed of a virus

};


struct botprofile_t
{
	int spent_time = 0; //Since the game's beginning, how many milliseconds have passed
	int decisions_made = 0; //How many actions were taken by the bot
	int intelligence = 0; //Difficulty level of an AI
	int warmuptime = 4000; //Time in milliseconds before the first action of an AI
	int decisiontime = 2500; //Time between actions in milliseconds
	float percent_to_freely_decide = 25; 
	float percent_to_aggress = 50;

	////////////////////////////////////////////////////////////
	/// Sets the attributes for 'percent_to_aggress' and 'percent_to_freely_decide'
	/// 'free' : Input for percent_to_freely_decide
	/// 'aggr' : Input for percent_to_aggress
	////////////////////////////////////////////////////////////
	void SetPercents(float free, float aggr)
	{
		percent_to_aggress = aggr;
		percent_to_freely_decide = free;
	}

	////////////////////////////////////////////////////////////
	/// Sets the attributes for 'intelligence', 'warmuptime' and 'decisiontime' if they are valid numbers
	/// 'intel' : Input for 'intelligence'
	/// 'warm' : Input for 'warmuptime'
	/// 'dec' : Input for 'decisiontime'
	////////////////////////////////////////////////////////////
	void SetToughness(int intel, int warm, int dec)
	{
		if(intel > 0)
			intelligence = intel;
		if(warm > 0)
			warmuptime = warm;
		if(dec > 0)
			decisiontime = dec;
	}

	////////////////////////////////////////////////////////////
	/// 'Resets' the attributes of an AI with some changes 
	////////////////////////////////////////////////////////////
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



////////////////////////////////////////////////////////////
/// Representating number of species for each player
////////////////////////////////////////////////////////////
struct graphdata_t
{
	int spec[9];
};

////////////////////////////////////////////////////////////
/// Match object
////////////////////////////////////////////////////////////
struct cmatch_t
{
	bool pause = true; // if the match is paused

	//TODO: Change graph to std::vector
	graphdata_t graph[14400]; //graph for how a match happened
	int graph_timer = 0;
	int timer = 0;
	bool reset_timer = true;

	//TODO: Change cells and species to std::vector
	cell_t cells[100];
	int cell_count = 0;
	specy_t species[10000];
	botprofile_t profiles[8]; //Controlling for all AI-controlled opponents
	bool physics_enabled = true;


	////////////////////////////////////////////////////////////
	/// Function that adds a predefined cell to a match
	/// 'c' : Predefined cell
	/// 'owner' : Which player is the owner of the cell. 0 if 'world' owns the cell 
	/// 'x' ; 'y' : Position of the cell
	////////////////////////////////////////////////////////////
	void AddCell(cell_t c, int owner, float x, float y);

	////////////////////////////////////////////////////////////
	/// Simulates each ejected virus
	/// Moves them closer to their destination according to the time passed
	/// If they reach their destination, they are destroyed and the cell gets damaged or reinforced based on the owner
	////////////////////////////////////////////////////////////
	void SimulateSpecies();

	////////////////////////////////////////////////////////////
	/// Simulates each cell
	/// Produces local species for each player-owned cell if there is still space left
	/// Cells owned by 'world' don't produce
	////////////////////////////////////////////////////////////
	void Produce();
	
	////////////////////////////////////////////////////////////
	/// Draws the bottom bar, representing the power (virus-count) of each player with at least 1 cell
	////////////////////////////////////////////////////////////
	void DrawPowerBar();
	////////////////////////////////////////////////////////////
	/// Draws every cell, virus instance and the power-bar on top
	/// 'finished' : Parameter to know if the match is finished or paused
	////////////////////////////////////////////////////////////
	void Draw(bool finished);


	////////////////////////////////////////////////////////////
	/// Ejects viruses from a cell
	/// 'a' : Cell of origin
	/// 'b' : Cell of destination
	////////////////////////////////////////////////////////////
	void MoveSpecies(int a, int b);

	////////////////////////////////////////////////////////////
	/// Returns the euclidean distance of cells with id 'a' and 'b'
	////////////////////////////////////////////////////////////
	float CalcDistance(int a, int b);

	////////////////////////////////////////////////////////////
	/// Returns the euclidean distance of cells with id 'a' and 'b'
	/// if both cells eject at the same time 'tickstogo' ticks later
	////////////////////////////////////////////////////////////
	float CalcDistance(int a, int b, int tickstogo);

	////////////////////////////////////////////////////////////
	/// Returns the percentage for how much the 'id'th player owns from all viruses 
	////////////////////////////////////////////////////////////
	float CalcPercent(int id);

	////////////////////////////////////////////////////////////
	/// Returns how many cells the 'id'th player owns
	////////////////////////////////////////////////////////////
	int CalcOwnedCells(int id);

	////////////////////////////////////////////////////////////
	/// Returns how many viruses the 'id'th player owns
	////////////////////////////////////////////////////////////
	int CalcOwnedSpecies(int id);


	////////////////////////////////////////////////////////////
	/// Returns if the 'id'th player has all their cells filled with viruses 
	////////////////////////////////////////////////////////////
	bool isFull(int id);

	////////////////////////////////////////////////////////////
	/// Returns how many cells are owned by 'world'
	////////////////////////////////////////////////////////////
	int CalcEmptyCells();
	

	bool BotSafeThink(int id);
	bool BotFreeThink(int id);
	bool BotAggress(int id);
	bool BotFullThink(int id);
	void BotThink();

	////////////////////////////////////////////////////////////
	/// Returns if the player is the only player alive
	/// 'true' if the player is the last one standing
	/// 'false' if an other player is alive
	////////////////////////////////////////////////////////////
	bool hasWon();
	////////////////////////////////////////////////////////////
	/// Returns if only one player is alive
	/// 'true' if there is only one player alive
	/// 'false' if there are more players alive
	////////////////////////////////////////////////////////////
	bool hasEnded();

	////////////////////////////////////////////////////////////
	/// Weird physics calculation
	////////////////////////////////////////////////////////////
	void Physics();
	////////////////////////////////////////////////////////////
	/// Weird physics calculation
	////////////////////////////////////////////////////////////
	void CalculateReaction(double &velocityA, double &velocityAY, int massA, double &velocityB, double &velocityBY, int massB, float distX, float distY);
	////////////////////////////////////////////////////////////
	/// Weird physics calculation
	////////////////////////////////////////////////////////////
	void CalculateRelease(double &velocityAX, double &velocityAY, int massA, double velocityBX, float angleB);

	////////////////////////////////////////////////////////////
	/// Adds the current state to the graph
	////////////////////////////////////////////////////////////
	void EditGraph();
	////////////////////////////////////////////////////////////
	/// Draws the graph of a match
	/// It takes 2 seconds to draw the lines fully
	////////////////////////////////////////////////////////////
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







////////////////////////////////////////////////////////////
/// An instance of a big circle in the background
////////////////////////////////////////////////////////////
struct bgcell_t
{
	int size = 1;
	float posX, posY;

	float velocity = 1.f;
	float angle = 0.f;

	////////////////////////////////////////////////////////////
	/// Randomly generates parameters
	////////////////////////////////////////////////////////////
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
	////////////////////////////////////////////////////////////
	/// Sets up the default color scheme for the players
	/// Sets up the background cells
	/// Loads the hardest level for the player (TODO: save progress)
	////////////////////////////////////////////////////////////
	void Initialize();
	
	////////////////////////////////////////////////////////////
	/// Function that does everything basically
	/// Draws the background
	/// Draws the current tab
	/// Draws the fps counter
	////////////////////////////////////////////////////////////
	void Do();

	////////////////////////////////////////////////////////////
	/// Draws a white overlay on the entire screen
	/// 'i' how many milliseconds have passed
	/// Flash alpha ranges from 0-64 integer value
	////////////////////////////////////////////////////////////
	void RenderFlash(int i);

	////////////////////////////////////////////////////////////
	/// Draws and executes everything for in-game
	////////////////////////////////////////////////////////////
	void RenderIngame();


	////////////////////////////////////////////////////////////
	/// Draws the graph of a match with a menu
	////////////////////////////////////////////////////////////
	void RenderGraph();
	////////////////////////////////////////////////////////////
	/// Draws the buttons of the main menu
	////////////////////////////////////////////////////////////
	void RenderMainMenu();
	////////////////////////////////////////////////////////////
	/// Draws the fps counted every second
	////////////////////////////////////////////////////////////
	void RenderFPS();


	////////////////////////////////////////////////////////////
	/// Draws the option menu
	////////////////////////////////////////////////////////////
	void RenderOptions();
	////////////////////////////////////////////////////////////
	/// Draws the level select menu
	////////////////////////////////////////////////////////////
	void RenderSelect();
	////////////////////////////////////////////////////////////
	/// Draws the pause/continue symbol on top
	/// In case of a swap between pause and continue
	/// A big transparent pause/contnue symbol is drawn in the middle
	////////////////////////////////////////////////////////////
	void RenderPause();

	////////////////////////////////////////////////////////////
	/// Does the mousing
	/// While in-game, it allows the user to select cells, even multiple ones while holding the mouse
	/// On release, it ejects the viruses to the cell under the mouse
	/// If there is no cell under the mouse, selection gets forgotten, and nothing else happens
	////////////////////////////////////////////////////////////
	void Mouse();

	////////////////////////////////////////////////////////////
	/// Loads the last unlocked level
	////////////////////////////////////////////////////////////
	void LoadMaxLevel();

	////////////////////////////////////////////////////////////
	/// Loads the 'l'th level
	/// 'l' : index of level
	////////////////////////////////////////////////////////////
	void LoadLevel(int l);

	////////////////////////////////////////////////////////////
	/// Unused
	////////////////////////////////////////////////////////////
	void ApplyBackgroundShader();

	////////////////////////////////////////////////////////////
	/// Moves the circles in the background
	////////////////////////////////////////////////////////////
	void SimulateBackground();

	////////////////////////////////////////////////////////////
	/// Draws the background spheres
	////////////////////////////////////////////////////////////
	void DrawBackground();
};

extern sf::Color g_Colors[10];