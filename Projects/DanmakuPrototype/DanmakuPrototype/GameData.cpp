#include "GameData.h"

GLuint GameData::score{ 0 };
GLuint GameData::highScore{ 0 };
GLuint GameData::lives{ 3 };


void GameData::IncrementScore(GLuint value) {
	score += value;
	bool newHighScore{ false };
	if (score > highScore) {
		highScore = score;
		newHighScore = true;
	}

	LabelUtils::SetText("Score", std::to_string(score));
	if (newHighScore)
		LabelUtils::SetText("HighScore", std::to_string(highScore));
}