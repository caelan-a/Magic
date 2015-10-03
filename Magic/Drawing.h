#pragma once

namespace Drawing {
	const static int PIXELS_PER_METRE = 50;

	extern GLuint vao_surface;
	extern GLuint tex_box;

	GLuint loadTextureFile(std::string texturePath);
	GLuint loadSurface();
	void loadSprites();
	void drawTexture(GLuint tex, float x, float y, float width, float height, glm::vec3 tint, float alpha);
}