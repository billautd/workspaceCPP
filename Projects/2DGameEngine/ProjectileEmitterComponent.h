#pragma once
#include "TransformComponent.h"

class ProjectileEmitterComponent : public Component {
private:
	TransformComponent* transform{ nullptr };
	glm::vec2 origin{};
	const unsigned int speed{ 0 };
	const unsigned int range{ 0 };
	const float angleRad{ 0.0f };
	const bool shouldLoop{ true };

public:
	ProjectileEmitterComponent(const unsigned int speed, const unsigned int angleDeg, const unsigned int range, const bool shouldLoop);

	void Init() override;

	void Update(const float deltaTime) override;
};
