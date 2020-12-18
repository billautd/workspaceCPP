#pragma once
#include "CollisionTypeEnum.h"
#include "Constants.h"
#include "Entity.h"

class CollisionUtils {
public:
	static bool CheckRectangleCollision(Entity& thisEntity, Entity& otherEntity);
	static bool IsOutsideGame(Entity& entity);
};