/*
Author: Pindrought
Date: 2/25/2016
This is the solution for the client that you should have at the end of tutorial 7.
*/
#include "Client.h"
#include "Game.h"

int main111(int argc, char* argv[])
{
	Client* myClient=new Client("127.0.0.1",1111); //Create client to localhost ("127.0.0.1") on port 1111
	Game* game = new Game(myClient);
	if (!myClient->Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}
	game->run();
	return 0;
}

