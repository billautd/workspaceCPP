#include "Player.h"

void Player::Reset() {
	position = INITIAL_PLAYER_POSITION;
	size = INITIAL_PLAYER_SIZE;
	color = glm::vec3(1.0f);
}