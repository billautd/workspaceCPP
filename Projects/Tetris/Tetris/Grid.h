#pragma once
#include <map>
#include "glad/glad.h"
#include "SpriteRenderer.h"
#include "UtilsPiece.h"
#include "Block.h"
#include <vector>



class Grid
{
public:
	Grid();

	bool HasTile(GLshort x, GLshort y);
	Block* GetTile(GLshort x, GLshort y);
	void SetTile(Block* block);
	void SetPiece(Piece& piece);
	void ClearLine(GLshort x);
	bool IsLineEmpty(GLshort x);

	void Render(SpriteRenderer* renderer);
private:
	std::map<Position, Block*> tiles{};
};

