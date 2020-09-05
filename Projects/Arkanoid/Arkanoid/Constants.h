#pragma once
#include "glad/glad.h"
const GLfloat FPS_TARGET{ 60.0f };
const GLfloat FRAME_TARGET{ 1000 / FPS_TARGET };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };
const GLuint SCREEN_HEIGHT{ 600 };
const GLuint SCREEN_WIDTH{ static_cast<GLuint>(SCREEN_HEIGHT * ASPECT_RATIO) };