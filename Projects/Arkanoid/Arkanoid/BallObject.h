#pragma once
#include "GameObject.h"
#include "Constants.h" 

class BallObject : public GameObject {
public:
	BallObject() = default;
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D& sprite);

	glm::vec2 Move(GLfloat dt, GLuint windowWidth);
	void Reset(glm::vec2 position, glm::vec2 velocity);

	Collision CheckCollision(GameObject& obj) override;

	bool IsStuck() { return isStuck; }
	void SetStuck(bool stuck) { this->isStuck = stuck; }

	bool IsSticky() { return isSticky; }
	void SetSticky(bool sticky) { this->isSticky = sticky; }

	bool IsPassthrough() { return passthrough; }
	void SetPassthrough(bool passthrough) { this->passthrough = passthrough; }

	GLfloat GetRadius() { return radius; }
private:
	GLfloat radius{ BALL_RADIUS };
	bool isStuck{ true };
	bool isSticky{ false };
	bool passthrough{ false };

	//After collision
	DirectionEnum VectorDirection(glm::vec2 target);
};

