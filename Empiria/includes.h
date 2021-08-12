#pragma once
#include <d3d9.h>
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "fastParser.h"
#include "ITek.h"
#include "FileSys.h"
#include <chrono>
#include "IWindow.h"

extern sf::RenderWindow* g_Window;

#define PI 3.14159265



static int llrand() {
	int r = 0;

	for (int i = 0; i < 2; ++i) {
		r = (r << 15) | (rand() & 0x7FFF);
	}

	return r & 0xFFFFFFFF;
}

static int Random(int RandMin, int RandMax) //5-25
{
	int RandDifference = RandMax - RandMin + 1;  //20
	int ReturnValue = llrand() % RandDifference + RandMin;
	return ReturnValue;
}


static float RandFloat()
{
	return float(Random(0, 10000)) / 10000;
}

struct g_Instructions
{
	//static void SetupAnim(char* filename, int FullSizeX, int FullSizeY, int tilesizex, int tilesizey, float length);
};

struct coord
{
	int x, y;
};

struct mouse_t
{
	coord leftclickCoords;
	coord rightclickCoords;
	coord Coords;
	bool left_click = false, right_click = false;
	bool last_left = false, last_right = false;

	bool isHolding(bool leftfalse__righttrue = false)
	{
		if (leftfalse__righttrue)return right_click;
		else return left_click;
	}

	bool hasReleased(bool leftfalse__righttrue = false)
	{
		if (leftfalse__righttrue)
		{
			return last_right && !right_click;
		}
		else return last_left && !left_click;
	}

	bool hasJustClicked(bool leftfalse__righttrue = false)
	{
		if (leftfalse__righttrue)
		{
			return !last_right && right_click;
		}
		else return !last_left && left_click;
	}

	void Update(int x, int y)
	{
		Coords.x = x; Coords.y = y;
		last_left = left_click;
		last_right = right_click;
		left_click = GetAsyncKeyState(0x01);
		right_click = GetAsyncKeyState(0x02);

		if (hasJustClicked(false))
		{
			leftclickCoords = Coords;
		}
		if (hasJustClicked(true))
		{
			rightclickCoords = Coords;
		}

	}

	bool IsClickValid(bool leftfalse__righttrue = false)
	{
		if (leftfalse__righttrue)
		{
			if (abs(rightclickCoords.x - Coords.x) > 15 || abs(rightclickCoords.y - Coords.y) > 15)return false;
			//if (!hasJustClicked(leftfalse__righttrue) && !hasReleased(leftfalse__righttrue))return false;
		}
		else
		{
			if (abs(leftclickCoords.x - Coords.x) > 15 || abs(leftclickCoords.y - Coords.y) > 15)return false;
			//if (!hasJustClicked(leftfalse__righttrue) && !hasReleased(leftfalse__righttrue))return false;
		}
		return true;
	}

	bool IsBetween(int x, int y, int w, int h, int checkx, int checky)
	{
		return x < checkx && y < checky && checkx < x + w && checky < y + h;
	}

};

extern mouse_t g_Mouse;

