#include "stdafx.h"
#include "Drawing.h"

GLuint Drawing::createSurface(float vertices[], GLuint elements[]) {
	glUseProgram(Shader::flat);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(Shader::flat, "a_position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLint texAttrib = glGetAttribLocation(Shader::flat, "a_texcoords");
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(texAttrib);

	return vao;
}
GLuint Drawing::loadTextureFile(std::string texturePath) {
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	return tex;
}
void Drawing::loadQuad() {
	float vertices[] = {
		-1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
	};

	GLuint elements[] = {
		0,1,2,
		2,3,0
	};

	vao_quad = createSurface(vertices, elements);
}
void Drawing::loadSprites() {
	loadQuad();

	tex_box = loadTextureFile("data/textures/square.png");
}
void Drawing::drawTexture(GLuint tex, glm::vec3 tint, float alpha) {
	glUseProgram(Shader::flat);
	glBindVertexArray(vao_quad);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_box);
	glUniform1i(glGetUniformLocation(Shader::flat, "u_tex"), 0);
	glUniform3fv(glGetUniformLocation(Shader::flat, "u_tint"), 1, glm::value_ptr(tint));
	glUniform1f(glGetUniformLocation(Shader::flat, "u_alpha"), alpha);

	glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
}