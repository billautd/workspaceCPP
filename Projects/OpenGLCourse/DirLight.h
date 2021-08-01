#pragma once
#include "Light.h"

class DirLight : public Light {
public:
	const glm::vec3 direction;

	DirLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 color = glm::vec3(1.0f)) :
		Light(ambient, diffuse, specular, color), direction(direction) {};
};