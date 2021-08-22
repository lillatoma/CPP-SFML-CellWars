#include "structs.h"
#include "CWMenu.h"


sf::Color g_Colors[10];

float get_kvoc(int tick)
{
	double a = 100000;
	for (int i = 0; i < tick; i++)
	{
		a *= 999.f / 1000;
	}
	return ((float)a) / 100000;
}




void cmatch_t::Physics()
{
	using namespace std::chrono;
	static int count = 0;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();
	static int fps = 0;
	if (reset_timer)last = now;
	int diff = duration_cast<milliseconds>(now - last).count();
	last = now;
	if (pause)diff = 0;

	if (diff == 0)return;


	for (int i = 0; i < cell_count; i++)
	{
		if (cells[i].velocityX == 0.f && cells[i].velocityY == 0.f)
		{
			auto dx = cells[i].oposX - cells[i].posX;
			auto dy = cells[i].oposY - cells[i].posY;

			auto dist = sqrt(dx*dx + dy*dy);

			if (dist < 1) {
				cells[i].posX = cells[i].oposX;
				cells[i].posY = cells[i].oposY;
			}
			else
			{
				float mult = (float)(diff) / 50;
				auto nx = mult*(cells[i].oposX) + (dist - mult)*(cells[i].posX);
				auto ny = mult*(cells[i].oposY) + (dist - mult)*(cells[i].posY);
				nx /= dist;
				ny /= dist;
				cells[i].posX = nx;
				cells[i].posY = ny;
			}



		}
		else
		{
			for (int j = 0; j < cell_count; j++)
			{
				if (i <= j)continue;
				auto dist = CalcDistance(i, j, diff);
				if (dist * 2 < cells[i].size + cells[j].size)
				{
					//printf("\n %d with %d", i, j);
					if(CalcDistance(i,j,diff) < CalcDistance(i,j))
						CalculateReaction(cells[i].velocityX, cells[i].velocityY, cells[i].size, cells[j].velocityX, cells[j].velocityY, cells[j].size, 10 ,10);
				}

			}

			cells[i].posX += (float)diff / 1000 * cells[i].velocityX;
			cells[i].posY -= (float)diff / 1000 * cells[i].velocityY;

			float angle = 90;

			if (cells[i].velocityX != 0)angle = atan(cells[i].velocityY / cells[i].velocityX) * 180 / PI;

			int ts = 200; //slowing down speed




			if (cells[i].velocityX > 0.f)
			{
				auto kv = cos(angle * PI / 180);
				if (angle > 89 && angle < 91)kv = 1;
				cells[i].velocityX -= (double)(diff) / ts * kv;
				cells[i].velocityX *= get_kvoc(diff);
				if (cells[i].velocityX <= 0.1f)cells[i].velocityX = 0.f;
			}

			if (cells[i].velocityY > 0.f)
			{
				auto kv = sin(angle * PI / 180);
				if (angle > -1 && angle < 1)kv = 1;
				cells[i].velocityY -= (double)(diff) / ts * kv;
				cells[i].velocityY *= get_kvoc(diff);
				if (cells[i].velocityY <= 0.1f)cells[i].velocityY = 0.f;
			}
			if (cells[i].velocityX < 0.f)
			{
				auto kv = cos(angle * PI / 180);
				if (angle > 89 && angle < 91)kv = 1;
				cells[i].velocityX += (double)(diff) / ts * kv;
				cells[i].velocityX *= get_kvoc(diff);
				if (cells[i].velocityX >= -0.1f)cells[i].velocityX = 0.f;
			}

			if (cells[i].velocityY < 0.f)
			{
				auto kv = sin(angle * PI / 180);
				if (angle > -1 && angle < 1)kv = 1;
				cells[i].velocityY += (double)(diff) / ts * kv;
				cells[i].velocityY *= get_kvoc(diff);
				if (cells[i].velocityY >= -0.1f)cells[i].velocityY = 0.f;
			}

		}






		
	}

	for (int i = 0; i < cell_count; i++)
	{
		if (cells[i].posX < cells[i].size / 2 + 1) { cells[i].posX = cells[i].size / 2 + 1; cells[i].velocityX += 0.5f; }
		if (cells[i].posX > 1280 - (cells[i].size / 2 + 1)) { cells[i].posX = 1280 - (cells[i].size / 2 + 1); cells[i].velocityX -= 0.5f; }
		if (cells[i].posY < cells[i].size / 2 + 1) { cells[i].posY = cells[i].size / 2 + 1; cells[i].velocityY += 0.5f; }
		if (cells[i].posY > 715 - (cells[i].size / 2 + 1)) { cells[i].posY = 715 - (cells[i].size / 2 + 1); cells[i].velocityY -= 0.5f; }


		if (isnan(cells[i].velocityX))cells[i].velocityX = 0.f;
		if (isnan(cells[i].velocityY))cells[i].velocityX = 0.f;
		if (isnan(cells[i].posX))cells[i].posX = cells[i].oposX;
		if (isnan(cells[i].posY))cells[i].posY = cells[i].oposY;
	}
}

void cmatch_t::CalculateReaction(double &velocityAX, double &velocityAY, int massA, double &velocityBX, double &velocityBY, int massB, float distX, float distY)
{
	auto _ax = velocityAX, _ay = velocityAY, _bx = velocityBX, _by = velocityBY;

	float _ny = distX;
	float _nx = distY;

	double velA = sqrt(_ax*_ax + _ay*_ay);
	double velB = sqrt(_bx*_bx + _by*_by);

	float angA = 90, angB = 90, angN = 90;

	if(_ax != 0)
		angA = atan(-_ay / _ax) * 180 / PI;
	if (_ax < 0)angA += 180;
	if(_bx != 0)
		angB = atan(-_by / _bx) * 180 / PI;
	if (_bx < 0)angB += 180;
	if(_nx != 0)
		angN = atan(_ny / _nx) * 180 / PI;
	if (_nx < 0)angN += 180;

	if (velA == 0)angA = 180 + angB;
	if (velB == 0)angB = 180 + angA;

	while (angA < 0)angA += 360;
	while (angB < 0)angB += 360;
	while (angA > 360)angA -= 360;
	while (angB > 360)angB -= 360;


	angN = (angA*massA + angB*massB) / (massA+massB);


	auto velocity_cons = velA*massA + velB*massB;

	float newangA = angN + (angN - angA);
	float newangB = (angN + (angN - angB));

	newangA = angA + 180;
	newangB = angB + 180;

	double newvelA = velocity_cons*(massB) / (massA + massB) / massA * 1;
	double newvelB = velocity_cons*(massA) / (massA + massB) / massB * 1;

	velocityAX = cos(newangA * PI / 180) * newvelA;
	velocityAY = -sin(newangA * PI / 180)*newvelA;

	velocityBX = cos(newangB * PI / 180) * newvelB;
	velocityBY = -sin(newangB * PI / 180)*newvelB;



}

