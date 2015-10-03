#include "stdafx.h"
#include "Drawing.h"

GLuint Drawing::vao_surface = 0;
GLuint Drawing::tex_box = 0;

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
	if (image == nullptr) {
		std::cerr << "Failed to load image: " + texturePath;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	return tex;
}

GLuint Drawing::loadSurface() {
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

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	return vao;
}

void Drawing::loadSprites() {
	vao_surface = loadSurface();
	tex_box = loadTextureFile("data/textures/square.png");
}

void Drawing::drawTexture(GLuint tex, float x, float y, float width, float height, glm::vec3 tint, float alpha) {
	glUseProgram(Shader::flat);
	glBindVertexArray(Drawing::vao_surface);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(glGetUniformLocation(Shader::flat, "u_tex"), 0);
	glUniform3fv(glGetUniformLocation(Shader::flat, "u_tint"), 1, glm::value_ptr(tint));
	glUniform1f(glGetUniformLocation(Shader::flat, "u_alpha"), alpha);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
