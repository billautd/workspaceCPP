#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "DirectionEnum.h"
#include <map>

//DISPLAY
const GLfloat FPS_TARGET{ 60.0f };
const GLfloat FRAME_TARGET{ 1000 / FPS_TARGET };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };

const GLuint SCREEN_HEIGHT{ 600 };
const GLuint SCREEN_WIDTH{ static_cast<GLuint>(SCREEN_HEIGHT * ASPECT_RATIO) };

//PLAYER CONSTANTS
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const GLfloat PLAYER_VELOCITY{ 700.0f };

//BALL CONSTANTS
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const GLfloat BALL_RADIUS{ 12.0f };

//EFFECTS CONSTANTS
const GLfloat SHAKE_TIME{ 0.05f };

//POWERUP CONSTANTS
const glm::vec2 POWERUP_SIZE(60.0f, 20.0f);
const glm::vec2 POWERUP_VELOCITY(0.0f, 3.0f);
const GLfloat SPEED_INCREMENT{ 1.2f };
const GLfloat SIZE_INCREMENT{ 30.0f };

//UTILITY
const std::map<DirectionEnum, glm::vec2> COMPASS{
	{DirectionEnum::UP, glm::vec2(0.0f, -1.0f)},
	{DirectionEnum::RIGHT, glm::vec2(1.0f, 0.0f)},
	{DirectionEnum::DOWN, glm::vec2(0.0f, 1.0f)},
	{DirectionEnum::LEFT, glm::vec2(-1.0f, 0.0f)}
};

const GLfloat QUAD_TEXTURE_VERTICES[] = {
	//Pos       //Tex
	0.0f, 1.0f, 0.0f, 1.0f, //Bottom left
	1.0f, 0.0f, 1.0f, 0.0f, //Bottom right
	0.0f, 0.0f, 0.0f, 0.0f, //Top left

	0.0f, 1.0f, 0.0f, 1.0f, //Bottom right
	1.0f, 1.0f, 1.0f, 1.0f, //Top left
	1.0f, 0.0f, 1.0f, 0.0f //Top right
};
