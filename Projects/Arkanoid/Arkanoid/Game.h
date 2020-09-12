#pragma once
#include "GameStateEnum.h"
#include "glad/glad.h"
#include "Constants.h"
#include "PowerUp.h"
#include "BallObject.h"
#include "SDL.h"
#include "SDL_main.h"
#include "MusicManager.h"
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
	Game(GLuint width, GLuint height);
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

	GameStateEnum state{ GameStateEnum::GAME_INACTIVE };

	int keysNbr{ 1024 };
	const Uint8* keys{ new Uint8[keysNbr] };

	GLuint width{ SCREEN_WIDTH };
	GLuint height{ SCREEN_HEIGHT };
	SDL_Window* window{ nullptr };
	GameObject* player{ nullptr };
	BallObject* ball{ nullptr };
	SpriteRenderer* renderer{ nullptr };
	ParticleGenerator* particleGenerator{ nullptr };
	PostProcessor* postProcessor{ nullptr };
	MusicManager* musicManager{ nullptr };


	std::vector<GameLevel> levels{};
	GLuint level{ 3 };

	std::vector<PowerUp> powerUps{};
};

