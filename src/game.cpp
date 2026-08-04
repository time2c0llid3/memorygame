#include "game.h"

bool Game::setupWindow() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("ERROR: Could not Initilize SDL");
		return false;
	}
	m_window = SDL_CreateWindow("memorygame",
								m_windowWidth,
								m_windowHeight,
								SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	);
	if (!m_window) {
		SDL_Log("ERROR: Could not create SDL window");
		return false;
	}
	m_renderer = SDL_CreateRenderer(m_window, NULL);
	if (!m_renderer) {
		SDL_Log("ERROR: Could not create SDL renderer");
		return false;
	}
	return true;
};

void Game::gameLoop() {
	while(isRunning) {
		getInput();
		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 0);
		SDL_RenderClear(m_renderer);
		SDL_RenderPresent(m_renderer);
	}
}

void Game::cleanUp() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::getInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_EVENT_QUIT:
			isRunning = false;
	}
}


