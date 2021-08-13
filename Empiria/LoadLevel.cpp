#include "structs.h"


void cgame_t::LoadMaxLevel()
{
	//Whaw, what a solution :D
	if (level > 15)level = 15;
	current_level = level;
	Match.Reset(auto_pause);
	cell_t c;
	switch (level)
	{
	case 11:
		c.Set(1800, 60, 250, 150);
		Match.AddCell(c, 1, 930, 520);
		Match.AddCell(c, 2, 350, 200);

		c.Set(1200, 30, 200, 150);
		Match.AddCell(c, 0, 650, 200);
		Match.AddCell(c, 0, 350, 500);
		Match.AddCell(c, 0, 630, 520);
		Match.AddCell(c, 0, 930, 220);

		Match.profiles[0].SetPercents(25, 60);
		Match.profiles[0].SetToughness(1, 1000, 300);

		Match.cells[1].species = 180;
		break;
	case 12:
		c.Set(2100, 75, 125, 100);
		Match.AddCell(c, 0, 640, 358);
		c.Set(600, 15, 75, 100);
		for (int i = 0; i < 5; i++)
		{
			float x = 640 + cos((float)i * 72 * PI / 180) * 120;
			float y = 358 + sin((float)i * 72 * PI / 180) * 120;

			Match.AddCell(c, 0, x, y);
		}


		for (int i = 0; i < 4; i++)
		{
			c.Set(1200, 50, 150, 100);
			Match.AddCell(c, i + 1, 150 + (i % 2) * 980, 150 + (i / 2) * 420);
			c.Set(600, 15, 75, 100);

			for (int j = 0; j < 4; j++)
			{
				float x = 150 + cos((float)(36 -j * 48) * PI / 180) * 150;
				float y = 150 - sin((float)(36 -j * 48)* PI / 180) * 150;

				if (i % 2)x = 1280 - x;
				if (i / 2)y = 715 - y;
				Match.AddCell(c, 0, x, y);
			}
		}
		for (int i = 0; i < 3; i++)
		{
			Match.profiles[i].SetPercents(Random(10, 30), Random(15, 40));
			Match.profiles[i].SetToughness(1, Random(900, 1111), Random(500, 800));
		}

		break;
		








	case 1:
		c.Set(600, 50, 200, 120);
		Match.AddCell(c, 1, 150, 150);
		Match.AddCell(c, 2, 1280 - 150, 715 - 150);
		c.Set(600, 25, 200, 120); Match.AddCell(c, 0, 640, 358);
		c.Set(600, 10, 75, 120);
		Match.AddCell(c, 0, 320, 150);
		Match.AddCell(c, 0, 150, 320);
		Match.AddCell(c, 0, 1280 - 320, 715 - 150);
		Match.AddCell(c, 0, 1280 - 150, 715 - 320);

		Match.AddCell(c, 0, 490, 208);
		Match.AddCell(c, 0, 1280 - 490, 208);
		Match.AddCell(c, 0, 490, 715 - 208);
		Match.AddCell(c, 0, 1280 - 490, 715 - 208);

		Match.profiles[0].SetToughness(0, 10000, 0);

		break;
	case 2:
		c.Set(1500, 50, 120, 120);
		Match.AddCell(c, 0, 640, 358);
		c.Set(600, 50, 150, 120);
		Match.AddCell(c, 1, 75, 75);
		Match.AddCell(c, 2, 1205, 640);
		c.Set(600, 5, 50, 120);
		for (int i = 0; i < 6; i++)
		{
			if (i < 3)
			{
				int dist = 75 + 50 + 50;
				float x = 75 + cos((0 - 45 * i)*PI / 180)*dist;
				float y = 75 - sin((0 - 45 * i)*PI / 180)*dist;
				Match.AddCell(c, 0, x, y);
				Match.AddCell(c, 0, 1280 - x, 715 - y);
			}
			int dist = 60 + 50 + 25;
			float x = 640 + cos((0 - 60 * i)*PI / 180)*dist;
			float y = 358 + sin((0 - 60 * i)*PI / 180)*dist;
			Match.AddCell(c, 0, x, y);
		}

		Match.profiles[0].SetToughness(0, 5000, 0);

		break;
	case 3:
		c.Set(1500, 50, 200, 120);
		Match.AddCell(c, 1, 440, 358);
		Match.AddCell(c, 2, 840, 358);
		c.Set(1175, 50, 150, 120);
		Match.AddCell(c, 0, 200, 200);
		Match.AddCell(c, 0, 1280 - 200, 200);
		Match.AddCell(c, 0, 200, 715 - 200);
		Match.AddCell(c, 0, 1280 - 200, 715 - 200);

		Match.profiles[0].SetToughness(0, 2500, 5000);

		break;
	case 4:

		for (int i = 0; i < 4; i++)
		{
			c.Set(1800, 50, 150, 120);
			int x = (i % 2 == 1) ? (1100) : (180);
			int y = (i / 2) ? (575) : (140);
			Match.AddCell(c, i + 1, x, y);
			c.Set(900, 10, 75, 120);

			for (int j = 0; j < 3; j++)
			{
				auto _x = cos(-j * 45 * PI / 180) * 150;
				auto _y = -sin(-j * 45 * PI / 180) * 150;
				if (i % 2 == 1)_x = -_x;
				if (i / 2)_y = -_y;

				Match.AddCell(c, 0, x + _x, y + _y);
			}
			Match.profiles[i].SetPercents(30, 50);
		}
		c.Set(1800, 30, 150, 120);
		Match.AddCell(c, 0, 400, 358);
		Match.AddCell(c, 0, 880, 358);
		c.Set(2400, 100, 200, 120);
		Match.AddCell(c, 0, 640, 358);
		Match.profiles[2].SetToughness(0, 1500, 750);

		break;
	case 5:
		for (int i = 0; i < 3; i++)
		{
			c.Set(900, 50, 150, 150);

			Match.AddCell(c, i + 1, 220 + i * 440, 358);

			c.Set(600, 10, 75, 120);
			for (int j = 0; j < 6; j++)
			{
				auto _x = cos(-j * 60 * PI / 180) * 140;
				auto _y = -sin(-j * 60 * PI / 180) * 140;
				Match.AddCell(c, 0, 220 + i * 440 + _x, 358 + _y);
			}


			Match.profiles[i].SetPercents(35, 45);
		}
		Match.profiles[0].SetToughness(1, 1000, 500);
		Match.profiles[1].SetToughness(0, 1550, 1050);

		break;
	case 6:
		c.Set(1800, 175, 200, 250);

		Match.AddCell(c, 0, 150, 150);
		Match.AddCell(c, 0, 1130, 565);

		for (int i = 0; i < 3; i++)
		{

			auto _x = cos((-i * 120 + 120) * PI / 180) * 70;
			auto _y = -sin((-i * 120 + 120) * PI / 180) * 70;
			c.Set(1200, 50, 100, 120);

			float x = 640 + _x;
			float y = 358 + _y;
			Match.AddCell(c, i + 1, x, y);
			c.Set(1200, 25, 100, 120);


			for (int j = 0; j < 2; j++)
			{
				auto __x = cos((-i * 120 + 60 + j * 120) * PI / 180) * 120;
				auto __y = -sin((-i * 120 + 60 + j * 120) * PI / 180) * 120;
				x += __x; y += __y;
				Match.AddCell(c, 0, x, y);
				for (int k = 0; k < 2; k++)
				{
					__x = cos((-i * 120 + 60 + j * 120 + k * 60) * PI / 180) * 120;
					__y = -sin((-i * 120 + 60 + j * 120 + k * 60) * PI / 180) * 120;
					Match.AddCell(c, 0, x + __x, y + __y);

				}
			}

		}
		Match.profiles[0].SetPercents(35, 50);
		Match.profiles[1].SetPercents(20, 40);
		Match.profiles[0].SetToughness(1, 1500, 1000);
		Match.profiles[1].SetToughness(1, 2000, 750);

		break;
	case 7:
		c.Set(600, 20, 90, 100);
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				int x = j * 100 + 90;
				int y = i * 100 + 85;
				if (j % 2 == 1)y += 50;
				Match.AddCell(c, 0, x, y);
			}
		}

		Match.cells[0].owner_id = 1;
		Match.cells[5].owner_id = 2;
		Match.cells[10].owner_id = 3;
		Match.cells[25].owner_id = 4;
		Match.cells[35].owner_id = 5;
		Match.cells[61].owner_id = 6;
		Match.cells[66].owner_id = 7;
		Match.cells[71].owner_id = 8;
		Match.physics_enabled = false;

		for (int i = 0; i < 8; i++)
		{
			Match.profiles[i].SetPercents(Random(10, 15), Random(15, 25));
			Match.profiles[i].SetToughness(1, Random(5000, 6000), Random(750, 1000));
		}

		break;
	case 8:
		c.Set(600, 10, 100, 120);

		{
			int px = 640, py = 100;


			for (int i = 0; i < 3; i++)
			{
				float _x = cos((-60 - i * 120)*PI / 180) * 120;
				float _y = sin((-60 - i * 120)*PI / 180) * 120;
				for (int j = 0; j < 5; j++)
				{
					Match.AddCell(c, 0, px, py);
					px += _x;
					py -= _y;
				}

			}
		}
		{
			int px = 640, py = 304;


			for (int i = 0; i < 3; i++)
			{
				float _x = cos((-60 - i * 120)*PI / 180) * 120;
				float _y = sin((-60 - i * 120)*PI / 180) * 120;
				for (int j = 0; j < 2; j++)
				{
					Match.AddCell(c, 0, px, py);
					px += _x;
					py -= _y;
				}

			}


		}

		Match.cells[0].owner_id = 1;
		Match.cells[5].owner_id = 2;
		Match.cells[10].owner_id = 3;
		Match.cells[18].owner_id = 4;

		for (int i = 0; i < 3; i++)
		{
			Match.profiles[i].SetPercents(Random(15, 25), Random(20, 40));
			Match.profiles[i].SetToughness(i % 2, Random(1000, 2000 - (i % 2) * 500), Random(750, 1500 - (i % 2) * 500));
		}


		break;
	case 9:
		c.Set(600, 20, 90, 100);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int x = j * 100 + 290;
				int y = i * 100 + 85;
				if (j % 2 == 1)y += 50;
				Match.AddCell(c, 0, x, y);
			}
		}
		c.Set(1200, 50, 200, 150);
		Match.AddCell(c, 1, 150, 565);
		Match.AddCell(c, 2, 1130, 565);

		Match.profiles[0].SetPercents(30, 55);
		Match.profiles[0].SetToughness(1, 1000, 333);

		break;



	case 10:
		c.Set(900, 50, 200, 120);
		Match.AddCell(c, 2, 150, 150);



		for (int i = 0; i < 5; i++)
		{
			c.Set(600, 15, 80, 120);
			int _x = 150 + cos((-i * 37.5 + 30)*PI / 180) * 180;
			int _y = 150 - sin((-i * 37.5 + 30)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);
			c.Set(900, 30, 120, 120);
			if (i >= 3)continue;
			_x = 150 + cos((-i * 30 + 5)*PI / 180) * 320;
			_y = 150 - sin((-i * 30 + 5)*PI / 180) * 320;
			Match.AddCell(c, 0, _x, _y);

		}
		c.Set(900, 50, 200, 120);
		Match.AddCell(c, 0, 150, 565);
		Match.AddCell(c, 4, 565, 460);
		Match.AddCell(c, 0, 670, 200);
		Match.AddCell(c, 1, 1130, 565);
		Match.AddCell(c, 3, 1050, 130);
		for (int i = 1; i < 2; i++)
		{
			c.Set(900, 30, 120, 120);
			int _x = 150 + cos((-i * 40 + 40)*PI / 180) * 240;
			int _y = 565 - sin((-i * 40 + 40)*PI / 180) * 240;
			Match.AddCell(c, 0, _x, _y);
		}
		for (int i = 0; i < 4; i++)
		{
			c.Set(600, 15, 80, 120);
			int _x = 670 + cos((-i * 37.5 + 40)*PI / 180) * 180;
			int _y = 200 - sin((-i * 37.5 + 40)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);
			if (i == 0)continue;
			_x = 565 + cos((-i * 37.5 + 30)*PI / 180) * 180;
			_y = 460 - sin((-i * 37.5 + 30)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);
		}
		for (int i = 0; i < 3; i++)
		{
			c.Set(900, 15, 120, 120);
			int _x = 1130 - cos((-i * 40)*PI / 180) * 240;
			int _y = 565 + sin((-i * 40 - 0)*PI / 180) * 240;
			Match.AddCell(c, 0, _x, _y);
		}

		Match.profiles[0].SetPercents(20, 30);
		Match.profiles[0].SetToughness(1, 1500, 1000);
		Match.profiles[1].SetPercents(25, 35);
		Match.profiles[1].SetToughness(1, 1000, 750);
		Match.profiles[2].SetPercents(30, 40);
		Match.profiles[2].SetToughness(1, 750, 500);

		break;























	case 13:
		for (int i = 0; i < 3; i++)
		{
			c.Set(900 + (i % 2 == 1) * 900, 50, 150, 150);
			Match.AddCell(c, 1 + (i % 2 == 0), 240 + 400 * i, 358);
			c.Set(600, 20, 100, 150);

			for (int j = 0; j < 6; j++)
			{
				auto x = 240 + 400 * i + cos((j * 60 + 30) * PI / 180) * 150;
				auto y = 358 - sin((j * 60 + 30) * PI / 180) * 150;
				Match.AddCell(c, 0, x, y);
			}

			Match.profiles[0].SetPercents(33, 55);
			Match.profiles[0].SetToughness(1, 1500, 500);

		}
		break;

	case 14:
		c.Set(900, 50, 200, 120);
		Match.AddCell(c, 2, 150, 150);

		c.Set(600, 15, 80, 120);

		for (int i = 0; i < 5; i++)
		{
			int _x = 150 + cos((-i * 37.5 + 30)*PI / 180) * 180;
			int _y = 150 - sin((-i * 37.5 + 30)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);

		}
		c.Set(900, 75, 200, 120);
		Match.AddCell(c, 0, 150, 565);
		Match.AddCell(c, 0, 640, 150);
		Match.AddCell(c, 0, 640, 565);
		Match.AddCell(c, 0, 1130, 150);
		Match.AddCell(c, 0, 1130, 565);
		c.Set(600, 15, 80, 120);
		for (int i = 0; i < 5; i++)
		{
			int _x = 1130 - cos((-i * 37.5 + 30)*PI / 180) * 180;
			int _y = 565 + sin((-i * 37.5 + 30)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);

		}
		c.Set(1500, 75, 100, 120);
		Match.AddCell(c, 0, 640, 358);

		Match.cells[13].owner_id = 1;
		Match.profiles[0].SetPercents(10, 50);
		Match.profiles[0].SetToughness(1, 2000, 500);
		break;

	case 15:
		c.Set(600, 60, 120, 120);
		Match.AddCell(c, 1, 110, 605);

		for (int i = 0; i < 3; i++)
		{
			auto _x = 110 + cos((-i * 10 + 30)*PI / 180) * 900;
			auto _y = 605 - sin((-i * 10 + 30)*PI / 180) * 900;

			Match.AddCell(c, i + 2, _x, _y);
		}

		c.Set(600, 25, 120, 120);

		for (int i = -2; i < 2; i++)
		{
			auto _x = 110 + cos((-i * 12 + 26)*PI / 180) * 720;
			auto _y = 605 - sin((-i * 12 + 26)*PI / 180) * 720;

			Match.AddCell(c, 0, _x, _y);
		}
		for (int i = 0; i < 4; i++)
		{
			auto _x = 110 + cos((-i * 20 + 90)*PI / 180) * 500;
			auto _y = 605 - sin((-i * 20 + 90)*PI / 180) * 500;

			Match.AddCell(c, 0 + (i == 0) * 5, _x, _y);
		}
		//Match.AddCell(c, 2, 910, 110);
		for (int i = 0; i < 4; i++)
		{
			Match.profiles[i].SetPercents(Random(10, 30), Random(25, 35));
			Match.profiles[i].SetToughness(1, Random(1125, 1400), Random(225, 277));
		}
		for (int i = 0; i < Match.cell_count; i++)
		{
			if (Match.cells[i].owner_id > 2)Match.cells[i].species += 5;
		}

		break;

	}
}