void cmatch_t::CalculateRelease(double &velocityAX, double &velocityAY, int massA, double velocityB, float angleB)
{
	/*
	if (velocityA <= 0.f)
	{
		velocityA = 1.f / massA * velocityB;
		angleA = angleB;
		return;
	}
	*/


	float _ax = velocityAX;
	float _ay = velocityAY;


	float massB = 0.5f;

	float _bx = cos(angleB*PI / 180) * velocityB;
	float _by = sin(angleB*PI / 180) * velocityB;

	float _nx = _ax*massA + _bx * massB;
	float _ny = _ay*massA + _by * massB;

	_nx /= massA + massB;
	_ny /= massA + massB;
	//auto velA = sqrt(_nx*_nx + _ny*_ny);


	//double angA = 90;

	//if (_nx != 0)
	//	angA = atan(_ny / _nx) * 180 / PI;
	//if (angleB < 0)angA += 180;

	velocityAX = _nx;
	velocityAY = _ny;
}





void cmatch_t::AddCell(cell_t c, int owner, float x, float y)
{
	cells[cell_count].cell_id = cell_count;
	cells[cell_count].owner_id = owner;
	cells[cell_count].posX = x;
	cells[cell_count].posY = y;
	cells[cell_count].oposX = x;
	cells[cell_count].oposY = y;
	cells[cell_count].produced = 0.f;
	cells[cell_count].production_speed = c.production_speed;
	cells[cell_count].size = c.size;
	cells[cell_count].species = c.species;
	cells[cell_count].speed = c.speed;

	cells[cell_count].velocityX = 0.f;
	cells[cell_count].velocityY = 0.f;

	cell_count++;

}
void cell_t::Set(int prs, int spe, int siz, int sp)
{
	production_speed = prs;
	size = siz;
	species = spe;
	speed = sp;
}

void cmatch_t::Draw(bool finished)
{
	//Drawing all cells
	for (int i = 0; i < cell_count; i++)
	{
		cells[i].Draw(finished);
	}
	static sf::CircleShape circle(1);
	circle.setPointCount(5);
	
	//Drawing species
	for (int i = 0; i < 10000; i++)
	{

		if (species[i].active)
		{
			circle.setFillColor(g_Colors[species[i].owner_id]);
			circle.setPosition(species[i].posX, species[i].posY);
			//printf("%.f %.f\n", species[i].posX, species[i].posY);
			g_Window->draw(circle);
		}
	}

	//int y = 200;
	//for (int i = 0; i < 8; i++)
	//{
	//	if (GetPercent(i + 2) > 1.f)
	//	{
	//		//char buf[48];
	//		//int decs_should_have_made = (profiles[i].spent_time - profiles[i].warmuptime) / profiles[i].decisiontime + 1;
	//		//sprintf(buf, "Int: %d | Moves : %d out of %d (%d)", profiles[i].intelligence,profiles[i].decisions_made, decs_should_have_made, profiles[i].spent_time);
	//		//IWindow::RenderTextB(0, y, buf, 20, g_Colors[i + 2].r, g_Colors[i + 2].g, g_Colors[i + 2].b,128);
	//		//y += 30;
	//	}
	//}

	//Drawing the power bar
	DrawPowerBar();


}

void cmatch_t::Produce()
{
	using namespace std::chrono;
	static int count = 0;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();
	static int fps = 0;
	if (reset_timer)last = now;
	int diff = duration_cast<milliseconds>(now - last).count();
	
	//There is nothing to calculate if the game is paused
	if (pause)
	{
		diff = 0;
		last = now;
		return;
	}

	for (int i = 0; i < cell_count; i++)
	{
		if (cells[i].owner_id == 0)continue; //<-- We skip 'world'
		if(cells[i].species <= cells[i].size + 1)
		cells[i].produced += (float)(cells[i].production_speed)*diff / 60000; 
		else
			cells[i].produced += 1200.f*diff / 60000;
		while (cells[i].produced > 1.f)
		{
			cells[i].produced -= 1.f;
			if (cells[i].species <= cells[i].size + 1)
				cells[i].species++;
			else if (cells[i].species > cells[i].size + 1)
				cells[i].species--;
		}
	}
	last = now;

}

bool cell_t::isHovered()
{
	int gx = g_Mouse.Coords.x, gy = g_Mouse.Coords.y;
	return (gx - posX)*(gx - posX) + (gy - posY)*(gy - posY) < size*size / 4;
}

void cell_t::Draw(bool finished)
{
	static sf::CircleShape circle(size/2);


	//Setting up for the filled inner circle, which shows us how filled up a cell is with species
	//The circle grows with more species
	circle.setPosition(posX - species / 2, posY - species / 2);
	circle.setRadius(species / 2);
	circle.setFillColor(sf::Color(g_Colors[owner_id].r, g_Colors[owner_id].g, g_Colors[owner_id].b, 192));
	circle.setOutlineThickness(0);
	g_Window->draw(circle);

	//Setting up the most outer circle which is transparently filled with a thick outline
	circle.setRadius(size / 2);
	circle.setPosition(posX - size / 2, posY - size / 2);
	circle.setFillColor(sf::Color(g_Colors[owner_id].r, g_Colors[owner_id].g, g_Colors[owner_id].b, 32));
	circle.setOutlineThickness(size / 25);
	circle.setOutlineColor(g_Colors[owner_id]);
	circle.setPointCount(100);
	g_Window->draw(circle);

	//Finally 3 small lines are drawn in the middle
	for (int i = 0; i < 3; i++)
	{
		circle.setRadius(size * (i+1) / 8);
		circle.setPosition(posX - size * (i + 1) / 8, posY - size * (i + 1) / 8);
		circle.setFillColor(sf::Color(0, 0, 0, 0));
		circle.setOutlineThickness(1);
		circle.setOutlineColor(sf::Color(g_Colors[owner_id].r, g_Colors[owner_id].g, g_Colors[owner_id].b,128));
		_Window::AddToRenderList(circle);
	}

	//If the match is still being played, and the cursor is on a cell
	//we draw an overlay circle to indicate that the cell being hovered
	if (isHovered() && !finished)
	{
		circle.setFillColor(sf::Color(255, 255, 255, 64));
		circle.setOutlineColor(sf::Color(255, 255, 255, 64));
		_Window::AddToRenderList(circle);
	}
}

