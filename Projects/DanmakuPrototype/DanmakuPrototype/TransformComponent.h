#pragma once
#include "glm/glm.hpp"
#include "Component.h"
#include <iostream>

class TransformComponent : public Component {
public:
	TransformComponent(glm::vec2 position, glm::vec2 velocity, glm::vec2 size, GLfloat rotation = 0.0f) :
		position(position), velocity(velocity), size(size), rotation(rotation) {};

	void Init() override {}
	void Update(GLfloat dt) override {
		position += velocity * dt;
	}


	glm::vec2 GetPosition() { return position; }
	void SetPosition(glm::vec2 position) { this->position = position; }
	void SetPosition(GLfloat x, GLfloat y) { this->position = glm::vec2(x, y); }
	void SetPositionX(GLfloat x) { this->position.x = x; }
	void SetPositionY(GLfloat y) { this->position.y = y; }

	glm::vec2 GetVelocity() { return velocity; }
	void SetVelocity(glm::vec2 vel) { this->velocity = vel; }
	void SetVelocity(GLfloat x, GLfloat y) { this->velocity = glm::vec2(x, y); }
	void SetVelocityX(GLfloat x) { this->velocity.x = x; }
	void SetVelocityY(GLfloat y) { this->velocity.y = y; }

	glm::vec2 GetSize() { return size; }
	void SetSize(glm::vec2 size) { this->size = size; }
	void SetSize(GLfloat x, GLfloat y) { this->size = glm::vec2(x, y); }

	GLfloat GetWidth() { return size.x; }
	void SetWidth(GLfloat x) { this->size.x = x; }
	GLfloat GetHeight() { return size.y; }
	void SetHeight(GLfloat y) { this->size.y = y; }


	GLfloat GetRotation() { return rotation; }

private:
	glm::vec2 position{ glm::vec2(0.0f) };
	GLfloat rotation{ 0.0f };	//In degrees
	glm::vec2 velocity{};
	glm::vec2 size{ glm::vec2(100.0f) };
};