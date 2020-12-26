#include "Projectile.h"

Projectile::Projectile(glm::vec2 position, glm::vec2 velocity, glm::vec2 size, GLfloat rotation,
	std::string texture, glm::vec3 color, GLfloat alpha, bool isFromPlayer, std::string name, LayerEnum layer) : Entity(name, layer) {
	SetEntityType(isFromPlayer ? EntityTypeEnum::PLAYER_PROJECTILE : EntityTypeEnum::ENEMY_PROJECTILE);
	transform = AddComponent<TransformComponent>(position, velocity, size, rotation);
	sprite = AddComponent<SpriteComponent>("SpriteRendering", texture, false, color, alpha);
	collider = AddComponent<ColliderComponent>(position.x, position.y, size.x, size.y);
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
		Destroy();
	}
}