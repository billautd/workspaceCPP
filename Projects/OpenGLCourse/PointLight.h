#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	glm::vec3 position;
	const GLfloat constant{ 1.0f };
	const GLfloat linear;
	const GLfloat quadratic;

	PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, const GLfloat constant, const GLfloat linear, const GLfloat quadratic, glm::vec3 color = glm::vec3(1.0f)) :
		Light(ambient, diffuse, specular, color), position(position), constant(constant), linear(linear), quadratic(quadratic) {};
};