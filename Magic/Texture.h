#pragma once
class Texture
{
public:
	GLuint id;
	std::string type;
	aiString path;
	GLuint Texture::loadTextureFile(std::string directory, std::string name);
};

class CubeMap
{
public:
	GLuint id;
	void loadCubeMap(std::vector<const char*> faces);
};

class SkyBox
{
public:
	CubeMap map;
	Shader shader;
	GLuint vao;

	SkyBox(CubeMap m, Shader s, GLuint v);

	void draw();
	void uploadViewProj();
};

