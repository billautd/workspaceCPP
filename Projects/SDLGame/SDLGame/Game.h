#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "sol.hpp"
#include "Map.h"
#include "Entity.h"


class AssetManager;

class Game {
private:
	bool isRunning{false};
	SDL_Window* window{ nullptr };
	unsigned int ticksLastFrame{0};

public:
	Game();
	~Game() = default;

	static SDL_Renderer* renderer;
	static AssetManager* assetManager;
	static SDL_Event event;
	static SDL_Rect camera;
	static Map* map;
	static Entity* player;

	bool IsRunning() const { return this->isRunning; }
	void Initialize(int width, int height);
	void LoadLevel(unsigned int levelNumber);
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
	void HandleCameraMovement();
	void CheckCollisions();
	void ProcessGameOver();
	void ProcessNextLevel(unsigned int levelNumber);
};