#pragma once

class Shader {
public:
	GLuint id;
	void load(std::string vPath, std::string fPath);
	void Use();
	void Disable();
private:
	GLuint createShaderFromFile(int type, const std::string path);
	GLuint createShaderProgram(GLuint vertexS, GLuint fragmentS);
	GLuint loadShader(std::string vPath, std::string fPath);
};
