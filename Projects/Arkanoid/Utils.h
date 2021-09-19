#pragma once
#include "Direction.h"
#include "glm.hpp"

class Utils {
public:
	static Direction VectorDirection(const glm::vec2& target);
};