#pragma once
#include "Entity.h"
#include "ComponentsInclude.h"
class Player : public Entity
{
public:
	Player() : Entity() {}
	Player(std::string name = "Player", LayerEnum layer = LayerEnum::PLAYER_LAYER);

	void ProcessInput(SDL_Event& e, GLfloat dt) override;

	bool IsOutsideGame();
	void EmitProjectiles();
private:
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
	KeyboardControlComponent* kbd{ nullptr };

};

