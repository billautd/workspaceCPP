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

GLfloat timer{};

void Enemy::Update(GLfloat dt) {
	Entity::Update(dt);
	if (isTranslating) {
		if (timer <= 0 || CollisionUtils::IsOutsideGame(*this)) {
			//Stop translation
			isTranslating = false;
			transform->SetVelocity(glm::vec2());
		}
		else
			timer -= dt;
	}
}

void Enemy::Translate(glm::vec2 dest, GLfloat time) {
	isTranslating = true;
	timer = time;

	glm::vec2 current{ transform->GetPosition() };
	glm::vec2 speed{ (dest - current) / time };
	transform->SetVelocity(speed);
}