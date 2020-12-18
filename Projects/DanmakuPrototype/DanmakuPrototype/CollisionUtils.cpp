#include "CollisionUtils.h"

bool CollisionUtils::CheckRectangleCollision(Entity& thisEntity, Entity& otherEntity) {
	if (!thisEntity.HasComponent<ColliderComponent>() || !otherEntity.HasComponent<ColliderComponent>())
		return false;
	ColliderComponent& thisCollider{ *thisEntity.GetComponent<ColliderComponent>() };
	ColliderComponent& otherCollider{ *otherEntity.GetComponent<ColliderComponent>() };

	return thisCollider.GetX() < otherCollider.GetX() + otherCollider.GetWidth() &&
		thisCollider.GetX() + thisCollider.GetWidth() > otherCollider.GetX() &&
		thisCollider.GetY() < otherCollider.GetY() + otherCollider.GetHeight() &&
		thisCollider.GetHeight() + thisCollider.GetY() > otherCollider.GetY();
}

bool CollisionUtils::IsOutsideGame(Entity& entity) {
	if (!entity.HasComponent<TransformComponent>())
		return false;
	TransformComponent& transform{ *entity.GetComponent<TransformComponent>() };

	GLfloat x{ transform.GetPosition().x };
	GLfloat y{ transform.GetPosition().y };
	return x < GAME_POSITION.x || x + PLAYER_SIZE.x > GAME_POSITION.x + GAME_SIZE.x
		|| y < GAME_POSITION.y || y + PLAYER_SIZE.y > GAME_POSITION.y + GAME_SIZE.y;
}
