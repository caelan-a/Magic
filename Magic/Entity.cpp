#include "stdafx.h"
#include "Entity.h"

Entity::Entity(Model* model, Shader shader, glm::vec3 position) {
	this->model = model;
	this->defaultShader = shader;
	this->transform.position = position;

	Entities::entities.push_back(this);
}

void Entity::setScale(glm::vec3 scale) {
	this->transform.size = scale;
}

void Entity::rotate(glm::vec3 rotation)
{
	this->transform.rotation += rotation;
}

void Entity::draw(Shader shader) {
	uploadModelMatrix(shader);
	this->model->Draw(shader);
}

void Entity::uploadModelMatrix(Shader shader) {
	glm::mat4 modelMatrix;

	shader.Use();
	modelMatrix = glm::translate(modelMatrix, transform.position);

	modelMatrix = glm::rotate(modelMatrix, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	modelMatrix = glm::scale(modelMatrix, transform.size);

	glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	shader.Disable();
}


//	Entities
std::vector<Entity*> Entities::entities;

void Entities::drawEntities() {
	using namespace Entities;

	for (int i = 0; i < entities.size(); i++) {
		entities[i]->draw(entities[i]->defaultShader);
	}
}

void Entities::deleteEntities() {
	using namespace Entities;
	for (int i = 0; i < entities.size(); i++) {
		delete(entities[i]);
	}
}