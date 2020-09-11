#include "GameObject.h"

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D& sprite, glm::vec3 color, glm::vec2 velocity) :
	position(position), size(size), sprite(sprite), color(color), velocity(velocity) {}

void GameObject::Draw(SpriteRenderer& renderer) {
	//if (!this->isDestroyed)
	renderer.DrawSprite(sprite, position, size, rotation, color);
}

Collision GameObject::CheckCollision(GameObject& obj) {
	// collision x-axis?
	bool collisionX{ this->position.x + this->size.x >= obj.position.x &&
		obj.position.x + obj.size.x >= this->position.x };
	// collision y-axis?
	bool collisionY{ this->position.y + this->size.y >= obj.position.y &&
		obj.position.y + obj.size.y >= this->position.y };
	// collision only if on both axes

	return std::make_tuple(collisionX && collisionY, DirectionEnum::UP, glm::vec2(0.0f));
}


