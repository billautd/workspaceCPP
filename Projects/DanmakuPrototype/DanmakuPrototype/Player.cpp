#include "Player.h"
#include "Constants.h"
#include "Game.h"

void Player::ProcessInput(SDL_Event& e, GLfloat dt) {
	//Super
	Entity::ProcessInput(e, dt);

	KeyboardControlComponent* kbd{ GetComponent<KeyboardControlComponent>() };
	TransformComponent* transform{ GetComponent<TransformComponent>() };

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
}

bool Player::IsOutsideGame() {
	TransformComponent* transform{ GetComponent<TransformComponent>() };
	GLfloat x{ transform->GetPosition().x };
	GLfloat y{ transform->GetPosition().y };

	return x < GAME_POSITION.x || x + PLAYER_SIZE.x > GAME_POSITION.x + GAME_SIZE.x
		|| y < GAME_POSITION.y || y + PLAYER_SIZE.y > GAME_POSITION.y + GAME_SIZE.y;
}