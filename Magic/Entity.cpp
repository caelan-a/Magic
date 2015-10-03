#include "stdafx.h"
#include "Entity.h"


Entity::Entity(GLuint tex, float x, float y, float width, float height)
{
	transform.x = x;
	transform.y = y;
	transform.width = width;
	transform.height = height;
	transform.rotation = 0;

	appearance.texture = tex;
	appearance.alpha = 1.0f;
	appearance.tint = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Entity::setTint(float r, float g, float b) {
	appearance.tint = glm::vec3(r,g,b);
}

void Entity::setTexture(GLuint tex)
{
	appearance.texture = tex;
}

void Entity::setAlpha(float alpha)
{
	appearance.alpha = alpha;
}

Entity::Transform * Entity::getTransform()
{
	return &transform;
}

Entity::Appearance * Entity::getAppearance()
{
	return &appearance;
}

