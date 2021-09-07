#pragma once
#include "GameStateEnum.h"
#include "Constants.h"
#include "glfw3.h"
#include "SpriteRenderer.h"

class Game
{
public:
	const GameStateEnum state{GAME_ACTIVE};
	bool keys[1024]{};
	const GLuint width{ SCREEN_WIDTH };
	const GLuint height{ SCREEN_HEIGHT };
	GLFWwindow* window{ nullptr };

	void Init();
	void ProcessInput(const GLfloat dt);
	void Update(const GLfloat dt);
	void Render();
	void Clear();

private:
	const GLint InitGL();
	void LoadShaders();
	void LoadAssets();

	SpriteRenderer* spriteRenderer{ nullptr };
};

