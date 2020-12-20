#pragma once
#include "Constants.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(std::string name = "Projectile", LayerEnum layer = LayerEnum::PROJECTILE_LAYER);
	Projectile(glm::vec2 position, glm::vec2 velocity, glm::vec2 size, GLfloat rotation,
		Texture2D& texture, glm::vec3 color, GLfloat alpha, bool isFromPlayer = true, std::string name = "Projectile", LayerEnum layer = LayerEnum::PROJECTILE_LAYER);

	void Update(GLfloat dt) override;
private:
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
	ColliderComponent* collider{ nullptr };
};

