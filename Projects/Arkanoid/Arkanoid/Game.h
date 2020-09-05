#pragma once
#include "GameStateEnum.h"
#include "glad/glad.h"
#include "Constants.h"
#include "SDL.h"
#include "SDL_main.h"
#include <iostream>


class Game {
public:
	// C/D
	Game() = default;
	Game(GLuint width, GLuint height);
	~Game() = default;

	//Init game state (load shaders, textures, levels)
	int Init();
	//Game loop
	void ProcessInput(SDL_Event& e, GLfloat dt);
	void Update(GLfloat dt);
	void Render();

	//Utilitie
	GameStateEnum GetState() { return this->state; }
	SDL_Window* GetWindow() { return this->window; }

private:
	GameStateEnum state{ GameStateEnum::GAME_INACTIVE };
	int keysNbr{ 1024 };
	const Uint8* keys{ new Uint8[keysNbr] };
	GLuint width{ SCREEN_WIDTH };
	GLuint height{ SCREEN_HEIGHT };
	SDL_Window* window{ nullptr };

};

