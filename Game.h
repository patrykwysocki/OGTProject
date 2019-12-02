#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Dot.h"
class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvents();
	void update(float dt);
	void render();
	void quit();

	SDL_Window* p_window;
	SDL_Renderer* p_renderer;
	Dot m_player;
	Dot m_player2;
	bool m_quit = false;
};