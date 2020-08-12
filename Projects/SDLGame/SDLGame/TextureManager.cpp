#include "TextureManager.h"
#include "SDL_image.h"
#include "Game.h"
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char* filename) {
    int flags = IMG_INIT_PNG;
    int initFlags = IMG_Init(IMG_INIT_PNG);
    if ((initFlags&flags) != flags) {
        std::cout << "IMG_Init failed : " << IMG_GetError() << '\n';
        return nullptr;
    }
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        std::cout << "IMGLoad(" << filename << ") failed : " << IMG_GetError() << '\n';
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, texture, &sourceRectangle, &destinationRectangle, 0.0, NULL, flip);
}
