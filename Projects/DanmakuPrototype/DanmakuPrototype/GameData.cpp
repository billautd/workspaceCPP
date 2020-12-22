#include "GameData.h"

GLuint GameData::score{ 0 };
GLuint GameData::highScore{ 0 };

void GameData::IncrementScore(GLuint value) {
	score += value;
	bool newHighScore{ false };
	if (score > highScore) {
		highScore = score;
		newHighScore = true;
	}
	for (auto& entity : EntityManager::GetEntities()) {
		if (entity->GetEntityType() == EntityTypeEnum::LABEL && entity->GetName() == "Score")
			entity->GetComponent<TextComponent>()->SetText(std::to_string(score));
		else if (entity->GetEntityType() == EntityTypeEnum::LABEL && entity->GetName() == "HighScore" && newHighScore)
			entity->GetComponent<TextComponent>()->SetText(std::to_string(highScore));
	}
}