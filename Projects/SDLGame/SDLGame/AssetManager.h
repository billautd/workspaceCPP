#pragma once
#include "EntityManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include <map>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

class AssetManager {
private:
	EntityManager* manager{ nullptr };
	std::map<std::string, SDL_Texture*> textures{};
	std::map<std::string, TTF_Font*> fonts{};
public:
	AssetManager() = default;
	~AssetManager() = default;
	AssetManager(EntityManager* manager);
	void ClearData();
	void AddTexture(std::string textureId, const char* filePath);
	SDL_Texture* GetTexture(std::string textureId) const;

	void AddFont(std::string fontId, const char* fileName, unsigned int fontSize);
	TTF_Font* GetFont(std::string fontId) const;
};