void cmatch_t::MoveSpecies(int a, int b)
{
	if (a == b)return;
	int count = cells[a].species / 2;

	cells[a].species -= count;

	auto dx = cells[a].posX - cells[b].posX;
	auto dy = cells[a].posY - cells[b].posY;

	float angle = 90;
	if (dx != 0)
		angle = 180 + atan(-dy / dx) * 180 / PI;
	if (dx > 0)angle += 180;
	for (int i = 0; i < 10000; i++)
	{
		if (count <= 0)break;
		//Finding the first inactive species in order to make it active
		if (!species[i].active)
		{
			species[i].active = true;
			species[i].owner_id = cells[a].owner_id;
			species[i].posX = cells[a].posX + Random(-15, 15);
			species[i].posY = cells[a].posY + Random(-15, 15);
			species[i].speed = Random(cells[a].speed * 9 / 10,cells[a].speed * 10 / 9);
			species[i].target_id = b;
			count--;
			double speed = species[i].speed;
			

			//auto oldvel = cells[a].velocity;
			//CalculateReaction(cells[a].velocityX, cells[a].velocityY, cells[a].size, speed, angle, 1);
			CalculateRelease(cells[a].velocityX, cells[a].velocityY, cells[a].size*2, speed, angle);

		}


	}

}



void cmatch_t::SimulateSpecies()
{
	using namespace std::chrono;
	static int count = 0;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();
	static int fps = 0;

	if (reset_timer)
	{
		last = now;
	}
	int diff = duration_cast<milliseconds>(now - last).count();
	if (pause)diff = 0;
	timer += diff;
	last = now;

	for (int i = 0; i < 10000; i++)
	{
		if (species[i].active)
		{
			//Practically this block moves a virus instance closer to their destination
			//Then it recalculates the distance
			float dx = species[i].posX - cells[species[i].target_id].posX;
			float dy = species[i].posY - cells[species[i].target_id].posY;
			float dist = sqrt(dx*dx+dy*dy);
			
			float nx, ny;
			auto sp = species[i].speed;
			nx = (dist - sp*diff / 1000) * species[i].posX + (sp*diff / 1000) *cells[species[i].target_id].posX;
			ny = (dist - sp*diff / 1000) * species[i].posY + (sp*diff / 1000) *cells[species[i].target_id].posY;
			nx /= dist;
			ny /= dist;
			species[i].posX = nx;
			species[i].posY = ny;
			dx = species[i].posX - cells[species[i].target_id].posX;
			dy = species[i].posY - cells[species[i].target_id].posY;
			dist = sqrt(dx*dx + dy*dy);
			//If it's inside the cell, it should do something
			if (dist < cells[species[i].target_id].size/2 - 4)
			{
				float angle = 90;
				if (dx != 0)
					angle = atan(-dy / dx) * 180 / PI;
				if (dx > 0)angle += 180;

				//Cell destroy
				species[i].active = false;

				//Gross physics calculation
				CalculateRelease(cells[species[i].target_id].velocityX, cells[species[i].target_id].velocityY, cells[species[i].target_id].size*2, species[i].speed, angle);

				//If the virus instance has a cell from the same player, it reinforces it
				//Otherwise it damages it, by reducing the virus-count by one
				//In case of a cell reaching 0 'species', the ownership of it swaps in favour of the attacking virus' owner
				if (species[i].owner_id == cells[species[i].target_id].owner_id)
				{
					cells[species[i].target_id].species++;
				}
				else
				{
					cells[species[i].target_id].species--;

					if (cells[species[i].target_id].species < 0) { cells[species[i].target_id].owner_id = species[i].owner_id; cells[species[i].target_id].species = 0; }
				}
			}
			//It was for a glitch I cannot recall
			if (isnan(species[i].posX) || isnan(species[i].posY))species[i].active = false;

		}
	}
}

float cmatch_t::CalcDistance(int a, int b)
{
	auto dx = cells[a].posX - cells[b].posX;
	auto dy = cells[a].posY - cells[b].posY;

	return sqrt(dx*dx + dy*dy);
}

float cmatch_t::CalcDistance(int a, int b, int tickstogo)
{
	auto dx = cells[a].posX + cells[a].velocityX * tickstogo / 1000 - cells[b].posX - cells[b].velocityX * tickstogo / 1000;
	auto dy = cells[a].posY + cells[a].velocityY * tickstogo / 1000 - cells[b].posY - cells[b].velocityY * tickstogo / 1000;

	return sqrt(dx*dx + dy*dy);
}

bool cmatch_t::isFull(int id)
{
	int spec = 0;
	int size = 0;
	int cellc = 0;
	for (int i = 0; i < cell_count; i++)
	{
		if (cells[i].owner_id == id)
		{
			cellc++;
			spec += cells[i].species;
			size += cells[i].size;
		}
	}

	return spec > size - 2 * cellc;
}

float cmatch_t::CalcPercent(int id)
{
	int spec = 0;
	int total_spec = 0;
	for (int i = 0; i < cell_count; i++)
	{
		if (cells[i].owner_id == 0)continue;
		auto d = cells[i].species;
		if (cells[i].owner_id == id)spec+=d;

		total_spec += d;
	}

	for (int i = 0; i < 10000; i++)
	{
		if (species[i].active)
		{
			if (species[i].owner_id == id)spec++;
			total_spec++;
		}
	}

	return (float)(100 * spec) / total_spec;
}

int cmatch_t::CalcOwnedCells(int id)
{
	int cellc = 0;
	for (int i = 0; i < cell_count; i++)
	{
		if (cells[i].owner_id == id)cellc ++;

	}
	return cellc;
}

