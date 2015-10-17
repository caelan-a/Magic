#include "stdafx.h"
#include "Drawing.h"

class Camera;
extern Camera camera;

Assets assets;

Lighting::LightScene lightScene;

std::vector<Entity*> cubes;
Entity* tree;

//Entity* nanosuit;

//	Function Declarations
void createEntities();

class Ground {
public:
	float tileSize = 8.0f;
	float groundSize = 128.0f;

	void draw() {
		for (int i = 0; i < groundSize / tileSize; i++) {
			for (int j = 0; j < groundSize / tileSize; j++) {
				uploadModelMatrix(assets.shaders.modelShader, glm::vec3((j * 2 * tileSize) - (groundSize), 0.0f, (i * 2 * tileSize) - (groundSize)), tileSize);
				assets.models.plane->Draw(assets.shaders.modelShader);
			}
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
} ground;

void setLightScene(Lighting::LightScene &lightScene, Shader shader) {
	//	Set directional light
	float luminosity = Preferences::clearColour.r;
	Lighting::Colour colour;
	colour.ambient = glm::vec3(luminosity);
	colour.diffuse = glm::vec3(luminosity);
	colour.specular = glm::vec3(1.0f, 1.0f, 1.0f) * luminosity;

	glm::vec3 direction(-1.0f, -0.25f, -1.0f);

	//lightScene.setDirectionalLight(shader.id, direction, colour);

	//	Set 4 point lights
	Lighting::Attenuation attenuation;
	attenuation.constant = 1.0f;
	attenuation.linear = 0.09f;
	attenuation.quadratic = 0.032f;

	glm::vec3 pointColour;

	pointColour = glm::vec3(1.0f, 1.0f, 1.0f);
	colour.ambient = pointColour * 0.1f;
	colour.diffuse = pointColour * 0.8f;
	colour.specular = pointColour * 1.0f;
	lightScene.addPointLight(shader.id, 0, glm::vec3(5.0f, 7.0f, 10.0f), colour, attenuation);

	//	Upload Uniforms
	lightScene.uploadUniforms(shader);
}

void Drawing::init(Camera &cam) {
	camera = cam;
	assets.loadAssets();
	setLightScene(lightScene, assets.shaders.modelShader);
	createEntities();
}

void createEntities() {
	for (int i = 0; i < 2; i++) {
		cubes.push_back(new Entity(assets.models.cube, assets.shaders.modelShader, glm::vec3(i * 6.0f, 2.0f, -5.0f)));
		cubes[i]->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	}
	tree = new Entity(assets.models.tree, assets.shaders.modelShader, glm::vec3(0.0f, -0.5f, 5.0f));
	tree->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	//nanosuit = new Entity(assets.models.nanosuit, assets.shaders.modelShader, glm::vec3(0.0f, 0.0f, 5.0f));
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

void update() {
	for (int i = 0; i < Lighting::NR_POINT_LIGHTS; i++) {
		//lightScene.pointLights[i].setPosition(glm::vec3(lightScene.pointLights[i].position.x, lightScene.pointLights[i].position.y, 10.0f * glm::sin(glfwGetTime()) + 3.0f));
		//lightScene.pointLights[i].setPosition(glm::vec3(lightScene.pointLights[i].position.x, lightScene.pointLights[i].position.y, 10.0f * glm::sin(glfwGetTime()) + 3.0f));
		lightScene.pointLights[i].setPosition(glm::vec3(10.0f * glm::sin(glfwGetTime()) + 3.0f, lightScene.pointLights[i].position.y, 10.0f * glm::sin(glfwGetTime()) + 3.0f));
	}

}

void Drawing::render() {
	uploadViewProjection(assets.shaders.modelShader);
	uploadViewProjection(assets.shaders.lampShader);

	update();

	ground.draw();
	lightScene.drawPoints(assets.shaders.lampShader, assets.models.sphere);
	Entities::drawEntities();
}

void Drawing::cleanup()
{
	Entities::deleteEntities;
	assets.clean();
}
