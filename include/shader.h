#pragma once
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
	private:
		GLuint shaderProgramID;
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		void useShader();
		void deleteShader();
};
