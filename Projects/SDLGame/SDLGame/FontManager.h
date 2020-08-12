#pragma once
#include "Game.h"
#include "SDL.h"

class FontManager {
public:
	static TTF_Font* LoadFont(const char* fileName, unsigned int fontSize);
	static void Draw(SDL_Texture* texture, SDL_Rect position);
};