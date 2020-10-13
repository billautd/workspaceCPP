#pragma once
#include "Entity.h"
#include "ComponentsInclude.h"
#include "ResourceManager.h"

class Projectile : public Entity
{
public:
	Projectile() : Entity() {};
	Projectile(std::string name, LayerEnum layer = LayerEnum::PROJECTILE_LAYER) : Entity(name, layer) {};
	Projectile(glm::vec2 position, glm::vec2 velocity, glm::vec2 size, GLfloat rotation, Texture2D& texture, glm::vec3 color, GLfloat alpha, std::string name, LayerEnum layer = LayerEnum::PROJECTILE_LAYER) : Entity(name, layer) {
		transform = &AddComponent<TransformComponent>(position, velocity, size, rotation);
		sprite = &AddComponent<SpriteComponent>(ResourceManager::GetShader("SpriteRendering"), texture, false, color, alpha);
	};

	void Update(GLfloat dt) override;
	void Destroy() override;
private:
	TransformComponent* transform{ nullptr };
	SpriteComponent* sprite{ nullptr };
};

