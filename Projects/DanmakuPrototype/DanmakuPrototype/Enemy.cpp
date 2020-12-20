#include "Enemy.h"

Enemy::Enemy() : Entity() {
	SetEntityType(EntityTypeEnum::ENEMY);
}

Enemy::Enemy(glm::vec2 position, GLuint health, std::string name, LayerEnum layer) : Entity(name, layer), health(health) {
	SetEntityType(EntityTypeEnum::ENEMY);
	transform = AddComponent<TransformComponent>(position,
		glm::vec2(),
		ENEMY_SIZE);
	sprite = AddComponent<SpriteComponent>(ResourceManager::GetShader("SpriteRendering"), ResourceManager::GetTexture("enemy"), false);
	collider = AddComponent<ColliderComponent>();
}

GLfloat translationTimer{};

glm::vec2* source{ nullptr };
void Enemy::Update(GLfloat dt) {
	Entity::Update(dt);
	if (isTranslating) {
		if (translationTimer <= 0 || CollisionUtils::IsOutsideGame(*this)) {
			//Stop translation
			isTranslating = false;
			delete source;
			transform->SetVelocity(glm::vec2());
		}
		else
			translationTimer -= dt;
	}
}

void Enemy::Translate(glm::vec2 dest, GLfloat time) {
	isTranslating = true;
	translationTimer = time;

	//One allocation and no more
	if (!source)
		source = new glm::vec2(transform->GetPosition());
	glm::vec2 speed{ (dest - *source) / (2 * time) };
	transform->SetVelocity(speed);

}