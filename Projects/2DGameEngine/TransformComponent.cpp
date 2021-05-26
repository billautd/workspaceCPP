#include "TransformComponent.h"
#include "Game.h"
#include "Constants.h"

const bool TransformComponent::WillBeInsideWindow(const float deltaTime) const {
	const float newX{ GetX() + GetVelX() * deltaTime };
	const float newY{ GetY() + GetVelY() * deltaTime };

	return newX >= 0 && newY >= 0 && newX + GetWidth() <= Game::map->GetMapSizePixelsX() && newY + GetHeight() <= Game::map->GetMapSizePixelsY();
}

TransformComponent::TransformComponent(const unsigned int posX, const unsigned int posY, const unsigned int velX, const unsigned int velY,
	const unsigned int w, const unsigned int h, const bool mustStayInWindow) :
	position(glm::vec2(posX, posY)), velocity(glm::vec2(velX, velY)), width(w), height(h), mustStayInWindow(mustStayInWindow) {}

void TransformComponent::Init() {}

void TransformComponent::Update(const float deltaTime) {
	//Checks for collision with window border
	if (mustStayInWindow && !WillBeInsideWindow(deltaTime))
		return;

	position.y += velocity.y * deltaTime;
	position.x += velocity.x * deltaTime;
}

