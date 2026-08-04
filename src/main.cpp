#include <iostream>
#include "game.h"
int main()
{
	Game game;
	game.isRunning = game.setupWindow();
	game.gameLoop();
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
