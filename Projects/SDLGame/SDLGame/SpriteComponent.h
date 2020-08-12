#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "SDL.h"
#include "Game.h"
#include "TextureManager.h"
#include "Animation.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform{ nullptr };
	SDL_Texture* texture{ nullptr };

	//Position of texture in image file
	SDL_Rect sourceRectangle{};
	//Texture displayed in window

	SDL_Rect destinationRectangle{};
	SDL_RendererFlip spriteFlip{ SDL_FLIP_NONE };

	bool isAnimated{ false };
	unsigned int numFrames{ 0 };
	unsigned int animationSpeed{ 0 };
	bool isFixed{ false };
	std::map<std::string, Animation> animations{};
	std::string currentAnimationName{ "" };
	unsigned int animationIndex{ 0 };

public:
	SpriteComponent() = default;
	~SpriteComponent() = default;
	SpriteComponent(std::string textureAssetId) {
		isAnimated = false;
		isFixed = false;
		SetTexture(textureAssetId);
	}
	SpriteComponent(std::string textureAssetId, unsigned int numFrames, unsigned int animationSpeed, bool hasDirection, bool isFixed, bool isAnimated) :
		numFrames(numFrames), animationSpeed(animationSpeed), isFixed(isFixed), isAnimated(isAnimated) {
		if (hasDirection) {
			Animation animationDown = Animation(0, numFrames, animationSpeed);
			Animation animationRight = Animation(1, numFrames, animationSpeed);
			Animation animationLeft = Animation(2, numFrames, animationSpeed);
			Animation animationUp = Animation(3, numFrames, animationSpeed);
			animations.emplace("AnimationDown", animationDown);
			animations.emplace("AnimationRight", animationRight);
			animations.emplace("AnimationLeft", animationLeft);
			animations.emplace("AnimationUp", animationUp);

			animationIndex = 0;
			currentAnimationName = "AnimationDown";
		}
		else {
			Animation singleAnimation = Animation(0, numFrames, animationSpeed);
			animations.emplace("SingleAnimation", singleAnimation);
			animationIndex = 0;
			currentAnimationName = "SingleAnimation";
		}

		Play(currentAnimationName);
		SetTexture(textureAssetId);
	}

	SDL_RendererFlip GetFlip() const { return spriteFlip; }
	void SetFlip(SDL_RendererFlip flip) { spriteFlip = flip; }
	void SetTexture(std::string textureAssetId) { texture = Game::assetManager->GetTexture(textureAssetId); }

	void Play(std::string animationName) {
		numFrames = animations.at(animationName).GetNumFrames();
		animationIndex = animations.at(animationName).GetIndex();
		animationSpeed = animations.at(animationName).GetAnimationSpeed();
		currentAnimationName = animationName;
	}

	void Initialize() override {
		transform = GetOwner()->GetComponent<TransformComponent>();
		sourceRectangle.x = 0;
		sourceRectangle.y = 0;
		sourceRectangle.w = transform->GetWidth();
		sourceRectangle.h = transform->GetHeight();

	}

	void Update(float deltaTime) override {
		if (isAnimated) {
			sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
		}
		sourceRectangle.y = animationIndex * transform->GetHeight();

		destinationRectangle.x = static_cast<int>(transform->GetPosition().x) - (isFixed ? 0 : Game::camera.x);
		destinationRectangle.y = static_cast<int>(transform->GetPosition().y) - (isFixed ? 0 : Game::camera.y);
		destinationRectangle.w = static_cast<int>((transform->GetWidth() * transform->GetScale()));
		destinationRectangle.h = static_cast<int>((transform->GetHeight() * transform->GetScale()));
	}

	void Render() override {
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
	}
};