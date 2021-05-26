#include "ProjectileEmitterComponent.h" 
#include "Entity.h"

ProjectileEmitterComponent::ProjectileEmitterComponent(const unsigned int speed, const unsigned int angleDeg,
	const unsigned int range, const bool shouldLoop) :speed(speed), range(range), shouldLoop(shouldLoop),
	angleRad(glm::radians(static_cast<float>(angleDeg))) {}

void ProjectileEmitterComponent::Init() {
	transform = GetOwner().GetComponent<TransformComponent>();
	origin = glm::vec2(transform->GetX(), transform->GetY());
	transform->SetVelX(glm::cos(angleRad) * speed);
	transform->SetVelY(glm::sin(angleRad) * speed);
}

void ProjectileEmitterComponent::Update(const float deltaTime) {
	if (glm::distance(transform->GetPosition(), origin) > range) {
		if (shouldLoop) {
			transform->SetX(origin.x);
			transform->SetY(origin.y);
		}
		else
			GetOwner().Destroy();
	}
}
