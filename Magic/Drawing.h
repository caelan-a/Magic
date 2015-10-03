#pragma once

namespace Drawing {
	static GLuint vao_quad;
	static GLuint tex_box;

	GLuint createSurface(float vertices[], GLuint elements[]);
	GLuint loadTextureFile(std::string texturePath);
	void loadQuad();
	void loadSprites();
	void drawTexture(GLuint tex, glm::vec3 tint, float alpha);
}