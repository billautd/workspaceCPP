#include "Camera.h"

Camera::Camera(glm::vec3 cPosition, glm::vec3 cDirection, glm::vec3 cWorldUp, GLfloat cSpeed) : position(cPosition), worldUp(cWorldUp), speed(cSpeed) {
	direction = glm::normalize(cDirection);
	right = glm::normalize(-glm::cross(worldUp, direction));
	cameraUp = glm::normalize(-glm::cross(direction, right));
}

void Camera::LookAtCurrent(glm::mat4* view) {
	*view = glm::lookAt(position, position + direction, cameraUp);
}

void Camera::SetPosition(glm::vec3 position) {
	this->position = position;
}

void Camera::SetWorldUp(glm::vec3 worldUp) {
	this->worldUp = worldUp;
	right = glm::normalize(-glm::cross(worldUp, direction));
	cameraUp = glm::normalize(-glm::cross(direction, right));
}
