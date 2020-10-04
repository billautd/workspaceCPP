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
	if (keys[up])
		transform->SetPositionY(transform->GetPosition().y - velocity);

	//DOWN
	SDL_Scancode down{ kbd->GetDownKey() };
	if (keys[down])
		transform->SetPositionY(transform->GetPosition().y + velocity);

	//LEFT
	SDL_Scancode left{ kbd->GetLeftKey() };
	if (keys[left])
		transform->SetPositionX(transform->GetPosition().x - velocity);


	//RIGHT
	SDL_Scancode right{ kbd->GetRightKey() };
	if (keys[right])
		transform->SetPositionX(transform->GetPosition().x + velocity);



}
