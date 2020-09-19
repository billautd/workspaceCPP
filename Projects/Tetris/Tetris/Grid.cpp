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
	for (size_t i = 0; i < piece.blocks.size(); i++)
		SetTile(&piece.blocks.at(i));
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
		for (size_t i = 0; i < piece.blocks.size(); i++) {
			//If there is a tile below but it's a piece block, then continue
			if (UtilsPiece::HasBlockAtPos(piece, piece.blocks[i].GetX(), piece.blocks[i].GetY() - 1))
				continue;
			//If bottom or has a tile below
			if (piece.blocks[i].GetY() == 0 || HasTile(piece.blocks[i].GetX(), piece.blocks[i].GetY() - 1))
				return false;
		}
		return true;
	}
	else if (dir == DirectionEnum::LEFT) {
		for (size_t i = 0; i < piece.blocks.size(); i++) {
			//If there is a tile to the left but it's a piece block, then continue
			if (UtilsPiece::HasBlockAtPos(piece, piece.blocks[i].GetX() - 1, piece.blocks[i].GetY()))
				continue;
			//If left or has tile
			if (piece.blocks[i].GetX() == 0 || HasTile(piece.blocks[i].GetX() - 1, piece.blocks[i].GetY()))
				return false;
		}
		return true;
	}
	else if (dir == DirectionEnum::RIGHT) {
		for (size_t i = 0; i < piece.blocks.size(); i++) {
			//If there is a tile to the right but it's a piece block, then continue
			if (UtilsPiece::HasBlockAtPos(piece, piece.blocks[i].GetX() + 1, piece.blocks[i].GetY()))
				continue;
			//If left or has tile
			if (piece.blocks[i].GetX() == X_TILES - 1 || HasTile(piece.blocks[i].GetX() + 1, piece.blocks[i].GetY()))
				return false;
		}
		return true;
	}
	return false;
}

void Grid::MovePiece(Piece* piece, DirectionEnum dir) {
	//Clear previous tiles
	for (size_t i = 0; i < piece->blocks.size(); i++)
		tiles[Position(piece->blocks[i].GetX(), piece->blocks[i].GetY())] = nullptr;
	switch (dir) {
		case DirectionEnum::LEFT: {

			//Set new tiles on grid and change piece
			for (size_t i = 0; i < piece->blocks.size(); i++) {
				GLshort x{ piece->blocks[i].GetX() };
				GLshort y{ piece->blocks[i].GetY() };

				piece->blocks[i].SetX(x - 1);
				SetTile(&piece->blocks[i]);
			}
			piece->rotationCenter.x--;
			break;
		}
		case DirectionEnum::RIGHT: {
			//Set new tiles on grid and change piece
			for (size_t i = 0; i < piece->blocks.size(); i++) {
				GLshort x{ piece->blocks[i].GetX() };
				GLshort y{ piece->blocks[i].GetY() };

				piece->blocks[i].SetX(x + 1);
				SetTile(&piece->blocks[i]);
			}
			piece->rotationCenter.x++;
			break;
		}
		case DirectionEnum::DOWN: {
			//Set new tiles on grid and change piece
			for (size_t i = 0; i < piece->blocks.size(); i++) {
				GLshort x{ piece->blocks[i].GetX() };
				GLshort y{ piece->blocks[i].GetY() };

				piece->blocks[i].SetY(y - 1);
				SetTile(&piece->blocks[i]);
			}
			piece->rotationCenter.y--;
			break;
		}
	}
}

bool Grid::CanPieceRotate(Piece& piece, DirectionEnum dir) {
	return true;
}

void Grid::RotatePiece(Piece* piece, DirectionEnum dir) {
	if (piece->type == PieceTypeEnum::O)
		return;

	//Clear previous tiles
	for (size_t i = 0; i < piece->blocks.size(); i++)
		tiles[Position(piece->blocks[i].GetX(), piece->blocks[i].GetY())] = nullptr;
	if (dir == DirectionEnum::LEFT) {
		for (size_t i = 0; i < piece->blocks.size(); i++) {
			GLfloat directionVecX{ piece->blocks[i].GetX() - piece->rotationCenter.x + 1 };
			GLfloat directionVecY{ piece->blocks[i].GetY() - piece->rotationCenter.y };

			piece->blocks[i].SetX(static_cast<GLshort>(piece->rotationCenter.x - directionVecY));
			piece->blocks[i].SetY(static_cast<GLshort>(piece->rotationCenter.y + directionVecX));
			SetTile(&piece->blocks[i]);
		}
	}
	if (dir == DirectionEnum::RIGHT) {
		for (size_t i = 0; i < piece->blocks.size(); i++) {
			GLfloat directionVecX{ piece->blocks[i].GetX() - piece->rotationCenter.x };
			GLfloat directionVecY{ piece->blocks[i].GetY() - piece->rotationCenter.y };

			piece->blocks[i].SetX(static_cast<GLshort>(piece->rotationCenter.x + directionVecY - 1));
			piece->blocks[i].SetY(static_cast<GLshort>(piece->rotationCenter.y - directionVecX));
			SetTile(&piece->blocks[i]);
		}
	}
	return;
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