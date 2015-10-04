#pragma once
class Camera;

namespace Meshes {
	extern GLuint box;
	extern GLuint square;
}

namespace Textures {
	extern GLuint crate;
	extern GLuint grass;
}

namespace Drawing {
	const static int PIXELS_PER_METRE = 50;

	GLuint loadTextureFile(std::string texturePath);
	GLuint loadBox();
	GLuint loadSquare();

	void loadTextures();
	void drawTexture(GLuint texture, GLuint mesh, glm::vec3 &position, glm::vec3 &size, glm::vec4 &rotation, glm::vec3 &tint, float alpha);
	void init(Camera &cam);
	void loadMeshes();
	void drawGrid();
}