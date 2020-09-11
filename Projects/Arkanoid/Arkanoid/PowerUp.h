#pragma once
#include <string>
#include "GameObject.h"

class PowerUp : public GameObject {
public:
	PowerUp(std::string type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture);

	bool IsActivated() { return activated; }
	void SetActivated(bool activated) { this->activated = activated; }

	std::string GetType() { return type; }

	GLfloat GetDuration() { return duration; }
	void SetDuration(GLfloat duration) { this->duration = duration; }
private:
	std::string type{ "" };
	GLfloat duration{ 0.0f };
	bool activated{ false };
};

