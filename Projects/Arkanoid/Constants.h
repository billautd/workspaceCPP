#pragma once
#include "glad/glad.h"
#include "glm.hpp"

const GLuint SCREEN_HEIGHT{ 800 };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };
const GLuint SCREEN_WIDTH{ static_cast<GLuint>(ASPECT_RATIO * SCREEN_HEIGHT) };

//Player
const glm::vec2 PLAYER_SIZE{ 100.0f, 20.0f };
const GLfloat PLAYER_VELOCITY{ 500.0f };