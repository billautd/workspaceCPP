#include "Boss.h"

Boss::Boss(glm::vec2 position, GLuint health, std::string name, LayerEnum layer) : Enemy(position, health, name, layer) {
	lifeBar = EntityManager::AddEntity(new Entity("LifeBar", LayerEnum::UI_LAYER));
	lifeBarTransform = lifeBar->AddComponent<TransformComponent>(GAME_POSITION, glm::vec2(), glm::vec2(GAME_SIZE.x, 10.0f));
	lifeBar->AddComponent<SpriteComponent>("SpriteRendering", "lifeBar");
}

void Boss::Update(GLfloat dt) {
	Enemy::Update(dt);
	if (!IsDead())
		lifeBarTransform->SetWidth(static_cast<GLfloat>(GetHealth()) / static_cast<GLfloat>(GetTotalHealth()) * GAME_SIZE.x);
}

void Boss::Destroy() {
	lifeBar->Destroy();
	Entity::Destroy();
}