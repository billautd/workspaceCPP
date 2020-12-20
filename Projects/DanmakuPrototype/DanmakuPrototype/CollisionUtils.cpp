#include "CollisionUtils.h"

bool CollisionUtils::CheckRectangleCollision(ColliderComponent& thisCollider, ColliderComponent& otherCollider) {
	return thisCollider.GetX() < otherCollider.GetX() + otherCollider.GetWidth() &&
		thisCollider.GetX() + thisCollider.GetWidth() > otherCollider.GetX() &&
		thisCollider.GetY() < otherCollider.GetY() + otherCollider.GetHeight() &&
		thisCollider.GetHeight() + thisCollider.GetY() > otherCollider.GetY();
}

bool CollisionUtils::IsOutsideGame(Entity& entity) {

	TransformComponent& transform{ *entity.GetComponent<TransformComponent>() };

	GLfloat x{ transform.GetPosition().x };
	GLfloat y{ transform.GetPosition().y };
	return x < GAME_POSITION.x || x + PLAYER_SIZE.x > GAME_POSITION.x + GAME_SIZE.x
		|| y < GAME_POSITION.y || y + PLAYER_SIZE.y > GAME_POSITION.y + GAME_SIZE.y;
}
