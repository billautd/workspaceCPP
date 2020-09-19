#pragma once
#include "Block.h"
#include <vector>
#include "PieceTypeEnum.h"

struct Piece {
	std::vector<Block> blocks{};
	PieceTypeEnum type;
	glm::vec2 rotationCenter{ 0.0f };

	Piece(std::vector<Block> blocks, PieceTypeEnum type, glm::vec2 rotationCenter) :
		blocks(blocks), type(type), rotationCenter(rotationCenter) {}

	bool operator==(const Piece& piece) const {
		return type == piece.type && rotationCenter == piece.rotationCenter;
	}
};

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

	static bool HasBlockAtPos(Piece& piece, GLshort x, GLshort y);
};

