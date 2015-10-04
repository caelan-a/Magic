// Magic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const static int SCREEN_WIDTH = 1920;
const static int SCREEN_HEIGHT = 1080;

//	Global Objects
GLFWwindow* window;

//	Protofunctions
void init();
void checkInput();
void render();
void cleanup();

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		std::cout << "w was pressed";
}

int main(int argc, char **argv) {
	init();

	Shader::loadShaders();
	Drawing::loadSprites();

	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanup();
	exit(EXIT_SUCCESS);
}

void render() {
	using namespace Drawing;
	drawTexture(tex_box, 1.0f, 1.0f, 1.0f, 1.0f, glm::vec3(1.0f, 0.0f, 1.0f), 1.0f);
}

void init() {
	if (glfwInit() != GL_TRUE) {
		std::cout << "Failed to initialise GLFW";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Magic", nullptr, nullptr); 
	if (window == nullptr) {
		std::cout << "Failed to create window";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialise GLEW";
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetKeyCallback(window, key_callback);
	glfwSwapInterval(1);
}

void cleanup() {
	glfwDestroyWindow(window);
	glfwTerminate();
}