#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Dot.h"
#include "Client.h"
class Game
{
public:
	Game(Client* t_client);
	~Game();
	void run();
private:
	void processEvents();
	void update(float dt);
	void render();
	void quit();

	SDL_Window* p_window;
	SDL_Renderer* p_renderer;
	SDL_Surface* p_screenSurface;
	Dot m_player;
	Dot m_player2;
	bool m_quit = false;
	Client* m_client;
	SDL_Texture* texture;
}; 
