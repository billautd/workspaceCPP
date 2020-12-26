#pragma once
#include "Entity.h" 
#include "SpriteComponent.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "CollisionUtils.h"
#include <functional>

class Enemy : public Entity {
public:
	Enemy(glm::vec2 position, GLuint totalHealth = 1, std::string name = "Enemy", LayerEnum layer = LayerEnum::ENEMY_LAYER);

	void Update(GLfloat dt) override;

	GLuint GetTotalHealth() { return totalHealth; }
	GLuint GetHealth() { return health; }
	void SetHealth(GLuint health) { this->health = health; }
	void DecrementHealth() { health--; }
	bool IsDead() { return health <= 0; }
	void Translate(glm::vec2 dest, GLfloat time); //Time in seconds
	bool IsTranslating() { return isTranslating; }
private:
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
	ColliderComponent* collider{ nullptr };

	const GLuint totalHealth{ 1 };
	GLuint health{ 1 };
	bool isTranslating{ false };
};