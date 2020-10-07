#pragma once
#include "Entity.h"
#include "ComponentsInclude.h"
class Player : public Entity
{
public:
	Player(std::string name, LayerEnum layer) : Entity(name, layer) {};

	void ProcessInput(SDL_Event& e, GLfloat dt) override;

	bool IsOutsideGame();
};

