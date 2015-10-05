// Magic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//	Global Objects
GLFWwindow* window;
Camera camera;

//	Protofunctions
void init();
void checkInput();
void render();
void cleanup();
void getSystemInfo();

void checkInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//	Move input to class
	GLfloat cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W)) 
		camera.cameraPos += cameraSpeed * camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S))
		camera.cameraPos -= cameraSpeed * camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A))
		camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D))
		camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		camera.cameraFront -= glm::normalize(camera.cameraFront + glm::vec3(1.0f, 0.0f, 0.0f)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
		camera.cameraFront += glm::normalize(camera.cameraFront + glm::vec3(1.0f, 0.0f, 0.0f)) * cameraSpeed;
}

int main(int argc, char **argv) {
	init();

	camera = Camera();
	Drawing::init(camera);
	Shader::loadShaders();

	while (!glfwWindowShouldClose(window))
	{
		checkInput();

		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
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
	glUseProgram(Shader::flat);
	Drawing::drawGrid();
	for (float i = 0; i < 10; i++)
		for (float j = 0; j < 10; j++)
			drawTexture(Textures::crate, Meshes::box, glm::vec3(3.0f * i, glm::sin(2 * glfwGetTime() + (5*i)) + 3.0f, 5.0f * j), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 1.0f, glm::sin(glfwGetTime())), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
	glUseProgram(0);
}

void init() {

	if (glfwInit() != GL_TRUE) {
		std::cout << "Failed to initialise GLFW";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	if(!Preferences::fullscreen)
		window = glfwCreateWindow(Preferences::SCREEN_WIDTH, Preferences::SCREEN_HEIGHT, "Magic", nullptr, nullptr);
	else
		window = glfwCreateWindow(Preferences::SCREEN_WIDTH, Preferences::SCREEN_HEIGHT, "Magic", glfwGetPrimaryMonitor(), nullptr);
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

	getSystemInfo();

	//glViewport(0, 0, Preferences::SCREEN_WIDTH, Preferences::SCREEN_HEIGHT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	glfwSwapInterval(1);
}

void getSystemInfo() {
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;
}

void cleanup() {
	glfwDestroyWindow(window);
	glfwTerminate();
}