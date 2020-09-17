#include "UtilsPiece.h"

GLshort UtilsPiece::PieceBottomY(Piece& piece) {
	GLshort bottomY{ piece[0].GetY() };
	for (size_t i = 1; i < piece.size(); i++) {
		if (piece[i].GetY() < bottomY)
			bottomY = piece[i].GetY();
	}
	return bottomY;
}

void UtilsPiece::MovePieceDown(Piece* piece) {
	for (size_t i = 0; i < piece->size(); i++) {
		GLshort y{ (*piece)[i].GetY() };
		(*piece)[i].SetY(y - 1);
	}
}

Piece UtilsPiece::SpawnOPiece() {
	//Red
	glm::vec3 color = glm::vec3(0.8f, 0.0f, 0.0f);
	Piece piece{
		Block(4, 19, color),
		Block(5, 19, color),
		Block(4, 18, color),
		Block(5, 18, color)
	};

	return piece;
}

Piece UtilsPiece::SpawnTPiece() {
	//Yellow
	glm::vec3 color = glm::vec3(0.9f, 0.9f, 0.0f);
	Piece piece{
	Block(4, 19, color),
		Block(5, 19, color),
		Block(6, 19, color),
		Block(5, 18, color)
	};

	return piece;
}


Piece UtilsPiece::SpawnLPiece() {
	//Green
	glm::vec3 color = glm::vec3(0.8f, 0.8f, 0.0f);
	Piece piece{
	Block(6, 19, color),
		Block(4, 18, color),
		Block(5, 18, color),
		Block(6, 18, color)
	};

	return piece;
}

Piece UtilsPiece::SpawnZPiece() {
	//Orange
	glm::vec3 color = glm::vec3(0.9f, 0.5f, 0.0f);
	Piece piece{
	Block(4, 19, color),
		Block(5, 19, color),
		Block(5, 18, color),
		Block(6, 18, color)
	};
	return piece;
}

Piece UtilsPiece::SpawnSPiece() {
	//Purple
	glm::vec3 color = glm::vec3(0.5f, 0.8f, 0.5f);
	Piece piece{
	Block(5, 19, color),
		Block(6, 18, color),
		Block(4, 18, color),
		Block(5, 18, color)
	};
	return piece;
}

Piece UtilsPiece::SpawnJPiece() {
	// Blue
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.9f);
	Piece piece{
		Block(4, 19, color),
			Block(4, 18, color),
			Block(5, 18, color),
			Block(6, 18, color)
	};

	return piece;
}

Piece UtilsPiece::SpawnIPiece() {
	//Clear blue
	glm::vec3 color = glm::vec3(0.5f, 0.7f, 0.1f);
	Piece piece{
	Block(3, 19, color),
		Block(4, 19, color),
		Block(5, 19, color),
		Block(6, 19, color)
	};

	return piece;
}
