#include "Menu.h"
#include "gamestructs.h"

/*bool IsBetween(int x, int y, int w, int h, int checkx, int checky)
{
	return x < checkx && y < checky && checkx < x + w && checky < y + h;
}


bool CMenu::Button(int start_x, int start_y, int size_x, int size_y, char* text, bool should_interact)
{
	IWindow::RenderOverlay(start_x, start_y, size_x, size_y, 0, 0, 0, 255);
	bool cool = false;
	if (should_interact && g_Mouse.left_click && IsBetween(start_x, start_y, size_x, size_y, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))
	{
		IWindow::RenderOverlay(start_x + 1, start_y + 1, size_x - 1, size_y - 1, 252, 255, 132, 255);
		IWindow::RenderText(start_x + 16, start_y*0.75 + (start_y + size_y)*0.25, size_y / 2, 64, 0, 0, 255, text);
		cool = true;
	}
	else if (should_interact && !g_Mouse.left_click && IsBetween(start_x, start_y, size_x, size_y, g_Mouse.Coords.x, g_Mouse.Coords.y))
	{
		IWindow::RenderOverlay(start_x + 1, start_y + 1, size_x - 1, size_y - 1, 224, 224, 224, 255);
		IWindow::RenderText(start_x + 16, start_y*0.75 + (start_y + size_y)*0.25, size_y / 2, 0, 0, 0, 255, text);
		cool = true;
	}
	else
	{
		IWindow::RenderOverlay(start_x + 1, start_y + 1, size_x - 1, size_y - 1, 160, 160, 160, 255);
		IWindow::RenderText(start_x + 16, start_y*0.75 + (start_y + size_y)*0.25, size_y / 2, 0, 0, 0, 255, text);
	}

	return g_Mouse.hasReleased(false) && g_Mouse.IsClickValid(false) && should_interact && cool;
}

void CMenu::Table(int start_x, int start_y, int size_x, int size_y)
{
	IWindow::RenderOverlay(start_x, start_y, size_x, size_y, 0, 0, 0, 255);
	IWindow::RenderOverlay(start_x+1, start_y+1, size_x-1, size_y-1, 84, 74, 26, 255);
}

bool CMenu::PlayerCard(int start_x, int start_y, player_t* pPlayer, bool is_selected)
{
	int size_x = 160, size_y = 100;
	IWindow::RenderOverlay(start_x, start_y, size_x, size_y, 0, 0, 0, 255);


	if (is_selected)
		IWindow::RenderOverlay(start_x + 1, start_y + 1, size_x - 1, size_y - 1, 175, 240, 81, 255);
	else if(IsBetween(start_x,start_y,size_x,size_y,g_Mouse.Coords.x,g_Mouse.Coords.y))
		IWindow::RenderOverlay(start_x + 1, start_y + 1, size_x - 1, size_y - 1, 195, 176, 81, 255);
	else	IWindow::RenderOverlay(start_x + 1, start_y + 1, size_x - 1, size_y - 1, 165, 146, 51, 255);
	IWindow::RenderText(start_x + 3, start_y + 3, 16, 0, 0, 0, 255, pPlayer->playername);
	char AIM[32], DOD[32], ATK[32], DEF[32], INT[32];

	sprintf(AIM, "AIM: %d", pPlayer->aiming);
	sprintf(DOD, "DOD: %d", pPlayer->dodging);
	sprintf(ATK, "ATK: %d", pPlayer->attacking);
	sprintf(DEF, "DEF: %d", pPlayer->defending);
	sprintf(INT, "INT: %d", pPlayer->intelligence);

	IWindow::RenderText(start_x + 3, start_y + 24, 12, 0, 0, 0, 255, AIM);
	IWindow::RenderText(start_x + 3, start_y + 38, 12, 0, 0, 0, 255, DOD);
	IWindow::RenderText(start_x + 3, start_y + 52, 12, 0, 0, 0, 255, ATK);
	IWindow::RenderText(start_x + 3, start_y + 66, 12, 0, 0, 0, 255, DEF);
	IWindow::RenderText(start_x + 3, start_y + 80, 12, 0, 0, 0, 255, INT);


	return g_Mouse.hasReleased(false) && IsBetween(start_x, start_y, size_x, size_y, g_Mouse.Coords.x, g_Mouse.Coords.y) && IsBetween(start_x, start_y, size_x, size_y, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y);

	return false;
}

int CMenu::TextInput(int start_x, int start_y, char* text, int text_length, char* modifiable)
{
	int size_x = text_length * 20 + 80;
	int size_y = 180;
	IWindow::RenderOverlay(start_x, start_y, size_x, size_y, 0, 0, 0, 255);
	IWindow::RenderOverlay(start_x+1, start_y+1, size_x-1, size_y-1, 80, 140, 180, 255);
	IWindow::RenderText(start_x + 5, start_y + 5, 20, 255, 255, 255, 255, text);
	IWindow::RenderOverlay(start_x+10, start_y+30, size_x-20, 30, 0, 0, 0, 255);
	IWindow::RenderText(start_x + 12, start_y + 35, 20, 255, 255, 255, 255, modifiable);

	if (strlen(modifiable) > 0 && GetAsyncKeyState(VK_BACK) & 1)modifiable[strlen(modifiable)-1] = '\0';

	if (GetAsyncKeyState(VK_SPACE) & 1)
	{
		if (strlen(modifiable) < text_length)
			modifiable[strlen(modifiable)] = ' ';
	}

	for (int i = 0x41; i <= 0x5A; i++)
	{
		if (GetAsyncKeyState(i) & 1)
		{
			if(strlen(modifiable) < text_length)
			modifiable[strlen(modifiable)] = 'a' + i - 0x41;
		}
	}
	for (int i = 0x30; i <= 0x39; i++)
	{
		if (GetAsyncKeyState(i) & 1)
		{
			if (strlen(modifiable) < text_length)
				modifiable[strlen(modifiable)] = '0' + i - 0x41;
		}
	}

	if (Button(start_x + size_x - 100, start_y + 30, 95, 30, "Clear", true))
	{
		for (int i = 0; i < 32; i++)
			modifiable[i] = '\0';
	}

	if (Button(start_x + 10, start_y + 65, 200, 50, "Confirm", true))return 1;
	if (Button(start_x + size_x - 210, start_y + 65, 200, 50, "Deny", true))
	{
		return 2;
	}



	return 0;
}

void CMenu::RenderVersion()
{
	IWindow::RenderOverlay(0, 0, 1280, 720, 32, 32, 128, 222);
	IWindow::RenderText(2, 2, 16, 255, 0, 0, 255, "Counter-Strike Team Coacher\nversion: Alpha 0.1.2");
}

void CMenu::RenderMainMenu()
{
	static bool quit_prompt = false;
	RenderVersion();








	if (Button(540, 295, 200, 50, "Start", !quit_prompt))
	{
		current_tab = MENU_OVERVIEW;
	}
	if (Button(540, 375, 200, 50, "Quit", !quit_prompt))
	{
		quit_prompt = true;
	}


	if (quit_prompt)
	{
		Table(440, 270, 400, 180);
		IWindow::RenderText(460, 300, 20, 255, 255, 255, 255, "Are you sure you quit?");

		if (Button(460, 340, 150, 50, "Yes", quit_prompt))
		{
			std::exit(0x666);
		}

		else if (Button(670, 340, 150, 50, "No", quit_prompt))quit_prompt = false;
	}



}

void CMenu::RenderLeftSideBar()
{
	Table(0, 120, 240, 200);
	if (Button(0, 120, 240, 40, "Main Menu", true))current_tab = MENU_MAINMENU;
	else if (Button(0, 160, 240, 40, "Overview", true))current_tab = MENU_OVERVIEW;
	else if (Button(0, 200, 240, 40, "Players", true))current_tab = MENU_PLAYERS;
	else if (Button(0, 240, 240, 40, "Matchmaking", true))current_tab = MENU_MATCHMAKING;

}

void CMenu::RenderPlayers()
{
	static int selected = -1;
	static bool is_renaming = false;
	static char modifiable_name[32] = "modifiable name";

	RenderVersion();
	IWindow::RenderText(555, 20, 40, 255, 255, 255, 255, "Players");

	RenderLeftSideBar();

	game_t* pGame = (game_t*)father;

	if (pGame->free_players_left > 0)
	{
		char text[64] = "Claim Free Player (0)";
		text[19] = '0' + pGame->free_players_left;
		if (Button(1000, 80, 280, 32, text, !is_renaming))
		{
			pGame->ClaimFreePlayer();
		}
	}

	if (g_Mouse.hasReleased(false) && g_Mouse.Coords.y < 600 && !is_renaming)selected = -1;

	for(int i = 0; i< pGame->Material.number_of_players; i++)
	{
		if (PlayerCard(270 + i % 5 * 170, 130 + i / 5 * 110, pGame->Material.pPlayers[i], selected == i))
		{
			if(!is_renaming)
			selected = i;
		}

	}

	if (selected != -1)
	{
		Table(0, 600, 1280, 120);
		IWindow::RenderText(10, 610, 24, 255, 255, 255, 255, pGame->Material.pPlayers[selected]->playername);
		char avai[64] = "Skill Points: %d";
		sprintf(avai, avai, pGame->Material.pPlayers[selected]->skillpoints);
		IWindow::RenderText(10, 638, 16, 255, 255, 255, 255, avai);

		IWindow::RenderOverlay(10, 660, 252, 10, 0, 0, 0, 255);
		IWindow::RenderOverlay(11, 661, pGame->Material.pPlayers[selected]->experience/2, 8, 0, 150, 0, 255);

		IWindow::RenderOverlay(400, 605, 402, 42, 32, 32, 32, 255);

		int spend = 1;
		int skillpoints = pGame->Material.pPlayers[selected]->skillpoints;

		if (skillpoints > 20)spend = 5;
		if (skillpoints > 100)spend = 10;
		if (skillpoints > 500)spend = 25;
		if (skillpoints > 1500)spend = 50;

		if(Button(401, 606, 80, 40, "AIM", pGame->Material.pPlayers[selected]->skillpoints > 0) && !is_renaming)pGame->Material.pPlayers[selected]->SpendSkillPoint(0,spend);
		if (Button(481, 606, 80, 40, "DOD", pGame->Material.pPlayers[selected]->skillpoints > 0) && !is_renaming)pGame->Material.pPlayers[selected]->SpendSkillPoint(1, spend);
		if (Button(561, 606, 80, 40, "ATK", pGame->Material.pPlayers[selected]->skillpoints > 0) && !is_renaming)pGame->Material.pPlayers[selected]->SpendSkillPoint(3, spend);
		if (Button(641, 606, 80, 40, "DEF", pGame->Material.pPlayers[selected]->skillpoints > 0) && !is_renaming)pGame->Material.pPlayers[selected]->SpendSkillPoint(4, spend);
		if (Button(721, 606, 80, 40, "INT", pGame->Material.pPlayers[selected]->skillpoints > 0) && !is_renaming)pGame->Material.pPlayers[selected]->SpendSkillPoint(2, spend);



		if(Button(600, 650, 200, 40, "Rename", true))is_renaming = true;
		if (is_renaming)
		{
			auto inp = TextInput(400, 240, "Rename", 32, modifiable_name);
			if (inp == 1)
			{
				sprintf(pGame->Material.pPlayers[selected]->playername, modifiable_name);
				is_renaming = false;
				for(int i = 0; i < 32; i++)
				modifiable_name[i] = '\0';
			}
			if (inp == 2)
			{
				is_renaming = false;
				for (int i = 0; i < 32; i++)
					modifiable_name[i] = '\0';
			}
		}



	}







}

void CMenu::RenderMatchmaking()
{
	game_t* pGame = (game_t*)father;
	RenderVersion();
	IWindow::RenderText(505, 20, 40, 255, 255, 255, 255, "Matchmaking");

	static int total_selected = 0;
	static int selected_ids[5] = { -1,-1,-1,-1,-1 };


	RenderLeftSideBar();

	char asd[64];
	sprintf(asd, "%d, %d, %d, %d, %d", selected_ids[0], selected_ids[1], selected_ids[2], selected_ids[3], selected_ids[4]);
	IWindow::RenderText(0, 80, 20, 255, 0, 0, 255, asd);

	for (int i = 0; i< pGame->Material.number_of_players; i++)
	{
		bool good = false;
		for (int z = 0; z < 5; z++)if (selected_ids[z] == i)good = true;
		if (PlayerCard(270 + i % 5 * 170, 130 + i / 5 * 110, pGame->Material.pPlayers[i], good))
		{
			if (!good)
			{
				for (int z = 0; z < 5; z++)
				{
					if (selected_ids[z] == -1)
					{
						total_selected++;
						selected_ids[z] = i;
						break;
					}
				}
			}
			else
			{
				for (int z = 0; z < 5; z++)
				{

					if (selected_ids[z] == i)
					{
						total_selected--;
						selected_ids[z] = -1;
						break;
					}
				}
			}
		}

	}


	if (total_selected == 5)
	{
		if (Button(1000, 620, 270, 90, "Start", true))
		{
			player_t* ptmA[5];
			player_t** Pointer;
			for (int i = 0; i < 5; i++)
			{
				ptmA[i] = pGame->Material.pPlayers[selected_ids[i]];

			}
			Pointer = &ptmA[0];

			pGame->CreateMatch(Pointer);

		};
	}
}

void CMenu::RenderOverView()
{
	game_t* pGame = (game_t*)father;
	RenderVersion();
	IWindow::RenderText(540, 20, 40, 255, 255, 255, 255, "Overview");

	RenderLeftSideBar();

	static char* Ranks[18] = { "Silver I", "Silver II", "Silver III", "Silver IV", "Silver Elite", "Silver Elite Master", "Gold Nova I", "Gold Nova II", "Gold Nova III", "Gold Nova Master", "Master Guardian I", "Master Guardian II", "Master Guardian Elite", "Distinguished Master Guardian", "Legendary Eagle", "Legendary Eagle Master", "Supreme Master First Class", "The Global Elite" };


	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("rankok.png");
	static sf::Texture t;
	static sf::Sprite a;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}

	Table(980, 100, 280, 240);

	auto rating = pGame->Material.teamRating;
	auto rank = 0;
	if (rating < 100)rank = 1;
	else if (rating < 200)rank = 2;
	else if (rating < 300)rank = 3;
	else if (rating < 400)rank = 4;
	else if (rating < 500)rank = 5;
	else if (rating < 600)rank = 6;
	else if (rating < 750)rank = 7;
	else if (rating < 900)rank = 8;
	else if (rating < 1050)rank = 9;
	else if (rating < 1200)rank = 10;
	else if (rating < 1450)rank = 11;
	else if (rating < 1700)rank = 12;
	else if (rating < 1950)rank = 13;
	else if (rating < 2200)rank = 14;
	else if (rating < 2600)rank = 15;
	else if (rating < 3000)rank = 16;
	else if (rating < 3500)rank = 17;
	else rank = 18;

	rank -= 1;
	int _Y = rank % 6;
	int _X = rank / 6;


	a.setPosition(990, 110);
	a.setTextureRect(sf::IntRect(210 * _X, 84 * _Y, 210, 84));
	IWindow::AddToRenderList(a);

	char buffer[256];
	sprintf(buffer, "%s\nMatches played: %d\nMatches won: %d\nRounds won: %d\nRounds lost: %d", Ranks[rank], pGame->Material.number_of_matches, pGame->Material.number_of_wins, pGame->Material.total_won_rounds,pGame->Material.total_lost_rounds);

	IWindow::RenderText(990, 200, 17, 255, 255, 255, 255, buffer);




}

void CMenu::RenderMatch()
{
	game_t* pGame = (game_t*)father;
	RenderVersion();
	char teamatext[64], teambtext[64];
	sprintf(teamatext, "Team A - %d", pGame->Match.teamA.won_rounds);
	sprintf(teambtext, "Team B - %d", pGame->Match.teamB.won_rounds);
	IWindow::RenderText(50, 50, 20, 255, 255, 255, 255, teamatext);
	IWindow::RenderText(1050, 50, 20, 255, 255, 255, 255, teambtext);
	for (int i = 0; i < 5; i++)
	{

		PlayerCard(50, 70 + i * 110, pGame->Match.teamA.ingamers[i].origin, false);
		char dollartext[128];
		sprintf(dollartext, "$%d\n%s\nKills: %d\nDeaths: %d", pGame->Match.teamA.ingamers[i].money,g_Weapons[pGame->Match.teamA.ingamers[i].weapontype[pGame->Match.teamA.ingamers[i].currentweapon]].name, pGame->Match.teamA.ingamers[i].kills, pGame->Match.teamA.ingamers[i].death);
		IWindow::RenderText(250, 70+i*110, 20, 255, 255, 255, 255, dollartext);


		PlayerCard(1050, 70 + i * 110, pGame->Match.teamB.ingamers[i].origin, false);
		char pretext[40];
		sprintf(pretext, "Kills: %d\nDeaths: %d", pGame->Match.teamB.ingamers[i].kills, pGame->Match.teamB.ingamers[i].death);
		IWindow::RenderText(750, 70 + i * 110, 20, 255, 255, 255, 255, pretext);


	}

	if (Button(400, 560, 480, 40, "Simulate Round", true))
	{
		if (pGame->Match.Think())
		{
			pGame->Match.SimulateRound();
		}

	}
	if (!pGame->Match.Think())
	{
		auto mvp = pGame->Match.GetMVP();
		Table(300, 150, 580, 300);
		char buffer[64];
		sprintf(buffer, "    The MVP\nDamage dealt: %d", mvp->damage_dealt);
		IWindow::RenderText(450, 155, 18, 255, 255, 255, 255, buffer);
		PlayerCard(600, 200, mvp->origin, true);

	}


	if (!pGame->Match.Think() && Button(400, 640, 480, 40, "Back to Lobby", true))
	{
		pGame->Match.EndMatch();
		pGame->Material.number_of_matches++;

		pGame->Material.total_won_rounds += pGame->Match.teamA.won_rounds;
		pGame->Material.total_lost_rounds += pGame->Match.teamB.won_rounds;

		if (pGame->Match.teamA.won_rounds > pGame->Match.teamB.won_rounds)
		{
			pGame->Material.number_of_wins++;
			pGame->Material.teamRating += 25;
		}
		else
		{
			pGame->Material.teamRating -= 35;
			if (pGame->Material.teamRating < 0)pGame->Material.teamRating = 0;
		}

		pGame->is_match_finished = true;
		pGame->Menu.current_tab = MENU_MATCHMAKING;
	}



}

void CMenu::RenderTheThing()
{
	if (current_tab == MENU_MAINMENU)RenderMainMenu();
	else if (current_tab == MENU_OVERVIEW)RenderOverView();
	else if (current_tab == MENU_PLAYERS)RenderPlayers();
	else if (current_tab == MENU_MATCHMAKING)RenderMatchmaking();
	else if (current_tab == MENU_MATCH)RenderMatch();
}



*/