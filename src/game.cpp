#include "game.h"
#include <glad/glad.h>

bool Game::setupWindow() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("ERROR: Could not Initilize SDL");
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	m_window = SDL_CreateWindow("memorygame",
								m_windowWidth,
								m_windowHeight,
								SDL_WINDOW_OPENGL
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
	m_gContext = SDL_GL_CreateContext(m_window);
	if (!m_gContext) {
		SDL_Log("ERROR: Could not create OpenGL context");
		return false;
	}
	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cout << "ERROR: Could not Initilize GLAD" << std::endl;
		return false;
	}
	glViewport(0, 0, m_windowWidth, m_windowHeight);
	glEnable(GL_DEPTH_TEST);
	return true;
};

void Game::gameLoop() {
	while(isRunning) {
		getInput();
		renderContent();
	}
}

void Game::cleanUp() {
	SDL_GL_DestroyContext(m_gContext);
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

void Game::renderContent() {	
	glClearColor(0.769f, 0.51f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(m_window);
}

