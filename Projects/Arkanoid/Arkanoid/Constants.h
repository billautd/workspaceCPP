#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "DirectionEnum.h"
#include <map>

const GLfloat FPS_TARGET{ 60.0f };
const GLfloat FRAME_TARGET{ 1000 / FPS_TARGET };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };

const GLuint SCREEN_HEIGHT{ 600 };
const GLuint SCREEN_WIDTH{ static_cast<GLuint>(SCREEN_HEIGHT * ASPECT_RATIO) };

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const GLfloat PLAYER_VELOCITY{ 700.0f };

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const GLfloat BALL_RADIUS{ 12.0f };

const std::map<DirectionEnum, glm::vec2> COMPASS{
	{DirectionEnum::UP, glm::vec2(0.0f, -1.0f)},
	{DirectionEnum::RIGHT, glm::vec2(1.0f, 0.0f)},
	{DirectionEnum::DOWN, glm::vec2(0.0f, 1.0f)},
	{DirectionEnum::LEFT, glm::vec2(-1.0f, 0.0f)}
};