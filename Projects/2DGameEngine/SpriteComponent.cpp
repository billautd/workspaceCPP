#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const std::string textureId, const float scale, const bool isFixed, const bool isAnimated,
	const unsigned int numFrames, const unsigned int animationSpeed, const bool hasDirections) :
	texture(Game::assetManager.GetTexture(textureId)), scale(scale), isFixed(isFixed),
	isAnimated(isAnimated), numFrames(numFrames), animationSpeed(animationSpeed), hasDirections(hasDirections) {}

void SpriteComponent::Init() {
	//Init pointers to other components
	transform = GetOwner().GetComponent<TransformComponent>();

	if (hasDirections) {
		const Animation downAnimation{ Animation(0, numFrames, animationSpeed) };
		const Animation rightAnimation{ Animation(1, numFrames, animationSpeed) };
		const Animation leftAnimation{ Animation(2, numFrames, animationSpeed) };
		const Animation upAnimation{ Animation(3, numFrames, animationSpeed) };

		animations.emplace("downAnimation", downAnimation);
		animations.emplace("rightAnimation", rightAnimation);
		animations.emplace("leftAnimation", leftAnimation);
		animations.emplace("upAnimation", upAnimation);

		currentAnimationName = "downAnimation";
	}
	else {
		const Animation singleAnimation{ Animation(0, numFrames, animationSpeed) };
		animations.emplace("singleAnimation", singleAnimation);

		currentAnimationName = "singleAnimation";
	}

	Play(currentAnimationName);

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = transform->GetWidth();
	sourceRect.h = transform->GetHeight();
}

void SpriteComponent::Update(const float deltaTime) {
	if (isAnimated)
		sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);

	sourceRect.y = currentAnimationIndex * transform->GetHeight();

	destRect.x = static_cast<int>(transform->GetPosition().x - (isFixed ? 0 : Game::camera.x));
	destRect.y = static_cast<int>(transform->GetPosition().y - (isFixed ? 0 : Game::camera.y));
	destRect.w = static_cast<int>(transform->GetWidth() * scale);
	destRect.h = static_cast<int>(transform->GetHeight() * scale);
}

void SpriteComponent::Render() const {
	Game::assetManager.DrawTexture(texture, &sourceRect, &destRect, flip);
}

void SpriteComponent::Play(const std::string name) {
	const Animation animation{ animations.at(name) };
	numFrames = animation.GetNumFrames();
	animationSpeed = animation.GetAnimationSpeed();
	currentAnimationIndex = animation.GetIndex();
	currentAnimationName = name;
}