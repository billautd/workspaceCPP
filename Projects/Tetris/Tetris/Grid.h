#pragma once
#include <map>
#include "glad/glad.h"
#include "SpriteRenderer.h"
#include "UtilsPiece.h"
#include "Block.h"
#include "DirectionEnum.h"
#include <vector>



class Grid
{
public:
	Grid();

	bool HasTile(GLshort x, GLshort y);
	Block* GetTile(GLshort x, GLshort y);
	void SetTile(Block* block);
	void SetPiece(Piece& piece);
	void ClearTile(GLshort x, GLshort y);
	void ClearLine(GLshort y);
	bool IsLineEmpty(GLshort y);
	bool IsLineFull(GLshort y);

	bool CanPieceMove(Piece& piece, DirectionEnum dir);
	void MovePiece(Piece* piece, DirectionEnum dir);

	bool CanPieceRotate(Piece& piece, DirectionEnum dir);
	void RotatePiece(Piece* piece, DirectionEnum dir);

	void MovePiecesAboveDown(GLshort y);

	void Render(SpriteRenderer* renderer);
private:
	std::map<Position, Block*> tiles{};
};

