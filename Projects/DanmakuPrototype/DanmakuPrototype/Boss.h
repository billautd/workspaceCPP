#pragma once
#include "Enemy.h" 
#include "EntityManager.h"

class Boss : public Enemy {
public:
	Boss(glm::vec2 position, GLuint totalHealth = 1, std::string name = "Boss", LayerEnum layer = LayerEnum::ENEMY_LAYER);

	void Update(GLfloat dt) override;
	void Destroy() override;
private:
	Entity* lifeBar{ nullptr };
	TransformComponent* lifeBarTransform{ nullptr };
};