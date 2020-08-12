#include "Camera.h"

Camera::Camera(glm::vec3 cPosition, glm::vec3 cTarget, glm::vec3 cWorldUp, Glfloat cSpeed) : position(cPosition), target(cTarget), worldUp(cWorldUp), speed(cSpeed) {
	direction = glm::normalize(target - position);
	right = glm::normalize(-glm::cross(worldUp, direction));
	cameraUp = glm::normalize(-glm::cross(direction, right));
}

void Camera::LookAtCurrent(glm::mat4* view) {
	*view = glm::lookAt(position, target, cameraUp);
}

void Camera::SetPosition(glm::vec3 position) {
	this->position = position;
	direction = glm::normalize(target - position);
}

void Camera::SetTarget(glm::vec3 target) {
	this->target = target;
	direction = glm::normalize(target - position);
}

void Camera::SetWorldUp(glm::vec3 worldUp) {
	this->worldUp = worldUp;
	right = glm::normalize(-glm::cross(worldUp, direction));
	cameraUp = glm::normalize(-glm::cross(direction, right));
}
