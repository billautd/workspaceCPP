#pragma once
#include "GameStateEnum.h"
#include "glad/glad.h"
#include "Constants.h"
#include "PowerUp.h"
#include "BallObject.h"
#include "SDL.h"
#include "SDL_main.h"
#include "TextRenderer.h"
#include "MusicPlayer.h"
#include <iostream>
#include <vector>
#include "GameLevel.h"
#include "SDL_mixer.h"
#include "ParticleGenerator.h"
#include "PostProcessor.h"


class Game {
public:
	// C/D
	Game() = default;
	~Game();

	//Init game state (load shaders, textures, levels)
	int Init();
	//Game loop
	void ProcessInput(SDL_Event& e, GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void DoCollisions();

	void ResetBallPlayer();

	void SpawnPowerUp(GameObject& block);
	void UpdatePowerUps(GLfloat dt);

	//Utility
	GameStateEnum GetState() { return this->state; }
	SDL_Window* GetWindow() { return this->window; }


private:
	//SDL, OpenGl, Glad, ...
	int BackEndInit();

	void BallTileCollision(GameObject& obj);
	void BallPlayerCollision();
	void PowerUpPlayerCollision(PowerUp& powerUp);

	bool ShouldSpawn(GLuint chance);
	void ActivatePowerUp(PowerUp& powerUp);
	bool IsOtherPowerUpActive(std::string type);
	void ResetPowerUps();

	void Quit();

	GameStateEnum state{ GameStateEnum::GAME_INACTIVE };

	int keysNbr{ 1024 };
	const Uint8* keys{ new Uint8[keysNbr] };
	bool* keysProcessed{ new bool[keysNbr] {false} };

	GLuint width{ SCREEN_WIDTH };
	GLuint height{ SCREEN_HEIGHT };
	SDL_Window* window{ nullptr };
	GameObject* player{ nullptr };
	BallObject* ball{ nullptr };
	SpriteRenderer* renderer{ nullptr };
	ParticleGenerator* particleGenerator{ nullptr };
	PostProcessor* postProcessor{ nullptr };
	MusicPlayer* musicPlayer{ nullptr };
	TextRenderer* textRenderer{ nullptr };


	std::vector<GameLevel> levels{};
	GLuint level{ 0 };

	std::vector<PowerUp> powerUps{};

	GLuint lives{ 3 };
};

