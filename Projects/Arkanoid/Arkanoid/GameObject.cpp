#include "GameObject.h"

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D& sprite, glm::vec3 color, glm::vec2 velocity) :
	position(position), size(size), sprite(sprite), color(color), velocity(velocity) {}

void GameObject::Draw(SpriteRenderer& renderer) {
	//if (!this->isDestroyed)
	renderer.DrawSprite(sprite, position, size, rotation, color);
}


