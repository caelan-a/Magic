#include "stdafx.h"
#include "Lighting.h"

void Lighting::PointLight::uploadUniforms(GLuint shaderID)
{
	std::string id_s = std::to_string(id);
	glUniform3f(glGetUniformLocation(shaderID, ("light." + id_s + "position").c_str()), position.x, position.y, position.z);
	glUniform1i(glGetUniformLocation(shaderID, ("light." + id_s + "position").c_str()), isOn);
	glUniform3f(glGetUniformLocation(shaderID, ("light." + id_s + "position").c_str()), colour.ambient.x, colour.ambient.y, colour.ambient.z);
	glUniform3f(glGetUniformLocation(shaderID, ("light." + id_s + "position").c_str()), colour.diffuse.x, colour.diffuse.y, colour.diffuse.z);
	glUniform3f(glGetUniformLocation(shaderID, ("light." + id_s + "position").c_str()), colour.specular.x, colour.specular.y, colour.specular.z);
	glUniform1f(glGetUniformLocation(shaderID, ("light." + id_s + "position").c_str()), attenuation.constant);
	glUniform1f(glGetUniformLocation(shaderID, ("light." + id_s + "position").c_str()), attenuation.linear);
	glUniform1f(glGetUniformLocation(shaderID, ("light." + id_s + "position").c_str()), attenuation.quadratic);
}

void Lighting::DirectionalLight::uploadUniforms(GLuint shaderID)
{
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.direction"), direction.x, direction.y, direction.z);
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.ambient"), colour.ambient.x, colour.ambient.y, colour.ambient.z);
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.diffuse"), colour.diffuse.x, colour.diffuse.y, colour.diffuse.z);
	glUniform3f(glGetUniformLocation(shaderID, "directionalLight.specular"), colour.specular.x, colour.specular.y, colour.specular.z);
}
