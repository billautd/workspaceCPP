#include "Player.h"

Player::Player(std::string name, LayerEnum layer) : Entity(name, layer) {
	//Player init
	SetEntityType(EntityTypeEnum::PLAYER);
	transform = AddComponent<TransformComponent>(PLAYER_INIT_POSITION, glm::vec2(0.0f), PLAYER_SIZE);
	sprite = AddComponent<SpriteComponent>("SpriteRendering", "playerCenter");
	kbd = AddComponent<KeyboardControlComponent>();
	collider = AddComponent<ColliderComponent>(HITBOX_POSITION.x, HITBOX_POSITION.y, HITBOX_SIZE.x, HITBOX_SIZE.y);

	//Hitbox init
	hitbox = EntityManager::AddEntity(new Entity("Hitbox", LayerEnum::PROJECTILE_LAYER));
	hitbox->SetEntityType(EntityTypeEnum::PLAYER);
	hitboxTransform = hitbox->AddComponent<TransformComponent>(HITBOX_POSITION, glm::vec2(), HITBOX_SIZE);
	hitboxSprite = hitbox->AddComponent<SpriteComponent>("SpriteRendering", "hitbox", false);

	//Init textures
	for (GLuint i = 1; i <= PLAYER_SPRITE_NUMBER; i++) {
		playerLeftTextures.push_back(ResourceManager::GetTexture("playerLeft" + std::to_string(i)));
		playerRightTextures.push_back(ResourceManager::GetTexture("playerRight" + std::to_string(i)));
	}
}

GLfloat emitTimer{ 0.0f };
GLfloat spriteSwitchTimer{ 0.0f };
GLuint animationLeftCount{ 0 };
GLuint animationRightCount{ 0 };
void Player::ProcessInput(SDL_Event& e, GLfloat dt) {
	Entity::ProcessInput(e, dt);

	const Uint8* keys{ EventManager::keys };

	SDL_Scancode focus{ kbd->GetFocusKey() };
	GLfloat velocity{ keys[focus] ? PLAYER_VELOCITY / 3.0f : PLAYER_VELOCITY };
	hitboxSprite->SetIsVisible(keys[focus]);

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

		//Change player sprite
		spriteSwitchTimer += dt;
		if (spriteSwitchTimer >= PLAYER_SPRITE_SWITCH_TIME && animationLeftCount < PLAYER_SPRITE_NUMBER) {
			animationRightCount = 0;
			spriteSwitchTimer = 0;
			sprite->SetTexture(playerLeftTextures.at(animationLeftCount));
			animationLeftCount++;
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

		//Change player sprite
		spriteSwitchTimer += dt;
		if (spriteSwitchTimer >= PLAYER_SPRITE_SWITCH_TIME && animationRightCount < PLAYER_SPRITE_NUMBER) {
			animationLeftCount = 0;
			spriteSwitchTimer = 0;
			sprite->SetTexture(playerRightTextures.at(animationRightCount));
			animationRightCount++;
		}
	}
	else if (!keys[left]) {
		transform->SetVelocityX(0);
		hitboxTransform->SetVelocityX(0);
		spriteSwitchTimer = 0;
		animationLeftCount = 0;
		animationRightCount = 0;
		sprite->SetTexture(playerCenterTexture);
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
	for (GLuint i = 0; i < 4; i++) {
		EntityManager::AddEntity(new Projectile(
			glm::vec2(x + i * w / 4, y),
			glm::vec2(0.0f, -PROJECTILE_SPEED),
			PROJECTILE_SIZE,
			0.0f,
			"playerProjectile"));
	}
}