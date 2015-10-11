#include "stdafx.h"
#include "Lighting.h"

void Lighting::PointLight::uploadUniforms(GLuint shaderID, GLuint id)
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

void Lighting::DirectionalLight::uploadUniforms(GLuint shaderID)
{
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.direction"), direction.x, direction.y, direction.z);
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.ambient"), colour.ambient.x, colour.ambient.y, colour.ambient.z);
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.diffuse"), colour.diffuse.x, colour.diffuse.y, colour.diffuse.z);
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.specular"), colour.specular.x, colour.specular.y, colour.specular.z);
}

Lighting::LightScene::LightScene()
{

}

void Lighting::LightScene::setDirectionalLight(glm::vec3 direction, Colour colour)
{
	globalLight = DirectionalLight(direction, colour);
}

void Lighting::LightScene::addPointLight(glm::vec3 position, Colour colour, Attenuation attenuation, GLuint id)
{
	pointLights[id] = PointLight(position, colour, attenuation);
}

void Lighting::LightScene::uploadUniforms(GLuint shaderID)
{
	for (int i = 0; i < sizeof(pointLights); i++) {
		pointLights[i].uploadUniforms(shaderID, i);
	}
	globalLight.uploadUniforms(shaderID);
}

Lighting::PointLight::PointLight(glm::vec3 position, Colour colour, Attenuation attenuation)
{
	PointLight::position = position;
	PointLight::colour = colour;
	PointLight::attenuation = attenuation;
}

Lighting::PointLight::PointLight()
{
}

Lighting::DirectionalLight::DirectionalLight(glm::vec3 direction, Colour colour)
{
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

