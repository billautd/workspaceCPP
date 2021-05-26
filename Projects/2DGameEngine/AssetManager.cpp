#include "AssetManager.h" 
#include "Game.h"

void AssetManager::ClearData() {
	textures.clear();
	fonts.clear();
}

void AssetManager::AddTexture(const std::string id, const char* filePath) {
	textures.emplace(id, LoadTexture(filePath));
}

SDL_Texture* AssetManager::LoadTexture(const char* filePath) {
	SDL_Surface* surface{ IMG_Load(filePath) };
	if (!surface) {
		std::cerr << "IMG_Load : Error loading surface at path " << filePath << '\n' << IMG_GetError() << '\n';
		return nullptr;
	}

	SDL_Texture* texture{ SDL_CreateTextureFromSurface(Game::renderer.get(), surface) };
	if (!texture) {
		std::cerr << "SDL_CreateTextureFromSurface : Error creating texture from surface at path " << filePath << '\n' << IMG_GetError() << '\n';
		return nullptr;
	}


	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* AssetManager::GetTexture(const std::string id) const {
	return textures.at(id);
}

void AssetManager::DrawTexture(SDL_Texture* texture, const SDL_Rect* sourceRect, const SDL_Rect* destRect, const SDL_RendererFlip flip) const {
	SDL_RenderCopyEx(Game::renderer.get(), texture, sourceRect, destRect, 0.0, NULL, flip);
}

void AssetManager::AddFont(const std::string id, const char* filePath, const unsigned int fontSize) {
	fonts.emplace(id, LoadFont(filePath, fontSize));
}

TTF_Font* AssetManager::LoadFont(const char* filePath, const unsigned int fontSize) {
	return TTF_OpenFont(filePath, fontSize);
}

TTF_Font* AssetManager::GetFont(const std::string id) const {
	return fonts.at(id);
}

void AssetManager::DrawFont(SDL_Texture* fontTexture, const SDL_Rect* position) const {
	SDL_RenderCopy(Game::renderer.get(), fontTexture, nullptr, position);
}
