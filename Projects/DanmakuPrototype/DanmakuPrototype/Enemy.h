#pragma once
#include "Entity.h" 
#include "SpriteComponent.h"
#include "Constants.h"
#include "ResourceManager.h"

class Enemy : public Entity {
public:
	Enemy();
	Enemy(glm::vec2 position, GLuint health = 1, std::string name = "Enemy", LayerEnum layer = LayerEnum::ENEMY_LAYER);

	GLuint GetHealth() { return health; }
	void SetHealth(GLuint health) { this->health = health; }
	void DecrementHealth() { health--; }
	bool IsDead() { return health <= 0; }
private:
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
	ColliderComponent* collider{ nullptr };

	GLuint health{ 1 };
};