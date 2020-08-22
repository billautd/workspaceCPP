#pragma once
#include "Camera.h"
#include "Window.h"
#include "Shader.h"
#include "Model.h"
#include <map>
#include "Utils.h"
#include <vector>

class Game {
public:
	Game() = default;
	~Game();

	static Window* mainWindow;

	bool IsRunning() { return isRunning; }

	void Init();
	void ProcessKeyboardInput(SDL_Event& e);
	void ProcessMouseInput(SDL_Event& e);
	void ProcessMouseScrollInput(SDL_Event& e);

	void MVP();

	Shader* GetShader() { return shader; }

private:
	bool isRunning{ false };
	GLuint ticksLastFrame{ 0 };

	Camera* camera{ nullptr };
	Shader* shader{ nullptr };
};

