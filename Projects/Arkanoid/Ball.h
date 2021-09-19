#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "ResourceManager.h"

class Ball : public GameObject
{
public:
	GLfloat radius{BALL_RADIUS};
	bool isStuck{ true };
	bool isSticky{ false };
	bool isPassthrough{ false };

	Ball() : GameObject(INITIAL_BALL_POSITION, glm::vec2(2.0f * BALL_RADIUS), ResourceManager::GetTexture2D("ball"), INITIAL_BALL_VELOCITY) {}
	~Ball() {}

	void Move(const GLfloat dt, const GLuint windowWidth);
	void Reset();
};

