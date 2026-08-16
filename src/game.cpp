#include "game.h"
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
	setupObjects();
	while(isRunning) {
		getInput();
		renderContent();
	}
}

void Game::cleanUp() {
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
	squareShader->deleteShader();
	//delete squareShader;
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
	
	squareShader->useShader();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	
	glm::mat4 view = glm::mat4(1.0f);
	const float radius = 1.0f;
	float camX = sin((SDL_GetTicks()/1000.0f)) * radius;
	float camZ = cos((SDL_GetTicks()/1000.0f)) * radius;

	view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), cameraTarget, cameraUp);
	
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	unsigned int modelLoc = glGetUniformLocation(squareShader->shaderProgramID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	unsigned int viewLoc = glGetUniformLocation(squareShader->shaderProgramID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	unsigned int projectionLoc = glGetUniformLocation(squareShader->shaderProgramID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
		

	SDL_GL_SwapWindow(m_window);
}
void Game::setupCamera() {
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);
	cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
}
void Game::setupObjects() {
	glGenBuffers(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	/*-----Shader setup---------*/
	squareShader = new Shader("shaders/vs.glsl", "shaders/fs.glsl");
	/*----Texture Code----*/
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("assets/card_clubs_04.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	setupCamera();
}

