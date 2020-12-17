#include "Projectile.h"
#include "Constants.h"

Projectile::Projectile() : Entity() {
	SetEntityType(EntityTypeEnum::PROJECTILE);
};

Projectile::Projectile(std::string name, LayerEnum layer) : Entity(name, layer) {};

Projectile::Projectile(glm::vec2 position, glm::vec2 velocity, glm::vec2 size, GLfloat rotation, Texture2D& texture, glm::vec3 color, GLfloat alpha, std::string name, LayerEnum layer) : Entity(name, layer) {
	SetEntityType(EntityTypeEnum::PROJECTILE);
	transform = &AddComponent<TransformComponent>(position, velocity, size, rotation);
	sprite = &AddComponent<SpriteComponent>(ResourceManager::GetShader("SpriteRendering"), texture, false, color, alpha);
	collider = &AddComponent<ColliderComponent>();
};

void Projectile::Update(GLfloat dt) {
	//Super for update on all components
	Entity::Update(dt);

	GLfloat x{ transform->GetPosition().x };
	GLfloat y{ transform->GetPosition().y };
	GLfloat w{ transform->GetWidth() };
	GLfloat h{ transform->GetHeight() };

	//On leave screen, kill projectile
	if (x - w < 0 || x > GAME_POSITION.x + GAME_SIZE.x ||
		y - h < 0 || y > GAME_POSITION.y + GAME_SIZE.y) {
		this->SetActive(false);
	}
}