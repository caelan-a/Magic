#include "stdafx.h"
#include "Drawing.h"

class Camera;
extern Camera camera;

Assets assets;

Lighting::LightScene lightScene;

Entity* cube = nullptr;

class Ground {
public:
	Model* model;
	float tileSize = 2.0f;
	float groundSize = 16.0f;

	Ground(Model* model) {
		this->model = model;
	}

	void draw() {
		for (int i = 0; i < groundSize / tileSize; i++) {
			uploadModelMatrix(assets.shaders.modelShader, glm::vec3((i * tileSize) - (groundSize / 2), 0.0f, (i * tileSize) - (groundSize / 2)), tileSize);
			model->Draw(assets.shaders.modelShader);
		}
	}

	void uploadModelMatrix(Shader shader, glm::vec3 position, float size) {
		glm::mat4 modelMatrix;

		shader.Use();
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(size, size, size));
		glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		shader.Disable();
	}
};
Ground ground(assets.models.plane);

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
	lightScene.uploadUniforms(shader);
}

void Drawing::init(Camera &cam) {
	camera = cam;
	assets.loadAssets();
	setLightScene(lightScene, assets.shaders.modelShader);

	cube = new Entity(assets.models.cube, assets.shaders.modelShader, glm::vec3(0.0f, 2.0f, 0.0f));
	cube->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
}

void uploadViewProjection(Shader shader) {
	shader.Use();
	
	glm::mat4 view;
	view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
	glm::mat4 proj;
	proj = glm::perspective(camera.fov, (float)Preferences::SCREEN_WIDTH / (float)Preferences::SCREEN_HEIGHT, 0.1f, 100.0f);
	
	glUniform3f(glGetUniformLocation(shader.id, "cameraPos"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
	glUniformMatrix4fv(glGetUniformLocation(shader.id, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.id, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
	
	shader.Disable();
}

void Drawing::render() {
	uploadViewProjection(assets.shaders.modelShader);
	uploadViewProjection(assets.shaders.lampShader);

	ground.draw();
	lightScene.drawPoints(assets.shaders.lampShader, assets.models.cube);
	Entities::drawEntities();
}

void Drawing::cleanup()
{
	Entities::deleteEntities;
	assets.clean();
}
