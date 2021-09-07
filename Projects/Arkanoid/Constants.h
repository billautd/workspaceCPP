#pragma once
#include "glad/glad.h"

//Screen/Window
const GLuint SCREEN_HEIGHT{ 1080 };
const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };
const GLuint SCREEN_WIDTH{ static_cast<GLuint>(SCREEN_HEIGHT * ASPECT_RATIO) };