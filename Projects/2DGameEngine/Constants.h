#pragma once
#include "SDL.h"

const unsigned int WINDOW_HEIGHT{ 1000 };
const float WINDOW_RATIO{ 16.0f / 9.0f };
const unsigned int WINDOW_WIDTH{ static_cast<unsigned int>(WINDOW_HEIGHT * WINDOW_RATIO) };

const float FPS{ 60.0f };
const float FRAME_TARGET{ 1000.0f / FPS };

const SDL_Color WHITE_COLOR{ 255, 255, 255, 255 };
const SDL_Color GREEN_COLOR{ 0, 255, 0, 255 };
const SDL_Color RED_COLOR{ 255, 0, 0, 255 };
const SDL_Color BLUE_COLOR{ 0, 0, 255, 255 };