#pragma once
#include "Component.h"
#include "glm.hpp"
#include "EntityManager.h"
#include "TransformComponent.h"


class ProjectileEmitterComponent : public Component {
private:
	TransformComponent* transform{ nullptr };
	glm::vec2 origin{};
	unsigned int speed{ 0 };
	int range{ 0 };
	float angleRad{ 0.0f };
	bool shouldLoop{ false };

public:
	ProjectileEmitterComponent() = default;
	~ProjectileEmitterComponent() = default;
	ProjectileEmitterComponent(unsigned int speed, int angleDeg, int range, bool shouldLoop) : speed(speed), range(range), shouldLoop(shouldLoop) {
		angleRad = glm::radians(static_cast<float>(angleDeg));

	}

	void Initialize() override {
		transform = GetOwner()->GetComponent<TransformComponent>();
		origin = transform->GetPosition();
		transform->SetVelocity(static_cast<int>(speed * cos(angleRad)), static_cast<int>(speed * sin(angleRad)));
	}

	void Update(float deltaTime) override {
		if (glm::distance(transform->GetPosition(), origin) > range) {
			if (shouldLoop) 
				transform->SetPosition(origin);
			
			else 
				GetOwner()->Destroy();
		}
	}

	void Render() override {

	}
};