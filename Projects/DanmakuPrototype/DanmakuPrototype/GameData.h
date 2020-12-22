#pragma once
#include "glad/glad.h"
#include "EntityManager.h"
#include "TextComponent.h"

class GameData {
public:
	static void IncrementScore(GLuint value);
	static GLuint GetScore() { return score; };
	static GLuint GetHighScore() { return highScore; }
	static const GLuint ENEMY_HIT_SCORE{ 100 };
	static const GLuint ENEMY_KILL_SCORE{ 10000 };
private:
	static GLuint score;
	static GLuint highScore;
};

