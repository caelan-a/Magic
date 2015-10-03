#include "stdafx.h"
#include "Shader.h"

GLuint Shader::createShaderFromFile(int type, const std::string path) {
	const char* source = nullptr;

	std::string content;
	std::ifstream fileStream(path, std::ios::in);
	if (!fileStream.is_open()) {
		std::cerr << "Could not read file: " << path << ". File does not exist." << std::endl;
		//exit(EXIT_FAILURE);
	}
	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();

	source = content.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		std::cout << "Error compiling vertex shader:\n";
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		for (char c : buffer)
			std::cout << c;
		glDeleteShader(shader);
		//exit(EXIT_FAILURE);
	}

	return shader;
}

GLuint Shader::createShaderProgram(GLuint vertexS, GLuint fragmentS) {
	//std::string vstring = "#version 330\nin vec2 position;\nvoid main(){\ngl_Position=vec4(position,0.0,1.0);\n}";
	//std::string fstring = "#version 330\nout vec4 outColor;\nvoid main(){\outColor=vec4(1.0,1.0,1.0,1.0);\n}";

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexS);
	glAttachShader(shaderProgram, fragmentS);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexS);
	glDeleteShader(fragmentS);

	return shaderProgram;
}

GLuint Shader::loadShader(std::string vPath, std::string fPath) {
	GLuint vShader = createShaderFromFile(GL_VERTEX_SHADER, vPath);
	GLuint fShader = createShaderFromFile(GL_FRAGMENT_SHADER, fPath);

	GLuint program = createShaderProgram(vShader, fShader);

	return program;
}

GLuint Shader::loadDefaultShader() {
	return loadShader("shaders/v_default.glsl", "shaders/f_default.glsl");
}
