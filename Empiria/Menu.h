#pragma once
//#include "gamestructs.h"
#include "includes.h"

enum Menus
{
	MENU_MAINMENU,
	MENU_OVERVIEW,
	MENU_PLAYERS,
	MENU_MATCHMAKING,
	MENU_MATCH
};


struct player_t;

struct CMenu
{
	intptr_t father;
	int current_tab = MENU_MAINMENU;
	//coord click_start;


	

	
	static bool Button(int start_x, int start_y, int size_x, int size_y, char* text, bool should_interract);
	static void Table(int start_x, int start_y, int size_x, int size_y);
	static bool PlayerCard(int start_x, int start_y, player_t* pPlayer, bool is_selected);
	static int TextInput(int start_x, int start_y, char* text, int text_length, char* modifiable); // 0 - normal, 1 - confirmed, 2 - cancelled


	void RenderVersion();
	void RenderLeftSideBar();
	void RenderMainMenu();
	void RenderOverView();
	void RenderPlayers();
	void RenderMatchmaking();
	void RenderMatch();
	


	void RenderTheThing();


};