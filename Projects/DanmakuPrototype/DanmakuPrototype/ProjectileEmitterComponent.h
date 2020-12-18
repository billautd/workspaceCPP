#pragma once
#include "Texture2D.h"
#include "TransformComponent.h"
#include "Projectile.h"
#include "EntityManager.h"

class ProjectileEmitterComponent : public Component
{
public:
	ProjectileEmitterComponent() = default;
	ProjectileEmitterComponent(Texture2D& texture, GLfloat speed, GLfloat angle, glm::vec2 source, GLfloat delay);

	void Init() override;
	void Update(GLfloat dt) override;

private:
	TransformComponent* transform{ nullptr };
	Texture2D& projectile;
	GLfloat speed{ 0 };
	GLfloat angle{ 0 }; //In degrees
	glm::vec2 source{};

	GLfloat delay{ 0 };
	GLfloat timer{ 0 };

	void EmitProjectile();
};