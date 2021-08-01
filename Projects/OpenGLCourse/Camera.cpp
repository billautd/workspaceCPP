#include "Camera.h"

const void Camera::ProcessKeyboard(const CameraMovementEnum direction, const GLfloat deltaTime) {
	GLfloat velocity{ movementSpeed * deltaTime };
	glm::vec3 velocityFront{ front.x, 0.0f, front.z };
	if (direction == FORWARD)
		position += velocityFront * velocity;
	if (direction == BACKWARD)
		position -= velocityFront * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}


const void Camera::ProcessMouseMovement(const GLfloat xOffset, const GLfloat yOffset, const GLboolean constrainPitch) {

	yaw += xOffset * mouseSensitivity;
	pitch += yOffset * mouseSensitivity;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

const void Camera::ProcessMouseScroll(const GLfloat yOffset) {
	zoom -= (float)yOffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}

const void Camera::UpdateCameraVectors() {
	// calculate the new Front vector
	front = glm::normalize(glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
	// also re-calculate the Right and Up vector
	// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}