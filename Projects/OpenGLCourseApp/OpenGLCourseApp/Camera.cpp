#include "Camera.h"

Camera::Camera(glm::vec3 cPosition, glm::vec3 cWorldUp, GLfloat cYaw, GLfloat cPitch, GLfloat cSpeed, GLfloat cSensitivity, GLfloat cZoom) :
	position(cPosition), worldUp(cWorldUp), speed(cSpeed), sensitivity(cSensitivity), zoom(cZoom) {
	UpdateCameraVectors();
}

void Camera::LookAtCurrent(glm::mat4* view) {
	*view = glm::lookAt(position, position + direction, cameraUp);
}

//void Camera::SetWorldUp(glm::vec3 worldUp) {
//	this->worldUp = worldUp;
//	right = glm::normalize(-glm::cross(worldUp, direction));
//	cameraUp = glm::normalize(-glm::cross(direction, right));
//}

void Camera::UpdateCameraVectors() {
	direction = glm::normalize(
		glm::vec3(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),
			sin(glm::radians(yaw)) * cos(glm::radians(pitch))
		)
	);
	right = glm::normalize(glm::cross(direction, worldUp));
	cameraUp = glm::normalize(glm::cross(right, direction));
}

void Camera::ProcessKeyboardInput(GLfloat deltaTime) {
	const Uint8* kbdState = SDL_GetKeyboardState(nullptr);

	//Front
	if (kbdState[SDL_GetScancodeFromKey(SDLK_z)])
		position += deltaTime * speed * glm::vec3(direction.x, 0.0f, direction.z);
	//Back
	if (kbdState[SDL_GetScancodeFromKey(SDLK_s)])
		position -= deltaTime * speed * glm::vec3(direction.x, 0.0f, direction.z);
	//Left	
	if (kbdState[SDL_GetScancodeFromKey(SDLK_q)])
		position -= deltaTime * speed * glm::vec3(right.x, 0.0f, right.z);
	//Right
	if (kbdState[SDL_GetScancodeFromKey(SDLK_d)])
		position += deltaTime * speed * glm::vec3(right.x, 0.0f, right.z);
}

GLuint lastX{ 0 };
GLuint lastY{ 0 };
GLboolean firstMouse{ true };
void Camera::ProcessMouseInput(GLfloat x, GLfloat y) {
	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	GLfloat xoffset{ x - lastX };
	GLfloat yoffset{ lastY - y };

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	UpdateCameraVectors();

	lastX = x;
	lastY = y;
}

void Camera::ProcessMouseScrollInput(GLfloat yOffset) {
	zoom -= yOffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}
