
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* argv[])
{
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture;

	bool isRunning = true;

	int frameRate = 10;
	int frameDelay = 1000 / frameRate;
	Uint32 frameStart;
	int frameTime;

	while (isRunning)
	{
		frameStart = SDL_GetTicks();

		int frame = 0;


		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				case SDLK_LEFT:
					break;
				case SDLK_RIGHT:
					break;
				case SDLK_ESCAPE:
					isRunning = false;
				default:
					break;
				}
				break;

			case SDL_KEYUP:
				break;

			case SDL_QUIT:
				isRunning = false;
				break;

			default:
				break;
			}
		}

		//update

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		//render
		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return EXIT_SUCCESS;
}