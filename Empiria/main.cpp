#include "includes.h"
#include "Interfaces.h"
#include "structs.h"

sf::RenderWindow* g_Window = new sf::RenderWindow;
mouse_t g_Mouse;




int main()
{
	FreeConsole();

	cgame_t Game;

	srand(time(NULL));
	//for (int i = 0x10; i < 0xC0; i++){	printf("\n%c - 0x", i);	std::cout << std::hex << (int)i;}
	//Game.SetUp();
	g_Files.LoadAll();
	g_Files.ListLoadedFiles();

	g_Window->create(sf::VideoMode(1280,720), "Cell Wars by zenkii1337", sf::Style::Titlebar | sf::Style::Close);
	g_Window->setFramerateLimit(60);

	Game.Initialize();
	


	for (int i = 0; i < 2; i++)
	{
		int angA = 88;
		int angN = 184;
		int a = angA + 2 * (180 + angN - angA);
		while (a > 360)a -= 360;
		printf("\n%d - %d    %d", i, angN + (angN-angA), a);
	}


	while (g_Window->isOpen())
	{
		static int m_x = 0, m_y = 0;
		sf::Event _event;
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
			case sf::Event::MouseButtonPressed:
				break;
			}


		}



		g_Window->clear();
		//IWindow::RenderOverlay(0, 0, 1280, 720, 0, 0, 0, 255);

		if(GetActiveWindow())
		g_Mouse.Update(m_x, m_y);

		
		//IWindow::RenderTextB(0, 0, "Tesztelllllesy\n123\n0.1234", 16);
		Game.Do();
		char buf[16];
		sprintf(buf, "%d %d", m_x, m_y);
		//IWindow::RenderTextB(0, 32, buf, 16);


		
		g_Window->display();
	}


}























