#pragma once
#include "Block.h"
#include <vector>

typedef std::vector<Block> Piece;

class UtilsPiece {
public:
	static GLshort PieceBottomY(Piece& piece);
	static void MovePieceDown(Piece* piece);
	static Piece SpawnOPiece();
	static Piece SpawnTPiece();
	static Piece SpawnLPiece();
	static Piece SpawnZPiece();
	static Piece SpawnSPiece();
	static Piece SpawnJPiece();
	static Piece SpawnIPiece();
};

