#include "BallObject.h"

BallObject::BallObject(glm::vec2 position, GLfloat radius, glm::vec2 velocity, Texture2D& sprite) : radius(radius) {
	this->position = position;
	this->velocity = velocity;
	this->sprite = sprite;
	this->size = glm::vec2(radius * 2);
}

glm::vec2 BallObject::Move(GLfloat dt, GLuint windowWidth) {
	if (!this->isStuck) {
		//Move
		this->position += this->velocity * dt;
		//Check if in-bounds
		if (this->position.x <= 0.0f) {
			this->velocity.x *= -1;
			this->position.x = 0.0f;
		}
		else if (this->position.x + this->size.x >= windowWidth) {
			this->velocity.x *= -1;
			this->position.x = windowWidth - this->size.x;
		}
		else if (this->position.y <= 0.0f) {
			this->velocity.y *= -1;
			this->position.y = 0.0f;
		}

	}
	return this->position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity) {
	this->position = position;
	this->velocity = velocity;
	this->isStuck = true;
}
