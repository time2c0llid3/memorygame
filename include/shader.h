#pragma once
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
	public:
		GLuint shaderProgramID;
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		void useShader();
		void deleteShader();
};
