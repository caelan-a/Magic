#include "stdafx.h"
#include "Entity.h"


void Entity::draw(Shader shader) {
	uploadModelMatrix(shader);
	this->model->Draw(shader);
}

void Entity::uploadModelMatrix(Shader shader) {
	shader.Use();
	modelMatrix = glm::rotate(modelMatrix, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	modelMatrix = glm::translate(modelMatrix, transform.position);

	modelMatrix = glm::scale(modelMatrix, transform.size);

	glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	shader.Disable();
}