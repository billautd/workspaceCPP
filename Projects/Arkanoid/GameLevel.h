#pragma once
#include "GameObject.h"
#include <vector>

class GameLevel
{
public:
	std::vector<GameObject> bricks{};

	GameLevel() {};
	~GameLevel() {};

	void Load(const char* file, const GLuint levelWidth, const GLuint levelHeight);
	void Draw(SpriteRenderer& renderer);
	bool IsCompleted();

private:
	void Init(const std::vector<std::vector<GLuint>> tileData, const GLuint levelWidth, const GLuint levelHeight);
};

