#pragma once
#include "Entity.h" 
#include "SpriteComponent.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "CollisionUtils.h"

class Enemy : public Entity {
public:
	Enemy();
	Enemy(glm::vec2 position, GLuint health = 1, std::string name = "Enemy", LayerEnum layer = LayerEnum::ENEMY_LAYER);

	void Update(GLfloat dt) override;

	GLuint GetHealth() { return health; }
	void SetHealth(GLuint health) { this->health = health; }
	void DecrementHealth() { health--; }
	bool IsDead() { return health <= 0; }
	void Translate(glm::vec2 dest, GLfloat time); //Time in seconds

private:
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
	ColliderComponent* collider{ nullptr };

	GLuint health{ 1 };
	bool isTranslating{ false };
};