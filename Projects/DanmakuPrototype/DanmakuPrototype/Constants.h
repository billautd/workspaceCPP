#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"

//DISPLAY
const GLfloat FPS_TARGET{ 60.0f };
const GLfloat FRAME_TIME_TARGET{ 1000 / FPS_TARGET };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };

const GLuint SCREEN_HEIGHT{ 600 };
const GLuint SCREEN_WIDTH{ static_cast<GLuint>(SCREEN_HEIGHT * ASPECT_RATIO) };

const glm::vec2 GAME_POSITION(10.0f);
const glm::vec2 GAME_SIZE(3 * SCREEN_WIDTH / 5 - 20.0f, SCREEN_HEIGHT - 20.0f);

//TEXTURES
const GLfloat QUAD_TEXTURE_VERTICES[] = {
	//Pos       //Tex
	0.0f, 1.0f, 0.0f, 1.0f, //Bottom left
	1.0f, 0.0f, 1.0f, 0.0f, //Bottom right
	0.0f, 0.0f, 0.0f, 0.0f, //Top left

	0.0f, 1.0f, 0.0f, 1.0f, //Bottom right
	1.0f, 1.0f, 1.0f, 1.0f, //Top left
	1.0f, 0.0f, 1.0f, 0.0f //Top right
};