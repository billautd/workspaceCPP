#include "ColliderComponent.h"
#include "Entity.h"

void ColliderComponent::Init() {
	transform = GetOwner().GetComponent<TransformComponent>();
	sprite = GetOwner().GetComponent<SpriteComponent>();
	sourceRect = { 0, 0, transform->GetWidth(), transform->GetHeight() };
	destRect = { collider.x, collider.y, collider.w, collider.h };
}

void ColliderComponent::Update(const float deltaTime) {
	collider.x = static_cast<int>(transform->GetX());
	collider.y = static_cast<int>(transform->GetY());
	collider.w = static_cast<int>(transform->GetWidth() * sprite->GetScale());
	collider.h = static_cast<int>(transform->GetHeight() * sprite->GetScale());
	destRect.x = collider.x - Game::camera.x;
	destRect.y = collider.y - Game::camera.y;
}

const bool ColliderComponent::CheckRectangleCollision(const ColliderComponent* other) const {
	SDL_Rect rectangleA = this->collider;
	SDL_Rect rectangleB = other->GetCollider();
	return	rectangleA.x + rectangleA.w >= rectangleB.x &&
		rectangleB.x + rectangleB.w >= rectangleA.x &&
		rectangleA.y + rectangleA.h >= rectangleB.y &&
		rectangleB.y + rectangleB.h >= rectangleA.y;
}