int cmatch_t::CalcOwnedSpecies(int id)
{
	int spec = 0;
	for (int i = 0; i < cell_count; i++)
	{
		if (cells[i].owner_id == 0)continue;
		auto d = cells[i].species;
		if (cells[i].owner_id == id)spec += d;
	}

	for (int i = 0; i < 10000; i++)
	{
		if (species[i].active)
		{
			if (species[i].owner_id == id)spec++;
		}
	}

	return spec;
}

int cmatch_t::CalcEmptyCells()
{
	int c = 0;
	for (int i = 0; i < cell_count; i++)
	{
		if (cells[i].owner_id == 0)c++;
	}
	return c;
}





void cmatch_t::DrawPowerBar()
{
	float x = 0;
	for (int i = 1; i < 10; i++)
	{
		auto perc = CalcPercent(i);
		float _x = perc * 1280 / 100;
		int r = g_Colors[i].r;
		int g = g_Colors[i].g;
		int b = g_Colors[i].b;
		int a = g_Colors[i].a;

		//bool longen = ((int)(x+_x))

		_Window::RenderOverlay(x, 715, _x+1, 10, r, g, b, 255);
		x += _x;

		//For our player we draw a triangle, and draw the percentage on top
		if (i == 1)
		{
			sf::Vertex triangle[] =
			{
				sf::Vertex(sf::Vector2f(x,713)),
				sf::Vertex(sf::Vector2f(x - 6,703)),
				sf::Vertex(sf::Vector2f(x + 6,703))
			};
			
			for (int j = 0; j < 3; j++)triangle[j].color = g_Colors[1];

			g_Window->draw(triangle, 3, sf::Triangles);

			char buf[16] = "";
			sprintf(buf, "%.2f%c", perc, '%');

			_Window::RenderTextB(x - 25, 680, buf, 20, g_Colors[1].r, g_Colors[1].g, g_Colors[1].b);

		}


	}






}

bool cmatch_t::hasWon()
{
	for (int i = 0; i < cell_count; i++)
	{
		if (cells[i].owner_id > 1)return false;
	}
	for (int i = 0; i < 10000; i++)
	{
		if (species[i].active && species[i].owner_id > 1)return false;
	}
	return true;
}

void cgame_t::Initialize()
{
	g_Colors[0] = sf::Color(128, 128, 128, 255);
	g_Colors[1] = sf::Color(255, 0, 0, 255);
	g_Colors[2] = sf::Color(0, 255, 0, 255);
	g_Colors[3] = sf::Color(0, 0, 255, 255);
	g_Colors[4] = sf::Color(255, 255, 0, 255);
	g_Colors[5] = sf::Color(255, 0, 255, 255);
	g_Colors[6] = sf::Color(0, 255, 255, 255);
	g_Colors[7] = sf::Color(255, 255, 255, 255);
	g_Colors[8] = sf::Color(64, 128, 192, 255);
	g_Colors[9] = sf::Color(192, 128, 64, 255);

	bg.CellCount = Random(50, 250);
	for (int i = 0; i < bg.CellCount; i++)bg.Cells[i].Initialize();

	LoadMaxLevel();
}




bool cmatch_t::hasEnded()
{
	bool active_players[10] = { false,false,false,false,false,false,false,false,false,false };
	for (int i = 0; i < cell_count; i++)
	{
		active_players[cells[i].owner_id] = true;
	}
	for (int i = 0; i < 10000; i++)
	{
		if (species[i].active)active_players[species[i].owner_id] = true;
	}

	int count = 0;
	for (int i = 1; i < 10; i++)
	{
		count += active_players[i];
	}
	return count == 1;
}




void cgame_t::Mouse()
{
	static int selected_cells = 0;
	static int cells[10];

	static sf::Color sel_col = sf::Color(255, 255, 0, 255);
	static sf::Color tar_col = sf::Color(32, 192, 0, 255);

	if (g_Mouse.isHolding())
	{
		int target = -1;

		for (int i = 0; i < 100; i++)
			if (Match.cells[i].isHovered())target = i;

		if(selected_cells <= 10)
			for (int i = 0; i < Match.cell_count; i++)
			{
				for (int s = 0; s < selected_cells; s++)
				{
					if (Match.cells[i].isHovered())
					{
						auto size = Match.cells[i].size / 2 + 7 + Match.cells[i].size / 25;
						sf::CircleShape circle(size);
						circle.setPosition(Match.cells[i].posX - size, Match.cells[i].posY - size);
						circle.setOutlineColor(tar_col);
						circle.setOutlineThickness(2);
						circle.setFillColor(sf::Color(0, 0, 0, 0));
						_Window::AddToRenderList(circle);
					}
					else if (i == cells[s])
					{
						auto size = Match.cells[i].size / 2 + 5 + Match.cells[i].size / 25;
						sf::CircleShape circle(size);
						circle.setPosition(Match.cells[i].posX - size, Match.cells[i].posY -size);
						circle.setOutlineColor(sel_col);
						circle.setOutlineThickness(2);
						circle.setFillColor(sf::Color(0, 0, 0, 0));
						_Window::AddToRenderList(circle);


						float dx = Match.cells[i].posX - g_Mouse.Coords.x;
						float dy = Match.cells[i].posY - g_Mouse.Coords.y;
						float dist = sqrt(dx*dx + dy*dy);
						if (target != -1)dist = sqrt(pow(Match.cells[i].posX - Match.cells[target].posX, 2) + pow(Match.cells[i].posY - Match.cells[target].posY, 2));
						float sx = ((dist - (dist - Match.cells[i].size/2 - 6))*g_Mouse.Coords.x + (dist - Match.cells[i].size/2- 6)*Match.cells[i].posX) / dist;
						float sy = ((dist - (dist - Match.cells[i].size/2 - 6))*g_Mouse.Coords.y + (dist - Match.cells[i].size/2- 6)*Match.cells[i].posY) / dist;

						float ex = g_Mouse.Coords.x, ey = g_Mouse.Coords.y;

						if (target != -1)
						{
							sx = ((dist - (dist - Match.cells[i].size / 2 - 6))*Match.cells[target].posX + (dist - Match.cells[i].size / 2 - 6)*Match.cells[i].posX) / dist;
							sy = ((dist - (dist - Match.cells[i].size / 2 - 6))*Match.cells[target].posY + (dist - Match.cells[i].size / 2 - 6)*Match.cells[i].posY) / dist;
							ex = ((Match.cells[target].size/2 + 8)*Match.cells[i].posX + (dist - Match.cells[target].size / 2 - 8)*Match.cells[target].posX) / dist;
							ey = ((Match.cells[target].size / 2 + 8)*Match.cells[i].posY + (dist - Match.cells[target].size / 2 - 8)*Match.cells[target].posY) / dist;
						}

						sf::Vertex line[] =
						{
							sf::Vertex(sf::Vector2f(sx,sy)),
							sf::Vertex(sf::Vector2f(ex,ey)),
							sf::Vertex(sf::Vector2f(sx+1,sy+1)),
							sf::Vertex(sf::Vector2f(ex+1,ey+1)),
							sf::Vertex(sf::Vector2f(sx+2,sy+2)),
							sf::Vertex(sf::Vector2f(ex+2,ey+2))
						};
						line[0].color = sf::Color(sel_col);
						line[1].color = sf::Color(tar_col);
						line[2].color = sf::Color(sel_col);
						line[3].color = sf::Color(tar_col);
						line[4].color = sf::Color(sel_col);
						line[5].color = sf::Color(tar_col);
						g_Window->draw(line,6,sf::Lines);
						
					}
				}
				if (!Match.cells[i].isHovered())continue;
				if (Match.cells[i].owner_id == 1)
				{
					bool should_add = true;
					for (int s = 0; s < selected_cells; s++)
					{
						if (i == cells[s] || selected_cells == 10)
						{
							should_add = false;
						}
					}

					if (should_add)
					{
						

						cells[selected_cells] = i;
						selected_cells++;
					}
				}
			}

	}
	else
	{
		bool target_found = false;
		int target_id = 0;
		for (int i = 0; i < Match.cell_count; i++)
		{
			if (Match.cells[i].isHovered())
			{
				target_found = true;
				target_id = i;
				break;
			}
		}

		if (target_found)
		{
			for (int i = 0; i < selected_cells; i++)
			{
				if(Match.cells[cells[i]].owner_id == 1)
				Match.MoveSpecies(cells[i], target_id);
				//printf("\nMoving from %d to %d", cells[i], target_id);
			}
		}

		selected_cells = 0;
	}

}


