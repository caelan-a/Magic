// Magic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//	Global Objects
SDL_Window* window;
SDL_GLContext context;
SDL_Event windowEvent;

bool quit = false;

//	Protofunctions
void init();
void checkInput();
void render();
void cleanup();

int main(int argc, char **argv) {
	init();

	while (!quit) {
		checkInput();
		render();
	}

	cleanup();

	exit(EXIT_SUCCESS);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	Drawing::drawTexture(Drawing::tex_box, glm::vec3(1.0f,1.0f,1.0f), 1.0f);

	SDL_GL_SwapWindow(window);
}

void checkInput() {
	if (SDL_PollEvent(&windowEvent)) {
		if (windowEvent.type == SDL_QUIT) {
			quit = true;
		}
	}
}

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader::loadShaders();
	Drawing::loadSprites();
}

void cleanup() {
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}
