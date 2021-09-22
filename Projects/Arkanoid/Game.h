#pragma once
#include "GameState.h"
#include "Constants.h"
#include "glfw3.h"
#include "SpriteRenderer.h"
#include "Direction.h"
#include "GameLevel.h"
#include "Player.h"
#include "TextRenderer.h"
#include "Ball.h"
#include "PostProcessor.h"
#include "PowerUp.h"
#include <irrKlang/irrKlang.h>
#include "ParticleRenderer.h"

typedef std::tuple<bool, Direction, glm::vec2> Collision;

class Game
{
public:
	GameState state{ GAME_MENU };
	bool keys[1024]{};
	bool processedKeys[1024]{};
	GLuint width{ SCREEN_WIDTH };
	GLuint height{ SCREEN_HEIGHT };
	GLFWwindow* window{ nullptr };
	std::vector<GameLevel> levels{};
	GLuint currentLevel{ 0 };
	std::vector<PowerUp> powerUps{};
	GLuint lives{ INITIAL_LIVES };

	Game();
	~Game();

	const int InitGL();
	void Init();
	void ProcessInput(const GLfloat dt);
	void Update(const GLfloat dt);
	void Render();
	void DoCollisions();
	bool CheckCollision(const GameObject& obj1, const GameObject& obj2);
	Collision CheckCollision(const Ball& ball, const GameObject& obj2);
	void ResetPlayer();
	void ResetLevel();
	void SpawnPowerUps(const GameObject& block);
	void UpdatePowerUps(const GLfloat dt);
	void ActivatePowerUp(const PowerUp& powerUp);

	SpriteRenderer* spriteRenderer{ nullptr };
	ParticleRenderer* particleRenderer{ nullptr };
	PostProcessor* postProcessor{ nullptr };
	irrklang::ISoundEngine* soundEngine{ nullptr };
	TextRenderer* textRenderer{ nullptr };
	Player* player{nullptr};
	Ball* ball{ nullptr };

private:
	bool ShouldSpawn(const GLuint chance);
	bool IsOtherPowerUpActive(const std::string type);
};

