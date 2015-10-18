#pragma once
class Texture
{
public:
	GLuint id;
	std::string type;
	aiString path;
	GLuint Texture::loadTextureFile(std::string directory, std::string name);
};

