#include "Enemy.h"

Enemy::Enemy() : Entity() {
	SetEntityType(EntityTypeEnum::ENEMY);
}

Enemy::Enemy(glm::vec2 position, GLuint health, std::string name, LayerEnum layer) : Entity(name, layer), health(health) {
	SetEntityType(EntityTypeEnum::ENEMY);
	transform = &AddComponent<TransformComponent>(position,
		glm::vec2(),
		ENEMY_SIZE);
	sprite = &AddComponent<SpriteComponent>(ResourceManager::GetShader("SpriteRendering"), ResourceManager::GetTexture("enemy"), false);
	collider = &AddComponent<ColliderComponent>();
}