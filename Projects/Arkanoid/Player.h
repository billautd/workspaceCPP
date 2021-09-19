#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "ResourceManager.h"

class Player : public GameObject {
public:
	Player() : GameObject(INITIAL_PLAYER_POSITION, 
		INITIAL_PLAYER_SIZE, ResourceManager::GetTexture2D("paddle"), glm::vec2(PLAYER_VELOCITY, 0.0f)) {}

	~Player() {}

	void Reset();
};
