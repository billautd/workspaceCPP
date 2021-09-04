#pragma once
#include "GameStateEnum.h"
#include "Constants.h"
#include "glfw3.h"

class Game
{
public:
	const GameStateEnum state{};
	bool keys[1024];
	const GLuint width{ SCREEN_WIDTH };
	const GLuint height{ SCREEN_HEIGHT };
	GLFWwindow* window{ nullptr };

	const GLint InitGL();
	void Init();
	void ProcessInput(const GLfloat dt) const;
	void Update(const GLfloat dt) const;
	void Render() const;
	void Clear() const;
};

