#include "GameObject.h"

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(sprite, position, size, rotation, color);
}
