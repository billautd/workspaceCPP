#include "Enemy.h"
#include "Constants.h"
#include "ResourceManager.h"

Enemy::Enemy() : Entity() {
	SetEntityType(EntityTypeEnum::ENEMY);
}

Enemy::Enemy(std::string name, LayerEnum layer) : Entity(name, layer) {
	SetEntityType(EntityTypeEnum::ENEMY);
	transform = &AddComponent<TransformComponent>(glm::vec2(GAME_POSITION.x + GAME_SIZE.x / 2 - ENEMY_SIZE.x / 2, GAME_POSITION.y + 20.0f),
		glm::vec2(),
		ENEMY_SIZE);
	sprite = &AddComponent<SpriteComponent>(ResourceManager::GetShader("SpriteRendering"), ResourceManager::GetTexture("enemy"), false);
	collider = &AddComponent<ColliderComponent>();
}