#pragma once
#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "glm/glm.hpp"

class GameObject {
public:
	//C/D
	GameObject() = default;
	GameObject(glm::vec2 position, glm::vec2 size, Texture2D& sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));

	//Draw
	virtual void Draw(SpriteRenderer& renderer);

	//Utility
	void SetSolid(bool solid) { isSolid = solid; }
	bool IsDestroyed() { return isDestroyed; }
	void SetDestroyed(bool destroy) { this->isDestroyed = destroy; }
	bool IsSolid() { return isSolid; }
	glm::vec2 GetPosition() { return position; }
	void SetPosition(glm::vec2 position) { this->position = position; }
	glm::vec2 GetSize() { return size; }

protected:
	glm::vec2 position{ glm::vec2(0.0f) };
	glm::vec2 size{ glm::vec2(1.0f) };
	glm::vec2 velocity{ glm::vec2(0.0f) };
	glm::vec3 color{ glm::vec3(1.0f) };
	GLfloat rotation{ 0.0f };
	bool isSolid{ false };
	bool isDestroyed{ false };

	Texture2D sprite;

};

