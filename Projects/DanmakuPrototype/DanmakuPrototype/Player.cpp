#include "Player.h"

Player::Player() : Entity() {
	SetEntityType(EntityTypeEnum::PLAYER);
}

Player::Player(std::string name, LayerEnum layer) : Entity(name, layer) {
	//Player init
	SetEntityType(EntityTypeEnum::PLAYER);
	transform = AddComponent<TransformComponent>(PLAYER_INIT_POSITION, glm::vec2(0.0f), PLAYER_SIZE);
	sprite = AddComponent<SpriteComponent>(ResourceManager::GetShader("SpriteRendering"), ResourceManager::GetTexture("player"), true);
	kbd = AddComponent<KeyboardControlComponent>();
	collider = AddComponent<ColliderComponent>(HITBOX_POSITION.x, HITBOX_POSITION.y, HITBOX_SIZE.x, HITBOX_SIZE.y);

	//Hitbox init
	hitbox = EntityManager::AddEntity(new Entity("Hitbox", LayerEnum::PROJECTILE_LAYER));
	hitbox->SetEntityType(EntityTypeEnum::PLAYER);
	hitboxTransform = hitbox->AddComponent<TransformComponent>(HITBOX_POSITION, glm::vec2(), HITBOX_SIZE);
	hitbox->AddComponent<SpriteComponent>(ResourceManager::GetShader("SpriteRendering"), ResourceManager::GetTexture("hitbox"), false);
}

GLfloat emitTimer{ 0.0f };
void Player::ProcessInput(SDL_Event& e, GLfloat dt) {
	//Super
	Entity::ProcessInput(e, dt);


	const Uint8* keys{ EventManager::keys };


	//UP
	SDL_Scancode up{ kbd->GetUpKey() };
	if (keys[up]) {
		if (CollisionUtils::WillBeOutsideGame(*transform, glm::vec2(0, -PLAYER_VELOCITY * dt))) {
			transform->SetVelocityY(0);
			hitboxTransform->SetVelocityY(0);
			transform->SetPositionY(GAME_POSITION.y);
			hitboxTransform->SetPositionY(GAME_POSITION.y + PLAYER_SIZE.y / 2.0f - HITBOX_SIZE.y / 2.0f);
		}
		else {
			transform->SetVelocityY(-PLAYER_VELOCITY);
			hitboxTransform->SetVelocityY(-PLAYER_VELOCITY);
		}

	}
	else {
		transform->SetVelocityY(0);
		hitboxTransform->SetVelocityY(0);
	}


	//DOWN
	SDL_Scancode down{ kbd->GetDownKey() };
	if (keys[down]) {
		if (CollisionUtils::WillBeOutsideGame(*transform, glm::vec2(0, PLAYER_VELOCITY * dt))) {
			transform->SetVelocityY(0);
			hitboxTransform->SetVelocityY(0);
			transform->SetPositionY(GAME_POSITION.y + GAME_SIZE.y - PLAYER_SIZE.y);
			hitboxTransform->SetPositionY(GAME_POSITION.y + GAME_SIZE.y - PLAYER_SIZE.y + PLAYER_SIZE.y / 2.0f - HITBOX_SIZE.y / 2.0f);
		}
		else {
			transform->SetVelocityY(PLAYER_VELOCITY);
			hitboxTransform->SetVelocityY(PLAYER_VELOCITY);
		}
	}
	else if (!keys[up]) {
		transform->SetVelocityY(0);
		hitboxTransform->SetVelocityY(0);
	}

	//LEFT
	SDL_Scancode left{ kbd->GetLeftKey() };
	if (keys[left]) {
		if (CollisionUtils::WillBeOutsideGame(*transform, glm::vec2(-PLAYER_VELOCITY * dt, 0))) {
			transform->SetVelocityX(0);
			hitboxTransform->SetVelocityX(0);
			transform->SetPositionX(GAME_POSITION.x);
			hitboxTransform->SetPositionX(GAME_POSITION.x + PLAYER_SIZE.x / 2.0f - HITBOX_SIZE.x / 2.0f);
		}
		else {
			transform->SetVelocityX(-PLAYER_VELOCITY);
			hitboxTransform->SetVelocityX(-PLAYER_VELOCITY);
		}
	}

	else {
		transform->SetVelocityX(0);
		hitboxTransform->SetVelocityX(0);
	}

	//RIGHT
	SDL_Scancode right{ kbd->GetRightKey() };
	if (keys[right]) {
		if (CollisionUtils::WillBeOutsideGame(*transform, glm::vec2(PLAYER_VELOCITY * dt, 0))) {
			transform->SetVelocityX(0);
			hitboxTransform->SetVelocityX(0);
			transform->SetPositionX(GAME_POSITION.x + GAME_SIZE.x - PLAYER_SIZE.x);
			hitboxTransform->SetPositionX(GAME_POSITION.x + GAME_SIZE.x - PLAYER_SIZE.x + PLAYER_SIZE.x / 2.0f - HITBOX_SIZE.x / 2.0f);
		}
		else {
			transform->SetVelocityX(PLAYER_VELOCITY);
			hitboxTransform->SetVelocityX(PLAYER_VELOCITY);
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
		glm::vec2(x + w / 2, y - 20.0f),
		glm::vec2(0.0f, -PROJECTILE_SPEED),
		PROJECTILE_SIZE,
		0.0f,
		ResourceManager::GetTexture("playerProjectile"),
		glm::vec3(1.0f),
		1.0f,
		"Projectile"));
}