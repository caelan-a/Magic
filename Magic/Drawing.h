#pragma once
class Camera;

namespace Drawing {
	const static int PIXELS_PER_METRE = 50;

	GLuint loadTextureFile(std::string texturePath);
	GLuint loadBox();
	GLuint loadSquare();

	void loadTextures();
	void drawTexture(GLuint diffuse, GLuint specular, GLuint mesh, glm::vec3 &position, glm::vec3 &size, glm::vec4 &rotation);
	void init(Camera &cam);
	void loadMeshes();
	void loadShaders();
	void drawGrid();
	void drawLamp(glm::vec3 position);

	void render();
}