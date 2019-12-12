#include "Game.h"

/// <summary>
/// Game()
/// Main Game constructor used to initialise SDL, create a window and initialise SDL_IMG
/// </summary>
Game::Game(Client *t_client):
	m_client(t_client)
{
	m_player = Dot();
	m_player2 = Dot();
	m_player2.setPosition(Vector2D(-200, -200));
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
	else
	{
		// Create a Renderer
		p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (NULL == p_renderer)
		{
			std::cout << "Error: Could not create renderer" << std::endl;
		}
		p_screenSurface = SDL_GetWindowSurface(p_window);

		if (!m_client->Connect())
		{
			std::cout << "Failed to connect to server..." << std::endl;
		}
		else
		{
			std::string playerPos = "X:" + std::to_string(m_player.getPosition().m_x) + ",Y:" + std::to_string(m_player.getPosition().m_y);
			std::cout << playerPos << std::endl;
			m_client->getPlayerVector(playerPos);
		}
		// Initialise SDL_IMG
		if (IMG_Init(IMG_INIT_PNG) == 0)
		{
			std::cout << "Failed to initialise IMG" << std::endl;
		}
		if (m_client->getPlayerId() % 2 == 0)
		{
			m_player.initTexture(p_renderer, "Assets/redcircle.png", false);
			m_player2.initTexture(p_renderer, "Assets/bluecircle.png", true);
		}
		else
		{
			m_player.initTexture(p_renderer, "Assets/bluecircle.png", true);
			m_player2.initTexture(p_renderer, "Assets/redcircle.png", false);
		}
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
		
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			m_player.move(Vector2D(0, -3));
			break;
		case SDLK_DOWN:
			m_player.move(Vector2D(0, 3));
			break;
		case SDLK_LEFT:
			m_player.move(Vector2D(-3, 0));
			break;
		case SDLK_RIGHT:
			m_player.move(Vector2D(3, 0));
			break;
		case SDLK_ESCAPE:
			m_quit = true;
			break;
		default:
			break;
		}

		if(event.type==SDL_KEYDOWN && event.key.repeat==0)
		{
			
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

	std::string playerPos = "X:" + std::to_string(m_player.getPosition().m_x) + ",Y:" + std::to_string(m_player.getPosition().m_y);
	m_client->SendPlayerVector(playerPos);
	m_player.update(dt);
	m_player2.setPosition(m_client->getEnemy());
	if (m_player.getIschaser() && m_player.checkCollision(m_player2.getPosition(), m_player2.getRadius()))
	{
		std::cout << "collision" << std::endl;
	}
}

/// <summary>
/// render()
/// Method used to render any game objects that have to be drawn
/// </summary>
void Game::render()
{
	//SDL_SetRenderDrawColor(p_renderer, 150, 150, 150, 255);

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