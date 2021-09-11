#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "ResourceManager.h"


const glm::vec2 INITIAL_POSITION{ glm::vec2(SCREEN_WIDTH / 2.0f - BALL_RADIUS, SCREEN_HEIGHT - PLAYER_SIZE.y - 2.0f * BALL_RADIUS) };

class Ball : public GameObject
{
public:
	GLfloat radius{BALL_RADIUS};
	bool isStuck{ true };

	Ball() : GameObject(INITIAL_POSITION, glm::vec2(2.0f * BALL_RADIUS), ResourceManager::GetTexture2D("ball"), BALL_VELOCITY) {}
	~Ball() {}

	void Move(const GLfloat dt, const GLuint windowWidth);
	void Reset();
};

