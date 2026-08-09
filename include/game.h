#include <SDL3/SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <array>

#define VERTSIZE 12
#define INDEXSIZE 6

class Game {
	private:
		const int m_windowWidth{ 1280 };
		const int m_windowHeight{ 720 };
		SDL_Window* m_window{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
		SDL_GLContext m_gContext{ nullptr };
		/*------opengl rendering members-------*/
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";
			
		const GLfloat vertices[VERTSIZE] = { 
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
		     0.5f, -0.5f, 0.0f 
		};
		const GLint indices[INDEXSIZE] = { 
			0, 1, 2,
			1, 2, 3
		};
		GLuint VAO, VBO, EBO;
		GLuint shaderProgram;
		/*-----------------------------------*/
		void getInput();
		void renderContent();

	public:
		bool isRunning{ false };
		bool setupWindow();
		void gameLoop();
		void cleanUp();
};