void cgame_t::LoadLevel(int l)
{
	if (l > 15)l = 15;
	current_level = l;
	Match.Reset(auto_pause);
	cell_t c;

	printf("\n%d", l);
	switch (l)
	{
	case 11:
		c.Set(1800, 60, 250, 150);
		Match.AddCell(c, 1, 930, 520);
		Match.AddCell(c, 2, 350, 200);

		c.Set(1200, 30, 200, 150);
		Match.AddCell(c, 0, 650, 200);
		Match.AddCell(c, 0, 350, 500);
		Match.AddCell(c, 0, 630, 520);
		Match.AddCell(c, 0, 930, 220);

		Match.profiles[0].SetPercents(25, 60);
		Match.profiles[0].SetToughness(1, 1000, 300);

		Match.cells[1].species = 180;
		break;
	case 12:
		c.Set(2100, 75, 125, 100);
		Match.AddCell(c, 0, 640, 358);
		c.Set(600, 15, 75, 100);
		for (int i = 0; i < 5; i++)
		{
			float x = 640 + cos((float)i * 72 * PI / 180) * 120;
			float y = 358 + sin((float)i * 72 * PI / 180) * 120;

			Match.AddCell(c, 0, x, y);
		}


		for (int i = 0; i < 4; i++)
		{
			c.Set(1200, 50, 150, 100);
			Match.AddCell(c, i + 1, 150 + (i % 2) * 980, 150 + (i / 2) * 420);
			c.Set(600, 15, 75, 100);

			for (int j = 0; j < 4; j++)
			{
				float x = 150 + cos((float)(36 - j * 48) * PI / 180) * 150;
				float y = 150 - sin((float)(36 - j * 48)* PI / 180) * 150;

				if (i % 2)x = 1280 - x;
				if (i / 2)y = 715 - y;
				Match.AddCell(c, 0, x, y);
			}
		}
		for (int i = 0; i < 3; i++)
		{
			Match.profiles[i].SetPercents(Random(10, 30), Random(15, 40));
			Match.profiles[i].SetToughness(1, Random(900, 1111), Random(500, 800));
		}

		break;









	case 1:
		c.Set(600, 50, 200, 120);
		Match.AddCell(c, 1, 150, 150);
		Match.AddCell(c, 2, 1280 - 150, 715 - 150);
		c.Set(600, 25, 200, 120); Match.AddCell(c, 0, 640, 358);
		c.Set(600, 10, 75, 120);
		Match.AddCell(c, 0, 320, 150);
		Match.AddCell(c, 0, 150, 320);
		Match.AddCell(c, 0, 1280 - 320, 715 - 150);
		Match.AddCell(c, 0, 1280 - 150, 715 - 320);

		Match.AddCell(c, 0, 490, 208);
		Match.AddCell(c, 0, 1280 - 490, 208);
		Match.AddCell(c, 0, 490, 715 - 208);
		Match.AddCell(c, 0, 1280 - 490, 715 - 208);

		Match.profiles[0].SetToughness(0, 10000, 0);

		break;
	case 2:
		c.Set(1500, 50, 120, 120);
		Match.AddCell(c, 0, 640, 358);
		c.Set(600, 50, 150, 120);
		Match.AddCell(c, 1, 75, 75);
		Match.AddCell(c, 2, 1205, 640);
		c.Set(600, 5, 50, 120);
		for (int i = 0; i < 6; i++)
		{
			if (i < 3)
			{
				int dist = 75 + 50 + 50;
				float x = 75 + cos((0 - 45 * i)*PI / 180)*dist;
				float y = 75 - sin((0 - 45 * i)*PI / 180)*dist;
				Match.AddCell(c, 0, x, y);
				Match.AddCell(c, 0, 1280 - x, 715 - y);
			}
			int dist = 60 + 50 + 25;
			float x = 640 + cos((0 - 60 * i)*PI / 180)*dist;
			float y = 358 + sin((0 - 60 * i)*PI / 180)*dist;
			Match.AddCell(c, 0, x, y);
		}

		Match.profiles[0].SetToughness(0, 5000, 0);

		break;
	case 3:
		c.Set(1500, 50, 200, 120);
		Match.AddCell(c, 1, 440, 358);
		Match.AddCell(c, 2, 840, 358);
		c.Set(1175, 50, 150, 120);
		Match.AddCell(c, 0, 200, 200);
		Match.AddCell(c, 0, 1280 - 200, 200);
		Match.AddCell(c, 0, 200, 715 - 200);
		Match.AddCell(c, 0, 1280 - 200, 715 - 200);

		Match.profiles[0].SetToughness(0, 2500, 5000);

		break;
	case 4:

		for (int i = 0; i < 4; i++)
		{
			c.Set(1800, 50, 150, 120);
			int x = (i % 2 == 1) ? (1100) : (180);
			int y = (i / 2) ? (575) : (140);
			Match.AddCell(c, i + 1, x, y);
			c.Set(900, 10, 75, 120);

			for (int j = 0; j < 3; j++)
			{
				auto _x = cos(-j * 45 * PI / 180) * 150;
				auto _y = -sin(-j * 45 * PI / 180) * 150;
				if (i % 2 == 1)_x = -_x;
				if (i / 2)_y = -_y;

				Match.AddCell(c, 0, x + _x, y + _y);
			}
			Match.profiles[i].SetPercents(30, 50);
		}
		c.Set(1800, 30, 150, 120);
		Match.AddCell(c, 0, 400, 358);
		Match.AddCell(c, 0, 880, 358);
		c.Set(2400, 100, 200, 120);
		Match.AddCell(c, 0, 640, 358);
		Match.profiles[2].SetToughness(0, 1500, 750);

		break;
	case 5:
		for (int i = 0; i < 3; i++)
		{
			c.Set(900, 50, 150, 150);

			Match.AddCell(c, i + 1, 220 + i * 440, 358);

			c.Set(600, 10, 75, 120);
			for (int j = 0; j < 6; j++)
			{
				auto _x = cos(-j * 60 * PI / 180) * 140;
				auto _y = -sin(-j * 60 * PI / 180) * 140;
				Match.AddCell(c, 0, 220 + i * 440 + _x, 358 + _y);
			}


			Match.profiles[i].SetPercents(35, 45);
		}
		Match.profiles[0].SetToughness(1, 1000, 500);
		Match.profiles[1].SetToughness(0, 1550, 1050);

		break;
	case 6:
		c.Set(1800, 175, 200, 250);

		Match.AddCell(c, 0, 150, 150);
		Match.AddCell(c, 0, 1130, 565);

		for (int i = 0; i < 3; i++)
		{

			auto _x = cos((-i * 120 + 120) * PI / 180) * 70;
			auto _y = -sin((-i * 120 + 120) * PI / 180) * 70;
			c.Set(1200, 50, 100, 120);

			float x = 640 + _x;
			float y = 358 + _y;
			Match.AddCell(c, i + 1, x, y);
			c.Set(1200, 25, 100, 120);


			for (int j = 0; j < 2; j++)
			{
				auto __x = cos((-i * 120 + 60 + j * 120) * PI / 180) * 120;
				auto __y = -sin((-i * 120 + 60 + j * 120) * PI / 180) * 120;
				x += __x; y += __y;
				Match.AddCell(c, 0, x, y);
				for (int k = 0; k < 2; k++)
				{
					__x = cos((-i * 120 + 60 + j * 120 + k * 60) * PI / 180) * 120;
					__y = -sin((-i * 120 + 60 + j * 120 + k * 60) * PI / 180) * 120;
					Match.AddCell(c, 0, x + __x, y + __y);

				}
			}

		}
		Match.profiles[0].SetPercents(35, 50);
		Match.profiles[1].SetPercents(20, 40);
		Match.profiles[0].SetToughness(1, 1500, 1000);
		Match.profiles[1].SetToughness(1, 2000, 750);

		break;
	case 7:
		c.Set(600, 20, 90, 100);
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				int x = j * 100 + 90;
				int y = i * 100 + 85;
				if (j % 2 == 1)y += 50;
				Match.AddCell(c, 0, x, y);
			}
		}

		Match.cells[0].owner_id = 1;
		Match.cells[5].owner_id = 2;
		Match.cells[10].owner_id = 3;
		Match.cells[25].owner_id = 4;
		Match.cells[35].owner_id = 5;
		Match.cells[61].owner_id = 6;
		Match.cells[66].owner_id = 7;
		Match.cells[71].owner_id = 8;
		Match.physics_enabled = false;

		for (int i = 0; i < 8; i++)
		{
			Match.profiles[i].SetPercents(Random(10, 15), Random(15, 25));
			Match.profiles[i].SetToughness(1, Random(5000, 6000), Random(750, 1000));
		}

		break;
	case 8:
		c.Set(600, 10, 100, 120);

		{
			int px = 640, py = 100;


			for (int i = 0; i < 3; i++)
			{
				float _x = cos((-60 - i * 120)*PI / 180) * 120;
				float _y = sin((-60 - i * 120)*PI / 180) * 120;
				for (int j = 0; j < 5; j++)
				{
					Match.AddCell(c, 0, px, py);
					px += _x;
					py -= _y;
				}

			}
		}
		{
			int px = 640, py = 304;


			for (int i = 0; i < 3; i++)
			{
				float _x = cos((-60 - i * 120)*PI / 180) * 120;
				float _y = sin((-60 - i * 120)*PI / 180) * 120;
				for (int j = 0; j < 2; j++)
				{
					Match.AddCell(c, 0, px, py);
					px += _x;
					py -= _y;
				}

			}


		}

		Match.cells[0].owner_id = 1;
		Match.cells[5].owner_id = 2;
		Match.cells[10].owner_id = 3;
		Match.cells[18].owner_id = 4;

		for (int i = 0; i < 3; i++)
		{
			Match.profiles[i].SetPercents(Random(15, 25), Random(20, 40));
			Match.profiles[i].SetToughness(i % 2, Random(1000, 2000 - (i % 2) * 500), Random(750, 1500 - (i % 2) * 500));
		}


		break;
	case 9:
		c.Set(600, 20, 90, 100);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int x = j * 100 + 290;
				int y = i * 100 + 85;
				if (j % 2 == 1)y += 50;
				Match.AddCell(c, 0, x, y);
			}
		}
		c.Set(1200, 50, 200, 150);
		Match.AddCell(c, 1, 150, 565);
		Match.AddCell(c, 2, 1130, 565);

		Match.profiles[0].SetPercents(30, 55);
		Match.profiles[0].SetToughness(1, 1000, 333);

		break;



	case 10:
		c.Set(900, 50, 200, 120);
		Match.AddCell(c, 2, 150, 150);



		for (int i = 0; i < 5; i++)
		{
			c.Set(600, 15, 80, 120);
			int _x = 150 + cos((-i * 37.5 + 30)*PI / 180) * 180;
			int _y = 150 - sin((-i * 37.5 + 30)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);
			c.Set(900, 30, 120, 120);
			if (i >= 3)continue;
			_x = 150 + cos((-i * 30 + 5)*PI / 180) * 320;
			_y = 150 - sin((-i * 30 + 5)*PI / 180) * 320;
			Match.AddCell(c, 0, _x, _y);

		}
		c.Set(900, 50, 200, 120);
		Match.AddCell(c, 0, 150, 565);
		Match.AddCell(c, 4, 565, 460);
		Match.AddCell(c, 0, 670, 200);
		Match.AddCell(c, 1, 1130, 565);
		Match.AddCell(c, 3, 1050, 130);
		for (int i = 1; i < 2; i++)
		{
			c.Set(900, 30, 120, 120);
			int _x = 150 + cos((-i * 40 + 40)*PI / 180) * 240;
			int _y = 565 - sin((-i * 40 + 40)*PI / 180) * 240;
			Match.AddCell(c, 0, _x, _y);
		}
		for (int i = 0; i < 4; i++)
		{
			c.Set(600, 15, 80, 120);
			int _x = 670 + cos((-i * 37.5 + 40)*PI / 180) * 180;
			int _y = 200 - sin((-i * 37.5 + 40)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);
			if (i == 0)continue;
			_x = 565 + cos((-i * 37.5 + 30)*PI / 180) * 180;
			_y = 460 - sin((-i * 37.5 + 30)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);
		}
		for (int i = 0; i < 3; i++)
		{
			c.Set(900, 15, 120, 120);
			int _x = 1130 - cos((-i * 40)*PI / 180) * 240;
			int _y = 565 + sin((-i * 40 - 0)*PI / 180) * 240;
			Match.AddCell(c, 0, _x, _y);
		}

		Match.profiles[0].SetPercents(20, 30);
		Match.profiles[0].SetToughness(1, 1500, 1000);
		Match.profiles[1].SetPercents(25, 35);
		Match.profiles[1].SetToughness(1, 1000, 750);
		Match.profiles[2].SetPercents(30, 40);
		Match.profiles[2].SetToughness(1, 750, 500);

		break;























	case 13:
		for (int i = 0; i < 3; i++)
		{
			c.Set(900 + (i % 2 == 1) * 900, 50, 150, 150);
			Match.AddCell(c, 1 + (i % 2 == 0), 240 + 400 * i, 358);
			c.Set(600, 20, 100, 150);

			for (int j = 0; j < 6; j++)
			{
				auto x = 240 + 400 * i + cos((j * 60 + 30) * PI / 180) * 150;
				auto y = 358 - sin((j * 60 + 30) * PI / 180) * 150;
				Match.AddCell(c, 0, x, y);
			}

			Match.profiles[0].SetPercents(33, 55);
			Match.profiles[0].SetToughness(1, 1500, 500);

		}
		break;

	case 14:
		c.Set(900, 50, 200, 120);
		Match.AddCell(c, 2, 150, 150);

		c.Set(600, 15, 80, 120);

		for (int i = 0; i < 5; i++)
		{
			int _x = 150 + cos((-i * 37.5 + 30)*PI / 180) * 180;
			int _y = 150 - sin((-i * 37.5 + 30)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);

		}
		c.Set(900, 75, 200, 120);
		Match.AddCell(c, 0, 150, 565);
		Match.AddCell(c, 0, 640, 150);
		Match.AddCell(c, 0, 640, 565);
		Match.AddCell(c, 0, 1130, 150);
		Match.AddCell(c, 0, 1130, 565);
		c.Set(600, 15, 80, 120);
		for (int i = 0; i < 5; i++)
		{
			int _x = 1130 - cos((-i * 37.5 + 30)*PI / 180) * 180;
			int _y = 565 + sin((-i * 37.5 + 30)*PI / 180) * 180;
			Match.AddCell(c, 0, _x, _y);

		}
		c.Set(1500, 75, 100, 120);
		Match.AddCell(c, 0, 640, 358);

		Match.cells[13].owner_id = 1;
		Match.profiles[0].SetPercents(10, 50);
		Match.profiles[0].SetToughness(1, 2000, 500);
		break;

	case 15:
		c.Set(600, 60, 120, 120);
		Match.AddCell(c, 1, 110, 605);

		for (int i = 0; i < 3; i++)
		{
			auto _x = 110 + cos((-i * 10 + 30)*PI / 180) * 900;
			auto _y = 605 - sin((-i * 10 + 30)*PI / 180) * 900;

			Match.AddCell(c, i + 2, _x, _y);
		}

		c.Set(600, 25, 120, 120);

		for (int i = -2; i < 2; i++)
		{
			auto _x = 110 + cos((-i * 12 + 26)*PI / 180) * 720;
			auto _y = 605 - sin((-i * 12 + 26)*PI / 180) * 720;

			Match.AddCell(c, 0, _x, _y);
		}
		for (int i = 0; i < 4; i++)
		{
			auto _x = 110 + cos((-i * 20 + 90)*PI / 180) * 500;
			auto _y = 605 - sin((-i * 20 + 90)*PI / 180) * 500;

			Match.AddCell(c, 0 + (i == 0) * 5, _x, _y);
		}
		//Match.AddCell(c, 2, 910, 110);
		for (int i = 0; i < 4; i++)
		{
			Match.profiles[i].SetPercents(Random(10, 30), Random(25, 35));
			Match.profiles[i].SetToughness(1, Random(1125, 1400), Random(225, 277));
		}
		for (int i = 0; i < Match.cell_count; i++)
		{
			if (Match.cells[i].owner_id > 2)Match.cells[i].species += 5;
		}

		break;

	}
}