#pragma once
#include "Component.h"
#include "TextureManager.h"
#include "AssetManager.h"
#include "Game.h"
#include <SDL.h>
#include "glm.hpp"

class TileComponent : public Component {
private:
	SDL_Texture* texture{ nullptr };
	SDL_Rect sourceRectangle{};
	SDL_Rect destinationRectangle{};
	glm::vec2 position{};
public:
	TileComponent() = default;
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(std::string textureId, unsigned int sourceRectX, unsigned int sourceRectY, int x, int y, float scale, unsigned int tileSize) {
		texture = Game::assetManager->GetTexture(textureId);

		sourceRectangle.x = sourceRectX;
		sourceRectangle.y = sourceRectY;
		sourceRectangle.w = tileSize;
		sourceRectangle.h = tileSize;

		destinationRectangle.x = x;
		destinationRectangle.y = y;
		destinationRectangle.w = static_cast<int>(tileSize * scale);
		destinationRectangle.h = static_cast<int>(tileSize * scale);

		position.x = static_cast<float>(x);
		position.y = static_cast<float>(y);
	}

	void Initialize() override {

	}

	void Update(float deltaTime) override {
		destinationRectangle.x = static_cast<int>(position.x) - Game::camera.x;
		destinationRectangle.y = static_cast<int>(position.y) - Game::camera.y;
	}

	void Render() override {
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
	}

};