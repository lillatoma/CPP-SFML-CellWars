#pragma once
#include "includes.h"

struct IWindow
{
	static void AddToRenderList(sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);
	static void RenderOverlay(int x, int y, int w, int h, int r, int g, int b, int _a);

	static void RenderText(int x, int y, char* text, int fontsize, int r = 255, int g = 255, int b = 255, int _a = 255);
	static void RenderTextB(int x, int y, char* text, int fontsize, int r = 255, int g = 255, int b = 255, int _a = 255);
	

	static void RenderTexture(sf::Texture t, sf::Sprite a, int x, int y, int r = 255, int g = 255, int b = 255, int _a = 255);
};