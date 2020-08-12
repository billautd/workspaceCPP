
#pragma once
#include "Component.h"
#include "EntityManager.h"
#include "glm.hpp"
#include "SDL.h"
#include "Game.h"
#include "Map.h"

class TransformComponent : public Component {
private:
	glm::vec2 position{ 0,0 };
	glm::vec2 velocity{ 0,0 };
	unsigned int width{ 0 };
	unsigned int height{ 0 };
	float scale{ 0 };
	bool stayInBounds{ false };

public:
	TransformComponent() = default;
	~TransformComponent() = default;
	TransformComponent(int posX, int posY, int velX, int velY, unsigned int w, unsigned int h, float s) {
		position = glm::vec2{ posX, posY };
		velocity = glm::vec2{ velX, velY };
		width = w;
		height = h;
		scale = s;
	}

	void Initialize() override {};
	void Update(float deltaTime) override {
		//Handle Player OOB
		if (GetOwner()->GetName().compare("player") == 0) {
			//Check end of map collision
			HandlePlayerOOB(deltaTime);
		}
		else {
			position.x += velocity.x * deltaTime;
			position.y += velocity.y * deltaTime;
		}
	}
	void Render() override {

	};

	void HandlePlayerOOB(float deltaTime) {
		if (position.x + velocity.x * deltaTime >= 0 &&
			position.x + velocity.x * deltaTime + width <= Game::map->GetMapSizeX())
		{
			position.x += velocity.x * deltaTime;
		}

		if (position.y + velocity.y * deltaTime >= 0 &&
			position.y + velocity.y * deltaTime + height <= Game::map->GetMapSizeY()) {
			position.y += velocity.y * deltaTime;
		}
	}
		

	unsigned int GetWidth() const { return width; }
	unsigned int GetHeight() const { return height; }
	glm::vec2 GetPosition() const { return position; }
	glm::vec2 GetVelocity() const { return velocity; }
	float GetScale() const { return scale; }
	void SetPosition(int x, int y) { this->position = glm::vec2{ x,y }; }
	void SetPosition(glm::vec2 newPosition) { this->position = newPosition; }
	void SetVelocity(int velX, int velY) { this->velocity = glm::vec2{ velX, velY }; }
	void SetVelocity(glm::vec2 newVelocity) { this->velocity = newVelocity; }

};