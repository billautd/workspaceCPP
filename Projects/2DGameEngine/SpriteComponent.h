#pragma once
#include "TransformComponent.h"
#include "Game.h"
#include "SDL.h"
#include "Animation.h"

class SpriteComponent : public Component
{
private:
	SDL_Texture* texture{ nullptr };
	SDL_Rect sourceRect{};
	SDL_Rect destRect{};
	const SDL_RendererFlip flip{ SDL_FLIP_NONE };
	const float scale{ 1.0f };

	const bool isAnimated{ false };
	const bool isFixed{ false };
	const bool hasDirections{ false };
	std::map<const std::string, const Animation> animations{};

	unsigned int numFrames{ 0 };
	unsigned int animationSpeed{ 0 };
	unsigned int currentAnimationIndex{ 0 };
	std::string currentAnimationName{ "" };

	TransformComponent* transform{ nullptr };

public:
	SpriteComponent(const std::string textureId, const float scale = 1.0f, const bool isFixed = false,
		const bool isAnimated = false, const unsigned int numFrames = 0, const unsigned int animationSpeed = 0, const bool hasDirections = false);

	void Init() override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void Play(const std::string name);

	const float GetScale() const { return scale; }
};

