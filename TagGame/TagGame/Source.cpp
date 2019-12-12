
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include "Game.h"
void startup();
void runServer(); 
void runClient();

int main(int argc, char* argv[])
{
	startup();
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
	Server MyServer(1111, true); //Create server on port 1111, false=do not loopback to localhost (others can connect)
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

	Client* myClient = new Client(ip, 1111); //Create client to localhost ("127.0.0.1") on port 1111
	Game* game = new Game(myClient);
	game->run();

	//if (connected)
	//{
	//	std::string userinput; //holds the user's chat message
	//	while (true)
	//	{
	//		std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
	//		myClient->SendString(userinput); //Send string to server
	//	}
	//}

	system("pause");
}