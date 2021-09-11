#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "ResourceManager.h"

class Player : public GameObject {
public:
	Player() : GameObject(glm::vec2(SCREEN_WIDTH / 2.0f - PLAYER_SIZE.x / 2.0f, SCREEN_HEIGHT - PLAYER_SIZE.y), 
		PLAYER_SIZE, ResourceManager::GetTexture2D("paddle"), glm::vec2(PLAYER_VELOCITY, 0.0f)) {}

	~Player() {}
};
