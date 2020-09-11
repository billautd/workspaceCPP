#include "PowerUp.h"
#include "Constants.h"

PowerUp::PowerUp(std::string type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
	: GameObject(position, POWERUP_SIZE, texture, color, POWERUP_VELOCITY), type(type), duration(duration) {}
