#include "Ball.h"

void Ball::Move(const GLfloat dt, const GLuint windowWidth)
{
	if (!isStuck) {
		glm::vec2 newPosition{ position + dt * velocity };
		if (newPosition.x <= 0.0f) {
			velocity.x *= -1.0f;
			newPosition.x = 0.0f;
		}
		else if (newPosition.x + size.x >= windowWidth) {
			velocity.x *= -1.0f;
			newPosition.x = windowWidth - size.x;
		}
		if (newPosition.y <= 0.0f) {
			velocity.y *= -1.0f;
			newPosition.y = 0.0f;
		}
		position = newPosition;
	}
}

void Ball::Reset()
{
	isStuck = true;
	isSticky = false;
	isPassthrough = false;
	color = glm::vec3(1.0f);
	position = INITIAL_BALL_POSITION;
	velocity = INITIAL_BALL_VELOCITY;
}