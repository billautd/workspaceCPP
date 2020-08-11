#pragma once

const GLfloat ASPECT_RATIO{ 16.0f / 9.0f };
const GLuint WINDOW_HEIGHT{ 720 };
const GLuint WINDOW_WIDTH{ static_cast<GLuint>(WINDOW_HEIGHT * ASPECT_RATIO) };

const GLfloat FPS_TARGET{ 60.0f };
const GLfloat FRAME_TARGET_TIME{ 1000.0f / FPS_TARGET };
