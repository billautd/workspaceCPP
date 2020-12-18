#include "ProjectileEmitterComponent.h"

ProjectileEmitterComponent::ProjectileEmitterComponent(Texture2D& texture, GLfloat speed, GLfloat angle, glm::vec2 source, GLfloat delay)
	: projectile(texture), speed(speed), angle(angle), source(source), timer(delay), delay(delay) {}

void ProjectileEmitterComponent::Init() {
	transform = GetOwner()->GetComponent<TransformComponent>();
}

void ProjectileEmitterComponent::Update(GLfloat dt) {
	source = transform->GetPosition() + glm::vec2{ transform->GetWidth() / 2.0f, transform->GetHeight() };
	if (timer <= 0) {
		EmitProjectile();
		timer = delay;
	}
	else
		timer -= dt;
}

void ProjectileEmitterComponent::EmitProjectile() {
	glm::vec2 speedVector{ cos(angle) * speed, -sin(angle) * speed };
	EntityManager::AddEntity(new Projectile(source, speedVector, PROJECTILE_SIZE, 0.0f, projectile, glm::vec3(1.0f), 1.0f, "Projectile"));
}