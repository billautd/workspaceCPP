#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include <glad\glad.h>
#include <SDL_ttf.h>
#include <iostream>

class Camera {
public:
	Camera(glm::vec3 cPosition = glm::vec3{ 0.0f, 0.0f, 10.0f }, glm::vec3 cWorldUp = glm::vec3(0.0f, 1.0f, 0.0f),
		GLfloat cYaw = -90.f, GLfloat cPitch = 0.0f, GLfloat cSpeed = 10.0f, GLfloat cSensitivity = 0.1f, GLfloat cZoom = 45.0f);
	~Camera() = default;

	GLfloat GetZoom() { return zoom; }
	glm::vec3 GetPosition() { return position; }

	glm::mat4 LookAtCurrent();

	void UpdateCameraVectors();

	void ProcessKeyboardInput(GLfloat deltaTime);
	void ProcessMouseInput(GLfloat x, GLfloat y);
	void ProcessMouseScrollInput(GLfloat yOffset);

private:
	glm::vec3 position{};
	glm::vec3 direction{};
	glm::vec3 worldUp{};
	glm::vec3 cameraUp{};
	glm::vec3 right{};
	GLfloat speed{ 1.0f };
	GLfloat sensitivity{ 1.0f };
	GLfloat zoom{ 1.0f };
	GLfloat yaw{ -90.0f };
	GLfloat pitch{ 0.0f };
};

