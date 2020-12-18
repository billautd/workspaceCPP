#pragma once
#include "KeyboardControlComponent.h"
#include "Constants.h"
#include "SpriteComponent.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "CollisionUtils.h"
#include "Projectile.h"

class Player : public Entity
{
public:
	Player();
	Player(std::string name = "Player", LayerEnum layer = LayerEnum::PLAYER_LAYER);

	void ProcessInput(SDL_Event& e, GLfloat dt) override;
	void EmitProjectiles();
private:
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
	KeyboardControlComponent* kbd{ nullptr };
	ColliderComponent* collider{ nullptr };

};

