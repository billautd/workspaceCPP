#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* manager) : manager(manager){}

void AssetManager::ClearData() {
	textures.clear();
	fonts.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
	textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) const {
	if(textures.find(textureId) != textures.end())
		return textures.at(textureId); 
	std::cout << "Cannot get texture : " << textureId << '\n';
	return nullptr;
}

void AssetManager::AddFont(std::string fontId, const char* fileName, unsigned int fontSize) {
	TTF_Font* font = FontManager::LoadFont(fileName, fontSize);
	if (!font) {
		std::cerr << "Error loading font : " << fileName << '\n';
		return;
	}
	fonts.emplace(fontId, font);
}

TTF_Font* AssetManager::GetFont(std::string fontId) const {
	if (fonts.find(fontId) != fonts.end())
		return fonts.at(fontId);
	std::cout << "Cannot get texture : " << fontId << '\n';
	return nullptr;
}
