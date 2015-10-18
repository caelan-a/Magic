#include "stdafx.h"
#include "Texture.h"

GLuint Texture::loadTextureFile(std::string directory, std::string name) {
	GLuint tex;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height;
	unsigned char* image = SOIL_load_image((directory + name).c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (!image) {
		std::cout << "Unable to load: " << directory << name << std::endl;
	}
	else {
		std::cout << "Successfully loaded: " << directory << name << std::endl;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	id = tex;
	path = name;
	return tex;
}

void CubeMap::loadCubeMap(std::vector<const char*> faces)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);
		if (!image) {
			std::cout << "Unable to load: " << faces[i] << std::endl;
		}
		else {
			std::cout << "Successfully loaded: " << faces[i] << std::endl;
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	id = textureId;
}

SkyBox::SkyBox(CubeMap m, Shader s, GLuint v)
{
	this->map = m;
	this->shader = s;
	this->vao = v;
}

void SkyBox::draw() {
	uploadViewProj();

	glDepthMask(GL_FALSE);
	shader.Use();
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, map.id);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glActiveTexture(0);
	glBindVertexArray(0);
	shader.Disable();
	glDepthMask(GL_TRUE);
}

void SkyBox::uploadViewProj()
{
	shader.Use();
	glm::mat4 view;
	view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
	
	glm::mat4 mview = glm::mat4(glm::mat3(view));
	
	glm::mat4 proj;
	proj = glm::perspective(camera.fov, (float)Preferences::SCREEN_WIDTH / (float)Preferences::SCREEN_HEIGHT, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shader.id, "view"), 1, GL_FALSE, glm::value_ptr(mview));
	glUniformMatrix4fv(glGetUniformLocation(shader.id, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
	shader.Disable();
}

