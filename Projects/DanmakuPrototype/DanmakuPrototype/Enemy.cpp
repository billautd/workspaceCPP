#include "Enemy.h"

Enemy::Enemy(glm::vec2 position, GLuint totalHealth, std::string name, LayerEnum layer) : Entity(name, layer), totalHealth(totalHealth), health(totalHealth) {
	SetEntityType(EntityTypeEnum::ENEMY);
	transform = AddComponent<TransformComponent>(position,
		glm::vec2(),
		ENEMY_SIZE);
	sprite = AddComponent<SpriteComponent>("SpriteRendering", "enemy", false);
	collider = AddComponent<ColliderComponent>(position.x, position.y, ENEMY_SIZE.x, ENEMY_SIZE.y);
}

GLfloat translationTimer{};
glm::vec2* source{ nullptr };

void Enemy::Update(GLfloat dt) {
	Entity::Update(dt);
	if (isTranslating) {
		if (translationTimer <= 0 || CollisionUtils::WillBeOutsideGame(*transform, transform->GetVelocity())) {
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