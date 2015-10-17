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

GLfloat lastFrame = 0.0f;
GLfloat deltaTime = 0.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void checkInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	GLfloat cameraSpeed = 10.0f;
	if (glfwGetKey(window, GLFW_KEY_W))
		camera.cameraPos += cameraSpeed * deltaTime * camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S))
		camera.cameraPos -= cameraSpeed * deltaTime * camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A))
		camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * deltaTime * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D))
		camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * deltaTime * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_E))
		camera.cameraPos += glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q))
		camera.cameraPos += glm::vec3(0.0f, -1.0f, 0.0f) * deltaTime * cameraSpeed;

}

int main(int argc, char **argv) {
	init();

	camera = Camera();
	Drawing::init(camera);

	while (!glfwWindowShouldClose(window))
	{
		checkInput();

		glClearColor(Preferences::clearColour.r, Preferences::clearColour.g, Preferences::clearColour.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Drawing::render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanup();
	exit(EXIT_SUCCESS);
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSwapInterval(1);
}

void getSystemInfo() {
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
}

void cleanup() {
	Drawing::cleanup();
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool firstMouse = true;
GLfloat lastX = Preferences::SCREEN_WIDTH / 2;
GLfloat lastY = Preferences::SCREEN_HEIGHT / 2;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) 
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xOffset = xpos - lastX;
	GLfloat yOffset = lastY - ypos;
	GLfloat sensitivity = 0.005f;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	camera.pitch += yOffset;
	camera.yaw += xOffset;

	if (camera.pitch > 89.0f)
		camera.pitch = 89.0f;
	else if (camera.pitch < -89.0f)
		camera.pitch = -89.0f;

	lastX = xpos;
	lastY = ypos;
	camera.setEulerRotation();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (camera.fov >= 1.0f && camera.fov <= 45.0f)
		camera.fov -= yoffset * 0.05f;
	if (camera.fov <= 1.0f)
		camera.fov = 1.0f;
	if (camera.fov >= 45.0f)
		camera.fov = 45.0f;
}
