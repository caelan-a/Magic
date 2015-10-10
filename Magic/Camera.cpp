#include "stdafx.h"
#include "Camera.h"

Camera::Camera() {
	Camera::cameraPos = glm::vec3(15.0f, 3.0f, 20.0f);
	Camera::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::setEulerRotation()
{
	glm::vec3 newRotation(glm::cos(pitch) * glm::cos(yaw), glm::sin(pitch), glm::cos(pitch) * glm::sin(yaw));
	cameraFront = glm::normalize(newRotation);
}
