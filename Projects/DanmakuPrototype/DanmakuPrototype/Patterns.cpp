#include "Patterns.h"

GLfloat moveToCenterThenShootDownDefaultDelay{ 0.005f };
GLfloat moveToCenterThenShootDownDelay{ moveToCenterThenShootDownDefaultDelay };
GLdouble moveToCenterThenShootDownTimer{ 0 };
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
		for (GLuint i = 0; i < 20; i++) {
			GLdouble angle{ sin(2 * moveToCenterThenShootDownTimer) + 2 * M_PI * i / 20 };
			EntityManager::AddEntity(new Projectile(
				comp->GetOwner()->GetComponent<TransformComponent>()->GetPosition() + ENEMY_SIZE / 2.0f,
				glm::vec2{ 100.0f * cos(angle), 100.0f * sin(angle) },
				PROJECTILE_SIZE,
				0.0f,
				ResourceManager::GetTexture("enemyProjectile"),
				glm::vec3(1.0f),
				1.0f,
				false
			));
		}
		moveToCenterThenShootDownDelay = moveToCenterThenShootDownDefaultDelay;
	}
	else
		moveToCenterThenShootDownDelay -= dt;

	moveToCenterThenShootDownTimer += dt;
}