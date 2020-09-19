#pragma once
#include "glad/glad.h"
#include <map>
#include "DirectionEnum.h"

//Display
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };
const GLuint WINDOW_HEIGHT{ 1000 };
const GLuint WINDOW_WIDTH{ static_cast<GLuint>(ASPECT_RATIO * WINDOW_HEIGHT) };
const GLuint GRID_HEIGHT{ WINDOW_HEIGHT - 20 };
const GLuint GRID_WIDTH{ GRID_HEIGHT / 2 };
const GLuint GRID_X{ (WINDOW_WIDTH - GRID_WIDTH) / 2 };
const GLuint GRID_Y{ (WINDOW_HEIGHT - GRID_HEIGHT) / 2 };

//FPS
const GLfloat FPS{ 60.0f };
const GLfloat FRAME_TIME{ 1000.0f / 60.0f };

//Textures
const GLfloat QUAD_TEXTURE_VERTICES[] = {
	//Pos       //Tex
	0.0f, 1.0f, 0.0f, 1.0f, //Bottom left
	1.0f, 0.0f, 1.0f, 0.0f, //Bottom right
	0.0f, 0.0f, 0.0f, 0.0f, //Top left

	0.0f, 1.0f, 0.0f, 1.0f, //Bottom right
	1.0f, 1.0f, 1.0f, 1.0f, //Top left
	1.0f, 0.0f, 1.0f, 0.0f //Top right
};

//Grid
const GLshort X_TILES{ 10 };
const GLshort Y_TILES{ 20 };
const GLfloat TILE_SIZE{ GRID_HEIGHT / Y_TILES };

const std::map<DirectionEnum, glm::vec2> COMPASS{
	{DirectionEnum::UP, glm::vec2(0.0f, -1.0f)},
	{DirectionEnum::RIGHT, glm::vec2(1.0f, 0.0f)},
	{DirectionEnum::DOWN, glm::vec2(0.0f, 1.0f)},
	{DirectionEnum::LEFT, glm::vec2(-1.0f, 0.0f)}
};

//Game
const GLfloat INITIAL_FALLING_SPEED{ 1.0f };
const GLfloat INITIAL_MOVE_LR_SPEED{ 0.2f };