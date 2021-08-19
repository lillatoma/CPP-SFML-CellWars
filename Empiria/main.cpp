#include "includes.h"
#include "structs.h"

sf::RenderWindow* g_Window = new sf::RenderWindow;
mouse_t g_Mouse;




int main()
{
	//We don't need console window
	FreeConsole();
	srand(time(NULL));
	g_Files.LoadAll();
	//g_Files.ListLoadedFiles(); //this one prints in the console

	g_Window->create(sf::VideoMode(1280,720), "Cell Wars by zenkii1337", sf::Style::Titlebar | sf::Style::Close);
	g_Window->setFramerateLimit(60);
	
	cgame_t Game;
	Game.Initialize();

	while (g_Window->isOpen())
	{
		static int m_x = 0, m_y = 0;
		sf::Event _event;
		//Processing all SFML events that we need
		while (g_Window->pollEvent(_event))
		{
			switch (_event.type)
			{
			case sf::Event::Closed:
					g_Window->close();
					break;
			case sf::Event::MouseMoved:
				m_x = _event.mouseMove.x;
				m_y = _event.mouseMove.y;
			break;
			}


		}
		//Changing the screen to a black, blank one
		g_Window->clear();

		if(GetActiveWindow())
			g_Mouse.Update(m_x, m_y);
		
		Game.Do();

		g_Window->display();
	}


}























