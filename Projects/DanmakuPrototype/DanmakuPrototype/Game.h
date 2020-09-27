#pragma once
#include "GameStateEnum.h"
#include "Constants.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "SDL.h"
class Game
{
public:
	// C/D
	Game() = default;
	~Game() = default;

	//Init game state (load shaders, textures, levels)
	int Init();
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

	//Input
	int keysNbr{ 1024 };
	const Uint8* keys{ new Uint8[keysNbr] };
	bool* keysProcessed{ new bool[keysNbr] {false} };

	//Screen
	GLuint width{ SCREEN_WIDTH };
	GLuint height{ SCREEN_HEIGHT };
	SDL_Window* mainWindow{ nullptr };

	//Renderers
	SpriteRenderer* spriteRenderer{ nullptr };
	TextRenderer* textRenderer{ nullptr };
};

