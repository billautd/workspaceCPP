#include "Player.h"

Player::Player(std::string name, LayerEnum layer) : Entity(name, layer) {
	//Player init
	SetEntityType(EntityTypeEnum::PLAYER);
	transform = AddComponent<TransformComponent>(PLAYER_INIT_POSITION, glm::vec2(0.0f), PLAYER_SIZE);
	sprite = AddComponent<SpriteComponent>("SpriteRendering", "playerCenter", true);
	kbd = AddComponent<KeyboardControlComponent>();
	collider = AddComponent<ColliderComponent>(HITBOX_POSITION.x, HITBOX_POSITION.y, HITBOX_SIZE.x, HITBOX_SIZE.y);

	//Hitbox init
	hitbox = EntityManager::AddEntity(new Entity("Hitbox", LayerEnum::PROJECTILE_LAYER));
	hitbox->SetEntityType(EntityTypeEnum::PLAYER);
	hitboxTransform = hitbox->AddComponent<TransformComponent>(HITBOX_POSITION, glm::vec2(), HITBOX_SIZE);
	hitbox->AddComponent<SpriteComponent>("SpriteRendering", "hitbox", false);
}

GLfloat emitTimer{ 0.0f };
void Player::ProcessInput(SDL_Event& e, GLfloat dt) {
	Entity::ProcessInput(e, dt);

	const Uint8* keys{ EventManager::keys };

	SDL_Scancode focus{ kbd->GetFocusKey() };
	GLfloat velocity{ keys[focus] ? PLAYER_VELOCITY / 3.0f : PLAYER_VELOCITY };

	//UP
	SDL_Scancode up{ kbd->GetUpKey() };
	if (keys[up]) {
		if (CollisionUtils::WillBeOutsideGame(*transform, glm::vec2(0, -velocity * dt))) {
			transform->SetVelocityY(0);
			hitboxTransform->SetVelocityY(0);
			transform->SetPositionY(GAME_POSITION.y);
			hitboxTransform->SetPositionY(GAME_POSITION.y + PLAYER_SIZE.y / 2.0f - HITBOX_SIZE.y / 2.0f);
		}
		else {
			transform->SetVelocityY(-velocity);
			hitboxTransform->SetVelocityY(-velocity);
		}

	}
	else {
		transform->SetVelocityY(0);
		hitboxTransform->SetVelocityY(0);
	}


	//DOWN
	SDL_Scancode down{ kbd->GetDownKey() };
	if (keys[down]) {
		if (CollisionUtils::WillBeOutsideGame(*transform, glm::vec2(0, velocity * dt))) {
			transform->SetVelocityY(0);
			hitboxTransform->SetVelocityY(0);
			transform->SetPositionY(GAME_POSITION.y + GAME_SIZE.y - PLAYER_SIZE.y);
			hitboxTransform->SetPositionY(GAME_POSITION.y + GAME_SIZE.y - PLAYER_SIZE.y + PLAYER_SIZE.y / 2.0f - HITBOX_SIZE.y / 2.0f);
		}
		else {
			transform->SetVelocityY(velocity);
			hitboxTransform->SetVelocityY(velocity);
		}
	}
	else if (!keys[up]) {
		transform->SetVelocityY(0);
		hitboxTransform->SetVelocityY(0);
	}

	//LEFT
	SDL_Scancode left{ kbd->GetLeftKey() };
	if (keys[left]) {
		if (CollisionUtils::WillBeOutsideGame(*transform, glm::vec2(-velocity * dt, 0))) {
			transform->SetVelocityX(0);
			hitboxTransform->SetVelocityX(0);
			transform->SetPositionX(GAME_POSITION.x);
			hitboxTransform->SetPositionX(GAME_POSITION.x + PLAYER_SIZE.x / 2.0f - HITBOX_SIZE.x / 2.0f);
		}
		else {
			transform->SetVelocityX(-velocity);
			hitboxTransform->SetVelocityX(-velocity);
		}
	}

	else {
		transform->SetVelocityX(0);
		hitboxTransform->SetVelocityX(0);
	}

	//RIGHT
	SDL_Scancode right{ kbd->GetRightKey() };
	if (keys[right]) {
		if (CollisionUtils::WillBeOutsideGame(*transform, glm::vec2(velocity * dt, 0))) {
			transform->SetVelocityX(0);
			hitboxTransform->SetVelocityX(0);
			transform->SetPositionX(GAME_POSITION.x + GAME_SIZE.x - PLAYER_SIZE.x);
			hitboxTransform->SetPositionX(GAME_POSITION.x + GAME_SIZE.x - PLAYER_SIZE.x + PLAYER_SIZE.x / 2.0f - HITBOX_SIZE.x / 2.0f);
		}
		else {
			transform->SetVelocityX(velocity);
			hitboxTransform->SetVelocityX(velocity);
		}
	}
	else if (!keys[left]) {
		transform->SetVelocityX(0);
		hitboxTransform->SetVelocityX(0);
	}

	SDL_Scancode shoot{ kbd->GetShootKey() };
	if (keys[shoot]) {
		if (emitTimer <= 0.0f) {
			EmitProjectiles();
			emitTimer = PROJECTILE_EMIT_SPEED;
		}
		else {
			emitTimer -= dt;
		}
	}
}

GLuint projectileCount{ 0 };
void Player::EmitProjectiles() {
	GLfloat x{ transform->GetPosition().x };
	GLfloat y{ transform->GetPosition().y };
	GLfloat w{ transform->GetWidth() };

	EntityManager::AddEntity(new Projectile(
		glm::vec2(x + w / 4, y - 20.0f),
		glm::vec2(0.0f, -PROJECTILE_SPEED),
		PROJECTILE_SIZE,
		0.0f,
		"playerProjectile",
		glm::vec3(1.0f),
		1.0f,
		"Projectile"));

	EntityManager::AddEntity(new Projectile(
		glm::vec2(x + 3 * w / 4, y - 20.0f),
		glm::vec2(0.0f, -PROJECTILE_SPEED),
		PROJECTILE_SIZE,
		0.0f,
		"playerProjectile",
		glm::vec3(1.0f),
		1.0f,
		"Projectile"));
}