void cgame_t::RenderPause()
{
	if (GetAsyncKeyState(0x50) & 1)Match.pause = !Match.pause;
	static bool last_pause = false;

	using namespace std::chrono;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();


	if (last_pause != Match.pause)
	{
		last = now;
	}
	int diff = duration_cast<milliseconds>(now - last).count();

		if (Match.pause)
		{
			float scale = 2 - (float)diff / 1000;

			sf::Vertex paus[] =
			{
				sf::Vertex(sf::Vector2f(640 - scale * 150,360 - scale * 150)),
				sf::Vertex(sf::Vector2f(640 - scale * 50,360 - scale * 150)),
				sf::Vertex(sf::Vector2f(640 - scale * 50,360 + scale * 150)),
				sf::Vertex(sf::Vector2f(640 - scale * 150,360 + scale * 150)),
				sf::Vertex(sf::Vector2f(640 + scale * 150,360 - scale * 150)),
				sf::Vertex(sf::Vector2f(640 + scale * 50,360 - scale * 150)),
				sf::Vertex(sf::Vector2f(640 + scale * 50,360 + scale * 150)),
				sf::Vertex(sf::Vector2f(640 + scale * 150,360 + scale * 150)),
			};
			float _a = (float)(1000 - diff) / 1000 * 64;
			int a = _a;
			for (int i = 0; i < 8; i++)paus[i].color = sf::Color(255, 255, 255, a);
			if(diff < 1000)
				g_Window->draw(paus, 8, sf::Quads);


			sf::Vertex play[] =
			{
				sf::Vertex(sf::Vector2f(1200 + 24,30)),
				sf::Vertex(sf::Vector2f(1200 - 12,30 - 16)),
				sf::Vertex(sf::Vector2f(1200 - 12,30 + 16))
			};
			for (int i = 0; i < 3; i++)
			{
				if (g_Mouse.IsBetween(1185, 14, 39, 32, g_Mouse.Coords.x, g_Mouse.Coords.y))
					play[i].color = sf::Color(225, 225, 225, 255);
				else
					play[i].color = sf::Color(192,192,192, 255);

			}
			g_Window->draw(play, 3, sf::Triangles);

			_Window::RenderTextB(514, 0, "The test is currently paused", 20);

		}
		else
		{
			float scale = 1 + (float)diff / 1000;

			sf::Vertex play[] =
			{
				sf::Vertex(sf::Vector2f(640 + scale * 240,360)),
				sf::Vertex(sf::Vector2f(640 - scale * 120,360 - scale * 160)),
				sf::Vertex(sf::Vector2f(640 - scale * 120,360 + scale * 160))
			};
			float _a = (float)(1000-diff) / 1000 * 64;
			int a = _a;
			for (int i = 0; i < 3; i++)play[i].color = sf::Color(255, 255, 255, a);
			if (diff < 1000)
				g_Window->draw(play, 3, sf::Triangles);
			scale = 1;
			sf::Vertex paus[] =
			{
				sf::Vertex(sf::Vector2f(1200 - scale * 15,30 - scale * 15)),
				sf::Vertex(sf::Vector2f(1200 - scale * 5,30 - scale * 15)),
				sf::Vertex(sf::Vector2f(1200 - scale * 5,30 + scale * 15)),
				sf::Vertex(sf::Vector2f(1200 - scale * 15,30 + scale * 15)),
				sf::Vertex(sf::Vector2f(1200 + scale * 15,30 - scale * 15)),
				sf::Vertex(sf::Vector2f(1200 + scale * 5,30 - scale * 15)),
				sf::Vertex(sf::Vector2f(1200 + scale * 5,30 + scale * 15)),
				sf::Vertex(sf::Vector2f(1200 + scale * 15,30 + scale * 15)),
			};
			for (int i = 0; i < 8; i++)
			{
				if (g_Mouse.IsBetween(1185, 14, 39, 32, g_Mouse.Coords.x, g_Mouse.Coords.y))
					paus[i].color = sf::Color(225, 225, 225, 255);
				else
					paus[i].color = sf::Color(192, 192, 192, 255);

			}
			g_Window->draw(paus, 8, sf::Quads);
		}

	last_pause = Match.pause;

	if (g_Mouse.IsBetween(1185, 14, 39, 32, g_Mouse.Coords.x, g_Mouse.Coords.y) && g_Mouse.hasReleased() && g_Mouse.IsClickValid())Match.pause = !Match.pause;



}

