#include "Utils.h"
#include "Constants.h"

Direction Utils::VectorDirection(const glm::vec2& target) {
	GLfloat max{ 0.0f };
	GLint bestMatch{ -1 };
	for (GLuint i{ 0 }; i < 4; i++) {
		GLfloat dotProduct{ glm::dot(glm::normalize(target), compass[i]) };
		if (dotProduct > max) {
			max = dotProduct;
			bestMatch = i;
		}
	}
	return static_cast<Direction>(bestMatch);
}