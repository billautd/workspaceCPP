#pragma once
#include "SpriteRenderer.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "GameObject.h"

class GameLevel {
public:
	//C/D
	GameLevel() = default;

	//Load from file
	void Load(const char* file, GLuint levelWidth, GLuint levelHeight);
	//Render
	void Draw(SpriteRenderer& renderer);
	//Check if level is completed <=> non-solid tiles destroyed
	bool IsCompleted();

	//Utility
	std::vector<GameObject>& GetBricks() { return bricks; }

private:
	std::vector<GameObject> bricks{};
	void Init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

