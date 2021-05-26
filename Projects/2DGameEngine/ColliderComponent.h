#pragma once
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <string>
#include "SDL.h"

class ColliderComponent : public Component {
private:
	const std::string colliderTag{ "" };
	SDL_Rect collider{};
	SDL_Rect sourceRect{};
	SDL_Rect destRect{};
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
public:
	ColliderComponent(std::string colliderTag, const int x, const int y, const int width, const int height) :
		colliderTag(colliderTag), collider({ x, y, width, height }) {}

	void Init() override;
	void Update(const float deltaTime) override;
	SDL_Rect GetCollider() const { return collider; }
	const std::string GetColliderTag() const { return colliderTag; }
	const bool CheckRectangleCollision(const ColliderComponent* other) const;
};