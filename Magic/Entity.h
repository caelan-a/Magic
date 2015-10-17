#pragma once
class Entity
{
public:
	struct Transform {
		glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	} transform;

	Shader defaultShader;
	Model* model = nullptr;

	void setScale(glm::vec3 scale);

	Entity(Model* model, Shader shader, glm::vec3 position);
	void draw(Shader shader);
	void uploadModelMatrix(Shader shader);
};

namespace Entities {
	extern std::vector<Entity*> entities;
	void drawEntities();
	void deleteEntities();
};