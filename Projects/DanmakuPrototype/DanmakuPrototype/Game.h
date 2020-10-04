#pragma once
#include "GameStateEnum.h"
#include "Constants.h"
#include "EntityManager.h"
#include "SDL.h"

class Game
{
public:
	Game() = default;
	~Game() = default;

	//Init game state (load shaders, textures, levels)
	int Init();
	void LoadShaders();
	void LoadAssets();
	void LoadEntities();
	//Game loop
	void ProcessInput(SDL_Event& e, GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void Quit();

	GameStateEnum GetState() { return state; }
	SDL_Window* GetMainWindow() { return mainWindow; }
private:
	//SDL, OpenGl, Glad, ...
	int BackEndInit();

	//Current game state
	GameStateEnum state{ GameStateEnum::GAME_INACTIVE };

	//Screen
	GLuint width{ SCREEN_WIDTH };
	GLuint height{ SCREEN_HEIGHT };
	SDL_Window* mainWindow{ nullptr };

	//Input
};

