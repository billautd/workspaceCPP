#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include <iostream>

class TransformComponent : public Component {
public:
	TransformComponent(glm::vec2 position, glm::vec2 velocity, glm::vec2 size, GLfloat rotation = 0.0f) : position(position), velocity(velocity), size(size), rotation(rotation) {};
	void Init() override {}

	void Update(GLfloat dt) override {
		position += velocity * dt;
	}

	glm::vec2 GetPosition() { return position; }
	void SetPosition(glm::vec2 position) { this->position = position; }
	glm::vec2 GetVelocity() { return velocity; }
	glm::vec2 GetSize() { return size; }
	GLfloat GetWidth() { return size.x; }
	GLfloat GetHeight() { return size.y; }
	GLfloat GetRotation() { return rotation; }

private:
	glm::vec2 position{ glm::vec2(0.0f) };
	GLfloat rotation{ 0.0f };	//In degrees
	glm::vec2 velocity{};
	glm::vec2 size{ glm::vec2(100.0f) };
};