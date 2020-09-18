#pragma once
#include "Block.h"
#include <vector>

typedef std::vector<Block> Piece;

class UtilsPiece {
public:
	static GLshort PieceBottom(Piece& piece);
	static GLshort PieceLeft(Piece& piece);
	static GLshort PieceRight(Piece& piece);

	static Piece* SpawnOPiece();
	static Piece* SpawnTPiece();
	static Piece* SpawnLPiece();
	static Piece* SpawnZPiece();
	static Piece* SpawnSPiece();
	static Piece* SpawnJPiece();
	static Piece* SpawnIPiece();
	static Piece* SpawnRandomPiece();

	static void FreePiece(Piece& piece);

	static bool HasBlockAtPos(Piece& piece, GLshort x, GLshort y);
};