void cgame_t::RenderIngame()
{
	bool space = GetAsyncKeyState(VK_SPACE) & 1;
	char lev[32] = "";
	sprintf(lev, "Level %d", current_level);
	bool ended = Match.hasEnded();
	bool won = Match.hasWon();

	_Window::RenderTextB(0, 0, lev, 16);

	//Does everything when the match is being played
	if (!ended)
	{
		Match.SimulateSpecies();
		Match.Produce();
		if (Match.physics_enabled)
			Match.Physics();
		if(!Match.pause)
			Mouse();
		Match.BotThink();
		Match.EditGraph();
		Match.reset_timer = false;
	}
	else Match.reset_timer = true;
	//if (GetAsyncKeyState(VK_F6) & 1)Match.MoveSpecies(1, 0);
	
	
	Match.Draw(ended || Match.pause);

	using namespace std::chrono;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();

	if (!ended)
	{
		last = now;
	}

	int dif = duration_cast<milliseconds>(now - last).count();

	float alpha = (float)dif * 128 / 4000;

	//Draws a red overlay in case of losing
	if (ended && !won)_Window::RenderOverlay(0, 0, 1280, 720, 128, 0, 0, min(alpha, 128));

	//If the match is finished, or the player loses, draws some buttons and text
	if (ended || Match.CalcPercent(1) == 0.f)
	{

		char tim[64] = "";
		int min = Match.timer / 60000;
		int sec = (Match.timer % 60000) / 1000;
		int ms = Match.timer % 1000;


		sprintf(tim, "Time elapsed: %d:%s%d.%s%s%d", min, ((sec < 10) ? ("0") : ("")), sec, ((ms < 100) ? ("0") : ("")), ((ms < 10) ? ("0") : ("")), ms);
		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++)
				_Window::RenderTextB(585 + x, 150 + y, lev, 36, 0, 0, 0, 255);

		_Window::RenderTextB(585, 150, lev, 36, 255, 255, 255, 255);

		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++)
				_Window::RenderTextB(565 + x, 200 + y, "Test finished!", 24, 0, 0, 0, 255);

		_Window::RenderTextB(565, 200, "Test finished!", 24, 255, 255, 255, 255);

		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++)
				_Window::RenderTextB(515 + x, 230 + y, tim, 24, 0, 0, 0, 255);

		_Window::RenderTextB(515, 230, tim, 24, 255, 255, 255, 255);

		if (won)
		{
			static button_t graf;
			static bool gr = false;
			if (!gr)
			{
				graf.main_color = sf::Color(192, 192, 192, 255);
				graf.hl_color = sf::Color(225,225,225, 255);
				graf.outline_color = sf::Color::Black;
				graf.text_color = sf::Color::Black;
				graf.x = 1080;
				graf.y = 620;
				graf.h = 100;
				graf.w = 200;
				graf.text = "NEXT";
				graf.textsize = 50;
				graf.tx = 35;
				graf.ty = 20;
			}


			last_success = true;

			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
					_Window::RenderTextB(553 + x, 270 + y, "Test successful!", 24, 0, 0, 0, 255);
			}

			_Window::RenderTextB(553, 270, "Test successful!", 24, 255, 255, 0, 255);

			/*for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
					IWindow::RenderTextB(500 + x, 690 + y, "Press SPACE to continue!", 24, 0, 0, 0, 255);
			}

			IWindow::RenderTextB(500, 690, "Press SPACE to continue!", 24, 255, 255, 255, 255);*/

			if (space || graf.Button())
			{
				if(current_level == level)
					level++;
				current_level++;
				tab = TAB_SHOWGRAPH;
			}

		}
		else
		{
			last_success = false;
			static button_t again;
			static bool gr = false;
			if (!gr)
			{
				again.main_color = sf::Color(192, 192, 192, 255);
				again.hl_color = sf::Color(225, 225, 225, 255);
				again.outline_color = sf::Color::Black;
				again.text_color = sf::Color::Black;
				again.x = 1080;
				again.y = 620;
				again.h = 100;
				again.w = 200;
				again.text = "NEXT";
				again.textsize = 50;
				again.tx = 35;
				again.ty = 20;
			}

			/*for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
					IWindow::RenderTextB(500 + x, 690 + y, "Press SPACE to try again!", 24, 0, 0, 0, 255);
			}

			IWindow::RenderTextB(500, 690, "Press SPACE to try again!", 24, 255, 255, 255, 255);*/

			if (space || again.Button())
			{
				tab = TAB_SHOWGRAPH;
			}
		}

	}
	//F5 loads the highest level
	if (GetAsyncKeyState(VK_F5) & 1)
	{
		Sleep(50);
		bool old_pause = Match.pause;
		LoadMaxLevel();
		Match.pause = old_pause;
	}

	//Renders the pause sign
	RenderPause();
}

void cgame_t::RenderGraph()
{
	bool space = GetAsyncKeyState(VK_SPACE) & 1;
	Match.ShowGraph();
	char lev[32] = "";
	sprintf(lev, "Level %d", current_level - last_success);
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
			_Window::RenderTextB(585 + x, 30 + y, lev, 36, 0, 0, 0, 255);
	}

	_Window::RenderTextB(585, 30, lev, 36, 255, 255, 255, 255);


	static button_t again;
	static button_t menu;
	static bool gr = false;
	//For static function setup
	if (!gr)
	{
		again.main_color = sf::Color(192, 192, 192, 255);
		again.hl_color = sf::Color(225, 225, 225, 255);
		again.outline_color = sf::Color::Black;
		again.text_color = sf::Color::Black;
		again.x = 1080;
		again.y = 620;
		again.h = 100;
		again.w = 200;
		again.text = "NEXT";
		again.textsize = 50;
		again.tx = 35;
		again.ty = 20;
		
		menu.main_color = sf::Color(192, 192, 192, 255);
		menu.hl_color = sf::Color(225, 225, 225, 255);
		menu.outline_color = sf::Color::Black;
		menu.text_color = sf::Color::Black;
		menu.x = 0;
		menu.y = 620;
		menu.h = 100;
		menu.w = 200;
		menu.text = "MENU";
		menu.textsize = 50;
		menu.tx = 35;
		menu.ty = 20;


		gr = true;
	}

	if (last_success)
	{
		again.text = "NEXT";
		again.tx = 35;
	}
	else
	{
		again.text = "AGAIN";
		again.tx = 25;
	}

	if (space || again.Button())
	{
		LoadLevel(current_level);
		tab = TAB_INGAME;
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 1 || menu.Button())
	{
		tab = TAB_MAINMENU;
	}
}

