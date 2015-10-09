#pragma once
class Camera
{
public:
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	Camera();
	void setEulerRotation();
};
