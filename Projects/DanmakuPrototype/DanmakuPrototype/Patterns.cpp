#include "Patterns.h"

GLfloat moveToCenterThenShootDownDefaultDelay{ 0.5f };
GLfloat moveToCenterThenShootDownDelay{ moveToCenterThenShootDownDefaultDelay };
bool moveToCenterThenShootDownStartedTranslation{ false };
void Patterns::MoveToCenterThenShootDown(FirePatternComponent* comp, GLfloat dt) {
	Enemy* enemy{ dynamic_cast<Enemy*>(comp->GetOwner()) };
	if (!moveToCenterThenShootDownStartedTranslation) {
		enemy->Translate(GAME_POSITION + GAME_SIZE / 2.0f, 1.5f);
		moveToCenterThenShootDownStartedTranslation = true;
	}

	if (enemy->IsTranslating())
		return;

	if (moveToCenterThenShootDownDelay <= 0) {
		EntityManager::AddEntity(new Projectile(
			enemy->GetComponent<TransformComponent>()->GetPosition() + ENEMY_SIZE / 2.0f,
			glm::vec2{ 0, 100.0f },
			PROJECTILE_SIZE,
			0.0f,
			"enemyProjectile",
			glm::vec3(1.0f),
			1.0f,
			false
		));
		moveToCenterThenShootDownDelay = moveToCenterThenShootDownDefaultDelay;
	}
	else
		moveToCenterThenShootDownDelay -= dt;
}

GLfloat moveToCenterThenSpiralDefaultDelay{ 0.05f };
GLfloat moveToCenterThenSpiralDelay{ moveToCenterThenShootDownDefaultDelay };
GLdouble moveToCenterThenSpiralTimer{ 0 };
bool moveToCenterThenSpiralStartedTranslation{ false };
void Patterns::MoveToCenterThenSpiral(FirePatternComponent* comp, GLfloat dt) {
	Enemy* enemy{ dynamic_cast<Enemy*>(comp->GetOwner()) };
	if (!moveToCenterThenSpiralStartedTranslation) {
		enemy->Translate(GAME_POSITION + GAME_SIZE / 2.0f, 1.5f);
		moveToCenterThenSpiralStartedTranslation = true;
	}

	if (enemy->IsTranslating())
		return;

	if (moveToCenterThenSpiralDelay <= 0) {
		for (GLuint i = 0; i < 20; i++) {
			GLdouble angle{ sin(2 * moveToCenterThenSpiralTimer) + 2 * M_PI * i / 20 };
			EntityManager::AddEntity(new Projectile(
				enemy->GetComponent<TransformComponent>()->GetPosition() + ENEMY_SIZE / 2.0f,
				glm::vec2{ 80.0f * cos(angle), 80.0f * sin(angle) },
				PROJECTILE_SIZE,
				0.0f,
				"enemyProjectile",
				glm::vec3(1.0f),
				1.0f,
				false
			));
		}
		moveToCenterThenSpiralDelay = moveToCenterThenSpiralDefaultDelay;
	}
	else
		moveToCenterThenSpiralDelay -= dt;

	moveToCenterThenSpiralTimer += dt;
}