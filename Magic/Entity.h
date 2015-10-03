#pragma once
class Entity
{
	struct Transform {
		float x;
		float y;
		float width;
		float height;
		float rotation;
	} transform;

	struct Appearance {
		GLuint texture;
		glm::vec3 tint;
		float alpha;
	} appearance;

public:
	Entity(GLuint tex, float x, float y, float width, float height);
	void setTint(float r, float g, float b);
	void setTexture(GLuint tex);
	void setAlpha(float alpha);

	Entity::Transform* getTransform();
	Entity::Appearance* getAppearance();
};

