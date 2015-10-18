#include "stdafx.h"
#include "Assets.h"

Assets::Assets()
{
}

void Assets::loadQuad()
{
	GLfloat vertices[] = {
		1.0f,  1.0f, 1.0f, 1.0f, // Top Right
		1.0f, -1.0f, 1.0f, 0.0f,  // Bottom Right
		-1.0f, -1.0f, 0.0f, 0.0f,  // Bottom Left
		-1.0f,  1.0f, 0.0f, 1.0f,   // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(0);

	Shader surfaceShader;
	surfaceShader.load("shaders/v_surface.glsl", "shaders/f_surface.glsl");

	shaders.surfaceShader = surfaceShader;
	models.quad = VAO;
	textures.splash.loadTextureFile("data/textures/", "splash.png");
}

void Assets::loadShaders()
{
	shaders.lampShader.load("shaders/v_lamp.glsl", "shaders/f_lamp.glsl");
	shaders.modelShader.load("shaders/v_model.glsl", "shaders/f_model.glsl");
	shaders.outlineShader.load("shaders/v_outline.glsl", "shaders/f_outline.glsl");
}

void Assets::loadModels() {
	models.plane = new Model("data/models/plane/plane.obj");
	models.cube = new Model("data/models/cube/textured_cube.obj");
	models.sphere = new Model("data/models/orb/orb.obj");
	//models.tree = new Model("data/models/tree/tree.obj");
	models.nanosuit = new Model("data/models/nanosuit/nanosuit.obj");
}

void Assets::loadTextures()
{

}
