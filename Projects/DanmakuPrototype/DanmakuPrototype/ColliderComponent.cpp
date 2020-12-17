#include "ColliderComponent.h"

void ColliderComponent::Init() {
	this->transform = GetOwner()->GetComponent<TransformComponent>();
}

void ColliderComponent::Update(GLfloat dt) {
	x = transform->GetPosition().x;
	y = transform->GetPosition().y;
	width = transform->GetWidth();
	height = transform->GetHeight();
}