#pragma once
#include "Component.h"
#include "SDL.h"
#include "glm.hpp"
#include <string>

class TileComponent : public Component
{
private:
	SDL_Texture* texture{ nullptr };
	SDL_Rect sourceRect{};
	SDL_Rect destRect{};
	glm::vec2 position{};
public:
	TileComponent(const unsigned int sourceRectX, const unsigned int sourceRectY, const unsigned int x, const unsigned int y,
		const unsigned int tileSize, const float scale, const std::string textureId);
	~TileComponent();


	void Update(const float deltaTime) override;
	void Render() const override;

};

