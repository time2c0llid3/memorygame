#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "game.h"
int main()
{
	Game game;
	if (game.setupWindow()) {
		game.isRunning = true;
	}
	game.gameLoop();
	game.cleanUp();
	return 0;
}