void cgame_t::RenderMainMenu()
{
	static button_t buts[4];
	static bool gr = false;
	//Static functinon setup
	if (!gr)
	{
		for (int i = 0; i < 4; i++)
		{
			buts[i].main_color = sf::Color(192, 192, 192, 255);
			buts[i].hl_color = sf::Color(225, 225, 225, 255);
			buts[i].outline_color = sf::Color::Black;
			buts[i].text_color = sf::Color::Black;
			buts[i].x = 400;
			buts[i].y = 120 + i * 120;
			buts[i].h = 100;
			buts[i].w = 480;
			buts[i].text = "MENU";
			buts[i].textsize = 50;
			buts[i].tx = 0;
			buts[i].ty = 20;
		}
		buts[0].text = "CONTINUE";


		buts[0].tx = 112;
		buts[1].text = "SELECT LEVEL";
		buts[1].tx = 60;
		buts[2].text = "OPTIONS";
		buts[2].tx = 130;
		buts[3].text = "QUIT GAME";
		buts[3].tx = 102;
		gr = true;
	}

	if (level != 1)
	{
		buts[0].text = "CONTINUE";
		buts[0].tx = 112;
	}
	else
	{
		buts[0].text = "PLAY";
		buts[0].tx = 180;
	}
	
	if (buts[0].Button())
	{
		tab = TAB_INGAME;
		LoadMaxLevel();
	}
	if (buts[1].Button())tab = TAB_CHOOSELEVEL;
	if (buts[2].Button())tab = TAB_OPTIONS;
	if (buts[3].Button())std::exit(1);



	_Window::RenderTextB(860, 675, "Created by: zenkii1337", 40, 255, 255, 255, 255);

}

void cgame_t::RenderFlash(int i)
{
	if (i > 1000)return;

	float _a = 64.f * (1000 - i) / 1000;
	int a = _a;

	_Window::RenderOverlay(0, 0, 1280, 720, 255, 255, 255, a);

}

int get_fps()
{
	using namespace std::chrono;
	static int count = 0;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();
	static int fps = 0;

	count++;

	if (duration_cast<milliseconds>(now - last).count() > 1000) {
		fps = count;
		count = 0;
		last = now;
	}

	return fps;
}

void cgame_t::RenderFPS()
{
	char fps[16];
	sprintf(fps, "%d FPS", get_fps());
	_Window::RenderTextB(1100, 0, fps, 16, 255, 255, 0, 255);
}

void cgame_t::RenderOptions()
{
	_Window::RenderOverlay(100, 80, 1080, 560, 0, 0, 0, 128);
	static button_t buts[5];
	static bool gr = false;
	static int fps_cap = 1;
	static int color = 2;


	static button_t menu;

	//Static function setup
	if (!gr)
	{
		for (int i = 0; i < 5; i++)
		{
			buts[i].main_color = sf::Color(192, 192, 192, 255);
			buts[i].hl_color = sf::Color(225, 225, 225, 255);
			buts[i].outline_color = sf::Color::Black;
			buts[i].text_color = sf::Color::Black;
			buts[i].x = 400;
			buts[i].y = 120;
			buts[i].h = 100;
			buts[i].w = 400;
			buts[i].text = "MENU";
			buts[i].textsize = 50;
			buts[i].tx = 0;
			buts[i].ty = 20;
		}
		buts[0].text = "SHOW FPS";
		buts[0].tx = 70;
		buts[0].x = 160;
		buts[1].x = 700;
		buts[1].text = "60 FPS";
		buts[1].tx = 118;
		buts[2].text = "COLOR";
		buts[2].tx = 115;
		buts[2].x = 160;
		buts[2].y = 240;
		buts[3].main_color = g_Colors[1];
		buts[3].hl_color = g_Colors[1];
		buts[3].x = 700;
		buts[3].y = 240;
		buts[3].text = nullptr;
		buts[4].text = "AUTOPAUSE";
		buts[4].x = 160;
		buts[4].y = 360;
		buts[4].tx = 50;


		menu.main_color = sf::Color(192, 192, 192, 255);
		menu.hl_color = sf::Color(225, 225, 225, 255);
		menu.outline_color = sf::Color::Black;
		menu.text_color = sf::Color::Black;
		menu.x = 0;
		menu.y = 620;
		menu.h = 100;
		menu.w = 200;
		menu.text = "MENU";
		menu.textsize = 50;
		menu.tx = 35;
		menu.ty = 20;
		gr = true;

	}
	
	if (show_fps)
	{
		buts[0].main_color = sf::Color(128, 192, 128, 255);
		buts[0].hl_color = sf::Color(160, 225, 160, 225);
	}
	else
	{
		buts[0].main_color = sf::Color(192,128, 128, 255);
		buts[0].hl_color = sf::Color(225,160, 160, 225);
	}
	if (auto_pause)
	{
		buts[4].main_color = sf::Color(128, 192, 128, 255);
		buts[4].hl_color = sf::Color(160, 225, 160, 225);
	}
	else
	{
		buts[4].main_color = sf::Color(192, 128, 128, 255);
		buts[4].hl_color = sf::Color(225, 160, 160, 225);
	}

	if (buts[0].Button())
	{
		show_fps = !show_fps;
	}
	if (buts[1].Button())
	{
		static char* fps_[] = { "30 FPS","60 FPS","120 FPS","MAX FPS" };
		static int tx[] = { 118,118,105,92};

		fps_cap++;
		if (fps_cap > 3)fps_cap = 0;

		buts[1].text = fps_[fps_cap];
		buts[1].tx = tx[fps_cap];
		if (fps_cap == 0)
			g_Window->setFramerateLimit(30);
		else if (fps_cap == 1)
			g_Window->setFramerateLimit(60);
		else if (fps_cap == 2)
			g_Window->setFramerateLimit(120);
		else if (fps_cap == 3)
			g_Window->setFramerateLimit(0);

	}
	if (buts[2].Button())
	{
		color++;
		if (color > 9)color = 2;

		auto a = g_Colors[1];
		auto b = g_Colors[color];

		g_Colors[1] = b;
		g_Colors[color] = a;
		buts[3].main_color = g_Colors[1];
		buts[3].hl_color = g_Colors[1];
	}
	buts[3].Button();
	if (buts[4].Button())auto_pause = !auto_pause;

	if (menu.Button())tab = TAB_MAINMENU;
}

