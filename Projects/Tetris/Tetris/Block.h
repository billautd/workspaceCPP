#pragma once
#include "glad/glad.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <iostream>
#include "Texture2D.h"

struct Position {
	GLshort x;
	GLshort y;

	Position(GLshort x, GLshort y) : x(x), y(y) {};

	bool operator<(const Position& pos) const {
		if (x < pos.x) return true;
		if (x > pos.x) return false;
		if (y < pos.y) return true;
		if (y > pos.y) return false;

		return false;
	}

	bool operator==(const Position& pos) const {
		return x == pos.x && y == pos.y;
	}
};

class Block {
public:
	Block() = default;
	Block(GLshort x, GLshort y, glm::vec3 color) : color(color) { pos.x = x; pos.y = y; };
	~Block() = default;

	void Render(SpriteRenderer* renderer);

	GLshort GetX() { return pos.x; }
	void SetX(GLshort x) { pos.x = x; }
	GLshort GetY() { return pos.y; }
	void SetY(GLshort y) { pos.y = y; }
	glm::vec3 GetColor() { return color; }
	void SetColor(glm::vec3 color) { this->color = color; }

	friend std::ostream& operator<<(std::ostream& os, const Block& block) {
		os << block.pos.x << ", " << block.pos.y << ", (" << block.color.r << ", " << block.color.g << ", " << block.color.b << ")";
		return os;
	}
	bool operator==(const Block& block) const {
		//Color should not be necessary
		return block.pos.x == pos.x && block.pos.y == pos.y;
	}
private:
	Texture2D texture{ texture = ResourceManager::LoadTexture("block", "./Textures/block.png", false) };
	glm::vec3 color{ glm::vec3(1.0f) };
	Position pos{ 0,0 };
};

