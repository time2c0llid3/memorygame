#include <SDL3/SDL.h>
#include <iostream>

class Game {
	private:
		const int m_windowWidth{ 1280 };
		const int m_windowHeight{ 720 };
		SDL_Window* m_window{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
		SDL_GLContext m_gContext{ nullptr };
		void getInput();
		void renderContent();
	public:
		bool isRunning{ false };
		bool setupWindow();
		void gameLoop();
		void cleanUp();
};

