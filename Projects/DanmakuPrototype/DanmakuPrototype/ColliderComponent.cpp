#include "ColliderComponent.h"

void ColliderComponent::Init() {
	this->transform = GetOwner()->GetComponent<TransformComponent>();
	GetOwner()->SetHasCollision(true);
}


void ColliderComponent::Update(GLfloat dt) {
	x += transform->GetVelocity().x * dt * 2.0f;
	y += transform->GetVelocity().y * dt * 2.0f;
}