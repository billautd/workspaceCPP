#pragma once
#include "Component.h"
#include "SDL.h"
#include "TransformComponent.h"
#include "TextureManager.h"
#include "Game.h"
#include "AssetManager.h"

class ColliderComponent : public Component {
private:
	std::string colliderTag{ "" };
	SDL_Rect collider{};
	SDL_Rect sourceRectangle{};
	SDL_Rect destinationRectangle{};
	TransformComponent* transform{};
public:
	ColliderComponent() = default;
	~ColliderComponent() = default;
	ColliderComponent(std::string colliderTag, int x, int y, unsigned int w, unsigned int h) : colliderTag(colliderTag) {
		collider = SDL_Rect{ x, y, static_cast<int>(w), static_cast<int>(h) };
	};

	void Initialize() override {
		if (GetOwner()->HasComponent<TransformComponent>()) {
			transform = GetOwner()->GetComponent<TransformComponent>();
			sourceRectangle = { 0, 0, static_cast<int>(transform->GetWidth()), static_cast<int>(transform->GetHeight()) };
			destinationRectangle = {collider.x, collider.y, collider.w, collider.h };
		}
	}

	void Update(float deltaTime) override {
		collider.x = static_cast<int>(transform->GetPosition().x);
		collider.y = static_cast<int>(transform->GetPosition().y);
		collider.w = static_cast<int>(transform->GetWidth() * transform->GetScale());
		collider.h = static_cast<int>(transform->GetHeight() * transform->GetScale());
		destinationRectangle.x = collider.x - Game::camera.x;
		destinationRectangle.y = collider.y - Game::camera.y;
	}

	void Render() override {
	}

	SDL_Rect GetCollider() const { return collider; }
	std::string GetColliderTag() const { return colliderTag; }
};