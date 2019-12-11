#include "Game.h"

/// <summary>
/// Game()
/// Main Game constructor used to initialise SDL, create a window and initialise SDL_IMG
/// </summary>
Game::Game(Client *t_client):
	m_client(t_client)
{
	// Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL" << std::endl;
	}

	// Create a Window
	p_window = SDL_CreateWindow("Online Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1080, 720, SDL_WINDOW_SHOWN);
	if (NULL == p_window)
	{
		std::cout << "Error: Could not create window" << std::endl;
	}

	// Create a Renderer
	p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (NULL == p_renderer)
	{
		std::cout << "Error: Could not create renderer" << std::endl;
	}

	// Initialise SDL_IMG
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		std::cout << "Failed to initialise IMG" << std::endl;
	}
	std::string playerPos = "X:" + std::to_string(m_player.getPosition().getX()) + ",Y:" + std::to_string(m_player.getPosition().getY());
	m_client->getPlayerVector(playerPos);
	if (m_client->getPlayerId() % 2 == 0)
	{
		m_player.initTexture(p_renderer, "Assets/circle.png");
		m_player2.initTexture(p_renderer, "Assets/circle.png");
	}
	else
	{
		m_player.initTexture(p_renderer, "Assets/circle.png");
		m_player2.initTexture(p_renderer, "Assets/circle.png");
	}

}

/// <summary>
/// ~Game()
/// Destructor function for the Game class
/// </summary>
Game::~Game() {}

/// <summary>
/// run()
/// Main game loop for the game, runs methods for updating, rendering and event handling
/// </summary>
void Game::run()
{
	bool exit = false;
	float timePerFrame = 1000.f / 60.f;
	Uint32 timeSinceLastUpdate = 0;
	Uint32 timeSinceStart = SDL_GetTicks();
	while (!m_quit)
	{
		processEvents();
		timeSinceLastUpdate += SDL_GetTicks() - timeSinceStart;
		timeSinceStart = SDL_GetTicks();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
	quit();
}

/// <summary>
/// processEvents()
/// Method used to poll events in SDL such as keyboard events or window close events
/// </summary>
void Game::processEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_quit = true;
		}
		if(event.type==SDL_KEYDOWN && event.key.repeat==0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_quit = true;
				break;
			default:
				break;
			}
		}
	}
}

/// <summary>
/// update(float dt)
/// Method used to update game objects and attributes
/// </summary>
/// <param name="dt">The time that has passed since the last update call in seconds</param>
void Game::update(float dt)
{
	m_player.update(dt);
	m_player2.setPosition(m_client->getEnemy());
	//collision detection
}

/// <summary>
/// render()
/// Method used to render any game objects that have to be drawn
/// </summary>
void Game::render()
{
	SDL_SetRenderDrawColor(p_renderer, 150, 150, 150, 255);
	SDL_RenderClear(p_renderer);
	m_player.render(p_renderer);
	m_player2.render(p_renderer);
	SDL_RenderPresent(p_renderer);

}

/// <summary>
/// quit()
/// Method used to appropriately end use of the SDL and SDL_IMG libraries
/// </summary>
void Game::quit()
{
	SDL_DestroyRenderer(p_renderer);
	SDL_DestroyWindow(p_window);
	IMG_Quit();
	SDL_Quit();
}