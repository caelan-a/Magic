// Magic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

SDL_Window* window;
SDL_GLContext context;

void init() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	window = SDL_CreateWindow("Magic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cout << "Failed to create window";
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		std::cout << "Failed to create context";
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialise GLEW";
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
}


int main(int argc, char **argv) {
	init();

	float vertices[] = {
		-0.5f,  0.5f,
		0.5f,  0.5f,
		0.5f, -0.5f,
	};

	GLuint shaderProgram = Shader::loadDefaultShader();
	glUseProgram(shaderProgram);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);


	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}

		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

