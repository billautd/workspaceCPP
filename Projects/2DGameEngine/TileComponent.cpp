#include "TileComponent.h"
#include "Game.h"

TileComponent::TileComponent(const unsigned int sourceRectX, const unsigned int sourceRectY, const unsigned int x, const unsigned int y,
	const unsigned int tileSize, const float scale, const std::string textureId) {
	sourceRect.x = sourceRectX;
	sourceRect.y = sourceRectY;
	sourceRect.w = tileSize;
	sourceRect.h = tileSize;

	destRect.x = x;
	destRect.y = y;
	destRect.w = static_cast<int>(tileSize * scale);
	destRect.h = static_cast<int>(tileSize * scale);

	position.x = static_cast<float>(x);
	position.y = static_cast<float>(y);

	texture = Game::assetManager.GetTexture(textureId);
}

TileComponent::~TileComponent() {
	SDL_DestroyTexture(texture);
}

void TileComponent::Update(const float deltaTime) {
	destRect.x = static_cast<unsigned int>(position.x - Game::camera.x);
	destRect.y = static_cast<unsigned int>(position.y - Game::camera.y);
}

void TileComponent::Render() const {
	Game::assetManager.DrawTexture(texture, &sourceRect, &destRect, SDL_FLIP_NONE);
}
