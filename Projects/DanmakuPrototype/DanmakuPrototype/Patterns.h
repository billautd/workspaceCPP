#pragma once
#include <glad/glad.h>
#include <math.h>
#include "EntityManager.h"
#include "Projectile.h"
#include "FirePatternComponent.h"

class Patterns {
public:
	static void MoveToCenterThenShootDown(FirePatternComponent* comp, GLfloat dt);
};