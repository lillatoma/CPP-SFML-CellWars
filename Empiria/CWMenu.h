#include "structs.h"

struct button_t
{
	int x, y, w, h;
	char* text = nullptr;
	int textsize;
	int tx, ty;

	sf::Color main_color;
	sf::Color hl_color;
	sf::Color outline_color;
	sf::Color text_color;
	bool Button()
	{
		bool hover = g_Mouse.IsBetween(x, y, w, h,g_Mouse.Coords.x,g_Mouse.Coords.y);

		if (hover)
			_Window::RenderOverlay(x, y, w, h, hl_color.r, hl_color.g, hl_color.b, hl_color.a);
		else 
			_Window::RenderOverlay(x, y, w, h, main_color.r,main_color.g,main_color.b,main_color.a);

		_Window::RenderOverlay(x - 1, y - 1, w + 2, 1, outline_color.r, outline_color.g, outline_color.b, outline_color.a);
		_Window::RenderOverlay(x - 1, y + h + 1, w + 2, 1, outline_color.r, outline_color.g, outline_color.b, outline_color.a);
		_Window::RenderOverlay(x - 1, y - 1, 1, h+2, outline_color.r, outline_color.g, outline_color.b, outline_color.a);
		_Window::RenderOverlay(x + w + 1, y - 1, 1, h + 2, outline_color.r, outline_color.g, outline_color.b, outline_color.a);
		if (text != nullptr)
		_Window::RenderTextB(x + tx, y + ty, text, textsize, text_color.r, text_color.g, text_color.b, text_color.a);

		return g_Mouse.hasReleased() && g_Mouse.IsClickValid() && hover;
	}
};