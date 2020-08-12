#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glad\glad.h>

class Camera {
public:
	Camera() = default;
	Camera(glm::vec3 cPosition, glm::vec3 cDirection, glm::vec3 worldUp, GLfloat cSpeed);
	~Camera() = default;

	void LookAtCurrent(glm::mat4* view);

	glm::vec3 GetPosition() { return position; }
	glm::vec3 GetDirection() { return direction; }
	glm::vec3 GetWorldUp() { return worldUp; }
	glm::vec3 GetCameraUp() { return cameraUp; }
	glm::vec3 GetRight() { return right; }
	GLfloat GetSpeed() { return speed; }

	void SetPosition(glm::vec3 position);
	void SetWorldUp(glm::vec3 worldUp);
	void SetSpeed(GLfloat speed) { this->speed = speed; }

private:
	glm::vec3 position{};
	glm::vec3 direction{};
	glm::vec3 worldUp{};
	glm::vec3 cameraUp{};
	glm::vec3 right{};
	GLfloat speed{ 0.0f };
};

