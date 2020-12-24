#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"

//DISPLAY
const GLfloat FPS_TARGET{ 60.0f };
const GLfloat FRAME_TIME_TARGET{ 1000 / FPS_TARGET };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };

const GLuint SCREEN_HEIGHT{ 900 };
const GLuint SCREEN_WIDTH{ static_cast<GLuint>(SCREEN_HEIGHT * ASPECT_RATIO) };

const glm::vec2 GAME_POSITION{ glm::vec2(10.0f) };
const glm::vec2 GAME_SIZE(2 * SCREEN_WIDTH / 3 - 20.0f, SCREEN_HEIGHT - 20.0f);
const glm::vec2 UI_POSITION{ GAME_POSITION + glm::vec2(GAME_SIZE.x, 0) };
const glm::vec2 UI_POSITION_2{ UI_POSITION + glm::vec2(300.0f, 0) };

const glm::vec2 PLAYER_SIZE{ glm::vec2(64.0f, 64.0f) };
const GLfloat PLAYER_VELOCITY{ 200.0f };
const glm::vec2 PLAYER_INIT_POSITION{ glm::vec2(GAME_POSITION.x + GAME_SIZE.x / 2.0f - PLAYER_SIZE.x / 2, GAME_POSITION.y + GAME_SIZE.y - PLAYER_SIZE.y) };
const glm::vec2 HITBOX_SIZE{ glm::vec2(8.0f, 8.0f) };
const glm::vec2 HITBOX_POSITION{ PLAYER_INIT_POSITION + PLAYER_SIZE / 2.0f - HITBOX_SIZE / 2.0f };

const glm::vec2 PROJECTILE_SIZE{ glm::vec2(6.0f, 6.0f) };

const glm::vec2 ENEMY_SIZE{ glm::vec2(32.0f, 32.0f) };

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

//GAME
const GLfloat PROJECTILE_EMIT_SPEED{ 0.02f };
const GLfloat PROJECTILE_SPEED{ 500.0f };