#include "stdafx.h"
#include "Drawing.h"

class Camera;
extern Camera camera;

//	Shaders
Shader lampShader;
Shader modelShader;

Lighting::LightScene lightScene;
Model* nanosuit = nullptr;

void Drawing::loadShaders() {
	lampShader.load("shaders/v_lamp.glsl", "shaders/f_lamp.glsl");
	modelShader.load("shaders/v_model.glsl", "shaders/f_model.glsl");
}

void loadModels() {
	nanosuit = new Model("data/models/cube/textured_cube.obj");
}

void setLightScene(Lighting::LightScene &lightScene, Shader shader) {
	//	Set directional light
	float luminosity = 0.5f;
	Lighting::Colour colour;
	colour.ambient = glm::vec3(luminosity);
	colour.diffuse = glm::vec3(luminosity);
	colour.specular = glm::vec3(1.0f, 1.0f, 1.0f) * luminosity;

	glm::vec3 direction(-1.0f, -0.25f, -1.0f);

	lightScene.setDirectionalLight(shader.id, direction, colour);

	//	Set 4 point lights
	Lighting::Attenuation attenuation;
	attenuation.constant = 1.0f;
	attenuation.linear = 0.09f;
	attenuation.quadratic = 0.032f;

	glm::vec3 pointColour;

	pointColour = glm::vec3(1.0f, 0.0f, 0.0f);
	colour.ambient = pointColour * 0.2f;
	colour.diffuse = pointColour;
	colour.specular = pointColour;
	lightScene.addPointLight(shader.id, 0, glm::vec3(18.0f, 2.0f, 24.0f), colour, attenuation);

	pointColour = glm::vec3(0.0f, 1.0f, 0.0f);
	colour.ambient = pointColour * 0.2f;
	colour.diffuse = pointColour;
	colour.specular = pointColour;
	lightScene.addPointLight(shader.id, 1, glm::vec3(1.0f, 2.0f, 24.0f), colour, attenuation);

	pointColour = glm::vec3(0.0f, 0.0f, 1.0f);
	colour.ambient = pointColour * 0.2f;
	colour.diffuse = pointColour;
	colour.specular = pointColour;
	lightScene.addPointLight(shader.id, 2, glm::vec3(1.0f, 2.0f, 14.0f), colour, attenuation);

	pointColour = glm::vec3(1.0f, 0.0f, 1.0f);
	colour.ambient = pointColour * 0.2f;
	colour.diffuse = pointColour;
	colour.specular = pointColour;
	lightScene.addPointLight(shader.id, 3, glm::vec3(18.0f, 2.0f, 14.0f), colour, attenuation);

	//	Upload Uniforms
	lightScene.uploadUniforms(modelShader);
}

void Drawing::init(Camera &cam) {
	camera = cam;

	loadShaders();
	loadModels();

	setLightScene(lightScene, modelShader);
}

void uploadViewProjection(Shader shader) {
	shader.Use();
	
	glm::mat4 view;
	view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
	glm::mat4 proj;
	proj = glm::perspective(camera.fov, (float)Preferences::SCREEN_WIDTH / (float)Preferences::SCREEN_HEIGHT, 0.1f, 100.0f);
	
	glUniform3f(glGetUniformLocation(modelShader.id, "cameraPos"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
	glUniformMatrix4fv(glGetUniformLocation(modelShader.id, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.id, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
	
	shader.Disable();
}

void Drawing::render() {
	uploadViewProjection(modelShader);

	modelShader.Use();
	float size = 1.0f;
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(10.0f, 1.5f, 15.0f));
	model = glm::scale(model, glm::vec3(size, size, size));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.id, "model"), 1, GL_FALSE, glm::value_ptr(model));
	modelShader.Disable();
	nanosuit->Draw(modelShader);
}

void Drawing::cleanup()
{
	delete(nanosuit);
}

