#pragma once
#include "glm.hpp"
#include "SDL.h"

#include "Component.h"

class TransformComponent : public Component
{
private:
	glm::vec2 position{};
	glm::vec2 velocity{};
	const int width{ 0 };
	const int height{ 0 };
	const bool mustStayInWindow{ false };

	const bool WillBeInsideWindow(const float deltaTime) const;
public:
	TransformComponent(const unsigned int posX, const unsigned int posY, const unsigned int velX, const unsigned int velY, const unsigned int w, const unsigned int h, const bool mustStayInWindow = false);
	void Init() override;
	void Update(const float deltaTime) override;

	glm::vec2 GetPosition() const { return position; }
	const float GetX() const { return position.x; }
	const float GetY() const { return position.y; }
	const float GetVelX() const { return velocity.x; }
	const float GetVelY() const { return velocity.y; }
	const int GetWidth() const { return width; }
	const int GetHeight() const { return height; }
	void SetX(const float x) { position.x = x; }
	void SetY(const float y) { position.y = y; }
	void SetVelX(const float velX) { velocity.x = velX; }
	void SetVelY(const float velY) { velocity.y = velY; }

};

