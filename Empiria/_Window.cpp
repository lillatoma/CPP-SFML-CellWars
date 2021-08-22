#include "_Window.h"

void _Window::AddToRenderList(sf::Drawable &drawable, const sf::RenderStates &states)
{
	g_Window->draw(drawable, states);
}

void _Window::RenderOverlay(int x, int y,int w, int h, int r, int g, int b, int _a)
{
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("overla.png");
	static sf::Texture t;
	static sf::Sprite a;

	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}

	a.setPosition(x, y);
	a.setScale(sf::Vector2f((float)(w) / 128, (float)(h) / 128));
	a.setColor(sf::Color(r,g,b,_a));
	

	_Window::AddToRenderList(a);
}

void _Window::RenderText(int x, int y, char* text, int fontsize, int r, int g, int b, int _a)
{
	static bool bLoaded = false;
	static file_t f = g_Files.GetFileByName("character.png");
	static sf::Texture t;
	static sf::Sprite a;


	int _x = x, _y = y;




	if (!bLoaded)
	{
		bLoaded = true;
		t.loadFromMemory(f.loc_in_mem, f.size);
		a.setTexture(t);
	}


	a.setScale(sf::Vector2f(1.0f*fontsize / 32, 1.0f*fontsize / 32));
	a.setColor(sf::Color(r, g, b, _a));
	int len = strlen(text);
	for (int i = 0; i < len; i++)
	{
		int High = text[i] / 16;
		int Low = text[i] % 16;

		if (text[i] == '\n')
		{
			_y += fontsize*0.8f + 1; _x = x;
		}
		else
		{
			a.setPosition(_x, _y);
			a.setTextureRect(sf::IntRect(32 * Low, 32 * High, 32, 32));
			_x += fontsize * 0.8f;
			_Window::AddToRenderList(a);
		}

	}

}

void _Window::RenderTextB(int x, int y, char* text, int fontsize, int r, int g, int b, int _a)
{
	static bool loaded = false;
	static sf::Font font;
	static file_t f = g_Files.GetFileByName("arial.ttf");
	if (!loaded)
	{
		font.loadFromMemory(f.loc_in_mem, f.size);
		loaded = true;
	}

	static sf::Text Text;
	Text.setFont(font);
	Text.setString(text);
	Text.setCharacterSize(fontsize);
	Text.setPosition(x, y);
	Text.setFillColor(sf::Color(r, g, b, _a));
	_Window::AddToRenderList(Text);

}

void _Window::RenderTexture(sf::Texture t, sf::Sprite a, int x, int y, int r, int g, int b, int _a )
{

	a.setPosition(x, y);
	a.setColor(sf::Color(r, g, b, _a));


	_Window::AddToRenderList(a);
}