#pragma once
#include "GameState.h"
#include "Constants.h"
#include "glfw3.h"
#include "SpriteRenderer.h"
#include "GameLevel.h"
#include "Player.h"

class Game
{
public:
	GameState state{ GAME_ACTIVE };
	bool keys[1024]{};
	GLuint width{ SCREEN_WIDTH };
	GLuint height{ SCREEN_HEIGHT };
	GLFWwindow* window{ nullptr };
	std::vector<GameLevel> levels{};
	GLuint currentLevel{0};

	Game();
	~Game();

	const int InitGL();
	void Init();
	void ProcessInput(const GLfloat dt);
	void Update(const GLfloat dt);
	void Render();

	SpriteRenderer* spriteRenderer{ nullptr };
	Player* player{nullptr};
};

