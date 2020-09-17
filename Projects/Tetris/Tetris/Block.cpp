#include "Block.h"
#include "Constants.h"

void Block::Render(SpriteRenderer* renderer) {
	renderer->DrawSprite(texture,
		glm::vec2(
			GRID_X + pos.x * TILE_SIZE,
			GRID_Y + (Y_TILES - pos.y - 1) * TILE_SIZE),
		glm::vec2(TILE_SIZE),
		0.0f,
		color);
}