#pragma once
#include "glm.hpp"
#include "glad/glad.h"

class Material {
public:
	const glm::vec3 diffuse;
	const glm::vec3 specular;
	const GLfloat shininess;

	Material(const glm::vec3 diffuse, const glm::vec3 specular, const GLfloat shininess) :
		diffuse(diffuse), specular(specular), shininess(shininess) {};
};
