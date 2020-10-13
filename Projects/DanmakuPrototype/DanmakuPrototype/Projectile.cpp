#include "Projectile.h"
#include "Constants.h"

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

void Projectile::Destroy() {
	delete transform;
	delete sprite;
}