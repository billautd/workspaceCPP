#pragma once
#include "Texture2D.h"
#include "SpriteRenderer.h"
#include <tuple>
#include "DirectionEnum.h"
#include "glm/glm.hpp"

//Bool = is colliding
//DirectionEnum = if colliding, direction of collision
//glm::vec2 = difference vector 
typedef std::tuple<bool, DirectionEnum, glm::vec2> Collision;

class GameObject {
public:
	//C/D
	GameObject() = default;
	GameObject(glm::vec2 position, glm::vec2 size, Texture2D& sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));

	//Draw
	virtual void Draw(SpriteRenderer& renderer);
	virtual Collision CheckCollision(GameObject& obj);

	//Utility
	void SetSolid(bool solid) { isSolid = solid; }
	bool IsSolid() { return isSolid; }

	bool IsDestroyed() { return isDestroyed; }
	void SetDestroyed(bool destroy) { this->isDestroyed = destroy; }

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

	void SetColor(glm::vec3 color) { this->color = color; }
	void SetColor(GLfloat r, GLfloat g, GLfloat b) { this->color = glm::vec3(r, g, b); }

	glm::vec2 GetSize() { return size; }
	void SetSize(glm::vec2 size) { this->size = size; }
	void SetSize(GLfloat x, GLfloat y) { this->size = glm::vec2(x, y); }
	void SetSizeX(GLfloat x) { this->size.x = x; }
	void SetSizeY(GLfloat y) { this->size.y = y; }

protected:
	glm::vec2 position{ glm::vec2(0.0f) };
	glm::vec2 size{ glm::vec2(1.0f) };
	glm::vec2 velocity{ glm::vec2(0.0f) };
	glm::vec3 color{ glm::vec3(1.0f) };
	GLfloat rotation{ 0.0f };
	bool isSolid{ false };
	bool isDestroyed{ false };

	Texture2D sprite{};
};

