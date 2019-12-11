
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Server.h"
#include "Client.h"

void startup();
void runServer(); 
void runClient();

int main(int argc, char* argv[])
{
	startup();



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

void startup()
{
	std::cout << "[1]Host server, [2]Connect to server" << std::endl;
	int input;
	std::cin >> input;
	switch (input)
	{
	case 1:
		runServer();
		break;
	case 2:
		runClient();
		break;
	default:
		break;
	}
}

void runServer()
{
	Server MyServer(1111, false); //Create server on port 1111, false=do not loopback to localhost (others can connect)
	while (true)
	{
		MyServer.ListenForNewConnection(); //Accept new connection (if someones trying to connect)
	}
}

void runClient() 
{
	std::string ipString;
	std::cout << "Input ip: ";
	std::cin >> ipString;
	const char* ip = ipString.c_str();
	bool connected = true;

	Client myClient(ip, 1111); //Create client to connect to server 127.0.0.1 [localhost] on port 1111
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		bool connected = false;
	}

	if (connected)
	{
		std::string userinput; //holds the user's chat message
		while (true)
		{
			std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
			myClient.SendString(userinput); //Send string to server
		}
	}

	system("pause");
}