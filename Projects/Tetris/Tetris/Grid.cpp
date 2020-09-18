#include "Grid.h"
#include "Constants.h"
#include <iostream>


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

void Grid::DestroyTile(GLshort x, GLshort y) {
	free(tiles[Position(x, y)]);
}

void Grid::DestroyLine(GLshort y) {
	for (GLshort x = 0; x < X_TILES; x++)
		DestroyTile(x, y);
}

bool Grid::IsLineEmpty(GLshort y) {
	if (y < 0)
		return false;
	for (GLshort x = 0; x < X_TILES; x++) {
		if (HasTile(x, y))
			return false;
	}
	return true;
}

bool Grid::CanPieceMove(Piece& piece, DirectionEnum dir) {
	if (dir == DirectionEnum::DOWN) {
		for (size_t i = 0; i < piece.size(); i++) {
			//If there is a tile below but it's a piece block, then continue
			if (UtilsPiece::HasBlockAtPos(piece, piece[i].GetX(), piece[i].GetY() - 1))
				continue;
			//If bottom or has a tile below
			if (piece[i].GetY() == 0 || HasTile(piece[i].GetX(), piece[i].GetY() - 1))
				return false;
		}
		return true;
	}
	else if (dir == DirectionEnum::LEFT) {
		for (size_t i = 0; i < piece.size(); i++) {
			//If there is a tile to the left but it's a piece block, then continue
			if (UtilsPiece::HasBlockAtPos(piece, piece[i].GetX() - 1, piece[i].GetY()))
				continue;
			//If left or has tile
			if (piece[i].GetX() == 0 || HasTile(piece[i].GetX() - 1, piece[i].GetY()))
				return false;
		}
		return true;
	}
	else if (dir == DirectionEnum::RIGHT) {
		for (size_t i = 0; i < piece.size(); i++) {
			//If there is a tile to the right but it's a piece block, then continue
			if (UtilsPiece::HasBlockAtPos(piece, piece[i].GetX() + 1, piece[i].GetY()))
				continue;
			//If left or has tile
			if (piece[i].GetX() == X_TILES - 1 || HasTile(piece[i].GetX() + 1, piece[i].GetY()))
				return false;
		}
		return true;
	}
	return false;
}

void Grid::MovePiece(Piece* piece, DirectionEnum dir) {
	//Clear previous tiles
	for (size_t i = 0; i < piece->size(); i++)
		tiles[Position((*piece)[i].GetX(), (*piece)[i].GetY())] = nullptr;
	switch (dir) {
		case DirectionEnum::LEFT: {

			//Set new tiles on grid and change piece
			for (size_t i = 0; i < piece->size(); i++) {
				GLshort x{ (*piece)[i].GetX() };
				GLshort y{ (*piece)[i].GetY() };

				(*piece)[i].SetX(x - 1);
				SetTile(&(*piece)[i]);
			}
			break;
		}
		case DirectionEnum::RIGHT: {
			//Set new tiles on grid and change piece
			for (size_t i = 0; i < piece->size(); i++) {
				GLshort x{ (*piece)[i].GetX() };
				GLshort y{ (*piece)[i].GetY() };

				(*piece)[i].SetX(x + 1);
				SetTile(&(*piece)[i]);
			}
			break;
		}
		case DirectionEnum::DOWN: {
			//Set new tiles on grid and change piece
			for (size_t i = 0; i < piece->size(); i++) {
				GLshort x{ (*piece)[i].GetX() };
				GLshort y{ (*piece)[i].GetY() };

				(*piece)[i].SetY(y - 1);
				SetTile(&(*piece)[i]);
			}
			break;
		}
	}
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