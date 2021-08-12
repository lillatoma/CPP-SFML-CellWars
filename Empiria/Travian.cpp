#include "Interfaces.h"

void travian_t::Initalize()
{
	Map.GenerateMap();

	AddNewPlayer();
	AddLocalPlayer();
	AddNewPlayer();
	IBuildings::CreateAllBuildings();
	events.main = this;
}

void travian_t::Draw()
{
	IWindow::RenderOverlay(0, 0, 1280, 720, 74, 172, 44, 255);

	if (Tab == 0)DrawOuter();
	else if (Tab == 1)DrawInner();
	else if (Tab == 2)DrawMap();

	DrawMenu();
}

void travian_t::DrawMap()
{
	int s = 7 * 70;
	

	static int pmx = 0;
	static int pmy = 0;

	static bool selected = false;
	static int sel_x = 0, sel_y = 0;

	while (map_x < -400.5)map_x += 801;
	while (map_x > 400.5)map_x -= 801;
	while (map_y < -400.5) map_y += 801;
	while (map_y > 400.5)map_y -= 801;



	bool holding = g_Mouse.isHolding();
	bool is_left_good = g_Mouse.IsBetween((1280 - s) / 2, (720 - s) / 2 + 100, s, s, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y);

	int m_x = g_Mouse.leftclickCoords.x, m_y = g_Mouse.leftclickCoords.y;

	float s_x, s_y;

	if (holding && is_left_good)
	{
		int dx = g_Mouse.Coords.x - g_Mouse.leftclickCoords.x;
		int dy = g_Mouse.Coords.y - g_Mouse.leftclickCoords.y;
		s_x = map_x-  (float)dx/70;
		s_y = map_y + (float)dy/70;
		pmx = dx, pmy = dy;
	}
	else
	{
		s_x = map_x;
		s_y = map_y;
	}

	if (g_Mouse.hasReleased() && is_left_good)
	{
		map_x = map_x - (float)pmx / 70;
		map_y = map_y + (float)pmy / 70;
	}

	
	int left, top;
	if (s_x > 4)left = s_x - 3.5f;
	else left = s_x - 4.5f;

	if (s_y < -4)top = s_y + 3.5f;
	else top = s_y + 4.5f;



	float tx = s_x - left-4.5f;
	float ty = s_y - top + 4.5f;

	if (g_Mouse.hasReleased() && g_Mouse.IsClickValid())
	{
		if (!g_Mouse.IsBetween(640 - s / 2, 460 - s / 2, s, s, m_x, m_y) && !g_Mouse.IsBetween(900, 300, 300, 400, m_x, m_y))selected = false;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int cx = left + i;
			int cy = top - j;
			int _x = 640 - s / 2 + i*s / 7 - s / 7 - (s * tx) / 7;
			int _y = 460 - s / 2 + j* s / 7 - s / 7 + (s * ty) / 7;


			while (cx < -400.5)cx += 801;
			while (cx > 400.5)cx -= 801;
			while (cy < -400.5) cy += 801;
			while (cy > 400.5)cy -= 801;

			Map.DrawAField(_x,_y, cx,cy, s/7);

			char buf[16];
			sprintf(buf,"%d | %d", cx, cy);
			IWindow::RenderTextB(_x, _y, buf, 12, 0, 0, 0, 255);

			if (g_Mouse.hasReleased() && g_Mouse.IsClickValid())
			{

				if (g_Mouse.IsBetween(_x, _y, s / 7, s / 7, m_x, m_y))
				{
					if (g_Mouse.IsBetween(640 - s / 2, 460 - s / 2, s, s, m_x, m_y))
					{
						selected = true;
						sel_x = cx; sel_y = cy;
					}
				}
			}
		}
	}
	//IWindow::RenderOverlay((1280 - s) / 2, (720 - s) / 2 + 100, s, s, 255, 255, 255, 255);
	if (GetAsyncKeyState(VK_LEFT))map_x -= 0.01f;
	if (GetAsyncKeyState(VK_UP))map_y += 0.01f;

	int alph = 255;
	IWindow::RenderOverlay(0, 0, 640 - s / 2, 720, 74, 172, 44, alph);
	IWindow::RenderOverlay(0, 0, 1280, 360 - s / 2 + 100, 74, 172, 44, alph);
	IWindow::RenderOverlay(640 - s / 2 + s, 0, 1280, 720, 74, 172, 44, alph);
	IWindow::RenderOverlay(0, 360 - s / 2 + s + 100, 1280, 720, 74, 172, 44, alph);
	
	
	if (selected)
	{
		int resp = Map.DrawFieldInfo(sel_x, sel_y);
		
		if (resp == 1)
		{
			map_x = sel_x + 0.5f;
			map_y = sel_y - 0.5f;
		}
	}
}