void cgame_t::RenderSelect()
{
	button_t levels[15];
	static button_t menu;
	static bool gr = false;

	//Static function setup
	if (!gr)
	{
		menu.main_color = sf::Color(192, 192, 192, 255);
		menu.hl_color = sf::Color(225, 225, 225, 255);
		menu.outline_color = sf::Color::Black;
		menu.text_color = sf::Color::Black;
		menu.x = 0;
		menu.y = 620;
		menu.h = 100;
		menu.w = 200;
		menu.text = "MENU";
		menu.textsize = 50;
		menu.tx = 35;
		menu.ty = 20;
		gr = true;
	}
	static char* lname[] = { "Level 1","Level 2","Level 3","Level 4","Level 5","Level 6","Level 7","Level 8","Level 9","Level 10","Level 11","Level 12","Level 13","Level 14","Level 15" };
	for (int i = 0; i < 15; i++)
	{
		if (level > i)
		{
			levels[i].main_color = sf::Color(192, 192, 192, 255);
			levels[i].hl_color = sf::Color(225, 225, 225, 255);
		}
		else
		{
			levels[i].main_color = sf::Color(192, 192, 192, 128);
			levels[i].hl_color = sf::Color(192,192,192, 128);
		}
		levels[i].outline_color = sf::Color::Black;
		levels[i].text_color = sf::Color::Black;
		levels[i].textsize = 30;
		levels[i].text = lname[i];
		levels[i].w = 300;
		levels[i].h = 80;
		levels[i].x = 140 + (i / 5) * 350;
		levels[i].y = 60 + (i % 5) * 100;
		levels[i].tx = 102;
		levels[i].ty = 23;
		if (i >= 9)levels[i].tx -= 10;
	}

	for (int i = 0; i < 15; i++)
	{
		if (levels[i].Button() && level > i)
		{
			LoadLevel(i+1);
			tab = TAB_INGAME;
		}
	}

	if (menu.Button())tab = TAB_MAINMENU;
}

void cgame_t::Do()
{
	SimulateBackground();
	DrawBackground();
	//ApplyBackgroundShader();

	static int last_tab = tab;
	using namespace std::chrono;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();
	int diff = duration_cast<milliseconds>(now - last).count();

	if (tab != last_tab)
	{
		last = now;
		last_tab = tab;
	}

	RenderFlash(diff);
	if (tab == TAB_INGAME)
		RenderIngame();
	else if (tab == TAB_SHOWGRAPH)
		RenderGraph();
	else if (tab == TAB_MAINMENU)
		RenderMainMenu();
	else if (tab == TAB_OPTIONS)
		RenderOptions();
	else if (tab == TAB_CHOOSELEVEL)
		RenderSelect();

	if (show_fps)RenderFPS();

	if (GetAsyncKeyState(VK_ESCAPE))tab = TAB_MAINMENU;


}

void cmatch_t::EditGraph()
{
	if (timer >= graph_timer)
	{
		int points = graph_timer / 250;

		for (int i = 0; i < 9; i++)
		{
			graph[points].spec[i] = CalcOwnedSpecies(i + 1);
		}

		graph_timer += 250;
	}
}

void cmatch_t::ShowGraph()
{
	bool active[9] = { false, false, false, false, false, false, false, false, false };
	int peak = 0;
	int points = graph_timer / 250;

	for (int i = 0; i < points; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (graph[i].spec[j] > peak)peak = graph[i].spec[j];
		}
	}

	sf::Vertex** data;
	
	data = new sf::Vertex*[9];

	for (int i = 0; i < 9; i++) {
		data[i] = new sf::Vertex[points];
		if (graph[0].spec[i] != 0)active[i] = true;
	}
	for (int i = 0; i < points; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			float x = 240 + (float)i * 800 / points;
			float y = 610 - (float)graph[i].spec[j] * 500 / peak;
			data[j][i] = sf::Vertex(sf::Vector2f(x, y));
			data[j][i].color = g_Colors[j + 1];
		}
	}





	_Window::RenderOverlay(240, 110, 800, 500, 0, 0, 0, 128);

	for (int i = 0; i < 6; i++)
	{
		_Window::RenderOverlay(240 + i * 160, 110, 1, 500, 32, 32, 32, 255);
		char tim[16];

		int _timer = graph_timer * i / 5;

		int min = _timer / 60000;
		int sec = (_timer % 60000) / 1000;


		sprintf(tim, "%d:%s%d", min, ((sec < 10) ? ("0") : ("")), sec);
		_Window::RenderTextB(225 + i * 160, 610, tim, 16);


		_Window::RenderOverlay(240, 110 + i * 100, 800, 1, 32, 32, 32, 255);
		if (i == 5)continue;
		char co[16];
		sprintf(co, "%d", peak*(5 - i) / 5);
		_Window::RenderTextB(200, 100 + i * 100, co, 16);

	}


	using namespace std::chrono;
	static auto last = high_resolution_clock::now();
	auto now = high_resolution_clock::now();

	static int last_peak = 0;
	static int last_length = 0;

	//It's very rare that the peak and exact length of two different matches are the same
	//In case this would happen, the graph would be fully drawn, without the animation
	if (last_peak != peak || last_length != timer)
	{
		last = now;
	}
	int diff = duration_cast<milliseconds>(now - last).count();

	for (int i = 0; i < 9; i++)
	{
		if (active[i])g_Window->draw(data[i], min(points,points*diff/2000), sf::PrimitiveType::LineStrip);
	}

	for (int i = 0; i < 9; i++)
	{
		delete[] data[i];
	}
	delete[] data;

	last_peak = peak;
	last_length = timer;
}