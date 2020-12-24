#pragma once
#include "glad/glad.h"
#include "EntityManager.h"
#include "Label.h"
#include "TextComponent.h"
#include "LabelUtils.h"

class GameData {
public:
	static void IncrementScore(GLuint value);
	static GLuint GetScore() { return score; };
	static GLuint GetHighScore() { return highScore; }
	static GLuint GetLives() { return lives; }
	static void DecrementLives() { lives--; }
	static const GLuint ENEMY_HIT_SCORE{ 100 };
	static const GLuint ENEMY_KILL_SCORE{ 10000 };
private:
	static GLuint score;
	static GLuint highScore;
	static GLuint lives;
};

