#pragma once
#include "SDL.h"

const float RATIO{ 16.0f / 9.0f };
const unsigned int WINDOW_HEIGHT{ 800 };
const unsigned int WINDOW_WIDTH{ static_cast<int>(WINDOW_HEIGHT*RATIO) };

const unsigned int FPS{ 60 };
const unsigned int FRAME_TARGET_TIME{ 1000 / FPS};

enum class CollisionType {
	NO_COLLISION,
	PLAYER_ENEMY_COLLISION,
	PLAYER_PROJECTILE_COLLISION,
	ENEMY_PROJECTILE_COLLISION,
	PLAYER_VEGETATION_COLLISION,
	PLAYER_LEVEL_COMPLETE_COLLISION
};

enum class LayerType {
	TILE_LAYER = 0,
	VEGETATION_LAYER = 1,
	ENEMY_LAYER = 2,
	OBSTACLE_LAYER = 3,
	PLAYER_LAYER = 4,
	PROJECTILE_LAYER = 5,
	UI_LAYER = 6
};

const unsigned int NUM_LAYER{ 7 };

const SDL_Color WHITE_COLOR{ 255, 255, 255, 255 };
const SDL_Color GREEN_COLOR{ 0, 255, 0, 255 };