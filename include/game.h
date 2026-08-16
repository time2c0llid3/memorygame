#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include "stb_image.h"
#include "shader.h"


#define VERTSIZE 20
#define INDEXSIZE 6

class Game {
	private:
		const int m_windowWidth{ 1280 };
		const int m_windowHeight{ 720 };
		SDL_Window* m_window{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
		SDL_GLContext m_gContext{ nullptr };
		/*------opengl rendering members-------*/			
		const GLfloat vertices[VERTSIZE] = { 
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		     0.5f, -0.5f, 0.0f, 1.0f, 0.0f
		};
		const GLint indices[INDEXSIZE] = { 
			0, 1, 2,
			1, 2, 3
		};
		GLuint VAO, VBO, EBO;
		GLuint texture;
		Shader* squareShader{ nullptr };
		glm::vec3 cameraPos;
		glm::vec3 cameraTarget;
		glm::vec3 cameraDirection;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight;
		glm::vec3 cameraUp;
		/*-----------------------------------*/
		void getInput();
		void renderContent();
		void setupObjects();
		void setupCamera();

	public:
		bool isRunning{ false };
		bool setupWindow();
		void gameLoop();
		void cleanUp();
};
#endif
