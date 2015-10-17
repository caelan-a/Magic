#pragma once
class Entity
{
public:
	struct Transform {
		glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	} transform;

	Model* model = nullptr;

	Entity(Model* model, glm::vec3 position) {
		this->model = model;
		this->transform.position = position;
	}

	void draw(Shader shader);

	glm::mat4 modelMatrix;
	void uploadModelMatrix(Shader shader);

};

