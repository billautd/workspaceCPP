#pragma once
#include "glad/glad.h"

const GLuint SCREEN_HEIGHT{ 1080 };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };
const GLuint SCREEN_WIDTH{ static_cast<GLuint>(ASPECT_RATIO * SCREEN_HEIGHT) };