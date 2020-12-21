#pragma once
#include "ColliderComponent.h"
#include "CollisionTypeEnum.h"
#include "Constants.h"
#include "Entity.h"

class CollisionUtils {
public:
	static bool CheckRectangleCollision(ColliderComponent& thisCollider, ColliderComponent& otherCollider);
	static bool WillBeOutsideGame(TransformComponent& transform, glm::vec2 futureVelocity);
};