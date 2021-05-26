#pragma once
#include <iostream>

#include "SDL.h"
#include "EntityManager.h"
#include "AssetManager.h"
#include "Map.h"


typedef std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> windowPtr;
typedef std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> rendererPtr;

class Game
{
private:
	bool isRunning{ false };
	windowPtr window{ nullptr, SDL_DestroyWindow };
	unsigned int ticksLastFrame{ 0 };

	void HandleCameraMovement() const;
	void CheckCollisions();
	void ProcessGameOver();
	void ProcessNextLevel(const unsigned int levelNumber);
public:
	bool IsRunning() const { return isRunning; }
	void LoadLevel(const unsigned short levelNumber) const;
	void Init();
	void ProcessInput();
	void Update();
	void Render() const;
	void Destroy() const;

	static rendererPtr renderer;
	static EntityManager entityManager;
	static AssetManager assetManager;
	static SDL_Event event;
	static SDL_Rect camera;
	static Map* map;
};

