#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <map>
#include <string>
#include "SDL_ttf.h"

class AssetManager
{
private:
	std::map<const std::string, SDL_Texture*> textures{};
	std::map<const std::string, TTF_Font*> fonts{};
public:
	~AssetManager() { ClearData(); }
	void ClearData();

	void AddTexture(const std::string id, const char* filePath);
	static SDL_Texture* LoadTexture(const char* filePath);
	SDL_Texture* GetTexture(const std::string id) const;
	void DrawTexture(SDL_Texture* texture, const SDL_Rect* sourceRect, const SDL_Rect* destRect, const SDL_RendererFlip flip) const;

	void AddFont(const std::string id, const char* filePath, const unsigned int fontSize);
	static TTF_Font* LoadFont(const char* filePath, const unsigned int fontSize);
	TTF_Font* GetFont(const std::string id) const;
	void DrawFont(SDL_Texture* fontTexture, const SDL_Rect* position) const;
};

