#include "UtilsPiece.h"
#include "UtilsGeneral.h"

GLshort UtilsPiece::PieceBottom(Piece& piece) {
	GLshort bottom{ piece[0].GetY() };
	for (size_t i = 1; i < piece.size(); i++) {
		if (piece[i].GetY() < bottom)
			bottom = piece[i].GetY();
	}
	return bottom;
}

GLshort UtilsPiece::PieceLeft(Piece& piece) {
	GLshort left{ piece[0].GetX() };
	for (size_t i = 1; i < piece.size(); i++) {
		if (piece[i].GetX() < left)
			left = piece[i].GetX();
	}
	return left;
}

GLshort UtilsPiece::PieceRight(Piece& piece) {
	GLshort right{ piece[0].GetX() };
	for (size_t i = 1; i < piece.size(); i++) {
		if (piece[i].GetX() > right)
			right = piece[i].GetX();
	}
	return right;
}

Piece* UtilsPiece::SpawnOPiece() {
	//Red
	glm::vec3 color = glm::vec3(0.8f, 0.0f, 0.0f);
	Piece* piece = new Piece({
		Block(4, 19, color),
		Block(5, 19, color),
		Block(4, 18, color),
		Block(5, 18, color)
		});

	return piece;
}

Piece* UtilsPiece::SpawnTPiece() {
	//Yellow
	glm::vec3 color = glm::vec3(0.9f, 0.9f, 0.0f);
	Piece* piece = new Piece({
	Block(4, 19, color),
		Block(5, 19, color),
		Block(6, 19, color),
		Block(5, 18, color)
		});

	return piece;
}


Piece* UtilsPiece::SpawnLPiece() {
	//Green
	glm::vec3 color = glm::vec3(0.8f, 0.8f, 0.0f);
	Piece* piece = new Piece({
	Block(6, 19, color),
		Block(4, 18, color),
		Block(5, 18, color),
		Block(6, 18, color)
		});

	return piece;
}

Piece* UtilsPiece::SpawnZPiece() {
	//Orange
	glm::vec3 color = glm::vec3(0.9f, 0.5f, 0.0f);
	Piece* piece = new Piece({
	Block(4, 19, color),
		Block(5, 19, color),
		Block(5, 18, color),
		Block(6, 18, color)
		});
	return piece;
}

Piece* UtilsPiece::SpawnSPiece() {
	//Purple
	glm::vec3 color = glm::vec3(0.5f, 0.8f, 0.5f);
	Piece* piece = new Piece({
	Block(5, 19, color),
		Block(6, 18, color),
		Block(4, 18, color),
		Block(5, 18, color)
		});
	return piece;
}

Piece* UtilsPiece::SpawnJPiece() {
	// Blue
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.9f);
	Piece* piece = new Piece({
		Block(4, 19, color),
			Block(4, 18, color),
			Block(5, 18, color),
			Block(6, 18, color)
		});

	return piece;
}

Piece* UtilsPiece::SpawnIPiece() {
	//Clear blue
	glm::vec3 color = glm::vec3(0.5f, 0.7f, 0.1f);
	Piece* piece = new Piece({
	Block(3, 19, color),
		Block(4, 19, color),
		Block(5, 19, color),
		Block(6, 19, color)
		});

	return piece;
}

Piece* UtilsPiece::SpawnRandomPiece() {
	GLshort id{ UtilsGeneral::RandomInt() % 7 };
	switch (id) {
		case 0:
			return SpawnIPiece();
		case 1:
			return SpawnJPiece();
		case 2:
			return SpawnLPiece();
		case 3:
			return SpawnOPiece();
		case 4:
			return SpawnSPiece();
		case 5:
			return SpawnTPiece();
		case 6:
			return SpawnZPiece();
	}
	return nullptr;
}

void UtilsPiece::FreePiece(Piece& piece) {
	for (size_t i = 0; i < piece.size(); i++)
		free(&piece[i]);
}

bool UtilsPiece::HasBlockAtPos(Piece& piece, GLshort x, GLshort y) {
	for (size_t i = 0; i < piece.size(); i++) {
		if (piece[i].GetX() == x && piece[i].GetY() == y)
			return true;
	}
	return false;
}
