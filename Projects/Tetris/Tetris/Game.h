#pragma once
#include "GameStateEnum.h"
#include "SDL.h"
#include "SpriteRenderer.h"
#include "glad/glad.h"
#include "Constants.h"
#include "Grid.h"

class Game {
public:
	Game() = default;
	~Game();

	//Init game state (shaders, levels, textures, ...)
	int Init();

	//Process input
	void ProcessInput(SDL_Event& e, GLfloat dt);
	//Update
	void Update(GLfloat dt);
	//Render
	void Render();
	//Clearing everything
	void Quit();


	GameStateEnum GetState() { return state; }
	SDL_Window* GetMainWindow() { return mainWindow; }
private:
	//SDL, OpenGL, GLAD, ...
	int BackEndInit();

	SDL_Window* mainWindow{ nullptr };

	SpriteRenderer* spriteRenderer{ nullptr };

	Grid* grid{ nullptr };

	GLuint width{ WINDOW_WIDTH };
	GLuint height{ WINDOW_HEIGHT };

	GameStateEnum state{ GameStateEnum::GAME_INACTIVE };
	int keysNbr{ 1024 };
	const Uint8* keys{ new Uint8[keysNbr] };
	bool* keysProcessed{ new bool[keysNbr] {false} };

	GLfloat fallSpeed{ INITIAL_FALLING_SPEED };

	Piece* currentPiece{ nullptr };
};

