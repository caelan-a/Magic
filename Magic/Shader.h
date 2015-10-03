#pragma once

namespace Shader {
	static GLuint flat;

	GLuint createShaderFromFile(int type, const std::string path);
	GLuint createShaderProgram(GLuint vertexS, GLuint fragmentS);
	GLuint loadShader(std::string vPath, std::string fPath);
	void loadShaders();
}
