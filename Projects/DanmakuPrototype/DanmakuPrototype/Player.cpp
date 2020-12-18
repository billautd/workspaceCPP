#include "Player.h"

Player::Player() : Entity() {
	SetEntityType(EntityTypeEnum::PLAYER);
}

Player::Player(std::string name, LayerEnum layer) : Entity(name, layer) {
	SetEntityType(EntityTypeEnum::PLAYER);
	transform = &AddComponent<TransformComponent>(glm::vec2(GAME_POSITION.x + GAME_SIZE.x / 2.0f - PLAYER_SIZE.x / 2, GAME_POSITION.y + GAME_SIZE.y - PLAYER_SIZE.y), glm::vec2(0.0f), PLAYER_SIZE);
	sprite = &AddComponent<SpriteComponent>(ResourceManager::GetShader("SpriteRendering"), ResourceManager::GetTexture("player"), true);
	kbd = &AddComponent<KeyboardControlComponent>();
	collider = &AddComponent<ColliderComponent>();
}

GLfloat emitTimer{ 0.0f };
void Player::ProcessInput(SDL_Event& e, GLfloat dt) {
	//Super
	Entity::ProcessInput(e, dt);


	const Uint8* keys{ EventManager::keys };

	GLfloat velocity{ PLAYER_VELOCITY * dt };

	//UP
	SDL_Scancode up{ kbd->GetUpKey() };
	if (keys[up]) {
		transform->SetPositionY(transform->GetPosition().y - velocity);
		if (IsOutsideGame())
			transform->SetPositionY(GAME_POSITION.y);
	}

	//DOWN
	SDL_Scancode down{ kbd->GetDownKey() };
	if (keys[down]) {
		transform->SetPositionY(transform->GetPosition().y + velocity);
		if (IsOutsideGame())
			transform->SetPositionY(GAME_POSITION.y + GAME_SIZE.y - PLAYER_SIZE.y);
	}

	//LEFT
	SDL_Scancode left{ kbd->GetLeftKey() };
	if (keys[left]) {
		transform->SetPositionX(transform->GetPosition().x - velocity);
		if (IsOutsideGame())
			transform->SetPositionX(GAME_POSITION.x);
	}


	//RIGHT
	SDL_Scancode right{ kbd->GetRightKey() };
	if (keys[right]) {
		transform->SetPositionX(transform->GetPosition().x + velocity);
		if (IsOutsideGame())
			transform->SetPositionX(GAME_POSITION.x + GAME_SIZE.x - PLAYER_SIZE.x);
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

bool Player::IsOutsideGame() {
	TransformComponent* transform{ GetComponent<TransformComponent>() };
	GLfloat x{ transform->GetPosition().x };
	GLfloat y{ transform->GetPosition().y };

	return x < GAME_POSITION.x || x + PLAYER_SIZE.x > GAME_POSITION.x + GAME_SIZE.x
		|| y < GAME_POSITION.y || y + PLAYER_SIZE.y > GAME_POSITION.y + GAME_SIZE.y;
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