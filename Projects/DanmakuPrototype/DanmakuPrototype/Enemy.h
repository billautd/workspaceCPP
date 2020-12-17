#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy();
	Enemy(std::string name = "Enemy", LayerEnum layer = LayerEnum::ENEMY_LAYER);

private:
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
	ColliderComponent* collider{ nullptr };
};