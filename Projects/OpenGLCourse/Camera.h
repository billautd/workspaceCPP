#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "CameraMovementEnum.h"
#include "Constants.h"

class Camera
{
private:
	// camera Attributes
	glm::vec3 position{ glm::vec3(0.0f, 1.0f, 10.0f) };
	glm::vec3 front{ glm::vec3(0.0f, 0.0f, -1.0f) };
	glm::vec3 up{ glm::vec3(0.0f, 1.0f, 0.0f) };
	glm::vec3 right{ glm::vec3(1.0f, 0.0f, 0.0f) };
	glm::vec3 worldUp{ glm::vec3(0.0f, 1.0f, 0.0f) };
	// euler Angles
	GLfloat yaw{ -90.0f };
	GLfloat pitch;
	// camera options
	const GLfloat movementSpeed{ 0.02f };
	const GLfloat mouseSensitivity{ 0.5f };
	GLfloat zoom{ 45.0f };
	//MVP
	const glm::mat4 cameraProjection{  };

	const void UpdateCameraVectors();
public:
	Camera() { UpdateCameraVectors(); }
	const glm::mat4 GetViewMatrix() const { return glm::lookAt(position, position + front, up); }
	const void ProcessKeyboard(const CameraMovementEnum direction, const GLfloat deltaTime);
	const void ProcessMouseMovement(const GLfloat xOffset, const GLfloat yOffset, const GLboolean constrainPitch = true);
	const void ProcessMouseScroll(const GLfloat yOffset);

	const glm::vec3 GetPosition() const { return position; }
	const glm::vec3 GetFront() const { return front; }
	const glm::vec3 GetUp() const { return up; }
	const GLfloat GetZoom() const { return zoom; }

	const glm::mat4 GetCameraView() const { return glm::lookAt(position, position + front, up); }
	const glm::mat4 GetCameraProjection() const { return glm::perspective(glm::radians(zoom), ASPECT_RATIO, 0.1f, 100.0f); }
};