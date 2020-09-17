#include "Grid.h"
#include "Constants.h"


Grid::Grid() {
	//Init grid
	for (GLshort y = 0; y < Y_TILES; y++) {
		for (GLshort x = 0; x < X_TILES; x++) {
			tiles[Position(x, y)] = nullptr;
		}
	}
}

bool Grid::HasTile(GLshort x, GLshort y) {
	return tiles[Position(x, y)] != nullptr;
}

Block* Grid::GetTile(GLshort x, GLshort y) {
	return tiles[Position(x, y)];
}

void Grid::SetTile(Block* block) {
	tiles[Position(block->GetX(), block->GetY())] = block;
}

void Grid::SetPiece(Piece& piece) {
	for (size_t i = 0; i < piece.size(); i++)
		SetTile(&piece.at(i));
}

void Grid::ClearLine(GLshort y) {
	for (GLshort x = 0; x < X_TILES; x++)
		tiles[Position(x, y)] = nullptr;
}

bool Grid::IsLineEmpty(GLshort y) {
	for (GLshort x = 0; x < X_TILES; x++) {
		if (HasTile(x, y))
			return false;
	}
	return true;
}

void Grid::Render(SpriteRenderer* renderer) {
	for (GLshort y = 0; y < Y_TILES; y++) {
		if (IsLineEmpty(y))
			continue;
		for (GLshort x = 0; x < X_TILES; x++) {
			Block* block{ tiles[Position(x, y)] };
			if (block)
				block->Render(renderer);
		}
	}
}