#pragma once
#include "glad/glad.h"
#include "glm.hpp"

class Character {
public:
	GLuint textureId{};
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint advance;
};
