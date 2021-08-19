#include "structs.h"

void cgame_t::SimulateBackground()
{
	using namespace std::chrono;
	static auto last = high_resolution_clock::now();

	auto now = high_resolution_clock::now();

	int diff = duration_cast<milliseconds>(now - last).count();
	last = now;

	for (int i = 0; i < bg.CellCount; i++)
	{
		auto size = bg.Cells[i].size;
		bg.Cells[i].posX += cos(bg.Cells[i].angle*PI / 180)*bg.Cells[i].velocity*diff / 1000;
		bg.Cells[i].posY -= sin(bg.Cells[i].angle*PI / 180)*bg.Cells[i].velocity*diff / 1000;
		float anglediff = (float)(Random(0, 15))*diff / 1000 * Random(-1, 1);
		bg.Cells[i].angle += anglediff;

		float vecX = cos(bg.Cells[i].angle*PI / 180)*bg.Cells[i].velocity;
		float vecY = -sin(bg.Cells[i].angle*PI / 180)*bg.Cells[i].velocity;

		if (bg.Cells[i].posX < bg.Cells[i].size || bg.Cells[i].posX > 1280 - bg.Cells[i].size || bg.Cells[i].posY < bg.Cells[i].size || bg.Cells[i].posY > 720 - bg.Cells[i].size)
		{
			if (bg.Cells[i].posX < -bg.Cells[i].size)vecX += bg.Cells[i].velocity*diff / 1000;
			if (bg.Cells[i].posX > 1280 + bg.Cells[i].size)vecX -= bg.Cells[i].velocity*diff / 1000;
			if (bg.Cells[i].posY < -bg.Cells[i].size)vecY += bg.Cells[i].velocity*diff / 1000;
			if (bg.Cells[i].posY > 720 + bg.Cells[i].size)vecY -= bg.Cells[i].velocity*diff / 1000;

			float angle = 90;
			if (vecY != 0)
				angle = atan(vecX / vecY) * 180 / PI;
			if (vecX < 0)angle += 180;

			bg.Cells[i].angle = angle;
		}
	}






}

void cgame_t::DrawBackground()
{
	for (int i = 0; i < bg.CellCount; i++)
	{
		int c = 200 - bg.Cells[i].size / 2;
		static sf::CircleShape circle(bg.Cells[i].size / 2);
		circle.setRadius(bg.Cells[i].size / 2);
		circle.setFillColor(sf::Color(c, c, c, 192));
		circle.setPosition(bg.Cells[i].posX - bg.Cells[i].size / 2, bg.Cells[i].posY - bg.Cells[i].size / 2);
		circle.setOutlineThickness(0);
		IWindow::AddToRenderList(circle);
	}

	IWindow::RenderOverlay(0, 0, 1280, 720, 16, 40, 80, 192);
}

void cgame_t::ApplyBackgroundShader()
{
	static sf::Shader shader;

	static file_t wave = g_Files.GetFileByName("wave.vert");
	static file_t blur = g_Files.GetFileByName("blur.frag");
	static bool bLoaded = false;

	if (!bLoaded)
		//shader.loadFromMemory(wave.loc_in_mem, blur.loc_in_mem);
		shader.loadFromFile("wave.vert", "blur.frag");
	bLoaded = true;

	shader.setUniform("blur_radius", 2);
	shader.setUniform("texture", sf::Shader::CurrentTexture);

	sf::RenderStates states;
	states.shader = &shader;


	static sf::Texture text;
	static sf::Sprite a;

	IWindow::RenderTextB(100, 100, "ASD", 16);

	text.update(*g_Window);
	a.setTexture(text);


	IWindow::RenderOverlay(60, 60, 1160, 600, 0, 0, 0, 128);

	sf::CircleShape circ(300);
	circ.setTexture(&text);
	g_Window->draw(a, states);
	//IWindow::AddToRenderList(circ, states);
}