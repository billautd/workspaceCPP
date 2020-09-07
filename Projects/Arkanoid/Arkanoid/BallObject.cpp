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

//AABB-circle => distance between closest point of circle to rectangle <= radius => collision
Collision BallObject::CheckCollision(GameObject& obj) {
	//Get centers  
	glm::vec2 ballCenter = this->position + this->radius;
	glm::vec2 aabbHalfExtents = obj.GetSize() / 2.0f;
	glm::vec2 aabbCenter = obj.GetPosition() + aabbHalfExtents;

	// get difference vector between both centers
	glm::vec2 difference = ballCenter - aabbCenter;
	glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabbCenter + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - ballCenter;

	if (glm::length(difference) < this->radius)
		return std::make_tuple(true, VectorDirection(difference), difference);
	else
		return std::make_tuple(false, DirectionEnum::UP, glm::vec2(0.0f));

}

DirectionEnum BallObject::VectorDirection(glm::vec2 target) {
	GLfloat max{ 0.0f };
	DirectionEnum bestMatch{ static_cast<DirectionEnum>(0) };

	for (size_t i = 0; i < COMPASS.size(); i++) {
		GLfloat dot = glm::dot(glm::normalize(target), COMPASS.at(static_cast<DirectionEnum>(i)));
		if (dot > max) {
			max = dot;
			bestMatch = static_cast<DirectionEnum>(i);
		}
	}
	return bestMatch;
}
