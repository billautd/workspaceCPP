#pragma once
#include "Component.h"
#include "glm/glm.hpp"

class TransformComponent : public Component {
public:
	TransformComponent(glm::vec2 pos, glm::vec2 vel, GLfloat width, GLfloat height, GLfloat scale) : position(pos), velocity(vel), width(width), height(height), scale(scale) {};
	void Init() override {}

	void Update(GLfloat dt) override {
		position += velocity * dt;
	}

	glm::vec2 GetPosition() { return position; }
	void SetPosition(glm::vec2 position) { this->position = position; }
	glm::vec2 GetVelocity() { return velocity; }
	GLfloat GetWidth() { return width; }
	GLfloat GetHeight() { return height; }
	glm::vec2 GetScale() { return scale; }

private:
	glm::vec2 position{};
	glm::vec2 velocity{};
	GLfloat width{ 10.0f };
	GLfloat height{ 10.0f };
	glm::vec2 scale{ 1.0f };
};