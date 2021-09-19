#pragma once
#include "GameObject.h"
#include "Constants.h"

class PowerUp : public GameObject {
public:
	std::string type{};
	GLfloat duration{};
	bool isActivated{ false };

	PowerUp(const std::string type, const glm::vec3 color, const GLfloat duration, const glm::vec2 position, const Texture2D& texture) :
		GameObject(position, POWERUP_SIZE, texture, POWERUP_VELOCITY, color), type(type), duration(duration)
	{}
};
