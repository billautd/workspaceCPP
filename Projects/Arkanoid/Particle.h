#pragma once
#include "glm.hpp"
#include "glad/glad.h"

class Particle {
public:
	glm::vec2 position{};
	glm::vec2 velocity{};
	glm::vec4 color{ glm::vec4(1.0f) };
	GLfloat life{};

	Particle() {}
	~Particle() {}
};