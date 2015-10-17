#include "stdafx.h"
#include "Lighting.h"

void Lighting::PointLight::uploadUniforms()
{
	std::string id_s = std::to_string(id);
	glUniform3f(glGetUniformLocation(shaderID, ("pointLights[" + id_s + "].position").c_str()), position.x, position.y, position.z);
	glUniform3f(glGetUniformLocation(shaderID, ("pointLights[" + id_s + "].ambient").c_str()), colour.ambient.x, colour.ambient.y, colour.ambient.z);
	glUniform3f(glGetUniformLocation(shaderID, ("pointLights[" + id_s + "].diffuse").c_str()), colour.diffuse.x, colour.diffuse.y, colour.diffuse.z);
	glUniform3f(glGetUniformLocation(shaderID, ("pointLights[" + id_s + "].specular").c_str()), colour.specular.x, colour.specular.y, colour.specular.z);
	glUniform1f(glGetUniformLocation(shaderID, ("pointLights[" + id_s + "].constant").c_str()), attenuation.constant);
	glUniform1f(glGetUniformLocation(shaderID, ("pointLights[" + id_s + "].linear").c_str()), attenuation.linear);
	glUniform1f(glGetUniformLocation(shaderID, ("pointLights[" + id_s + "]quadratic").c_str()), attenuation.quadratic);
}

void Lighting::PointLight::setPosition(glm::vec3 position)
{
	glUseProgram(shaderID);
	std::string id_s = std::to_string(id);
	PointLight::position = position;
	glUniform3f(glGetUniformLocation(shaderID, ("pointLights[" + id_s + "].position").c_str()), position.x, position.y, position.z);
	glUseProgram(0);
}

void Lighting::DirectionalLight::uploadUniforms()
{
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.direction"), direction.x, direction.y, direction.z);
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.ambient"), colour.ambient.x, colour.ambient.y, colour.ambient.z);
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.diffuse"), colour.diffuse.x, colour.diffuse.y, colour.diffuse.z);
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.specular"), colour.specular.x, colour.specular.y, colour.specular.z);
}

Lighting::LightScene::LightScene()
{
}

void Lighting::LightScene::drawPoints(Shader shader, Model* pointLightModel)
{
	for (int i = 0; i < NR_POINT_LIGHTS; i++) {
		pointLights[i].drawPoint(shader, pointLightModel);
	}
}

void Lighting::LightScene::setDirectionalLight(GLuint shaderID, glm::vec3 direction, Colour colour)
{
	globalLight = DirectionalLight(shaderID, direction, colour);
}

void Lighting::LightScene::addPointLight(GLuint shaderID, GLuint id, glm::vec3 position, Colour colour, Attenuation attenuation)
{
	pointLights[id] = PointLight(shaderID, id, position, colour, attenuation);
}

void Lighting::LightScene::uploadUniforms(Shader shader)
{
	shader.Use();
	for (int i = 0; i < Lighting::NR_POINT_LIGHTS; i++) {
		pointLights[i].uploadUniforms();
	}
	globalLight.uploadUniforms();
	shader.Disable();
}

Lighting::PointLight::PointLight(GLuint shaderID, GLuint id, glm::vec3 position, Colour colour, Attenuation attenuation)
{
	PointLight::shaderID = shaderID;
	PointLight::id = id;
	PointLight::position = position;
	PointLight::colour = colour;
	PointLight::attenuation = attenuation;
}

Lighting::PointLight::PointLight()
{
}

void Lighting::PointLight::drawPoint(Shader shader, Model* pointLightModel)
{
	shader.Use();
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, this->position);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniform3f(glGetUniformLocation(shader.id, "colour"),this->colour.diffuse.r, this->colour.diffuse.g, this->colour.diffuse.b);
	shader.Disable();
	pointLightModel->Draw(shader);
}

Lighting::DirectionalLight::DirectionalLight(GLuint shaderID, glm::vec3 direction, Colour colour)
{
	DirectionalLight::shaderID = shaderID;
	DirectionalLight::direction = direction;
	DirectionalLight::colour = colour;
}

Lighting::DirectionalLight::DirectionalLight()
{
}

void Lighting::LightScene::cleanup() {
	/*
	for (int i = 0; i < sizeof(pointLights); i++) {
		delete(pointLights[i]);
	}

	delete(globalLight);
	*/
}