void travian_t::DrawMenu()
{

	static int time = 0;
	int old_time = time;
	time = 0;

	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("menu.png");
	static sf::Texture t;
	static sf::Sprite a;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}

	bool klik = g_Mouse.hasReleased() && g_Mouse.IsClickValid();

	for (int i = 0; i < 5; i++)
	{
		a.setTextureRect(sf::IntRect(i * 100, 0, 100, 100));

		a.setPosition(390 + i * 100, 0);

		if (g_Mouse.IsBetween(390 + i * 100, 0, 100, 100, g_Mouse.Coords.x, g_Mouse.Coords.y))
			a.setColor(sf::Color(255, 255, 255, 255));
		else if (Tab == i)a.setColor(sf::Color(128, 255, 128, 255));
		else a.setColor(sf::Color(192, 192, 192, 255));

		IWindow::AddToRenderList(a);

		if (klik && g_Mouse.IsBetween(390 + i * 100, 0, 100, 100, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))
		{
			Tab = i;
			if (i == 2) 
				{
					map_x = local->villages[local->selected_village]->field->x + 0.5f; 
					map_y = local->villages[local->selected_village]->field->y - 0.5f;
				}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		static char* resn[5] = { "Outer", "Inner", "Map", "Stats","Tools" };
		if (g_Mouse.IsBetween(390 + i * 100, 0,100,100, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			time = old_time;
			time++;

			if (time > 30)
			{
				IWindow::RenderOverlay(g_Mouse.Coords.x, g_Mouse.Coords.y, 75, 30, 0, 0, 0, min(255, (time - 30) * 16));
				IWindow::RenderOverlay(g_Mouse.Coords.x + 1, g_Mouse.Coords.y + 1, 73, 28, 96, 96, 96, min(255, (time - 30) * 16));
				IWindow::RenderTextB(g_Mouse.Coords.x + 1, g_Mouse.Coords.y + 1, resn[i], 24);
			}
		}


	}

}

village_t* travian_t::GenerateNewVillage(int cx, int cy)
{
	auto v = &villages;
	while (v->next)
	{ 
		v = v->next;
	}
	v->next = new village_t;
	
	auto pField = &Map.fields[cx + 400][cy + 400];
	
}

void travian_t::AddNewPlayer()
{
	float range = 20.f;
	
	int ID = 0;
	auto pp = &players;
	while (pp->next)
	{
		pp = pp->next;
		ID++;
	}
	pp->next = new player_t;
	pp->next->base = this;
	pp->next->Initialize(range,Random(1,3));
	pp->next->id = ID + 1;

}

void travian_t::AddLocalPlayer()
{
	float range = 20.f;
	auto pp = &players;
	while (pp->next)pp = pp->next;

	pp->next = new player_t;
	pp->next->base = this;
	local = pp->next;

	pp->next->Initialize(range, Random(1, 3));
}

void travian_t::DrawActiveConstructions()
{
	int sum = IEvents::CountEvents(&events, local->villages[local->selected_village], _EVENT_BUILD_INNER) + IEvents::CountEvents(&events, local->villages[local->selected_village], _EVENT_BUILD_OUTER);

	if (sum <= 0)return;


	IWindow::RenderOverlay(320, 610, 640, 120, 255, 255, 255, 255);

	int count = 0;
	for (int i = events.active_events - 1; i >= 0; i--)
	{
		if (count >= 3)break;
		auto eve = &events.events[i];
		if (eve->requesting_id != local->villages[local->selected_village]->id)continue;
		int time;
		if (eve->eventtype == _EVENT_BUILD_INNER)
		{
			time = eve->event_force_time - events.Time;
			int type = local->villages[local->selected_village]->inner.buildings[eve->building_id].type;
			int level = eve->building_level;

			int hr = time / 60, mn = time % 60;


			char buffer[128];
			sprintf(buffer, "%s Level %d\tin %d:%s%d", IBuildings::GetBuildingName(type), level, hr, ((time > 10) ? ("") : "0"), mn);

			IWindow::RenderTextB(335, 620 + count * 25, buffer, 20, 0, 0, 0);
			count++;
		}
		else if (eve->eventtype == _EVENT_BUILD_OUTER)
		{
			time = eve->event_force_time - events.Time;
			int type = local->villages[local->selected_village]->outer.buildings[eve->building_id].type;
			int level = eve->building_level;

			int hr = time / 60, mn = time % 60;


			char buffer[128];
			sprintf(buffer, "%s Level %d\tin %d:%s%d", IBuildings::GetBuildingName(type), level, hr, ((time > 10) ? ("") : "0"), mn);
			IWindow::RenderTextB(335, 620 + count * 25, buffer, 20, 0, 0, 0);
			count++;
		}
		else continue;

		IWindow::RenderOverlay(900, 595 + count * 25, 50, 22, 120, 180, 45, 255);
		IWindow::RenderTextB(905, 592 + count * 25, "skip", 22);
		if (g_Mouse.hasReleased() && g_Mouse.IsClickValid() && g_Mouse.IsBetween(900, 595 + count * 25, 50, 22, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))
			IEvents::TimeTravel(&events, time);
	}
	
	//printf("\nsum: %d", sum);
}

void travian_t::DrawResourceBar()
{
	IWindow::RenderOverlay(320, 110, 640, 50, 255, 255, 255, 255);
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("mats.png");
	static sf::Texture t;
	static sf::Sprite a;

	static int time = 0;
	int old_time = time;
	time = 0;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}

	for (int i = 0; i < 4; i++)
	{
		a.setTextureRect(sf::IntRect(i * 32, 0, 32, 32));
		a.setPosition(330 + i * 160, 119);
		IWindow::RenderOverlay(325+ i * 160, 115, 150, 40, 192, 192, 192, 192);
		IWindow::RenderOverlay(330 + i * 160, 147, 140, 5, 64, 64, 64, 255);

		

		IWindow::AddToRenderList(a);
	}

	char wd[32], cl[32], ir[32], wh[32];

	int ware = 800;
	int gran = 800;
	auto sv = local->villages[local->selected_village];
	

	sprintf(wd, "%.f/%d\0", sv->res.Wood, ware);
	sprintf(cl, "%.f/%d\0", sv->res.Clay, ware);
	sprintf(ir, "%.f/%d\0", sv->res.Iron, ware);
	sprintf(wh, "%.f/%d\0", sv->res.Wheat, gran);

	IWindow::RenderTextB(362, 125, wd, 16, 0, 0, 0, 255);
	IWindow::RenderTextB(522, 125, cl, 16, 0, 0, 0, 255);
	IWindow::RenderTextB(682, 125, ir, 16, 0, 0, 0, 255);
	IWindow::RenderTextB(842, 125, wh, 16, 0, 0, 0, 255);

	IWindow::RenderOverlay(330, 147, 140 * sv->res.Wood / ware, 5, 120, 180, 60, 255);
	IWindow::RenderOverlay(490, 147, 140 * sv->res.Clay / ware, 5, 120, 180, 60, 255);
	IWindow::RenderOverlay(650, 147, 140 * sv->res.Iron/ ware, 5, 120, 180, 60, 255);
	IWindow::RenderOverlay(810, 147, 140 * sv->res.Wheat / ware, 5, 120, 180, 60, 255);


	for (int i = 0; i < 4; i++)
	{
		static char* resn[4] = { "Wood", "Clay", "Iron", "Wheat" };
		if (g_Mouse.IsBetween(325 + i * 160, 115, 150, 40, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			time = old_time;
			time++;

			if (time > 30)
			{
				IWindow::RenderOverlay(g_Mouse.Coords.x, g_Mouse.Coords.y, 75, 30, 0, 0, 0, min(255, (time - 30) * 16));
				IWindow::RenderOverlay(g_Mouse.Coords.x + 1, g_Mouse.Coords.y + 1, 73, 28, 96, 96, 96, min(255, (time - 30) * 16));
				IWindow::RenderTextB(g_Mouse.Coords.x + 1, g_Mouse.Coords.y + 1, resn[i], 24);
			}
		}


	}
}

void travian_t::DrawOuter()
{

	static int selected = -1;

	if (g_Mouse.hasReleased() && g_Mouse.IsClickValid() && g_Mouse.IsBetween(320, 0, 640, 160, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))selected = -1;

	if (selected == -1)
	{

		//IWindow::RenderOverlay(320, 110, 640, 50, 255, 255, 255, 255);
		static bool bLoaded = false;
		static file_t f = g_Files.GetFileByName("outervillage.png");
		static sf::Texture t;
		static sf::Sprite a;

		if (!bLoaded)
		{
			bLoaded = true;
			t.loadFromMemory(f.loc_in_mem, f.size);
			a.setTexture(t);
			a.setPosition(542, 351);
		}
		if (g_Mouse.IsBetween(542, 351, 160, 160, g_Mouse.Coords.x, g_Mouse.Coords.y))
		{
			IWindow::RenderOverlay(542, 351, 160, 160, 255, 255, 192, 32);
			a.setColor(sf::Color(255, 255, 192, 255));
		}
		else a.setColor(sf::Color(225, 225, 192, 255));

		IWindow::AddToRenderList(a);

		if (g_Mouse.hasReleased() && g_Mouse.IsClickValid() && g_Mouse.IsBetween(542, 351, 160, 160, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))Tab = 1;


		static int coord[18][2] = { {136,317}, {621,209}, {670,508}, {899, 290}, {383,289}, {263,354},
		{386,174},{735,176},{147,455},{787,416},{736,295},{919,421},
		{294,462},{415,400},{517,507},{508,233},{257,228},{851,169} };



		static bool abLoaded = false;
		static file_t af = g_Files.GetFileByName("buildings.png");
		static sf::Texture at;
		static sf::Sprite aa;

		if (!abLoaded)
		{
			abLoaded = true;
			at.loadFromMemory(af.loc_in_mem, af.size);
			aa.setTexture(at);
		}
		auto village = local->villages[local->selected_village];
		for (int i = 0; i < 18; i++)
		{
			if (g_Mouse.IsBetween(coord[i][0], coord[i][1], 100, 100, g_Mouse.Coords.x, g_Mouse.Coords.y))
				IWindow::RenderOverlay(coord[i][0], coord[i][1], 100, 100, 255, 255, 255, 32);
			aa.setTextureRect(sf::IntRect(village->outer.buildings[i].type * 100, 0, 100, 100));
			aa.setPosition(coord[i][0], coord[i][1]);

			sf::CircleShape Circle;
			Circle.setFillColor(sf::Color(255, 255, 255));
			Circle.setOutlineColor(sf::Color(0, 0, 0));
			Circle.setOutlineThickness(1);

			Circle.setPosition(coord[i][0] + 35, coord[i][1] + 35);
			Circle.setRadius(15);
			if (village->outer.buildings[i].level != village->outer.buildings[i].hi_level)Circle.setFillColor(sf::Color(255, 170, 80));

			IWindow::AddToRenderList(aa);
			IWindow::AddToRenderList(Circle);

			char buf[16];
			sprintf(buf, "%d\0", village->outer.buildings[i].level);
			IWindow::RenderTextB(coord[i][0] + 45, coord[i][1] + 41, buf, 16, 0, 0, 0);

			if (g_Mouse.hasReleased() && g_Mouse.IsClickValid())
				if (g_Mouse.IsBetween(coord[i][0], coord[i][1], 100, 100, g_Mouse.Coords.x, g_Mouse.Coords.y))
					selected = i;
		}



		IWindow::RenderOverlay(1040, 160, 240, 400, 255, 255, 255, 255);
		IWindow::RenderTextB(1050, 170, "Production", 24, 0, 0, 0);

		IWindow::RenderOverlay(320, 110, 640, 50, 255, 255, 255, 255);
		static bool cbLoaded = false;
		static file_t cf = g_Files.GetFileByName("mats.png");
		static sf::Texture ct;
		static sf::Sprite ca;
		static char* resnames[4] = { "Wood","Clay","Iron","Wheat" };

		{
			cbLoaded = true;
			ct.loadFromMemory(cf.loc_in_mem, cf.size);
			ca.setTexture(ct);
		}

		auto prod = IBuildings::GetProduction(village);



		int pr[4] = { (int)prod.Wood, (int)prod.Clay, (int)prod.Iron, (int)prod.Wheat };
		for (int i = 0; i < 4; i++)
		{
			ca.setTextureRect(sf::IntRect(i * 32, 0, 32, 32));
			ca.setPosition(1050, 200+i*36);
			IWindow::AddToRenderList(ca);

			char buf[24];
			sprintf(buf, "%s: %d/hr", resnames[i], pr[i]);

			IWindow::RenderTextB(1090, 200 + i * 36, buf, 24, 0, 0, 0);
		}


	}
	else
	{
		auto village = local->villages[local->selected_village];
		IWindow::RenderOverlay(320, 200, 640, 400, 225, 225, 225, 255);
		char titlebuf[64];
		sprintf(titlebuf, "%s Level %d", IBuildings::GetBuildingName(village->outer.buildings[selected].type), village->outer.buildings[selected].level);
		IWindow::RenderTextB(330, 210, titlebuf, 32, 0, 0, 0);
		
		char buf[96];
		sprintf(buf, "Production: %d/hr\nProduction next level: %d/hr", IBuildings::GetProductionForLevel(village->outer.buildings[selected].level), IBuildings::GetProductionForLevel(village->outer.buildings[selected].hi_level + 1));
		IWindow::RenderTextB(370, 250, buf, 20, 0, 0, 0);

		static bool cbLoaded = false;
		static file_t cf = g_Files.GetFileByName("mats.png");
		static sf::Texture ct;
		static sf::Sprite ca;
		static char* resnames[4] = { "Wood","Clay","Iron","Wheat" };

		{
			cbLoaded = true;
			ct.loadFromMemory(cf.loc_in_mem, cf.size);
			ca.setTexture(ct);
		}

		for (int i = 0; i < 2; i++)
		{
			ca.setPosition(335, 245 + i * 24);
			ca.setTextureRect(sf::IntRect((village->outer.buildings[selected].type - WOOD) * 32, 0, 32, 32));
			IWindow::AddToRenderList(ca);
		}

		auto cost = IBuildings::GetCost(village->outer.buildings[selected].type,village->outer.buildings[selected].hi_level);
		int c[4] = { cost.Wood, cost.Clay, cost.Iron, cost.Wheat };
		IWindow::RenderTextB(330, 320, "Upgrade cost:", 20, 0, 0, 0);
		for (int i = 0; i < 4; i++)
		{
			ca.setPosition(335, 345 + i * 30);
			ca.setTextureRect(sf::IntRect(i * 32, 0, 32, 32));
			IWindow::AddToRenderList(ca);
			char buf[16];
			sprintf(buf, "%d", c[i]);
			IWindow::RenderTextB(365, 345 + i * 30, buf, 24, 0, 0, 0);
		}

		char up_buf[32];
		sprintf(up_buf, "Upgrade to level %d", village->outer.buildings[selected].hi_level + 1);
		IWindow::RenderOverlay(330, 480, 300, 40, 0,0,0, 255);
		
		bool enough = cost <= village->res;

		if(!enough)
			IWindow::RenderOverlay(332, 482, 296, 36, 160, 70, 50, 255);
		else if(g_Mouse.IsBetween(330,480,300,40,g_Mouse.Coords.x,g_Mouse.Coords.y))
			IWindow::RenderOverlay(332, 482, 296, 36, 135*1.25, 160*1.25, 50*1.25, 255);
		else 	IWindow::RenderOverlay(332, 482, 296, 36, 135, 160, 50, 255);
		IWindow::RenderTextB(360, 487, up_buf, 20, 255, 255, 255);

		if (enough && g_Mouse.hasReleased() && g_Mouse.IsClickValid())
		{
			if (g_Mouse.IsBetween(330, 480, 300, 40, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))
			{
				local->BuildOuter(selected);
				selected = -1;
			}
		}

	}
	DrawResourceBar();
	DrawActiveConstructions();
}

void travian_t::DrawUniqueBuildingMessage(int &selected)
{
	auto village = local->villages[local->selected_village];
	IWindow::RenderOverlay(320, 200, 640, 400, 225, 225, 225, 255);
	char titlebuf[64];
	sprintf(titlebuf, "%s Level %d", IBuildings::GetBuildingName(village->inner.buildings[selected].type), village->inner.buildings[selected].level);
	IWindow::RenderTextB(330, 210, titlebuf, 32, 0, 0, 0);



	static bool cbLoaded = false;
	static file_t cf = g_Files.GetFileByName("mats.png");
	static sf::Texture ct;
	static sf::Sprite ca;
	static char* resnames[4] = { "Wood","Clay","Iron","Wheat" };

	{
		cbLoaded = true;
		ct.loadFromMemory(cf.loc_in_mem, cf.size);
		ca.setTexture(ct);
	}


	auto cost = IBuildings::GetCost(village->inner.buildings[selected].type, village->inner.buildings[selected].hi_level);
	int c[4] = { cost.Wood, cost.Clay, cost.Iron, cost.Wheat };
	IWindow::RenderTextB(330, 320, "Upgrade cost:", 20, 0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		ca.setPosition(335, 345 + i * 30);
		ca.setTextureRect(sf::IntRect(i * 32, 0, 32, 32));
		IWindow::AddToRenderList(ca);
		char buf[16];
		sprintf(buf, "%d", c[i]);
		IWindow::RenderTextB(365, 345 + i * 30, buf, 24, 0, 0, 0);
	}

	char up_buf[32];
	sprintf(up_buf, "Upgrade to level %d", village->inner.buildings[selected].hi_level + 1);
	IWindow::RenderOverlay(330, 480, 300, 40, 0, 0, 0, 255);

	bool enough = cost <= village->res;

	if (!enough)
		IWindow::RenderOverlay(332, 482, 296, 36, 160, 70, 50, 255);
	else if (g_Mouse.IsBetween(330, 480, 300, 40, g_Mouse.Coords.x, g_Mouse.Coords.y))
		IWindow::RenderOverlay(332, 482, 296, 36, 135 * 1.25, 160 * 1.25, 50 * 1.25, 255);
	else 	IWindow::RenderOverlay(332, 482, 296, 36, 135, 160, 50, 255);
	IWindow::RenderTextB(360, 487, up_buf, 20, 255, 255, 255);

	if (enough && g_Mouse.hasReleased() && g_Mouse.IsClickValid())
	{
		if (g_Mouse.IsBetween(330, 480, 300, 40, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))
		{
			local->BuildInner(selected);
			selected = -1;
		}
	}
}

void travian_t::DrawInner()
{

	static int selected = -1;
	auto village = local->villages[local->selected_village];
	if (g_Mouse.hasReleased() && g_Mouse.IsClickValid() && g_Mouse.IsBetween(320, 0, 640, 160, g_Mouse.leftclickCoords.x, g_Mouse.leftclickCoords.y))selected = -1;

	if (selected == -1)
	{

		static int coord[22][2] = { {587,246},{ 686,278},{584,374},{498,354},{499,267},{387,169},
		{489,175},{587,169},{689,182},{787,169},{396,262},{375,365}, 
		{786,264},{784,359},{349,456},{447,454},{549,465},{645,464}, 
		{734,457},{827,450},{681,368},{0,0}, };



		static bool abLoaded = false;
		static file_t af = g_Files.GetFileByName("buildings.png");
		static sf::Texture at;
		static sf::Sprite aa;

		if (!abLoaded)
		{
			abLoaded = true;
			at.loadFromMemory(af.loc_in_mem, af.size);
			aa.setTexture(at);
			aa.setScale(0.8f, 0.8f);
		}

		for (int i = 0; i < 21; i++)
		{

			if (g_Mouse.IsBetween(coord[i][0], coord[i][1], 80, 80, g_Mouse.Coords.x, g_Mouse.Coords.y))
				IWindow::RenderOverlay(coord[i][0], coord[i][1], 80, 80, 255, 255, 255, 32);

			if (village->inner.buildings[i].defined && village->inner.buildings[i].hi_level > 0)
			{
				aa.setTextureRect(sf::IntRect(village->inner.buildings[i].type * 100, 0, 100, 100));
				aa.setPosition(coord[i][0], coord[i][1]);


				

				IWindow::AddToRenderList(aa);




			}
			sf::CircleShape Circle;
			Circle.setFillColor(sf::Color(255, 255, 255));
			Circle.setOutlineColor(sf::Color(0, 0, 0));
			Circle.setOutlineThickness(1);
			if (village->inner.buildings[i].level != village->inner.buildings[i].hi_level)Circle.setFillColor(sf::Color(255, 170, 80));
			Circle.setPosition(coord[i][0] + 35, coord[i][1] + 35);
			Circle.setRadius(15);
			IWindow::AddToRenderList(Circle);
			if (village->inner.buildings[i].defined && village->inner.buildings[i].hi_level > 0)
			{
				char buf[16];
				sprintf(buf, "%d\0", village->inner.buildings[i].level);
				IWindow::RenderTextB(coord[i][0] + 45, coord[i][1] + 41, buf, 16, 0, 0, 0);
			}

			if (g_Mouse.hasReleased() && g_Mouse.IsClickValid())
				if (g_Mouse.IsBetween(coord[i][0], coord[i][1], 100, 100, g_Mouse.Coords.x, g_Mouse.Coords.y))
					selected = i;
		}
	}
	else DrawUniqueBuildingMessage(selected);
	DrawResourceBar();
	DrawActiveConstructions();
}


village_t* travian_t::GetVillage(int id)
{
	auto pVil = &villages;
	

	while (pVil->id != id && pVil->next != nullptr)
	{
		//printf("p%d", pVil->id);
		pVil = pVil->next;
		
	}

	return pVil;
}

void travian_t::Produce()
{
	auto village = &villages;

	while (village)
	{
		auto prod = IBuildings::GetProduction(village);

		prod.multiply(1.f / 60);
		village->res.add(prod);
		village->res.setmax(IBuildings::GetMaxStorage(village));

		village = village->next;
	}



}