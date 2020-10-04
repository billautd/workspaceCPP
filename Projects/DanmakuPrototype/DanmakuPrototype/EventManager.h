#pragma once
#include "SDL.h"
class EventManager {
public:
	static SDL_Event event;
	static int keysNbr;
	static const Uint8* keys;
	static bool* keysProcessed;
};