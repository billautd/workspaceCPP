#pragma once
#include "Entity.h"
#include "ComponentsInclude.h"
#include "ResourceManager.h"

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(std::string name = "Projectile", LayerEnum layer = LayerEnum::PROJECTILE_LAYER);
	Projectile(glm::vec2 position, glm::vec2 velocity, glm::vec2 size, GLfloat rotation, Texture2D& texture, glm::vec3 color, GLfloat alpha, std::string name, LayerEnum layer = LayerEnum::PROJECTILE_LAYER);

	void Update(GLfloat dt) override;
private:
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
	ColliderComponent* collider{ nullptr };
};

