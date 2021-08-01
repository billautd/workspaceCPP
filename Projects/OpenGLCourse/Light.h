#pragma once
#include "glm.hpp"
#include "glad/glad.h"

class Light {
public:
	glm::vec3 color;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
protected:
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color = glm::vec3(1.0f)) :
		ambient(ambient), diffuse(diffuse), specular(specular), color(color) {};
};