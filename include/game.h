#include <SDL3/SDL.h>
#include <iostream>

class Game {
	private:
		int windowWidth = 1280;
		int windowHeight = 720;
		SDL_Window* window = nullptr;
	public:
		bool isRunning = false;
		bool setupWindow();
		void gameLoop();
};

