#pragma once

#include <iostream>
#include <string>
#include <fstream>

namespace Shader {
	GLuint createShaderFromFile(int type, const std::string path);
	GLuint createShaderProgram(GLuint vertexS, GLuint fragmentS);
	GLuint loadShader(std::string vPath, std::string fPath);

	GLuint loadDefaultShader();

}
